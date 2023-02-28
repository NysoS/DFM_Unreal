// Fill out your copyright notice in the Description page of Project Settings.

#include "DashComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CollisionShape.h"

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

	// ...
}


bool UDashComponent::CanDash()
{
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(25.f);

	int32 nbSphere = 5;
	FVector Center = GetOwner()->GetActorLocation();

	FHitResult Result;
	TArray<AActor*> IgnoreActors;
	
	FVector NewPos = Center + GetOwner()->GetActorForwardVector();
	float DistanceBetweenIteration = Distance/5;
	for(int32 i = 0; i < nbSphere; ++i)
	{
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(),NewPos,NewPos,25.f,ETraceTypeQuery::TraceTypeQuery1,false,IgnoreActors,EDrawDebugTrace::ForDuration,Result,true,FLinearColor::Red,FLinearColor::Blue,5);
		NewPos += GetOwner()->GetActorForwardVector() * DistanceBetweenIteration;
	}
	return true;
}
