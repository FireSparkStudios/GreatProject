// Copyright (c) 2022 [Gorkem CEYLAN]


#include "UVitalityComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UUVitalityComponent::UUVitalityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set health properties
	DefaultHealth = 100.f;

	// Set stamina properties
	DefaultStamina = 10.f;
	RunningLimitPercentage = .2f;

}


// Called when the game starts
void UUVitalityComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UUVitalityComponent::HandleTakeAnyDamage);
	}

	Stamina = DefaultStamina;
	RunningLimit = DefaultStamina * RunningLimitPercentage;
	Health = DefaultHealth;
}


// Called every frame
void UUVitalityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUVitalityComponent::RegenerateStamina(float RegenerationAmount)
{
	Stamina = FMath::Min(DefaultStamina, Stamina + RegenerationAmount);
}

void UUVitalityComponent::DrainStamina(float DrainAmount)
{
	Stamina = FMath::Clamp(Stamina - DrainAmount, .0f, DefaultStamina);
}


void UUVitalityComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < 0.f)
	{
		// TODO Call healing funccc.
	}

	if (Damage == .0f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	UE_LOG(LogTemp, Log, TEXT("Health changed to : %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

