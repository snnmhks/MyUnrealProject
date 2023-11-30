// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyParent.h"
#include "Enemy_Bear.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API AEnemy_Bear : public AEnemyParent
{
	GENERATED_BODY()
private:

public:

public:
	AEnemy_Bear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
