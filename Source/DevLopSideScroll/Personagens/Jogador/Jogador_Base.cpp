//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "Jogador_Base.h"
#include "Components/SkeletalMeshComponent.h"
#include "DevLopSideScroll/Controles/GamePlayController.h"
#include "DevLopSideScroll/Personagens/NPC/Plataformas/PontoSpawn.h"
#include "EngineUtils.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopSideScroll/Personagens/NPC/Plataformas/ColisaoTeleport.h"
#include "DevLopSideScroll/PlayerStates/Interfaces/AlteraPlayerStateInterface.h"

AJogador_Base::AJogador_Base()
{
	CriaPersonagemConfig();
	CriaCameraConfig();
}

void AJogador_Base::BeginPlay()
{
	Super::BeginPlay();
	DefinePadroes();
	VerificaEscolhaPersonagem();
}

void AJogador_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DefineEstadoAtual();
	DefinePadroesVel(DeltaTime);
}

void AJogador_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoverFrente"), this, &AJogador_Base::MoverFrente);
	PlayerInputComponent->BindAxis(TEXT("MoverLado"), this, &AJogador_Base::MoverLado);

	PlayerInputComponent->BindAxis(TEXT("VirarCameraLado"), this, &AJogador_Base::VirarCameraLado);

	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Pressed, this, &AJogador_Base::VerificaPulo_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Pulo"), IE_Released, this, &AJogador_Base::VerificaPulo_Solto);

	PlayerInputComponent->
		BindAction(TEXT("Atirar"), IE_Pressed, this, &AJogador_Base::Atirar_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Atirar"), IE_Released, this, &AJogador_Base::Atirar_Solto);

	PlayerInputComponent->BindAction(TEXT("Interagir"), IE_Pressed, this,
	                                 &AJogador_Base::Interagir_Pressionado);
	PlayerInputComponent->BindAction(TEXT("Interagir"), IE_Released, this,
	                                 &AJogador_Base::Interagir_Solto);
}

void AJogador_Base::RecebeDanoNPCMetodo()
{
	if (Vida > 0)
	{
		Vida -= 10;
		if (Vida <= 0)
		{
			IAlteraPlayerStateInterface* VerPlayerState = Cast<IAlteraPlayerStateInterface>(this->GetPlayerState());
			FTimerHandle ContadorReviver;
			GetWorldTimerManager().SetTimer(ContadorReviver, Cast<AGamePlayController>(GetController()),
			                                &AGamePlayController::ReviveJogador, 5, false);
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesJogadorMetodo();
			}
		}
	}
}

void AJogador_Base::RecebeDanoTeleportMetodo(ETipoColisao TipoColisao, AActor* Alvo)
{
	UWorld* World = GetWorld();
	check(World);
	
	APontoSpawn* ObjetoEscolhido = nullptr;

	AColisaoTeleport* SpawnEncontrado = nullptr;
	
	FVector Local;
	
	switch (TipoColisao)
	{
	case ETipoColisao::AtivaSpawn:
		SpawnEncontrado = Cast<AColisaoTeleport>(Alvo);
		if (IsValid(SpawnEncontrado))
		{
			SpawnEncontrado->ObjetoSpawn->AtivaSpawnNPC();
		}
		Alvo->Destroy();
		break;
	case ETipoColisao::EvitaQueda:

		Vida -= 50;

		for (TActorIterator<APontoSpawn> It(World); It; ++It)
		{
			if (IsValid(ObjetoEscolhido) && (It->GetDistanceTo(this) < ObjetoEscolhido->GetDistanceTo(this)))
			{
				ObjetoEscolhido = *It;
			}
			else if (!IsValid(ObjetoEscolhido))
			{
				ObjetoEscolhido = *It;
			}
		}
		Local = ObjetoEscolhido->GetActorLocation();
		SetActorLocationAndRotation(FVector(Local.X, Local.Y, Local.Z + 50),
		                            ObjetoEscolhido->GetActorRotation(), false, nullptr,
		                            ETeleportType::TeleportPhysics);
		if (Vida <= 0)
		{
			IAlteraPlayerStateInterface* VerPlayerState = Cast<IAlteraPlayerStateInterface>(this->GetPlayerState());
			FTimerHandle ContadorReviver;
			GetWorldTimerManager().SetTimer(ContadorReviver, Cast<AGamePlayController>(GetController()),
			                                &AGamePlayController::ReviveJogador, 5, false);
			if (VerPlayerState)
			{
				VerPlayerState->AdicionaMortesJogadorMetodo();
			}
		}
		break;
	case ETipoColisao::FinalizaFase:
		Cast<AGamePlayController>(GetController())->Hud->AtivarTelaVencedor();
		break;
	default:
		break;
	}
}


void AJogador_Base::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	VerificaEscolhaPersonagem();
}
