// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationManager.h"
#include "Particle.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ASimulationManager::ASimulationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    particleAmount = 10;
    ScreenSize = 1000;
    ScreenRepresentation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Screen Representation Mesh, use the default floor"));
    SetRootComponent(ScreenRepresentation);
}

// Called when the game starts or when spawned
void ASimulationManager::BeginPlay()
{
	Super::BeginPlay();
    //400 is the size of the default floor
    FVector scale(ScreenSize / 400, ScreenSize / 400, 0);
    //Location should be 0 since everything gets calculated from the 0 coordinate
    FVector location(0, 0, 0);
    //Set the visual representation of the screen
    ScreenRepresentation->SetWorldScale3D(scale);
    ScreenRepresentation->SetWorldLocation(location);
    for (int i = 0; i < particleAmount; i++)
    {
        AParticle* particle = GetWorld()->SpawnActor<AParticle>(ParticleClass);
        particle->SetFieldSize(ScreenSize);
        particlesArr.Add(particle);
       
    }
}

// Called every frame
void ASimulationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    UpdateParticles(particlesArr);

}

void ASimulationManager::UpdateParticles(TArray<AParticle*> particles)
{

    for (int i = 0; i < particleAmount; i++) {
        particles[i]->ResetAccel();
        for (int j = 0; j < particleAmount; j++) {
            if (i == j) continue;
            //Get the mass of two particles
            double massi = particles[i]->GetMass();
            double massj = particles[j]->GetMass();
            //Calculate the distance between two particles
            double dx = particles[j]->GetX() - particles[i]->GetX();
            double dy = particles[j]->GetY() - particles[i]->GetY();
            double dist = sqrt(dx * dx + dy * dy);
            //Newton's law of universal gravitation
            double force = G * massi * massj / dist; // dist^2 if 3d gravity
            //Create a 2d vector for the applied acceleration
            FVector2D accelToApply(force * dx / dist / massi, force * dy / dist / massi);
            particles[i]->SetAccel(accelToApply);
        }
    }
}

