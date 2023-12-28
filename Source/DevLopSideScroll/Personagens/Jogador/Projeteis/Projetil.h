//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "DevLopSideScroll/Personagens/NPC/NPC_Base.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projetil.generated.h"

UCLASS()
class DEVLOPSIDESCROLL_API AProjetil : public AActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY()
	AActor* DonoProjetil;
	UPROPERTY()
	UProjectileMovementComponent* Projetil;
	UPROPERTY()
	UStaticMeshComponent* ProjetilMesh;
	
	UFUNCTION()
	void DanoAtaqueProjetil(AActor* InimigoDetectado);

	UFUNCTION()
	void DestruirProjetil();

	UFUNCTION()
	void InicioDanoColisao(UPrimitiveComponent* OverlappedComp, AActor* InimigoDetectado,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult)
	{
		if(IsValid(DonoProjetil))
		{
			if(InimigoDetectado != this && InimigoDetectado != DonoProjetil)
			{
				ANPC_Base* NPCDetectado = Cast<ANPC_Base>(InimigoDetectado);
				if (IsValid(NPCDetectado) && NPCDetectado->Vida > 0)
				{
					DanoAtaqueProjetil(InimigoDetectado);
				}
				else
				{
					FTimerHandle ContadorLocal;
					GetWorldTimerManager().SetTimer(ContadorLocal, this, &AProjetil::DestruirProjetil, 0.5, false);					
				}
			}
		}
	}
};
