// Mario


#include "Agarrador.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UAgarrador::UAgarrador()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAgarrador::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();//chequeo el physic handle componente de defaultpawn

	SetupInputComponet();//compruebo el funcionamiento del inputcomponent
	

	

	InputComponet ->BindAction(
	"agarrar",//nombre de la accion
	IE_Pressed,// cuando presiono
	this,//llamo a esta clase
	&UAgarrador::Agarrar
	);

	InputComponet ->BindAction(
	"agarrar",//nombre de la accion
	IE_Released,// cuando suelto
	this,//llamo a esta clase
	&UAgarrador::Soltar
	);

	// ...
	
}
//chequeo el physic handle componente
void UAgarrador::FindPhysicsHandle()
{	
	PhysicsHandle=GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); //esto es para agarrar las cosas
	
	if (!PhysicsHandle)//si no hay un phisichandle muestro un error de que no está
		{
		UE_LOG(LogTemp,Error,TEXT("No se encuentra el physic handle dentro de, %s"),*GetOwner()->GetName());
		}
}

//compruebo el funcionamiento del inputcomponent
void UAgarrador::SetupInputComponet()
{
	InputComponet=GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponet)
	{
		UE_LOG(LogTemp,Error,TEXT("Está el UInputComponent_InputComponet dentro de, %s"),*GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("No se encuentra el UInputComponent_InputComponet dentro de, %s"),*GetOwner()->GetName());
	}	
}


// Called every frame
void UAgarrador::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
	
	// ...
}
void UAgarrador::Agarrar()
{
	
	UE_LOG(LogTemp,Error,TEXT("He pulsado la tecla agarrar, "));
	//obtengo la vista de defaultpawn_BP
	FVector LocalizacionVistaDelJugador;
	FRotator RotacionVistaDelJugador;
	
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(LocalizacionVistaDelJugador,RotacionVistaDelJugador);

	/*UE_LOG(LogTemp,Warning,TEXT("%s"),*LocalizacionVistaDelJugador.ToString());
	UE_LOG(LogTemp,Warning,TEXT("%s"),*RotacionVistaDelJugador.ToString());*/
	
	// dibujamos una linea que vaya desde el jugador hasta una distancia(Reach"alcance de la linea") en función de su rotación

	FVector LineTraceEnd= LocalizacionVistaDelJugador + (RotacionVistaDelJugador.Vector()*AlcanceY);
	
	//UE_LOG(LogTemp,Warning,TEXT("AlcanceY, %s"),*LocalizacionVistaDelJugador.ToString());

	DrawDebugLine(GetWorld(),
		LocalizacionVistaDelJugador,
		LineTraceEnd,
		FColor(0,255,0),
		false,
		0,
		0,
		5.0f);

	//raycast hasta una determinada distancia

	FHitResult Hit;// informacion sobre el golpeo del Ray-tracing

	FCollisionQueryParams TraceParams(//parametros para el ray-tracing
		FName(""),//si los objetos que hacemos ray tracin son los que tengan algun tag(no en nuestro caso, luego vacio)
		false,//si queremos utilizar las coliciones coplejas
		GetOwner()//nos ignoramos a nosotros (defaultpawn_bp)
		);

	bool HasImpactado = GetWorld()->LineTraceSingleByObjectType(//lanzamos el ray tracing
	Hit,//un parametro de salida de tipo hit (lo definimos arriba)
	LocalizacionVistaDelJugador,//inicio del ray-casting
	LineTraceEnd,//final del ray casting
	FCollisionObjectQueryParams(ECC_PhysicsBody), //colisionamos con los elementos que esten en el canal physicsBody
	TraceParams
	);

	AActor* ActorContraElQueImpactaElRaycast=Hit.GetActor();

	
	if (HasImpactado)
	{
		
		UE_LOG(LogTemp,Warning,TEXT("El raycast choca con , %s"),*ActorContraElQueImpactaElRaycast->GetName());
	}
}
void UAgarrador::Soltar()
{
    	
	UE_LOG(LogTemp,Error,TEXT("He soltado lo que agarré, "));
}

