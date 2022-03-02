// Mario

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Agarrador.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROYECT1_API UAgarrador : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAgarrador();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)//para mostrar el elemento en el editor
	float AlcanceY=100.0;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle=nullptr;
	
	UPROPERTY()
	UInputComponent* InputComponet=nullptr;

	void Agarrar();	
	void Soltar();

	void FindPhysicsHandle();
	void SetupInputComponet();

	FHitResult FuncionesAgarrar() const;

	FVector GetObjetosQueAlcanzo() const;
	FVector GetPlayerWorldPosition() const;
};
