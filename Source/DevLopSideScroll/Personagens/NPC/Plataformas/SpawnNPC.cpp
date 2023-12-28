// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnNPC.h"
#include "DevLopSideScroll/Personagens/NPC/NPC_Base.h"


ASpawnNPC::ASpawnNPC()
{
	LocalReferenciaNPC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReferenciaCamera"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> referencia(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (referencia.Succeeded())
	{
		LocalReferenciaNPC->SetStaticMesh(referencia.Object);
		LocalReferenciaNPC->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LocalReferenciaNPC->SetCollisionResponseToAllChannels(ECR_Ignore);
		LocalReferenciaNPC->SetCollisionObjectType(ECC_WorldStatic);
		LocalReferenciaNPC->bHiddenInGame = true;
	}
}

void ASpawnNPC::AtivaSpawnNPC()
{
	GetWorldTimerManager().SetTimer(Contador, this, &ASpawnNPC::CriaNPC, ValorSequenciaSpawn, true);
}

void ASpawnNPC::BeginPlay()
{
	Super::BeginPlay();
}

void ASpawnNPC::CriaNPC()
{
	if (ContadorSpawn >= LimiteSpawn && ContadorSpawnAtivos == 0)
	{
		Plataforma->AtivaPlataforma(false, true);
		Destroy();
	}
	else if (ContadorSpawnAtivos < LimiteNPCVivo && ContadorSpawn < LimiteSpawn)
	{
		FRotator EscolhidoRotacaoSpawn;
		FVector EscolhidoLocalSpawn;
		if (LocaisSpawn.Num() > 0)
		{
			int RandomLocal = FMath::RandRange(0, LocaisSpawn.Num() - 1);
			EscolhidoRotacaoSpawn = LocaisSpawn[RandomLocal]->GetActorRotation();
			EscolhidoLocalSpawn = LocaisSpawn[RandomLocal]->GetActorLocation();
		}
		else
		{
			EscolhidoRotacaoSpawn = GetActorRotation();
			EscolhidoLocalSpawn = GetActorLocation();
		}
		ANPC_Base* NPC = GetWorld()->SpawnActorDeferred<ANPC_Base>(
			ANPC_Base::StaticClass(), FTransform(EscolhidoRotacaoSpawn, EscolhidoLocalSpawn));
		if (NPC)
		{
			NPC->Objetivos = Objetivos;
			NPC->FinishSpawning(FTransform(EscolhidoRotacaoSpawn, EscolhidoLocalSpawn));
			NPC->PontoSpawn = this;
			ContadorSpawn++;
			ContadorSpawnAtivos++;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "  NPCS falhou");
		}
	}
}
