// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AParticle::AParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//the default randomization values
	minX = 0;
	minY = 0;
	maxX = 50;
	maxY = 50;
	minMass = 1e10;
	maxMass = 1e12;
	//Create a static mesh component and set it as the root component
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
	//Set the vectors values to 0 just for safety
	FVector2d EmptyVector(0, 0);
	Velocity = EmptyVector;
	Acceleration = EmptyVector;
}

// Called when the game starts or when spawned
void AParticle::BeginPlay()
{
	Super::BeginPlay();
	//init random location
	FVector RandomLocation;
	RandomLocation.X = FMath::RandRange(minX, maxX);
	RandomLocation.Y = FMath::RandRange(minY, maxY);
	RandomLocation.Z = 0.0;
	SetActorLocation(RandomLocation);
	//init random mass
	mass = FMath::RandRange(minMass, maxMass);
}

// Called every frame
void AParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Update Velocity each frame and add it to the location
	Velocity += Acceleration * DeltaTime;

	//Convert the location to 2d
	FVector2D CurrentLocation2d(GetActorLocation());
	CurrentLocation2d += Velocity * DeltaTime;
	//Get the new location in 3d
	//if over one of the edges, reset the X and Y depending on which edge, the Warping mechanic
		while (CurrentLocation2d.X > S)
		{
			CurrentLocation2d.X = CurrentLocation2d.X - S;
		}
		while (CurrentLocation2d.Y > S)
		{
			CurrentLocation2d.Y = CurrentLocation2d.Y - S;
		}
		while (CurrentLocation2d.Y < 0)
		{
			CurrentLocation2d.Y = CurrentLocation2d.Y + S;
		}
		while (CurrentLocation2d.X < 0)
		{
			CurrentLocation2d.X = CurrentLocation2d.X + S;
		}

	
	FVector CurrentLocation(CurrentLocation2d.X, CurrentLocation2d.Y, 0);
	//set the location
	SetActorLocation(CurrentLocation);
	
}
//Deprecated
void AParticle::setX(double newLocationX)
{
	FVector NewLocation(newLocationX, GetActorLocation().Y, 0);
	SetActorLocation(NewLocation);
}
//Deprecated
void AParticle::setY(double newLocationY)
{
	FVector NewLocation(GetActorLocation().X, newLocationY, 0);
	SetActorLocation(NewLocation);
}

