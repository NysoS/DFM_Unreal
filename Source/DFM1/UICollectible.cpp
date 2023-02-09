// Fill out your copyright notice in the Description page of Project Settings.


#include "UICollectible.h"

#include "Collectible.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

UUICollectible::UUICollectible(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UUICollectible::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> CollectibleActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACollectible::StaticClass(), CollectibleActors);

	for(int i = 0; i < CollectibleActors.Num(); ++i)
	{
		ACollectible* Collectible = Cast<ACollectible>(CollectibleActors[i]);
		if(Collectible)
		{
			Collectible->DelegateTakeCollectible.AddDynamic(this,&UUICollectible::OnTakeCollectible);	
		}
	}
	
}

void UUICollectible::NativeDestruct()
{
	Super::NativeDestruct();
}

bool UUICollectible::Initialize()
{
	bool init = Super::Initialize();
	if(!init) return false;

	return init;
}

void UUICollectible::OnTakeCollectible(int32 nbCollectible)
{
	if(!CollectibleText) return;
	NbCollectibe += nbCollectible;
	FText text = FText::FromString(FString::FromInt(NbCollectibe)+" Coins");
	CollectibleText->SetText(text);
}
