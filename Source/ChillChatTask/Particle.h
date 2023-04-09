// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particle.generated.h"

UCLASS()
class CHILLCHATTASK_API AParticle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AParticle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//randomization values
	UPROPERTY(EditDefaultsOnly, Category = Randomization)
		double minX;
	UPROPERTY(EditDefaultsOnly, Category = Randomization)
		double minY;
	UPROPERTY(EditDefaultsOnly, Category = Randomization)
		double maxX;
	UPROPERTY(EditDefaultsOnly, Category = Randomization)
		double maxY;
	UPROPERTY(EditDefaultsOnly, Category = Randomization)
		double minMass;
	UPROPERTY(EditDefaultsOnly, Category = Randomization)
		double maxMass;
	//Static Mesh to display
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
		class UStaticMeshComponent* StaticMesh;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//All of these functions are one liners, so I might as well make them all FORCEINLINE to hopefully speed it up
	FORCEINLINE FVector GetLocation() const {return GetActorLocation();} // Get the x and y of the particle
	FORCEINLINE void SetAccel(FVector2D Accel) { Acceleration = Accel; }   // Set the x and y accel of the particle
	FORCEINLINE void ResetAccel() { Acceleration.Set(0,0); }   // Set the x and y accel of the particle to 0
	FORCEINLINE double GetMass() const { return mass; } // Get the x and y of the particle
	FORCEINLINE double GetX() const { return GetActorLocation().X; } // Get the x of the particle
	FORCEINLINE double GetY() const { return GetActorLocation().Y; } // Get the y of the particle
	FORCEINLINE void SetFieldSize(double fieldSize) { S = fieldSize; } // Set the field Size
	void setX(double newLocationX); //sets the X deprecated
	void setY(double newLocationY); //sets the Y deprecated

	
private:
	//FVector2D Location; // x and y of the particle
	FVector2D Acceleration; // x and y accelaration of the particle
	FVector2D Velocity;     // x and y veloctiy of the particle
	double mass; // the mass of the particle

	double S; // field size
};
