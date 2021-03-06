// 2012 - 2019 Soverance Studios
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

#include "PlayerStatAttribute.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStatAttribute
{
	GENERATED_USTRUCT_BODY()

	// Attribute Name used for legible display
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	FText Name;

	// Whether or not this attribute is currently LOCKED
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	bool Locked;

	// The upgrade cost stored in text form.  Updated with subsequent upgrades.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	FText UpgradeCostText;

	// The orb cost to improve this attribute by one
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	int32 UpgradeCost;

	// The current power level of this attribute - the player must spend orbs on upgrading to improve the level, which increases the effectiveness of the specified attribute
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	int32 CurrentPower;

	// Attribute Unlock Description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	FText UnlockDescription;

	// Attribute Upgrade Description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	FText UpgradeDescription;

	// Attribute Max Description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	FText MaxDescription;

	// Attribute Icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	UTexture2D* Icon;

	// Attribute Preview Art
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	UTexture2D* PreviewImg;
};
