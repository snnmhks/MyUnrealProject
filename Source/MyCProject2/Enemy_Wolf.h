// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyParent.h"
#include "Enemy_Wolf.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API AEnemy_Wolf : public AEnemyParent
{
	GENERATED_BODY()
	
public:
	AEnemy_Wolf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
};
