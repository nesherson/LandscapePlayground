#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LANDSCAPEPLAYGROUND_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void LookUp(float Value);
	void Turn(float Value);

private:

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
};