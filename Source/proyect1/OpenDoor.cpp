// Mario


#include "OpenDoor.h"


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

	
	
	InitialYaw=GetOwner()->GetActorRotation().Yaw;
	TargetYaw=InitialYaw+RotationYaw;
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FRotator CurrentRotation=GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp,Warning,TEXT("%s"),*CurrentRotation.ToString());
	// 14 interpolación
	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp,Warning,TEXT("Yaw es ,%f"),GetOwner()->GetActorRotation().Yaw);
	// para abrir la puerta

	//apertura de la puerta con lerp, dependiente de la velocidad del equipo
	//float siguientePasoEnElGiro=FMath::Lerp(GetOwner()->GetActorRotation().Yaw,TargetYaw,0.01f);
	//FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);

	//apertura de la puerta con FInterpConstantTo, dependiente de deltatime, apertura toda al mismo ritmo
	//float siguientePasoEnElGiro=FMath::FInterpConstantTo(GetOwner()->GetActorRotation().Yaw,TargetYaw,DeltaTime,45);
	//FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);

	//apertura de la puerta con FInterpTo, dependiente de deltatime.

	//Speed=1;
	
	float siguientePasoEnElGiro=FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,TargetYaw,DeltaTime,Speed);
	
	//siguientePasoEnElGiro =siguientePasoEnElGiro+InitialYa;
	
	FRotator OpenRotationContinua(0.0f,siguientePasoEnElGiro,0.0f);

	
	GetOwner()->SetActorRotation(OpenRotationContinua);

	

	

	// ...
}

