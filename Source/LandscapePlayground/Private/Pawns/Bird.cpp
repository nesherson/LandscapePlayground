#include "Pawns/Bird.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(Capsule);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 350.f;
	SpringArm->AddLocalRotation(FRotator(0, -20, 0));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);
}

void ABird::BeginPlay()
{
	Super::BeginPlay();
}

void ABird::MoveForward(float Value)
{
	if (Controller && Value != 0.f)
	{
		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, Value);
	}
}

void ABird::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ABird::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABird::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABird::Turn);
}

