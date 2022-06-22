// Copyright (c) 2022 [Gorkem CEYLAN]

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ACharacterClassBase.generated.h"

UCLASS()
class GREATPROJECT_API AACharacterClassBase : public ACharacter
{
	GENERATED_BODY()

	// Spring arm for third person camera.
	class USpringArmComponent* SpringArm;

	// Player's third person camera.
	class UCameraComponent* ThirdPersonCamera;

public:
	// Sets default values for this character's properties
	AACharacterClassBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	// controls what will happen when sprint start.
	void SprintStart();

	// controls what will happen when sprint stop.
	void SprintStop();

	void Jump() override;

	void StopJumping() override;

	bool deneme;

public:

	class UUVitalityComponent* VitalityComponent;

	float* Stamina;

	// How much stamina drained while running.
	float StaminaDrain;

	// How much stamina regenerate while character can regenerate.
	float StaminaRegen;

	// Control character is able to sprint.
	bool bCanSprint;

	// Is character sprinting?
	bool bIsSprinting;

	float StaminaLimit;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArmComponent() const { return SpringArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCamera; }
};
