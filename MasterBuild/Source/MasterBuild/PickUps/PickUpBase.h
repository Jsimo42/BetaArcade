//@AdamBirch 15/10/19

#pragma once

#include "Components/StaticMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS()
class MASTERBUILD_API APickUpBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpBase();

	UPROPERTY(EditAnywhere, Category = Body)
		class UStaticMeshComponent* Mesh;

	//string comparisons really slow but will have to do for now
	//TODO: Change to ENUM but try to do it without launching the collectable to -70000 on the z axis... 
	FString GetBuffType();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//movement
	UPROPERTY(EditAnywhere, Category = Movement)
		int speed;

	UPROPERTY(EditAnywhere, Category = Movement)
		float MaxHeight;//TODO: set as an offset from minheight 

	UPROPERTY(EditAnywhere, Category = Movement)
		float MinHeight;//TODO: set as spawn height
	FString BuffType = "GoldenCloak";
	UFUNCTION(BlueprintCallable)
		void OnOverlapStart(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Float(float DeltaTime);




};