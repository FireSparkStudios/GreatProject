// Copyright (c) 2022 [Gorkem CEYLAN]


#include "UVitalityComponent.h"

#include "UVitalityWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GreatProject/Public/ACharacterClassBase.h"


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

	// Set fullness properties
	DefaultFullness = 100.f;
	HungerRate = 60;
	HungerAmount = 1;
}


// Called when the game starts
void UUVitalityComponent::BeginPlay()
{
	Super::BeginPlay();

	MyOwner = Cast<AACharacterClassBase>(GetOwner());
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UUVitalityComponent::HandleTakeAnyDamage);
	}

	Health = DefaultHealth;

	Stamina = DefaultStamina;
	RunningLimit = DefaultStamina * RunningLimitPercentage;

	Fullness = DefaultFullness;

	GetWorld()->GetTimerManager().SetTimer(FullnessTimerHandle, this, &UUVitalityComponent::FullnessDecreaseByTime, HungerRate, true, HungerRate);

}


// Called every frame
void UUVitalityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUVitalityComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == .0f)
	{
		return;
	}

	if (Damage < 0.f)
	{
		// TODO Call healing funccc.
	}

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	UE_LOG(LogTemp, Log, TEXT("Health changed to : %s"), *FString::SanitizeFloat(Health));

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UUVitalityComponent::AddStamina(float Amount)
{
	Stamina = FMath::Clamp(Stamina + Amount, .0f, DefaultStamina);
	MyOwner->VitalityHUD->SetStamina(Stamina, DefaultStamina);
}

void UUVitalityComponent::FullnessDecreaseByTime()
{
	Fullness = FMath::Clamp(Fullness - HungerAmount, 0, DefaultHealth);

	UE_LOG(LogTemp, Error, TEXT("Fullness changed to : %s"), *FString::SanitizeFloat(Fullness));
}

