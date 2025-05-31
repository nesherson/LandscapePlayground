#include "Items/Item.h"
#include "LandscapePlayground/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	// const FVector ActorLocation = GetActorLocation();
	//
	// SetActorLocation(FVector(ActorLocation.X, ActorLocation.Y, ActorLocation.Z + 800));
	//
	// const FVector LineEnd = GetActorLocation() + GetActorForwardVector() * 100.f;
	//
	// DRAW_DEBUG_SPHERE(GetActorLocation());
	// DRAW_DEBUG_LINE(GetActorLocation(), LineEnd);
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	float deltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	AddActorWorldOffset(FVector(0, 0, deltaZ));
}

