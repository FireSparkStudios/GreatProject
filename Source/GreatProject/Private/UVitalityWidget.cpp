// Copyright (c) 2022 [Gorkem CEYLAN]


#include "UVitalityWidget.h"
#include "Components/ProgressBar.h"

void UUVitalityWidget::SetHealth(float CurrentHealth, float MaxHealth) 
{
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}


void UUVitalityWidget::SetStamina(float CurrentHealth, float MaxHealth)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(CurrentHealth / MaxHealth);
	}
}


void UUVitalityWidget::SetFullness(float CurrentFullness, float MaxFullness) 
{
	if (FullnessBar)
	{
		FullnessBar->SetPercent(CurrentFullness / MaxFullness);
	}
}

