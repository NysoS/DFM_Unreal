// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	Life = MaxLife;
	
}


// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 ULifeComponent::GetMaxLife()
{
	return MaxLife;
}

int32 ULifeComponent::GetLife()
{
	return Life;
}

/**
 * Invoke l'evenement 'DelegateTakeDamage' en passant en parametre le nombre de vie restant 
 */
void ULifeComponent::OntakeDamage()
{
	Life--;
	if(Life <= 0 )
	{
		Life = 0;
		UGameplayStatics::OpenLevel(GetWorld(),FName(*GetWorld()->GetName()));
	}
	DelegateTakeDamage.Broadcast(Life);
}
