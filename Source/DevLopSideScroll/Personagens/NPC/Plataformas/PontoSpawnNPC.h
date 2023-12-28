// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PontoSpawnNPC.generated.h"

UCLASS()
class DEVLOPSIDESCROLL_API APontoSpawnNPC : public AActor
{
	GENERATED_BODY()
	
public:	

	APontoSpawnNPC();

	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaNPC;
};
