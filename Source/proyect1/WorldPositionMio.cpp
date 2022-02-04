// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPositionMio.h"

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

	
	UE_LOG(LogTemp,Warning,TEXT("Esto es un Warning"));
	
}


// Called every frame
void UWorldPositionMio::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

