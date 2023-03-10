// Copyright Epic Games, Inc. All Rights Reserved.

#include "DFM1Character.h"

#include "DashComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LifeComponent.h"


//////////////////////////////////////////////////////////////////////////
// ADFM1Character

ADFM1Character::ADFM1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraDistance; // The camera follows at this distance behind the character

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	CameraOffset = GetActorLocation() - FollowCamera->GetComponentLocation();
}

void ADFM1Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Reup??ration du component Life
	LifeComponent = FindComponentByClass<ULifeComponent>();
	if(!LifeComponent)
	{
		delete LifeComponent;
		UE_LOG(LogTemp, Error, TEXT("Life Component Not found"));
	}

	//Reup??ration du component Dash
	DashComponent = FindComponentByClass<UDashComponent>();
	if(!DashComponent)
	{
		delete DashComponent;
		UE_LOG(LogTemp, Error, TEXT("Dash Component Not found"));
	}
	
	StartPosition = GetActorLocation();
}

void ADFM1Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CameraBoom->TargetArmLength = (CameraOffset.Z - GetActorLocation().Z) + CameraDistance;
}

/*
 *	Reinitialise la position du personnage, ?? la position de d??part  
 */
void ADFM1Character::ResetSpawn()
{
	SetActorLocation(StartPosition);
}

/*
 * Incr??mente le nombre de collectible
 */
void ADFM1Character::AddCollectible(int32 nbCollectible)
{
	NbCollectible += nbCollectible;
}

/*
 * D??cremente le nombre de collectible
 */
void ADFM1Character::RemoveCollectible(int32 nbCollectible)
{
	NbCollectible -= nbCollectible;
	if(NbCollectible <= 0)
	{
		NbCollectible = 0;
	}
}

int32 ADFM1Character::GetCountCollectible() const
{
	return NbCollectible;
}

/*
 * Fonction de callback, lorsque le personnage tombe dans le vide
 */
void ADFM1Character::FellOutOfWorld(const UDamageType& dmgType)
{
	Trapped();
}

/*
 * Applique un d??gat au personnage et reinitialise la position du personnage
 */
void ADFM1Character::Trapped()
{
	if(!LifeComponent) return;

	LifeComponent->OntakeDamage();

	ResetSpawn();
}


//////////////////////////////////////////////////////////////////////////
// Input

void ADFM1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADFM1Character::Move);
		//Dash
		EnhancedInputComponent->BindAction(DashLeftAction, ETriggerEvent::Triggered, this, &ADFM1Character::LeftDash);
		EnhancedInputComponent->BindAction(DashRightAction, ETriggerEvent::Triggered, this, &ADFM1Character::RightDash);
	}

}

void ADFM1Character::Move(const FInputActionValue& Value)
{
	
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if(DashComponent && DashComponent->IsDashing())
		return;
	
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, 0, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

/*
 * Effectue le dash circulaire vert la gauche
 */
void ADFM1Character::LeftDash()
{
	if(!DashComponent) return;
	DashComponent->SetOrientationDash(OrientationDash::DASH_Left);
	DashComponent->DashMoving();
}

/*
 * Effectue le dash circulaire vert la droite
 */
void ADFM1Character::RightDash()
{
	if(!DashComponent) return;
	DashComponent->SetOrientationDash(OrientationDash::DASH_Right);
	DashComponent->DashMoving();
}
