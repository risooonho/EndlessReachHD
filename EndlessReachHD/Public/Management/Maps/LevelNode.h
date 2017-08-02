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

#pragma once

#include "GameFramework/Actor.h"
#include "LevelName.h"
#include "LevelNode.generated.h"

USTRUCT(BlueprintType)
struct FLevelStruct
{
	GENERATED_USTRUCT_BODY()

	// Realm Enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	ELevelName LevelName;

	// Realm Name used for legible display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FText NameText;

	// Actual Map Name used for Streaming
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FName MapName;

	// Whether or not this level is currently LOCKED
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	bool Locked;

	// Recommended Player Level for this Realm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 RecLevel;

	// Realm Description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FText Description;

	// List Icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	UTexture2D* ListIcon;

	// Realm Preview Art
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	UTexture2D* RealmPreview;
};

UCLASS()
class ENDLESSREACHHD_API ALevelNode : public AActor
{
	GENERATED_BODY()

	/** The root scene component */
	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;	
	
public:	
	// Sets default values for this actor's properties
	ALevelNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** The root scene component */
	UPROPERTY(Category = Config, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FLevelStruct LevelConfig;	
};
