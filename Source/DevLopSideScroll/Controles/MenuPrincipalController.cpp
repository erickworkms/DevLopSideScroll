//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.


#include "MenuPrincipalController.h"


void AMenuPrincipalController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}