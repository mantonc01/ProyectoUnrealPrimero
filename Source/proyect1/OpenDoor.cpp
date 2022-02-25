// Mario


#include "OpenDoor.h"

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	DoorMesh=Cast<UMeshComponent>(GetOwner()->GetDefaultSubobjectByName("SM_Door"));

	
	
	InicialZeta=DoorMesh->GetComponentRotation().Yaw;
	
	ObjetivoZeta=InicialZeta+RotationYaw;
	
	ComponenteSonidoPuerta=GetOwner()->FindComponentByClass<UAudioComponent>();

	
	Presure_Plate=GetOwner()->FindComponentByClass<UBoxComponent>();
	if (!Presure_Plate)
	{
		UE_LOG(LogTemp,Warning,TEXT("no encuentro Presure_Plate"));
	}

	
	

	
}

float UOpenDoor:: TotalMassOfActorsInVolume() const
{
	TArray <AActor*> OverlappingActors;

	if (Presure_Plate)
	{
		Presure_Plate->GetOverlappingActors(OverlappingActors);
	}
	
	
	float MassAcumaltor=0;
	
	//si el componente tiene un tag
	
		for (int i=0;i<OverlappingActors.Num();i++)
        	{
        		//con esto se suma la masa de cada objeto o actor
        		UPrimitiveComponent* ActorWithPrimitiveComponent= OverlappingActors[i]->FindComponentByClass<UPrimitiveComponent>();
        		
        		if (ActorWithPrimitiveComponent && ActorWithPrimitiveComponent->ComponentHasTag(*OpenerTag))
        		{
        			MassAcumaltor += ActorWithPrimitiveComponent->GetMass();
        		}
        		
        	}
	
	
	return MassAcumaltor;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	/*if (Presure_Plate->IsOverlappingActor (ActorThatOpenDoor) )//si presionamos el disparador el método IsOverlappingActor
																//devuelve un booleano de ActorThatOpenDoor*/

	
	if (Presure_Plate && TotalMassOfActorsInVolume() > OpeningMass )
	{
		OpenDoor(DeltaTime);
		InitialTimeOpening_TiempoInicialApertura=GetWorld()->GetTimeSeconds();//obtengo el tiempo que estoy en el disparador
		
		/*SonidoAbrirPuerta->Play(2);
		UE_LOG(LogTemp,Warning,TEXT("Sonido abrir Puerta ,%s"),);*/
	}
	else
	{
		if (GetWorld()->GetTimeSeconds()>(ClosingDelay_TiempoDeCierre+InitialTimeOpening_TiempoInicialApertura))
		{
			CloseDoor(DeltaTime);

			/*SonidoAbrirPuerta->Play(2);
			UE_LOG(LogTemp,Warning,TEXT("Sonido abrir Puerta ,%s"),);*/
		}
		
	}

	
}


void UOpenDoor::OpenDoor(float DeltaTime)
{
	
	//apertura de la puerta con FInterpTo, dependiente de deltatime.	
	float siguientePasoEnElGiro=FMath::FInterpTo(DoorMesh->GetComponentRotation().Yaw,ObjetivoZeta,DeltaTime,Speed_Apertura);
	
	
	FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);
	
	
	DoorMesh->SetWorldRotation(OpenRotationContinua);
	
	if(!PuertaAbierta)
	{
		ComponenteSonidoPuerta->SetSound(SonidoAbrirPuerta);
		ComponenteSonidoPuerta->Play();
		UE_LOG(LogTemp,Warning,TEXT("Sonido abrir Puerta ,"));
		PuertaAbierta=true;		
		
	}
	
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float siguientePasoEnElGiro=FMath::FInterpTo(DoorMesh->GetComponentRotation().Yaw,InicialZeta,DeltaTime,Speed_Cierre);
	FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);	
	
	DoorMesh->SetWorldRotation(OpenRotationContinua);
	UE_LOG(LogTemp,Warning,TEXT("estoy cerrando"));
	if(PuertaAbierta)
	{
		ComponenteSonidoPuerta->SetSound(SonidoCerrarPuerta);
		ComponenteSonidoPuerta->Play();
		UE_LOG(LogTemp,Warning,TEXT("Sonido cerrar Puerta "));
		PuertaAbierta=false;	
		
	}
	

	
}

