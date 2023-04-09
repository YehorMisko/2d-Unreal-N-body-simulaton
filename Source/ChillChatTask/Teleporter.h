// Fill out your copyright notice in the Description page of Project Settings.

//Deprecated, because this is a slower approach
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class CHILLCHATTASK_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
		class UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Create a class to store at which teleporter should the particle warp to
	UPROPERTY(EditDefaultsOnly, Category = ExitTeleporter)
		TSubclassOf<ATeleporter> ExitTeleporterClass;
	UPROPERTY(EditAnywhere, Category = ExitTeleporter)
		ATeleporter* ExitTeleporter;

	//Custom Overlap function override for the Mesh
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//A Property to store if the teleporter is X or Y type of teleporter
	UPROPERTY(EditAnywhere, Category = ExitTeleporter)
	bool isX;
	//Variables for the enter and exits X and Y 
	double exitX;
	double enterX;
	double exitY;
	double enterY;
};
