//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopSideScroll/Personagens/Jogador/Jogador_Base.h"
#include "Kismet/KismetMathLibrary.h"

void AJogador_Base::MoverFrente(float valor)
{
	if (Acao != Queda && Acao != Morto)
	{
		FVector Frente = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

		FVector Costas = UKismetMathLibrary::GetRightVector
			(FRotator(0, GetControlRotation().Yaw, 0));
	}
}

void AJogador_Base::MoverLado(float valor)
{
	if (valor != 0)
	{
		if (Acao != Queda && Acao != Morto)
		{
			FVector Lado = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
			if (valor > 0)
			{
				GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
			else
			{
				GetMesh()->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
			}
			AddMovementInput(Lado, valor);
		}
	}
}
