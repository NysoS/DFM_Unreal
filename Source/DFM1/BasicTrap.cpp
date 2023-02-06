// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicTrap.h"

#include "DFM1Character.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"

// Sets default values
ABasicTrap::ABasicTrap()
{

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxComponent->SetupAttachment(StaticMesh);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 *	Récupère l'acteur qui passe a travers lui,
 *	Doit avoir 'Generate Overlap Event' activé pour fonctionner
 */
void ABasicTrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(!OtherActor) return;

	if(Cast<ACharacter>(OtherActor))
	{
		ADFM1Character* Character = Cast<ADFM1Character>(OtherActor);
		Character->Trapped();
	}
}

