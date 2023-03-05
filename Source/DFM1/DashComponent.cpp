// Fill out your copyright notice in the Description page of Project Settings.

#include "DashComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"
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
				DashProgress(DeltaTime);
			}
			else
			{
				DashReset();
			}
		}
		else if(eOrientationDash == OrientationDash::DASH_Right)
		{
			if(StepNextProjectionPosition >= 0)
			{
				DashProgress(DeltaTime);
			}
			else
			{
				DashReset();
			}
		}
	}
}

//Project le mouvement du dash circulaire
//Si il y a un obstacle on annule le dash
//Retourne true, si aucun obstacle a été touché
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

		FLinearColor colorDebug = i==nbSphere?FLinearColor::Green:FLinearColor::Red;

		//Affiche une sphère de debug sur chaque position projeter du dash
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), NewPos,NewPos,25.f,ETraceTypeQuery::TraceTypeQuery1,false,IgnoreActors,EDrawDebugTrace::ForDuration,Result,true,colorDebug,FLinearColor::Blue,5);
		if(Result.GetActor())
		{
			ProjectionPositions.Reset();
			return false;
		}
		ProjectionPositions.Push(new FVector(NewPos.X,NewPos.Y, NewPos.Z));
	}
	return true;
}

/**
 * Configure la l'orientation du dash et lance le mouvement du dash, si la projection du dash a detectée aucun obstacle
 */
void UDashComponent::DashMoving()
{
	if(!bNextDash)
		return;
	
	if(CanDash())
	{
		if(ProjectionPositions.IsEmpty())
			return;
		
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

/**
* Effectue le mouvement du dash a chaque frame, selon l'orientation du dash
* Le personnage se déplace sur chaque position projeter selon une vitesse définie/le nombre de position projeter
*/
void UDashComponent::DashProgress(float deltaTime)
{
	const float TimeProgress = TimeToDash/ProjectionPositions.Num();
	if(Time < TimeProgress)
	{
		Time += deltaTime * SpeedDash;
		GetOwner()->SetActorLocation(FMath::LerpStable(GetOwner()->GetActorLocation(),*ProjectionPositions[StepNextProjectionPosition],Time/TimeProgress));
	}else
	{
		Time = 0;
		eOrientationDash==OrientationDash::DASH_Left?StepNextProjectionPosition++:StepNextProjectionPosition--;
	}
}

/**
 * Réinitialise la configuration du mouvement du dash
 */
void UDashComponent::DashReset()
{
	bDashing = false;
	bNextDash = true;
	eOrientationDash = OrientationDash::DASH_None;
	StepNextProjectionPosition = 0;
}

bool UDashComponent::IsDashing()
{
	return bDashing;
}

void UDashComponent::SetOrientationDash(OrientationDash orientationDash)
{
	eOrientationDash = orientationDash;
}