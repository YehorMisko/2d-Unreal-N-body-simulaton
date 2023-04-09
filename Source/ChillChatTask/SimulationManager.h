// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulationManager.generated.h"

class AParticle;
UCLASS()
class CHILLCHATTASK_API ASimulationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulationManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//randomization values

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Array of particles
	TArray<AParticle*> particlesArr;
	//Amount of particles
	UPROPERTY(EditDefaultsOnly, Category = Customization)
		int particleAmount;
	// const gravity
	const double G = 6.6743e-11; 
	//The particle class that is going to be spawned
	UPROPERTY(EditDefaultsOnly, Category = Customization)
		TSubclassOf<AParticle> ParticleClass;
	//update the acceleration of each particle
	void UpdateParticles(TArray<AParticle*> particles);

	UPROPERTY(EditDefaultsOnly, Category = Customization)
		double ScreenSize;

	UPROPERTY(EditDefaultsOnly, Category = Customization)
		class UStaticMeshComponent* ScreenRepresentation;
};
