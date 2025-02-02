// Fill out your copyright notice in the Description page of Project Settings.

#include "Char_Wolf.h"


// Sets default values
AChar_Wolf::AChar_Wolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollider"), false);
	
	
}

// Called when the game starts or when spawned
void AChar_Wolf::BeginPlay()
{
	Super::BeginPlay();
	SetupOverlapEvents();
	
	AttackCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

//on collision with another object run this
void AChar_Wolf::OnOverlapStart(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//TODO: Check if CurrentItem is empty if not skip.
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(APickUpBase::StaticClass()))
	{
		CurrentItem = Cast<APickUpBase>(OtherActor);
		if (CurrentItem->GetBuffType() == "")
		{
			return;
		}
		if (CurrentItem->GetBuffType() == "SpeedBoost")
		{
			SpeedBoosted = true;
		}
		if (CurrentItem->GetBuffType() == "SlowDown")
		{

			Slowed = true;
		}
		if (CurrentItem->GetBuffType() == "BigMode")
		{
			this->SetActorScale3D(FVector(3, 3, 3));
		}
		// sets current item to the lest overlapped item. Could call something here to get item type and activate power up
	}
}

void AChar_Wolf::OnEnemyOverlapStart(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (isAttacking)
	{
		if (OtherActor && (OtherActor != this) && OtherComp->GetClass()->IsChildOf(UCapsuleComponent::StaticClass()) && OtherActor->GetClass()->IsChildOf(ASheepCharacter::StaticClass()))
		{
			
			if (OtherActor->bCanBeDamaged)
			{
				Points++;
				OtherActor->Destroy();
			}
		}
	}
}

void AChar_Wolf::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		CurrentItem = nullptr;
		TSincePickUP = 0;
	}
}

void AChar_Wolf::OnEnemyOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void AChar_Wolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentItem == NULL)
	{
		TSincePickUP += (10 * DeltaTime);
	}
	if (CurrentItem == NULL && TSincePickUP >= 100)
	{
		this->SetActorScale3D(FVector(1, 1, 1));
		SpeedBoosted = false;
		Slowed = false;
	}
}

// Called to bind functionality to input
void AChar_Wolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AChar_Wolf::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AChar_Wolf::StopJumping);
	PlayerInputComponent->BindAction("Sneak", IE_Pressed, this, &AChar_Wolf::Sneak);
	PlayerInputComponent->BindAction("Sneak", IE_Released, this, &AChar_Wolf::StopSneaking);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AChar_Wolf::Attack);

	PlayerInputComponent->BindAxis("MoveForward", this, &AChar_Wolf::MoveForward);
	PlayerInputComponent->BindAxis("TurnRate", this, &AChar_Wolf::TurnRate);
}
//adds dynamic functions for overlaps
void AChar_Wolf::SetupOverlapEvents()
{
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AChar_Wolf::OnOverlapStart);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AChar_Wolf::OnOverlapEnd);
}

void AChar_Wolf::MoveForward(float Value)
{
	if (SpeedBoosted == true)
	{
		moveSpeedMultiplier = 1.0f;
	}
	if (Slowed == true)
	{
		moveSpeedMultiplier = 0.3f;
	}
	Value = Value * moveSpeedMultiplier;

	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

		isMoving = true;
	}

	if (Value == 0.0f)
	{
		isMoving = false;
	}
}

void AChar_Wolf::TurnRate(float Rate)
{
	AddControllerYawInput(Rate * 90 * GetWorld()->GetDeltaSeconds());
}

void AChar_Wolf::Sneak()
{
	isSneaking = true;

	if (SpeedBoosted == false)
	{
		moveSpeedMultiplier = 0.3f;
	}
	if (SpeedBoosted == true)
	{
		moveSpeedMultiplier = 0.8f;
	}
	
}

void AChar_Wolf::StopSneaking()
{
	isSneaking = false;

	if (SpeedBoosted == false)
	{
		moveSpeedMultiplier = 0.8f;
	}
	if (SpeedBoosted == true)
	{
		moveSpeedMultiplier = 1.0f;
	}
}

void AChar_Wolf::Attack()
{
	if (!isSneaking)
	{
		isAttacking = true;

		UE_LOG(LogTemp, Warning, TEXT("Attack"));

		moveSpeedMultiplier = 0;
	}
}

void AChar_Wolf::Jump()
{
	ACharacter::Jump();
	isJumping = true;
}

void AChar_Wolf::StopJumping()
{
	ACharacter::StopJumping();
	isJumping = false;
}
