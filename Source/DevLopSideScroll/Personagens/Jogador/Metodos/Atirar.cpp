//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "DevLopSideScroll/Personagens/Jogador/Jogador_Base.h"
#include "GameFramework/CharacterMovementComponent.h"

void AJogador_Base::Atirar_Pressionado()
{
	if (PermiteTiro == true && ArmaAquecida == false)
	{
		PermiteTiro = false;
		CriaProjetil();
		GetWorldTimerManager().SetTimer(ProjetilTemporizador, this, &AJogador_Base::Permite_Tiro, VelocidadeTiro, false);
		ArmaAquecimento -= VelocidadeTiro * 30;
		if (ArmaAquecimento <= 0.0f)
		{
			ArmaAquecida = true;
		}
	}
}

void AJogador_Base::Atirar_Solto()
{
	PermiteTiro = true;
}
