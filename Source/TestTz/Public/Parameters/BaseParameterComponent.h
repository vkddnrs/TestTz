// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseParameterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTZ_API UBaseParameterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseParameterComponent();

protected:
	virtual void BeginPlay() override;          

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetParameter() const { return Parameter; }


protected:
     
     float Parameter = 0.0f;

     UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxParameter = 100.f;
		
};
