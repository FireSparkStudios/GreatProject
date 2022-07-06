// Copyright (c) 2022 [Gorkem CEYLAN]

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UVitalityWidget.generated.h"

class UProgressBar;

UCLASS()
class GREATPROJECT_API UUVitalityWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/* Update HUD with current health. */
	void SetHealth(float CurrentHealth, float MaxHealth);

	/* Update HUD with current stamina. */
	void SetStamina(float CurrentStamina, float MaxStamina);

	/* Update HUD with current fullness. */
	void SetFullness(float CurrentFullness, float MaxFullness);

	/* Widget to use to display current Health */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HealthBar;

	/* Widget to use to display current Stamina */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* StaminaBar;

	/* Widget to use to display current Health */
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* FullnessBar;

};
