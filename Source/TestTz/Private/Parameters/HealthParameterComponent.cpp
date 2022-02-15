// Fill out your copyright notice in the Description page of Project Settings.


#include "Parameters/HealthParameterComponent.h"

#include "SatietyParameterComponent.h"
#include "TimerManager.h"


void UHealthParameterComponent::BeginPlay()
{
     Super::BeginPlay();

     ensure(GetWorld());

     Health = MaxParameter;
     Parameter = Health;     

     auto SatietyComponent = GetOwner()->FindComponentByClass<USatietyParameterComponent>();
     if(SatietyComponent)
     {
          SatietyComponent->OnSatietyChanged.AddDynamic(this, &UHealthParameterComponent::SatietyChanged);
     }
}

void UHealthParameterComponent::SatietyChanged(float Satiety)
{
     if(Satiety == 0.0)
     {
          GetWorld()->GetTimerManager().SetTimer(ParameterTimer, this,
               &UHealthParameterComponent::HealthDecrease, ParameterDecreaseTimerRate, true); 
     }
}

void UHealthParameterComponent::HealthDecrease()
{
     if (Health >= ParameterDecreaseAmount)
     {
          Health -= ParameterDecreaseAmount;
          OnHealthChanged.Broadcast(Health);
     }
     else
     {
          GetWorld()->GetTimerManager().PauseTimer(ParameterTimer);
     }
}


