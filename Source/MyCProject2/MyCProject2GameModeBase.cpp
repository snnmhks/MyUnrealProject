// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyCProject2GameModeBase.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AMyCProject2GameModeBase::AMyCProject2GameModeBase() {
	DefaultPawnClass = AMyCharacter::StaticClass(); // ���� ���� �� �� � ĳ���͸� �������� ���� ����
	PlayerControllerClass = AMyPlayerController::StaticClass(); // ���� ���� �� �� � ��Ʈ�ѷ��� ������ �� ����
}