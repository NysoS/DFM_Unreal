// Fill out your copyright notice in the Description page of Project Settings.


#include "EndingZone.h"

#include "Collectible.h"
#include "DFM1Character.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEndingZone::AEndingZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Trigger Mesh"));
	MeshComponent->SetupAttachment(BoxComponent);
	
}

// Called when the game starts or when spawned
void AEndingZone::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> CollectiblesInScene;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACollectible::StaticClass(),CollectiblesInScene);
	TotalCoinsToUnlock = CollectiblesInScene.Num();
	UE_LOG(LogTemp, Warning, TEXT("Number of coins to unlock zone is %d"),TotalCoinsToUnlock);
	
}

// Called every frame
void AEndingZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndingZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if(const ADFM1Character* Character = Cast<ADFM1Character>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("ENDING ZONE TRIGGER WITH %d coins"), Character->GetCountCollectible());

		if(Character->GetCountCollectible() == TotalCoinsToUnlock)
		{
			UE_LOG(LogTemp, Warning, TEXT("Congratulation you have finish this game!!"));
		}else
		{
			UE_LOG(LogTemp, Warning, TEXT("Sorry bro, you don't have enough coins!! Come back later"));
		}
	}
}

