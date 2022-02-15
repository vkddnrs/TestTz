// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ParameterBarWidget.h"
#include "Components/ProgressBar.h"

void UParameterBarWidget::SetParameterPercent(float Percent)
{
     if(!ParameterProgressBar) return;
     ParameterProgressBar->SetPercent(Percent);

  
}

void UParameterBarWidget::SetParameterColor(FLinearColor Color)
{
     if (!ParameterProgressBar) return;
     ParameterProgressBar->SetFillColorAndOpacity(Color);
     ParameterProgressBar->SetVisibility(ESlateVisibility::Visible);

}

void UParameterBarWidget::SetParameterVisibility()
{
     if (!SeeingPlayer)
     {
          ParameterProgressBar->SetVisibility(ESlateVisibility::Hidden);

          //UE_LOG(LogTemp, Warning, TEXT("Widget = Hidden, bOnlyOwnerSee = %i, ControllerOwning = %s"),
          //     int(bOnlyOwnerSee), *(GetOwningPlayer()->GetName()))

          return;
     }

     if (bOnlyOwnerSee)
     {
          if (GetOwningPlayer() == SeeingPlayer)
          {
               ParameterProgressBar->SetVisibility(ESlateVisibility::Visible);
               //UE_LOG(LogTemp, Warning, TEXT("Widget = Visible, bOnlyOwnerSee = %i, ControllerOwning = %s, ControllerSeeingPlayer = %s"),
               //     int(bOnlyOwnerSee), *(GetOwningPlayer()->GetName()), *(SeeingPlayer->GetName()))
          }
          else
          {
               ParameterProgressBar->SetVisibility(ESlateVisibility::Hidden);
               //UE_LOG(LogTemp, Warning, TEXT("Widget = Hidden, bOnlyOwnerSee = %i, ControllerOwning = %s, ControllerSeeingPlayer = %s"),
               //     int(bOnlyOwnerSee), *(GetOwningPlayer()->GetName()), *(SeeingPlayer->GetName()))

          }
     }
     else
     {
          ParameterProgressBar->SetVisibility(ESlateVisibility::Visible);
          //UE_LOG(LogTemp, Warning, TEXT("Widget = Visible, bOnlyOwnerSee = %i, ControllerOwning = %s, ControllerSeeingPlayer = %s"),
          //     int(bOnlyOwnerSee), *(GetOwningPlayer()->GetName()), *(SeeingPlayer->GetName()))
     }
}
