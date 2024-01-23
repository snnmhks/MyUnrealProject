// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyParent.h"
#include "Enemy_Grunt.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API AEnemy_Grunt : public AEnemyParent
{
	GENERATED_BODY()
	
private:

public:
	// 타격시 이펙트
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* LDAttackEffect;
	UPROPERTY(VisibleAnywhere)
		class UParticleSystem* HittedEffect;
public:
	AEnemy_Grunt();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	virtual void PlayEffect() override;
	virtual void PlayHittedEffect(FVector SpawnLocation) override;
};
