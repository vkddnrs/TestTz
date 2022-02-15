// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parameters/BaseParameterComponent.h"
#include "HealthParameterComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, CurrHealth);

UCLASS()
class TESTTZ_API UHealthParameterComponent : public UBaseParameterComponent
{
	GENERATED_BODY()

public:
     UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

     virtual float GetParameter() const override { return Health; }

     UFUNCTION(BlueprintCallable, Category = WidgetUpdate)
	void WidgetUpdate() override { OnHealthChanged.Broadcast(-1); }

protected:
     virtual void BeginPlay() override;

     UFUNCTION()
	void SatietyChanged(float Satiety);


private:
     float Health = 0.0f;

     void HealthDecrease();
	
};


