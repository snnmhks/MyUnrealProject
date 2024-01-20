// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStartWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCPROJECT2_API UGameStartWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 게임 시작 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* GamePlay;
	// 설명창 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* HowToPlay;
	// 뒤로가기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Back;
	// 게임 시작 창
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* StartWindow;
	// 설명 창
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* HowToPlayWindow;

private:
	// 게임 시작 버튼 누르면 호출될 함수
	UFUNCTION()
		void StartGame();
	// 설명 버튼 누르면 호출될 함수
	UFUNCTION()
		void ShowHowToPlay();
	// 뒤로가기 버튼 누르면 호출될 함수
	UFUNCTION()
		void BackToGamePlay();

protected:
	virtual void NativeOnInitialized() override;
};
