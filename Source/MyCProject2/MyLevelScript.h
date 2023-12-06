// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MyLevelScript.generated.h"

/**
 * 
 */

// 레벨 블루프린트를 c++로 가져온것

UCLASS()
class MYCPROJECT2_API AMyLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AMyLevelScript();

	virtual void BeginPlay() override;
};
