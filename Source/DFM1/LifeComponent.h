// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMulticastDelegateTakeDamage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DFM1_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Life")
	int32 MaxLife;
	int32 Life;
	
	
public:	
	// Sets default values for this component's properties
	ULifeComponent();
	
	int32 GetMaxLife();
	int32 GetLife();
	
	UPROPERTY()
	FMulticastDelegateTakeDamage DelegateTakeDamage;
	UFUNCTION(BlueprintCallable, Category = "Custom Delegate")
	void OntakeDamage();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
