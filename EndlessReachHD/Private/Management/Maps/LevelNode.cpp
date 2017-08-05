// © 2014 - 2017 Soverance Studios
// http://www.soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "EndlessReachHD.h"
#include "EndlessReachHDGameMode.h"
#include "EndlessReachHDPawn.h"
#include "LevelNode.h"

// Sets default values
ALevelNode::ALevelNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates a scene component and sets it as the root
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;
	
	// configure Node Entry Radius
	NodeEntryRadius = CreateDefaultSubobject<USphereComponent>(TEXT("NodeEntryRadius"));
	NodeEntryRadius->SetupAttachment(RootComponent);
	NodeEntryRadius->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	NodeEntryRadius->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	NodeEntryRadius->OnComponentBeginOverlap.AddDynamic(this, &ALevelNode::OnOverlap);
	NodeEntryRadius->SetSphereRadius(250);
	NodeEntryRadius->SetSimulatePhysics(true);
	NodeEntryRadius->BodyInstance.bLockZTranslation = true;
	RootComponent = NodeEntryRadius;

	// Portal Visual Effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> NodePortalParticleObject(TEXT("/Game/VectorFields/Particles/P_Gateway.P_Gateway"));
	P_NodePortalFX = NodePortalParticleObject.Object;
	NodePortalFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("NodePortalFX"));
	NodePortalFX->SetupAttachment(RootComponent);
	NodePortalFX->Template = P_NodePortalFX;
	NodePortalFX->SetRelativeRotation(FRotator(0, 0, 0));
	NodePortalFX->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	NodePortalFX->bAutoActivate = false;

	// Teleport Visual Effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> NodeTeleportParticleObject(TEXT("/Game/VectorFields/Particles/P_Wormhole.P_Wormhole"));
	P_NodeTeleportFX = NodeTeleportParticleObject.Object;
	NodeTeleportFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("NodeTeleportFX"));
	NodeTeleportFX->SetupAttachment(RootComponent);
	NodeTeleportFX->Template = P_NodeTeleportFX;
	NodeTeleportFX->SetWorldRotation(FRotator(0, 0, 90));
	NodeTeleportFX->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	NodeTeleportFX->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ALevelNode::BeginPlay()
{
	Super::BeginPlay();
	
	// if the level is unlocked, then activate the portal to show this node on the map
	if (!LevelConfig.bIsLocked)
	{
		NodePortalFX->Activate();
	}
}

// Called every frame
void ALevelNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelNode::OnOverlap(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AEndlessReachHDPawn* HitPlayer = Cast<AEndlessReachHDPawn>(OtherActor);  // Check if hit actor is the player

		// Proceed with functions if you hit the player
		if (HitPlayer)
		{
			// Make sure it's actually the player ship, and not the bullets
			if (OtherComp == HitPlayer->ShipMeshComponent)  
			{
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("PLAYER HAS ENTERED A STREAMING WORMHOLE"));

				// if the level is unlocked, allow it to proceed
				if (!LevelConfig.bIsLocked)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, TEXT("Wormhole Status:  Unlocked"));

					// ensure this node is not currently in use
					if (!bInUse)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Emerald, TEXT("Wormhole Status:  Now in use..."));
						bInUse = true;  // flag in use
						
						AEndlessReachHDGameMode* GameMode = Cast<AEndlessReachHDGameMode>(GetWorld()->GetAuthGameMode());  // collect game mode reference
						// TO DO:  Start Teleport Sequence
						NodePortalFX->Deactivate();  // deactivate portal FX
						NodeTeleportFX->Activate();  // activate wormhole FX
						GameMode->UnloadMap(GameMode->GetMapName(GameMode->CurrentMap), GameMode->CurrentMap);  // unload the current map
						// TO DO:  Delay a few seconds then load the map which corresponds to this node
						// TO DO:  Set GameMode->CurrentMap to the value stored in LevelConfig.NodeNumber
					}
				}
			}
		}
	}
}