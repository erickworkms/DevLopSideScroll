//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "Projetil.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DevLopSideScroll/GameModes/GameplayFaseGameMode.h"
#include "Net/UnrealNetwork.h"

void AProjetil::DanoAtaqueProjetil(AActor* InimigoDetectado)
{
	AGameModeBase* GameModeEncontrado = GetWorld()->GetAuthGameMode();
	AGameplayFaseGameMode* GameMode = Cast<AGameplayFaseGameMode>(GameModeEncontrado);
	GameMode->DanoAtaqueProjetil(DonoProjetil,InimigoDetectado,this);
}

void AProjetil::DestruirProjetil()
{
	if (IsValid(this))
	{
		Destroy();
	}
}
