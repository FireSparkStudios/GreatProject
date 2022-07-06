// Copyright (c) 2022 [Gorkem CEYLAN]

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UVitalityComponent.generated.h"

class AACharacterClassBase;

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	 * Variables
	 */

	float DefaultHealth;

	float Health;

	AACharacterClassBase* MyOwner;

	// characters max stamina
	UPROPERTY(EditAnywhere, Category = "Vitality|Stamina")
	float DefaultStamina;

	// characters current stamina
	float Stamina;

	// Limit to able to run againg
	float RunningLimit;

	UPROPERTY(EditAnywhere, Category = "Vitality|Stamina")
	float RunningLimitPercentage;

	// Call this when you want to regenerate stamina
	void AddStamina(float Amount);

	// Max fullness
	float DefaultFullness;

	// Current fullness
	float Fullness;

	// How rare fullness decrease (seconds)
	float HungerRate;

	// How much fullness decrease by HungerRate
	float HungerAmount;

	FTimerHandle FullnessTimerHandle;

	/*
	 * Functions
	 */

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void FullnessDecreaseByTime();

	/*
	 * Signatures
	 */

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

};
