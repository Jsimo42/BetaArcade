//@AdamBirch 15/10/19

#include "TestItem.h"


// Sets default values
ATestItem::ATestItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = Mesh;

	

}

// Called when the game starts or when spawned
void ATestItem::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATestItem::OnOverlapStart);
}

void ATestItem::OnOverlapStart(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Mesh->SetVisibility(false);
	this->SetActorLocation(FVector(0, 0, 0));
}

// Called every frame
void ATestItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Float(DeltaTime);

}

void ATestItem::Float(float DeltaTime) //while item is alive moves up and down and (TODO: rotates)
{
	UPROPERTY(VisableAnywhere, Category = Movement)
	FVector CurrentLocation;
	CurrentLocation = this->GetActorLocation();
	if (CurrentLocation.Z > MaxHeight)//TODO: set as an offset from minheight 
	{
		speed = -speed;
	}
	if (CurrentLocation.Z < MinHeight)//TODO: set as spawn height
	{
		speed = -speed;
	}
	SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, (CurrentLocation.Z + (speed*DeltaTime))));
}