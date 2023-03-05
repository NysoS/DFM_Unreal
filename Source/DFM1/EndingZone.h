// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndingZone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMulticastDelegateEndGame);

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

	UPROPERTY(BlueprintAssignable, Category = "Custom Delegate")
	FMulticastDelegateEndGame DelegateEndGame;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called when actor overlap other one
	virtual void NotifyActorBeginOverlap (AActor * OtherActor) override;
};
