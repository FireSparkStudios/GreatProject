// Copyright (c) 2022 [Gorkem CEYLAN]

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UVitalityComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UUVitalityComponent*, HealthComp, float, Health,
											float, HealthDelta, const class UDamageType*, DamageType,
											class AController*, InstigatedBy, AActor*, DamageCauser);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GREATPROJECT_API UUVitalityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUVitalityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	AActor* MyOwner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// characters max stamina
	UPROPERTY(EditDefaultsOnly, Category = "Vitality|Stamina")
	float DefaultStamina;

	// characters current stamina
	float Stamina;

	// Limit to able to run againg
	float RunningLimit;

	UPROPERTY(EditDefaultsOnly, Category = "Vitality|Stamina")
	float RunningLimitPercentage;

	void RegenerateStamina(float RegenerationAmount);

	void DrainStamina(float DrainAmount);

	float DefaultHealth;

	float Health;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

};
