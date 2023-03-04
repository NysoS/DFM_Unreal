// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DashComponent.generated.h"

enum class OrientationDash
{
	DASH_None,
	DASH_Left,
	DASH_Right
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DFM1_API UDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDashComponent();

	TArray<FVector*> ProjectionPositions;
	int32 StepNextProjectionPosition = 0;
	FVector ActorLocation;
	
	bool bDashing;
	bool bNextDash = true;
	
	void DashMoving();
	bool IsDashing();
	void SetOrientationDash(OrientationDash orientationDash);
	
private:
	UPROPERTY(EditAnywhere, Category = "Dash Parameter")
	float Distance = 250.f;

	UPROPERTY(EditAnywhere, Category = "Dash Parameter", meta = (ClampMin = 0.1f, ClampMax = 1.0f, UIMin = 0.1f, UIMax = 1.0f))
	float TimeToDash = 0.5f;
	float Time;

	UPROPERTY(EditAnywhere, Category = "Dash Parameter")
	float SpeedDash = 1.f;

	bool CanDash();
	
	OrientationDash eOrientationDash = OrientationDash::DASH_Left;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
