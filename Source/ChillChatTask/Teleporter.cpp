// Fill out your copyright notice in the Description page of Project Settings.

//Deprecated, because this is a slower approach
#include "Teleporter.h"
#include "Components/StaticMeshComponent.h"
#include "Particle.h"
// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Create a static mesh component and set it as the root component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(Mesh);
	//By default the teleporter is X
	isX = true;
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
    exitX = ExitTeleporter->GetActorLocation().X;
    enterX = GetActorLocation().X;
	exitY = ExitTeleporter->GetActorLocation().Y;
	enterY = GetActorLocation().Y;
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if a Particle has overlaped, and if the ExitTeleporter exists
	if (OtherActor->GetClass()->GetName() == "BP_Particle_C" && IsValid(ExitTeleporter))
	{
		//The Particle that hit the teleporter
		AParticle* particle = Cast<AParticle>(OtherActor);
		//Teleport the Particle
		if (isX && enterX > exitX) 
		{
			FVector newLocation(ExitTeleporter->GetActorLocation().X + 50, particle->GetActorLocation().Y, 0);
			particle->SetActorLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("Get teleported by X lol"));
		}
		else if (isX && enterX < exitX)
		{
			FVector newLocation(ExitTeleporter->GetActorLocation().X - 50, particle->GetActorLocation().Y, 0);
			particle->SetActorLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("Get teleported by X lol"));
		}
		else if (!isX && enterY > exitY)
		{
			FVector newLocation(particle->GetActorLocation().X, ExitTeleporter->GetActorLocation().Y + 50, 0);
			particle->SetActorLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("Get teleported by Y lol"));
		}
		else {
			FVector newLocation(particle->GetActorLocation().X, ExitTeleporter->GetActorLocation().Y - 50, 0);
			particle->SetActorLocation(newLocation);
			UE_LOG(LogTemp, Warning, TEXT("Get teleported by Y lol"));
		}
		
	}

}

