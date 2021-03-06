// © 2012 - 2019 Soverance Studios
// https://soverance.com

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemies/EnemyMaster.h"
#include "Drone.generated.h"

UCLASS()
class ENDLESSREACHHD_API ADrone : public AEnemyMaster
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ADrone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Fire Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* FireAudio;
	USoundCue* S_FireAudio;

	// Death Audio
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UAudioComponent* DeathAudio;
	USoundCue* S_DeathAudio;

	// Explosion FX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	UParticleSystemComponent* ExplosionFX;
	UParticleSystem* P_ExplosionFX;

	// Suicide Flag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	bool bSuicide;

	// DEPRECATED - Enemy-Specific Aggro Function. 
	UFUNCTION(BlueprintCallable, Category = Combat)
	void DroneAggro();

	// Enemy-Specific Attack Function. 
	UFUNCTION(BlueprintCallable, Category = Combat)
	void DroneAttack();

	// Enemy-Specific Death Function. 
	UFUNCTION(BlueprintCallable, Category = Combat)
	void DroneDeath();

	UFUNCTION(BlueprintCallable, Category = Combat)
	void DroneDeathEffects();

	// Enemy-Specific Suicide Function. 
	UFUNCTION(BlueprintCallable, Category = Combat)
	void DroneSuicide();
};
