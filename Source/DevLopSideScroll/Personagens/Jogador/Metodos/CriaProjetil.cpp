//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#include "Components/SkeletalMeshComponent.h"
#include "DevLopSideScroll/Personagens/Jogador/Jogador_Base.h"
#include "DevLopSideScroll/Personagens/Jogador/Projeteis/ProjetilCMais.h"
#include "DevLopSideScroll/Personagens/Jogador/Projeteis/ProjetilCsharp.h"
#include "DevLopSideScroll/Personagens/Jogador/Projeteis/ProjetilJava.h"
#include "DevLopSideScroll/Personagens/Jogador/Projeteis/ProjetilNoCode.h"

void AJogador_Base::CriaProjetil()
{
	LocalSocketArma = Arma->GetSocketLocation("TiroSocket");
	RotacaoSocketArma = Arma->GetSocketRotation("TiroSocket");
	LocalSocketArma.Z -= 50;
	AProjetilNoCode* ProjetilEstagiario;
	AProjetilCsharp* ProjetilPleno;
	AProjetilJava* ProjetilSenior;
	AProjetilCMais* ProjetilChefe;

	
	switch (PersonagemNPC)
	{
	case Estagiario:
		QuantidadeDano = 10;
		VelocidadeTiro = 0.5;
		ProjetilEstagiario = GetWorld()->SpawnActor<AProjetilNoCode>(
			LocalSocketArma, RotacaoSocketArma);
		ProjetilEstagiario->DonoProjetil = this;
		break;
	case Pleno:
		QuantidadeDano = 10;
		VelocidadeTiro = 0.2;
		ProjetilPleno = GetWorld()->SpawnActor<AProjetilCsharp>(LocalSocketArma, RotacaoSocketArma);
		ProjetilPleno->DonoProjetil = this;
		break;
	case Senior:
		QuantidadeDano = 5;
		VelocidadeTiro = 0.1;
		ProjetilSenior = GetWorld()->SpawnActor<AProjetilJava>(LocalSocketArma, RotacaoSocketArma);
		ProjetilSenior->DonoProjetil = this;
		break;
	case Chefe:
		QuantidadeDano = 50;
		VelocidadeTiro = 1;
		ProjetilChefe = GetWorld()->SpawnActor<AProjetilCMais>(LocalSocketArma, RotacaoSocketArma);
		ProjetilChefe->DonoProjetil = this;
		break;
	default:
		VelocidadeTiro = 0.1;
		ProjetilSenior = GetWorld()->SpawnActor<AProjetilJava>(LocalSocketArma, RotacaoSocketArma);
		ProjetilSenior->DonoProjetil = this;
		break;
	}
}
