// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "MyLevelScript.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController 사용

void UShopWidget::NativeOnInitialized() {
	MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	Damage->OnHovered.AddDynamic(this, &UShopWidget::SetExplainDamage);
	Damage->OnPressed.AddDynamic(this, &UShopWidget::DamageUpgrade);
	Finish->OnPressed.AddDynamic(this, &UShopWidget::EndUpgrade);
}

void UShopWidget::DamageUpgrade() {
	UE_LOG(LogTemp, Log, TEXT("Click"));
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		MyPlayer->BaseDamage += 1;
	}
}

void UShopWidget::EndUpgrade() {
	Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->EndShop();
}

void UShopWidget::SetExplainDamage() {
	UE_LOG(LogTemp, Log, TEXT("Hovered"));
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Damage"))));
	ExplainUpgrade->SetText(FText::FromName(FName(TEXT("모든 데미지에 5를 추가한다."))));
}