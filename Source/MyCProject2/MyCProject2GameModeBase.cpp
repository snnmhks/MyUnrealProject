// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCProject2GameModeBase.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AMyCProject2GameModeBase::AMyCProject2GameModeBase() {
	DefaultPawnClass = AMyCharacter::StaticClass(); // 게임 시작 할 때 어떤 캐릭터를 시작으로 할지 설정
	PlayerControllerClass = AMyPlayerController::StaticClass(); // 게임 시작 할 때 어떤 컨트롤러로 시작할 지 설정
}