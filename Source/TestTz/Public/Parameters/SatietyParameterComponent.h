// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Parameters/BaseParameterComponent.h"
#include "SatietyParameterComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSatietyChanged, float, CurrSatiety);

UCLASS()
class TESTTZ_API USatietyParameterComponent : public UBaseParameterComponent
{
	GENERATED_BODY()

public:
     UPROPERTY(BlueprintAssignable)
	FOnSatietyChanged OnSatietyChanged;

     virtual float GetParameter() const override { return Satiety; }

     UFUNCTION(BlueprintCallable)
     void WidgetUpdate() override { OnSatietyChanged.Broadcast(-1); }

protected:
     virtual void BeginPlay() override;

private:
     float Satiety = 0.0f;

     void SatietyDecrease();
	
};
