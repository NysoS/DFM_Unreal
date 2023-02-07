// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectible.generated.h"

UCLASS()
class DFM1_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Collision")
	class USphereComponent* SphereCollider;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	class URotatingMovementComponent* RotatingMovementComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
