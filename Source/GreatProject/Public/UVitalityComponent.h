// Copyright (c) 2022 [Gorkem CEYLAN]

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UVitalityComponent.generated.h"


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

	// characters max stamina
	float DefaultStamina;

	// characters current stamina
	float Stamina;

	void RegenerateStamina(float RegenerationAmount);

	void DrainStamina(float DrainAmount); 
};
