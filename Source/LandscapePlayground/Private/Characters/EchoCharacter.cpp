#include "Characters/EchoCharacter.h"

AEchoCharacter::AEchoCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEchoCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEchoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEchoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

