// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UICollectible.generated.h"

/**
 * 
 */
UCLASS()
class DFM1_API UUICollectible : public UUserWidget
{
	GENERATED_BODY()
	
	int32 NbCollectibe = 0;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual bool Initialize() override;
	
public:
	UUICollectible(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CollectibleText;
	
	UFUNCTION(BlueprintCallable)
	void OnTakeCollectible(int32 nbCollectible);
};
