// Mario


#include "OpenDoor.h"
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
	//FRotator CurrentRotation=GetOwner()->GetActorRotation();

	//UE_LOG(LogTemp,Warning,TEXT("%s"),*CurrentRotation.ToString());

	
	//ej 15
	//FRotator OpenRotation(0.0f,90.0f,0.0f);
	
	//GetOwner()->SetActorRotation(OpenRotation);

	//ej 16

	
	
	InicialZeta=GetOwner()->GetActorRotation().Yaw;
	ObjetivoZeta=InicialZeta+RotationYaw;
	
	
	if (!ActorThatOpenDoor)//si no hay ningún ActorThatOpensDoor (es decir, que sea null) entonces colocamos
							//el DefaultPawn del primer PlayerController del Juego.
		{
		ActorThatOpenDoor=GetWorld()->GetFirstPlayerController()->GetPawn();
		}
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

	if (Presure_Plate->IsOverlappingActor (ActorThatOpenDoor) )//si presionamos el disparador el método IsOverlappingActor
																//devuelve un booleano de ActorThatOpenDoor
	{
		OpenDoor(DeltaTime);
		InitialTimeOpening_TiempoInicialApertura=GetWorld()->GetTimeSeconds();//obtengo el tiempo que estoy en el disparador
	}
	else
	{
		/*ClosingDelay_TiempoDeCierre=GetWorld()->GetTimeSeconds();//empiezo a contar
		if (ClosingDelay_TiempoDeCierre>InitialTimeOpening_TiempoInicialApertura)
		{
			CloseDoor(DeltaTime);
		}*/
		if (GetWorld()->GetTimeSeconds()>(ClosingDelay_TiempoDeCierre+InitialTimeOpening_TiempoInicialApertura))
		{
			CloseDoor(DeltaTime);
		}
		
	}

	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	//FRotator CurrentRotation=GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*CurrentRotation.ToString());
	// 14 interpolación
	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp,Warning,TEXT("Eje zeta es ,%f"),GetOwner()->GetActorRotation().Yaw);
	// para abrir la puerta

	//apertura de la puerta con lerp, dependiente de la velocidad del equipo
	//float siguientePasoEnElGiro=FMath::Lerp(GetOwner()->GetActorRotation().Yaw,TargetYaw,0.01f);
	//apertura de la puerta con lerp, dependiente de la velocidad del equipo, y con DeltaTime se soluciona
	//float siguientePasoEnElGiro=FMath::Lerp(GetOwner()->GetActorRotation().Yaw,TargetYaw,1.0f*DeltaTime);
	//FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);

	//apertura de la puerta con FInterpConstantTo, dependiente de deltatime, apertura toda al mismo ritmo
	//float siguientePasoEnElGiro=FMath::FInterpConstantTo(GetOwner()->GetActorRotation().Yaw,TargetYaw,DeltaTime,45);
	//FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);

	//apertura de la puerta con FInterpTo, dependiente de deltatime.	
	float siguientePasoEnElGiro=FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,ObjetivoZeta,DeltaTime,Speed_Apertura);
	
	
	
	FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);

	
	GetOwner()->SetActorRotation(OpenRotationContinua);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float siguientePasoEnElGiro=FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,InicialZeta,DeltaTime,Speed_Cierre);
	FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);	
	GetOwner()->SetActorRotation(OpenRotationContinua);
}

