//@AdamBirch 15/10/19

#pragma once

#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestItem.generated.h"

UCLASS()
class MASTERBUILD_API ATestItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestItem();

	UPROPERTY(EditAnywhere, Category = Body)
		class UStaticMeshComponent* Mesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//movement
	UPROPERTY(EditAnywhere, Category = Movement)
		int speed = 200;

	UPROPERTY(EditAnywhere, Category = Movement)
		float MaxHeight = 0;//TODO: set as an offset from minheight 

	UPROPERTY(EditAnywhere, Category = Movement)
		float MinHeight = 0;//TODO: set as spawn height

	UFUNCTION(BlueprintCallable)
		void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Float(float DeltaTime);
	

	
	
};
