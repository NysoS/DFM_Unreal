// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndingZone.generated.h"

UCLASS()
class DFM1_API AEndingZone : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Collision")
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* MeshComponent;

	int32 TotalCoinsToUnlock = 0;
	
public:	
	// Sets default values for this actor's properties
	AEndingZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap (AActor * OtherActor) override;
};
