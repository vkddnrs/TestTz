// Fill out your copyright notice in the Description page of Project Settings.


#include "Parameters/BaseParameterComponent.h"

UBaseParameterComponent::UBaseParameterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBaseParameterComponent::BeginPlay()
{
	Super::BeginPlay();

	Parameter = MaxParameter;
}


void UBaseParameterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

