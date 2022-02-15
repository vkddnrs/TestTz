// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestTzCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Parameters/HealthParameterComponent.h"
#include "Parameters/SatietyParameterComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/ParameterBarWidget.h"


//////////////////////////////////////////////////////////////////////////
// ATestTzCharacter

ATestTzCharacter::ATestTzCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	HealthComponent = CreateDefaultSubobject<UHealthParameterComponent>("HealthComponent");
	SatietyComponent = CreateDefaultSubobject<USatietyParameterComponent>("SatietyComponent");

	//HealthTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRenderComponent");
	//SatietyTextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("SatietyTextRenderComponent");

	//HealthTextRenderComponent->SetupAttachment(GetRootComponent());
	//SatietyTextRenderComponent->SetupAttachment(GetRootComponent());

	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
	SatietyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("SatietyWidgetComponent");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	SatietyWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	SatietyWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);


}

//////////////////////////////////////////////////////////////////////////
// Input

void ATestTzCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATestTzCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestTzCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATestTzCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATestTzCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATestTzCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATestTzCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATestTzCharacter::OnResetVR);
}

void ATestTzCharacter::SetSatiety(float Satiety)
{
     //SatietyTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), SatietyComponent->GetParameter())));

     if(Satiety == -1)
     {
          SatietyBarWidget->SetParameterVisibility();
          return;
     }
   
     SatietyBarWidget->SetParameterPercent(SatietyComponent->GetParameterPercent(Satiety)); // SatietyComponent->GetParameterPercent(Satiety));
     
}

void ATestTzCharacter::SetHealth(float Health)
{
     //HealthTextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), HealthComponent->GetParameter())));

     if(Health == -1)
     {
          HealthBarWidget->SetParameterVisibility();
          return;
     }

     HealthBarWidget->SetParameterPercent(HealthComponent->GetParameterPercent(Health));
     

}


void ATestTzCharacter::Tick(float DeltaSeconds)
{
     Super::Tick(DeltaSeconds);





}

void ATestTzCharacter::BeginPlay()
{
     Super::BeginPlay();

     ensure(HealthComponent);
     //ensure(HealthTextRenderComponent);
     ensure(SatietyComponent);
     //ensure(SatietyTextRenderComponent);

     ensure(HealthWidgetComponent);
     ensure(SatietyWidgetComponent);    

     HealthComponent->OnHealthChanged.AddDynamic(this, &ATestTzCharacter::SetHealth);
     SatietyComponent->OnSatietyChanged.AddDynamic(this, &ATestTzCharacter::SetSatiety);


     // TODO свести параметры в массив и обрабатывать их в цикле.
     HealthBarWidget = Cast<UParameterBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
     SatietyBarWidget = Cast<UParameterBarWidget>(SatietyWidgetComponent->GetUserWidgetObject());
     HealthBarWidget->SetParameterColor(FLinearColor::Green);
     SatietyBarWidget->SetParameterColor(FLinearColor::Yellow);
     HealthBarWidget->SetSeeingPlayer(Controller);
     SatietyBarWidget->SetSeeingPlayer(Controller);
     HealthBarWidget->SetParameterVisibility();
     SatietyBarWidget->SetParameterVisibility();


     
     SetHealth(HealthComponent->GetParameter());
     SetSatiety(SatietyComponent->GetParameter());

}

void ATestTzCharacter::OnResetVR()
{
	// If TestTz is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in TestTz.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATestTzCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ATestTzCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ATestTzCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATestTzCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATestTzCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATestTzCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
