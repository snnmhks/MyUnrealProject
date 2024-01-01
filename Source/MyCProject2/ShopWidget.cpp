// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "MyLevelScript.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController »ç¿ë

void UShopWidget::NativeOnInitialized() {
	MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	Damage->OnPressed.AddDynamic(this, &UShopWidget::DamageUpgrade);
	Finish->OnPressed.AddDynamic(this, &UShopWidget::EndUpgrade);
}

void UShopWidget::DamageUpgrade() {
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		MyPlayer->BaseDamage += 1;
	}
}

void UShopWidget::EndUpgrade() {
	Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->EndShop();
}