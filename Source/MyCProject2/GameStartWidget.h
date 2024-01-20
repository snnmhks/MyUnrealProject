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
	// ���� ���� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* GamePlay;
	// ����â ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* HowToPlay;
	// �ڷΰ��� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Back;
	// ���� ���� â
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* StartWindow;
	// ���� â
	UPROPERTY(meta = (BindWidget))
		class UCanvasPanel* HowToPlayWindow;

private:
	// ���� ���� ��ư ������ ȣ��� �Լ�
	UFUNCTION()
		void StartGame();
	// ���� ��ư ������ ȣ��� �Լ�
	UFUNCTION()
		void ShowHowToPlay();
	// �ڷΰ��� ��ư ������ ȣ��� �Լ�
	UFUNCTION()
		void BackToGamePlay();

protected:
	virtual void NativeOnInitialized() override;
};
