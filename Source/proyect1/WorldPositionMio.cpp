// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositionMio.h"
#include "GameFramework/Actor.h"

#include "IDetailTreeNode.h"

// Sets default values for this component's properties
UWorldPositionMio::UWorldPositionMio()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPositionMio::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetTransform().GetLocation().ToString());

	
	//UE_LOG(LogTemp,Warning,TEXT("Esto es un Warning"));
	//UE_LOG(LogTemp,Error,TEXT("Esto es un mensaje de ERROR"));
	//UE_LOG(LogTemp,Display,TEXT("Esto es un mensaje DE DISPLAY"));
	
	//FString Log=TEXT("HOLA");
	/*FString* PtroLog= &Log;
	FString NombreObjeto= GetOwner()->GetName();;
	
	int32 longitud1 =Log.Len();
	int32 longitud2 =(*PtroLog).Len();
	int32 longitud3 =PtroLog->Len();*/
	
	/*UE_LOG(LogTemp,Warning,TEXT("%d",longitud1));
	UE_LOG(LogTemp,Warning,TEXT("%d",longitud2));
	UE_LOG(LogTemp,Warning,TEXT("%d",longitud3));
	
	UE_LOG(LogTemp,Warning,TEXT("%s",*Log));
	UE_LOG(LogTemp,Warning,TEXT("%s",**PtroLog));
	*/

	/*UE_LOG(LogTemp,Warning,TEXT("%s",*GetOwner()->GetName()));*/
	//UE_LOG(LogTemp,Warning,TEXT("%s",NombreObjeto));

	
	
	
}


// Called every frame
void UWorldPositionMio::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

