//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopSideScroll/GameInstance/DevLopWarGameInstance.h"
#include "DevLopSideScroll/PlayerStates/ADevLopSideScrollGameStateBase.h"
#include "GameplayFaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEVLOPSIDESCROLL_API AGameplayFaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AGameplayFaseGameMode();

public:
	UFUNCTION()
	void DanoAtaqueProjetil(AActor* DonoProjetil,AActor* InimigoDetectado,AActor* Projetil);
	
	virtual void BeginPlay() override;

	UPROPERTY()
	ADevLopSideScrollGameStateBase* GameStateJogador;

	FTimerHandle ContadorTempo;
	
	UFUNCTION()
	void AtualizaTempo();
	
	UFUNCTION(BlueprintCallable)
	void RetornaMenuInicial();

private:
	UPROPERTY()
	UDevLopWarGameInstance* GameInstance;
};
