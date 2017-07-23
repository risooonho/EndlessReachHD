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
#include "Management/AsteroidManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAsteroidManager::AAsteroidManager()
{
	TotalAsteroids = 50;
	MinDistance = 50;
	MaxDistance = 10000;
	MinScale = 0.2f;
	MaxScale = 1.0f;
	ScaleMultiplier = 1;

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AsteroidMeshAsset(TEXT("/Game/Environment/Meshes/Rocks/SM_Cave_Rock_Med_01a.SM_Cave_Rock_Med_01a"));
	
	// Creates a scene component and sets it as the root
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Asteroid Procedural Generation
	for (int32 i = 0; i < TotalAsteroids; i++)
	{
		// Generate random asteroid settings
		FVector Location = FMath::VRand() * FMath::FRandRange(MinDistance, MaxDistance);  // random location
		FVector CorrectedLocation = FVector(Location.X, Location.Y, 0);  // force Z value to 0 for all asteroid locations (so they're on the same plane as the player)
		FRotator Rotation = FRotator(FMath::FRandRange(-180.0f, 180.0f), FMath::FRandRange(-180.0f, 180.0f), FMath::FRandRange(-180.0f, 180.0f));  // random rotation
		FVector Scale = UKismetMathLibrary::Conv_FloatToLinearColor((ScaleMultiplier * FMath::FRandRange(MinScale, MaxScale)));  // random scale
		// Spawn procedurally generated asteroids
		FString Name = "Asteroid_" + FString::FromInt(i);  // create name string
		FName AsteroidName = FName(*Name);  // convert name to FName
		UStaticMeshComponent* Asteroid = CreateDefaultSubobject<UStaticMeshComponent>(AsteroidName);  // Spawn asteroid
		Asteroid->SetStaticMesh(AsteroidMeshAsset.Object);  // set asteroid mesh
		Asteroid->SetupAttachment(RootComponent);  // attach to root
		Asteroid->SetWorldTransform(FTransform(Rotation, CorrectedLocation, Scale), false);
	}
}

// Called when the game starts or when spawned
void AAsteroidManager::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AAsteroidManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

