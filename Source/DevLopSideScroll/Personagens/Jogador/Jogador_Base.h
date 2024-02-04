//Este projeto foi criado para fins de divulgar conhecimento e pode ser utilizado a vontade.

//This project was created for the purpose of disseminating knowledge and can be used freely.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "DevLopSideScroll/Personagens/Enums/Lista_Enums.h"
#include "Interfaces/DanoProjetilInterface.h"
#include "Jogador_Base.generated.h"

UCLASS()
class DEVLOPSIDESCROLL_API AJogador_Base : public ACharacter, public IDanoProjetilInterface
{
	GENERATED_BODY()

	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCameraComponent* CameraPrincipal;
	UPROPERTY()
	USkeletalMeshComponent* Arma;
	UPROPERTY()
	UStaticMeshComponent* LocalReferenciaCamera;

public:

	AJogador_Base();
	
	UPROPERTY()
	FTimerHandle ProjetilTemporizador;

	UPROPERTY()
	TArray<FString> MeshesPlayer;
	UPROPERTY()
	TArray<FString> AnimacaoPlayer;
	UPROPERTY()
	FString CaminhoArma;

	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float Vida = 100;
	UPROPERTY()
	float Velocidade;
	UPROPERTY()
	float AnguloCorpo;
	UPROPERTY()
	float AnguloCameraX;
	UPROPERTY()
	float AnguloCameraY;
	UPROPERTY()
	float Direcao;
	UPROPERTY()
	float VelTempAnimacao;
	UPROPERTY()
	float ApontamentoZControle = 0.f;
	
	UPROPERTY(meta=(BlueprintProtected = "true"))
	float VelocidadeTiro = 0.05f;
	UPROPERTY(BlueprintReadOnly,Category="Variaveis")
	float ArmaAquecimento = 100.0f;
	UPROPERTY()
	float QuantidadeDano = 0.0f;
	UPROPERTY()
	float VelocidadeMax = 1000;
	UPROPERTY()
	float RotacaoMira;

	UPROPERTY()
	TEnumAsByte<TipoEstado> Estado = NoChaoAndando;
	UPROPERTY()
	TEnumAsByte<TipoAcao> Acao = Nada;
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Personagem")
	TEnumAsByte<TipoPersonagem> PersonagemNPC = Estagiario;

	UPROPERTY()
	UClass* Estagiario_Anim;
	UPROPERTY()
	UClass* Pleno_Anim;
	UPROPERTY()
	UClass* Senior_Anim;
	UPROPERTY()
	UClass* Chefe_Anim;

	UPROPERTY()
	bool BloqueiaContador = true;
	UPROPERTY()
	bool PersonagemSeMovimenta;
	UPROPERTY()
	bool Mirar = false;
	UPROPERTY()
	bool PermiteTiro = true;
	UPROPERTY()
	bool ArmaAquecida = false;

	UPROPERTY()
	FVector LocalSocketArma;

	UPROPERTY()
	FRotator RotacaoSocketArma;
	
	void CarregarAssetsPersonagem();

	void VerificaEscolhaPersonagem();
	
	void VerificaMeshPersonagem(float Index);

protected:
	virtual void BeginPlay() override;
	
	void MoverFrente(float valor);
	
	void MoverLado(float valor);
	
	void VirarCameraLado(float valor);

	void DefinePadroesVel(float valor);

	//Botões apertados
	void VerificaPulo_Pressionado();
	void VerificaPulo_Solto();
	void Atirar_Pressionado();
	void Atirar_Solto();
	
	void Interagir_Pressionado();
	void Interagir_Solto();
	void Permite_Tiro();

	//Metodos
	void DefinePadroes();

	void DefineEstadoAtual();
	void CriaCameraConfig();
	void CriaPersonagemConfig();
	void InicializaAttachPersonagem();
	void CriaProjetil();

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
		
	virtual void RecebeDanoNPCMetodo() override;

	virtual void RecebeDanoTeleportMetodo(ETipoColisao TipoColisao,AActor* Alvo) override;
};
