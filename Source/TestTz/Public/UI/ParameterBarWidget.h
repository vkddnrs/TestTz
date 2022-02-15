// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParameterBarWidget.generated.h"

class UProgressBar;

UCLASS()
class TESTTZ_API UParameterBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

     void SetParameterPercent(float Percent);
     void SetParameterColor(FLinearColor Color);
     void SetParameterVisibility();
     
     UFUNCTION(BlueprintCallable)
	void SetSeeingPlayer(class AController* _SeeingPlayer) { SeeingPlayer = _SeeingPlayer; }


protected:     

     UPROPERTY(meta = (BindWidget))
	UProgressBar* ParameterProgressBar;

     bool bOnlyOwnerSee = true;

     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Visibility)
	class AController* SeeingPlayer = nullptr;



     };


