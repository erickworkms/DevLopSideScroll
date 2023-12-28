// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PontoSpawn.generated.h"

UCLASS()
class DEVLOPSIDESCROLL_API APontoSpawn : public AActor
{
	GENERATED_BODY()
	
public:	

	APontoSpawn();

	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;
};
