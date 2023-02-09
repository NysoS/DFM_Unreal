// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"

#include "DFM1Character.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	RootComponent = SphereCollider;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(SphereCollider);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationObject"));
	
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollectible::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(Cast<ADFM1Character>(OtherActor))
	{
		ADFM1Character* Character = Cast<ADFM1Character>(OtherActor);
		if(!Character) return;
		Character->AddCollectible(1);
		DelegateTakeCollectible.Broadcast(1);
		Destroy();
	}
}