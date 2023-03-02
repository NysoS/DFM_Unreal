// Fill out your copyright notice in the Description page of Project Settings.

#include "DashComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TimelineComponent.h"
#include "CollisionShape.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		if(Time < TimeToDash)
		{
			Time += DeltaTime;
			GetOwner()->SetActorLocation(FMath::Lerp(ActorLocation, ActorLocation + GetOwner()->GetActorForwardVector() * Distance, Time/TimeToDash));	
		}else
		{
			bDashing = false;
			Time = 0;
		}
	}
}


bool UDashComponent::CanDash()
{
	if(bDashing)
		return false;
		
	int32 nbSphere = 5;
	FVector Center = GetOwner()->GetActorLocation();

	TArray<AActor*> IgnoreActors;
	
	FVector NewPos = Center + GetOwner()->GetActorForwardVector();
	float DistanceBetweenIteration = Distance/5;
	for(int32 i = 0; i <= nbSphere; i++)
	{
		FHitResult Result;
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(),NewPos,NewPos,25.f,ETraceTypeQuery::TraceTypeQuery1,false,IgnoreActors,EDrawDebugTrace::ForDuration,Result,true,FLinearColor::Red,FLinearColor::Blue,5);
		if(Result.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
			return false;
		}
		NewPos += GetOwner()->GetActorForwardVector() * DistanceBetweenIteration;
	}
	return true;
}

void UDashComponent::DashMoving()
{
	if(CanDash())
	{
		ActorLocation = GetOwner()->GetActorLocation();
		bDashing = true;
	}
}

bool UDashComponent::IsDashing()
{
	return bDashing;
}
