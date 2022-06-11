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

	DefaultStamina = 10;

}


// Called when the game starts
void UUVitalityComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Stamina = DefaultStamina;
	
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


