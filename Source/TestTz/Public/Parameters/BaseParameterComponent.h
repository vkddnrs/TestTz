// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseParameterComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTTZ_API UBaseParameterComponent : public UActorComponent
{
     GENERATED_BODY()

public:
     UBaseParameterComponent();

protected:
     virtual void BeginPlay() override;

public:
     virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
     virtual float GetParameterPercent(float Param) const;
     virtual float GetParameter() const { return Parameter; }

     
     virtual void WidgetUpdate() {}

protected:

     float Parameter = 0.0f;
     FTimerHandle ParameterTimer;


     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClapMin = "0.0", ClampMax = "1000.0"))
	float MaxParameter = 100.f;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ParameterDecrease", meta = (ClapMin = "0.0", ClampMax = "100.0"))
	float ParameterDecreaseTimerRate = 1.0;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ParameterDecrease")
	float ParameterDecreaseAmount = 10.0;

};
