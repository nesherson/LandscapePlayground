#include "Characters/EchoCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AEchoCharacter::AEchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 350.f;
	SpringArm->AddLocalRotation(FRotator(0, -20, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);
}

void AEchoCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Look);
	}
}

void AEchoCharacter::Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVec = InputActionValue.Get<FVector2D>();
	FVector ForwardVec = GetActorForwardVector();
	FVector RightVec = GetActorRightVector();

	AddMovementInput(ForwardVec, MovementVec.Y);
	AddMovementInput(RightVec, MovementVec.X);
}

void AEchoCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookVec = InputActionValue.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookVec.X);
		AddControllerPitchInput(LookVec.Y);
	}
}




