// Copyright (c) 2022 [Gorkem CEYLAN]


#include "ACharacterClassBase.h"

#include "UVitalityComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AACharacterClassBase::AACharacterClassBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(.0f, 500.f, .0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f; // The camera follows at this distance behind the character
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a third person camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;

	VitalityComponent = CreateDefaultSubobject<UUVitalityComponent>(TEXT("Vitality Component"));

	bCanSprint = true;
	bIsSprinting = false;

	StaminaDrain = 1;
	StaminaRegen = 2;
}

// Called when the game starts or when spawned
void AACharacterClassBase::BeginPlay()
{
	Super::BeginPlay();

	Stamina = &VitalityComponent->Stamina;
	StaminaLimit = *Stamina * 0.50;
	
}

// Called every frame
void AACharacterClassBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	deneme = bIsSprinting && bCanSprint && *Stamina > VitalityComponent->Stamina * 0.2f;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Cyan, FString::Printf(TEXT("Stamina: %s"), *FString::SanitizeFloat(*Stamina)));
	}

	if (!bIsSprinting && GetCharacterMovement()->IsMovingOnGround())
	{
		VitalityComponent->RegenerateStamina(StaminaRegen * GetWorld()->DeltaTimeSeconds);
	}
}

// Called to bind functionality to input
void AACharacterClassBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AACharacterClassBase::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AACharacterClassBase::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AACharacterClassBase::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AACharacterClassBase::SprintStop);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AACharacterClassBase::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AACharacterClassBase::MoveRight);

	// "turn" handles devices that provide an absolute delta, such as a mouse.
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
}

void AACharacterClassBase::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		if (*Stamina <= 0)
		{
			SprintStop();
		}

		// TODO make function for stamina usage

		if (bIsSprinting && bCanSprint)
		{
			VitalityComponent->DrainStamina(StaminaDrain*GetWorld()->DeltaTimeSeconds);
		}

	}
}

void AACharacterClassBase::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AACharacterClassBase::SprintStart()
{
	// TODO get back to normal walk speed when stamina is over!!
	if (bCanSprint && *Stamina > StaminaLimit)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = 1200;
	}
}

void AACharacterClassBase::SprintStop()
{
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
}

void AACharacterClassBase::Jump()
{
	Super::Jump();

	if (GetCharacterMovement()->IsMovingOnGround())
	{
		VitalityComponent->DrainStamina(1);
	}
}

void AACharacterClassBase::StopJumping()
{
	Super::StopJumping();
	
}

