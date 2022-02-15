// Fill out your copyright notice in the Description page of Project Settings.


#include "Parameters/BaseParameterComponent.h"

UBaseParameterComponent::UBaseParameterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBaseParameterComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UBaseParameterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UBaseParameterComponent::GetParameterPercent(float Param) const
{
     return Param / MaxParameter;
}

