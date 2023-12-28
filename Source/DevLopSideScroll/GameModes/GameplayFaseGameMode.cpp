//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "GameplayFaseGameMode.h"
#include "GameFramework/HUD.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopSideScroll/Personagens/Jogador/Jogador_Base.h"
#include "DevLopSideScroll/Personagens/NPC/NPC_Base.h"
#include "DevLopSideScroll/PlayerStates/ADevLopSideScrollGameStateBase.h"
#include "DevLopSideScroll/PlayerStates/DevOpPlayerState.h"
#include "Kismet/GameplayStatics.h"

AGameplayFaseGameMode::AGameplayFaseGameMode()
{
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDClass(TEXT("/Game/Mapas/HudGameplayBlueprint"));
	if (PlayerHUDClass.Succeeded())
	{
		HUDClass = PlayerHUDClass.Class;
	}
	PlayerControllerClass = AGamePlayController::StaticClass();
	GameStateClass = ADevLopSideScrollGameStateBase::StaticClass();
	PlayerStateClass = ADevOpPlayerState::StaticClass();
	DefaultPawnClass = nullptr;
}

void AGameplayFaseGameMode::DanoAtaqueProjetil(AActor* DonoProjetil, AActor* InimigoDetectado, AActor* Projetil)
{
	IDanoProjetilInterface* inimigoEncontrado = Cast<IDanoProjetilInterface>(InimigoDetectado);
	if (inimigoEncontrado)
	{
		inimigoEncontrado->DanoProjetilMetodo(DonoProjetil);
		Projetil->Destroy();
	}
	else if (InimigoDetectado != DonoProjetil)
	{
		Projetil->Destroy();
	}
}

void AGameplayFaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* DefaultPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (DefaultPlayerController)
	{
		DefaultPlayerController->bShowMouseCursor = true;
		DefaultPlayerController->DefaultMouseCursor = EMouseCursor::Crosshairs;

		GameInstance = Cast<UDevLopWarGameInstance>(GetWorld()->GetGameInstance());
		GameStateJogador = Cast<ADevLopSideScrollGameStateBase>(GameState);
		GameStateJogador->SetTempoJogo(300);
		GetWorldTimerManager().SetTimer(ContadorTempo, this, &AGameplayFaseGameMode::AtualizaTempo, 1, true);
	}
}

void AGameplayFaseGameMode::AtualizaTempo()
{
	GameStateJogador->DescontaTempoJogo();
}

void AGameplayFaseGameMode::RetornaMenuInicial()
{
	UWorld* World = GetWorld();
	check(World);

	UGameplayStatics::OpenLevel(World, TEXT("/Game/Mapas/TelaInicial"), true);
}
