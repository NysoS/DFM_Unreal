// Fill out your copyright notice in the Description page of Project Settings.

#include "DashComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TimelineComponent.h"
#include "CollisionShape.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDashComponent::UDashComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDashComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bDashing)
	{
		const float TimeProgress = TimeToDash/ProjectionPositions.Num();
		if(ProjectionPositions.IsEmpty())
		{
			bDashing = false;
			bNextDash = true;
			return;	
		}

		
		if(eOrientationDash == OrientationDash::DASH_Left)
		{
			if(StepNextProjectionPosition < ProjectionPositions.Num())
			{
				if(Time < TimeProgress)
				{
					Time += DeltaTime * SpeedDash;
					GetOwner()->SetActorLocation(FMath::LerpStable(GetOwner()->GetActorLocation(),*ProjectionPositions[StepNextProjectionPosition],Time/TimeProgress));
				}else
				{
					Time = 0;
					StepNextProjectionPosition++;
				}
			}else
			{
				bDashing = false;
				bNextDash = true;
				eOrientationDash = OrientationDash::DASH_None;
				StepNextProjectionPosition = 0;
			}
		}
		else if(eOrientationDash == OrientationDash::DASH_Right)
		{
			if(StepNextProjectionPosition >= 0)
			{
				if(Time < TimeProgress)
				{
					Time += DeltaTime * SpeedDash;
					GetOwner()->SetActorLocation(FMath::LerpStable(GetOwner()->GetActorLocation(),*ProjectionPositions[StepNextProjectionPosition],Time/TimeProgress));
				}else
				{
					Time = 0;
					StepNextProjectionPosition--;
				}
			}else
			{
				bDashing = false;
				bNextDash = true;
				eOrientationDash = OrientationDash::DASH_None;
				StepNextProjectionPosition = 0;
			}
		}
	}
}


bool UDashComponent::CanDash()
{
	if(!bNextDash)
		return false;

	if(eOrientationDash == OrientationDash::DASH_None)
		return false;

	if(!ProjectionPositions.IsEmpty())
		ProjectionPositions.Reset();
	
	int32 nbSphere = 6;
	FVector Origin = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * Distance/2;

	TArray<AActor*> IgnoreActors;
	
	FVector NewPos;
	
	for(int32 i = 0; i <= nbSphere; i++)
	{
		float t = (float)i/(float)(nbSphere);
		
		NewPos = Origin;

		if(eOrientationDash == OrientationDash::DASH_Right)
		{
			NewPos.X += (FMath::Cos((t*PI) + (GetOwner()->GetActorRotation().Yaw/180)*PI) * Distance/2);
			NewPos.Y += (FMath::Sin((t*PI) + (GetOwner()->GetActorRotation().Yaw/180)*PI) * Distance/2);			
		}else if(eOrientationDash == OrientationDash::DASH_Left)
		{
			NewPos.X -= (FMath::Cos((t*PI) + (GetOwner()->GetActorRotation().Yaw/180)*PI) * Distance/2);
			NewPos.Y -= (FMath::Sin((t*PI) + (GetOwner()->GetActorRotation().Yaw/180)*PI) * Distance/2);
		}
		
		FHitResult Result;

		FLinearColor color = i==nbSphere?FLinearColor::Green:FLinearColor::Red;
		
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), NewPos,NewPos,25.f,ETraceTypeQuery::TraceTypeQuery1,false,IgnoreActors,EDrawDebugTrace::ForDuration,Result,true,color,FLinearColor::Blue,5);
		if(Result.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
			ProjectionPositions.Reset();
			return false;
		}
		ProjectionPositions.Push(new FVector(NewPos.X,NewPos.Y, NewPos.Z));
	}
	return true;
}

void UDashComponent::DashMoving()
{
	if(!bNextDash)
		return;
	
	if(CanDash())
	{
		if(ProjectionPositions.IsEmpty())
			return;
		
		ActorLocation = GetOwner()->GetActorLocation();
		eOrientationDash==OrientationDash::DASH_Left?StepNextProjectionPosition=0:StepNextProjectionPosition=ProjectionPositions.Num()-1;
		bDashing = true;
		bNextDash = false;
	}
	else
	{
		if(!ProjectionPositions.IsEmpty())
			ProjectionPositions.Reset();
	}
}

bool UDashComponent::IsDashing()
{
	return bDashing;
}

void UDashComponent::SetOrientationDash(OrientationDash orientationDash)
{
	eOrientationDash = orientationDash;
}