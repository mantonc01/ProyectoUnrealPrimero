// Mario

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECT1_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float TotalMassOfActorsInVolume() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	


private:
	UPROPERTY(EditAnywhere)//para mostrar el elemento en el editor
	float RotationYaw=90.0;
	
	float ObjetivoZeta=0;//po
	float InicialZeta=0;
	
	UPROPERTY(EditAnywhere)
	float Speed_Apertura=1;

	
	
	

	//para introducir un disparador

	virtual void OpenDoor(float DeltaTime);
	virtual void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpenDoor=nullptr;;//actor que abre la puerta

	float InitialTimeOpening_TiempoInicialApertura=0;
	UPROPERTY(EditAnywhere)
	float ClosingDelay_TiempoDeCierre=1;
	UPROPERTY(EditAnywhere)
	float Speed_Cierre=1;

	UPROPERTY(EditAnywhere)
	float OpeningMass=50.0f;
	
	UPROPERTY(EditAnywhere)
	UAudioComponent* ComponenteSonidoPuerta=nullptr;

	bool PuertaAbierta=false;
	
	UPROPERTY(EditAnywhere)
	USoundBase* SonidoAbrirPuerta=nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* SonidoCerrarPuerta=nullptr;

	UPROPERTY()
	UMeshComponent* DoorMesh=nullptr;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* Presure_Plate=nullptr;

	UPROPERTY(EditAnywhere)
	FString OpenerTag="DoorOpener";
};
