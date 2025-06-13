#include "Characters/EchoCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GroomComponent.h"

AEchoCharacter::AEchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	ZoomSpeed = 10;
	ZoomMaxDistance = 500;
	ZoomMinDistance = 100;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 380.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 350.f;
	SpringArm->AddLocalRotation(FRotator(0, -20, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");
	
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
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
		EnhancedInputComponent->BindAction(ZoomInputAction, ETriggerEvent::Triggered, this, &AEchoCharacter::Zoom);
	}
}

void AEchoCharacter::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVec = InputActionValue.Get<FVector2D>();
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0, ControlRotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, MovementVec.Y);
	AddMovementInput(RightDirection, MovementVec.X);
}

void AEchoCharacter::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookVec = InputActionValue.Get<FVector2D>();

	if (GetController())
	{
		AddControllerPitchInput(LookVec.Y);
		AddControllerYawInput(LookVec.X);
	}
}

void AEchoCharacter::Zoom(const FInputActionValue& InputActionValue)
{
	const float ZoomValue = InputActionValue.Get<float>();

	if (SpringArm)
	{
		float ZoomDistance = SpringArm->TargetArmLength + ZoomValue * ZoomSpeed;

		if (ZoomDistance >= ZoomMinDistance && ZoomDistance <= ZoomMaxDistance)
		{
			SpringArm->TargetArmLength = ZoomDistance;
		}
	}
}




