// Fill out your copyright notice in the Description page of Project Settings.


#include "Parameters/SatietyParameterComponent.h"
#include "TimerManager.h"

void USatietyParameterComponent::BeginPlay()
{
     Super::BeginPlay();

     ensure(GetWorld());

     Satiety = MaxParameter;
     Parameter = Satiety;


     GetWorld()->GetTimerManager().SetTimer(ParameterTimer, this, &USatietyParameterComponent::SatietyDecrease,
          USatietyParameterComponent::ParameterDecreaseTimerRate, true);


}

void USatietyParameterComponent::SatietyDecrease()
{
     if(Satiety >= ParameterDecreaseAmount)
     {
          Satiety -= ParameterDecreaseAmount;
          OnSatietyChanged.Broadcast(Satiety);
     }

     else
     {
          GetWorld()->GetTimerManager().PauseTimer(ParameterTimer);
     }
}
