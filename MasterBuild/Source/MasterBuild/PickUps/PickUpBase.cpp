//@AdamBirch 15/10/19
#include "PickUpBase.h"
#include "Sheep/SheepCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/Material.h"
#include "AI/Navigation/NavigationSystem.h"



// Sets default values
APickUpBase::APickUpBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	//Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}



FString APickUpBase::GetBuffType()
{
	return BuffType;
}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	SetReplicateMovement(true);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnOverlapStart);

	MinHeight = this->GetActorLocation().Z + 20;
	MaxHeight = MinHeight + FloatDistance;

	Mesh->SetVisibility(false);

	RandomPosition.GenerateNewSeed();
}

void APickUpBase::OnOverlapStart(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor->IsA(ASheepCharacter::StaticClass())))
	{
		return;
	}

	Mesh->SetVisibility(false);
	this->SetActorLocation(FVector(-10000, -10000, 0));
	isAlive = false;
	TSincePickUP = 0;
}

// Called every frame
void APickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		Float(DeltaTime);
		Respawn(DeltaTime);
	}
}

void APickUpBase::Float(float DeltaTime) //while item is alive moves up and down and (TODO: rotates)
{
	if (isAlive == true)
	{
		UPROPERTY(VisableAnywhere, Category = Movement)
			FVector CurrentLocation;

		CurrentLocation = this->GetActorLocation();

		if (CurrentLocation.Z > MaxHeight)
		{
			speed = -100;
		}
		else if (CurrentLocation.Z < MinHeight)
		{
			speed = 100;
		}

		SetActorLocation(FVector(CurrentLocation.X, CurrentLocation.Y, (CurrentLocation.Z + (speed * DeltaTime))));
	}
	
}

void APickUpBase::Respawn(float DeltaTime)
{
	TSincePickUP += 10 * DeltaTime;
	if (isAlive == false && TSincePickUP >=200)
	{
		UNavigationSystem *navsys = UNavigationSystem::GetCurrent(GetWorld());

		FNavLocation Randomlocation;

		navsys->GetRandomReachablePointInRadius(FVector(-30, -60, MaxHeight), 1000.f, Randomlocation, navsys->MainNavData);

		this->SetActorLocation(Randomlocation.Location);
		//this->SetActorLocation(FVector((RandomPosition.FRandRange(-340, 360)), (RandomPosition.FRandRange(-700, 570)), MinHeight));
		Mesh->SetVisibility(true);
		isAlive = true;
	}
}
