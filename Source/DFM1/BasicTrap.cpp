// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicTrap.h"

#include "DFM1Character.h"
#include "LifeComponent.h"
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

void ABasicTrap::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(!OtherActor) return;

	if(OtherActor->FindComponentByClass<ULifeComponent>())
	{
		ULifeComponent* CharacterLifeComponent = OtherActor->FindComponentByClass<ULifeComponent>();
		CharacterLifeComponent->OntakeDamage();
	}

	UE_LOG(LogTemp, Warning, TEXT("Actor Overlap %s") ,*OtherActor->GetName());
}

