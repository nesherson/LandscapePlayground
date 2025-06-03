#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class LANDSCAPEPLAYGROUND_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Functions")
	float TimeConstant = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Functions")
	float Amplitude = 0.25f;

	UFUNCTION(BlueprintPure)
	float TransformedSin() const;

	UFUNCTION(BlueprintPure)
	float TransformedCos() const;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;
};
