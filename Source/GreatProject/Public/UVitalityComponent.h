// Copyright (c) 2022 [Gorkem CEYLAN]

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UVitalityComponent.generated.h"

class AACharacterClassBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UUVitalityComponent*, HealthComp, float, Health,
											float, HealthDelta, const class UDamageType*, DamageType,
											class AController*, InstigatedBy, AActor*, DamageCauser);

class UUVitalityWidget;
class UUVitalityComponent;

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

	AACharacterClassBase* MyOwner;

	// Widget class to spawn for the heads up display.
	UPROPERTY(Category = "Component HUD", EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUVitalityWidget> VitalityHUDClass;

	UPROPERTY()
	UUVitalityWidget* VitalityHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
	float DefaultHealth;

	// Max fullness
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
	float DefaultFullness;

	// characters max stamina
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
	float DefaultStamina;

	float Health;

	// Current fullness
	float Fullness;

	// characters current stamina
	float Stamina;

	// Limit to able to run againg
	float RunningLimit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
	float RunningLimitPercentage;

	// How rare fullness decrease (seconds)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
	float HungerRate;

	// How much fullness decrease by HungerRate
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Vitality")
	float HungerAmount;

	FTimerHandle FullnessTimerHandle;

	/*
	 * Functions
	 */

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void FullnessDecreaseByTime();

	// Call this when you want to regenerate stamina
	void AddStamina(float Amount);

public:

	void UpdateHealthBarPercentage();

	void UpdateStaminaBarPercentage();

	void UpdateFullnessBarPercentage();

	void UpdateVitalityBarsPercentage();

	/*
	 * Signatures
	 */

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChangedSignature OnHealthChanged;

};
