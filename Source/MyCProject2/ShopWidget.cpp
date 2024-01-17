// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "MyLevelScript.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController »ç¿ë

void UShopWidget::NativeOnInitialized() {
	MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());

	Damage->OnHovered.AddDynamic(this, &UShopWidget::SetExplainDamage);
	Damage->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	Damage->OnPressed.AddDynamic(this, &UShopWidget::DamageUpgrade);

	AttackSpeed->OnHovered.AddDynamic(this, &UShopWidget::SetExplainAttackSpeed);
	AttackSpeed->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	AttackSpeed->OnPressed.AddDynamic(this, &UShopWidget::AttackSpeedUpgrade);

	Defense->OnHovered.AddDynamic(this, &UShopWidget::SetExplainDefence);
	Defense->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	Defense->OnPressed.AddDynamic(this, &UShopWidget::DefenseUpgrade);

	Health->OnHovered.AddDynamic(this, &UShopWidget::SetExplainHealth);
	Health->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	Health->OnPressed.AddDynamic(this, &UShopWidget::HealthUpgrade);

	Energy->OnHovered.AddDynamic(this, &UShopWidget::SetExplainEnergy);
	Energy->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	Energy->OnPressed.AddDynamic(this, &UShopWidget::EnergyUpgrade);

	AutoAttack->OnHovered.AddDynamic(this, &UShopWidget::SetExplainAutoAttack);
	AutoAttack->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);

	MoreGold->OnHovered.AddDynamic(this, &UShopWidget::SetExplainMoreGold);
	MoreGold->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);

	MoreEnemy->OnHovered.AddDynamic(this, &UShopWidget::SetExplainMoreEnemy);
	MoreEnemy->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);

	Finish->OnPressed.AddDynamic(this, &UShopWidget::EndUpgrade);
}

void UShopWidget::DamageUpgrade() {
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			MyPlayer->BaseDamage += 5;
		}
	}
}

void UShopWidget::AttackSpeedUpgrade() {
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (10 > FMath::RandRange(0, 100)) {
			MyPlayer->AttackSpeed += 0.1;
		}
	}
}

void UShopWidget::DefenseUpgrade() {
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			MyPlayer->BaseDefense += 1;
		}
	}
}

void UShopWidget::HealthUpgrade() {
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			MyPlayer->MaxHP += 10;
		}
	}
}

void UShopWidget::EnergyUpgrade() {
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			MyPlayer->MaxMP += 10;
		}
	}
}

void UShopWidget::EndUpgrade() {
	Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->EndShop();
}

void UShopWidget::SetExplainDamage() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Damage"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Plus All Damage +5"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("Damage +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(MyPlayer->BaseDamage)));
}

void UShopWidget::SetExplainAttackSpeed() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Attack Speed"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Attack speed increases by 10% \nMax Speed is 50%"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("Attack Speed +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt((MyPlayer->AttackSpeed - 1)*10)));
}

void UShopWidget::SetExplainDefence() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Defence"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Damage received is reduced by 1"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("Defence +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(MyPlayer->BaseDefense)));
}

void UShopWidget::SetExplainHealth() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Health"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Maximum health increases by 10"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("Health +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(MyPlayer->MaxHP)));
}

void UShopWidget::SetExplainEnergy() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Energy"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Maximum energy increases by 10"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("Energy +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(MyPlayer->MaxMP)));
}

void UShopWidget::SetExplainAutoAttack() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("Auto Attack"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Deals 10 damage to a nearby enemy every 5 seconds.\nMax Auto Attack is 5"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("Auto Attack +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(0)));
}

void UShopWidget::SetExplainMoreGold() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("More Gold"))));
	ExplainUpgrade->SetText(FText::FromString(FString(TEXT("Gold acquisition amount increases by 10%"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("More Gold +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(0)));
}

void UShopWidget::SetExplainMoreEnemy() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	UpgradeTitle->SetText(FText::FromName(FName(TEXT("More Enemy"))));
	ExplainUpgrade->SetText(FText::FromName(FName(TEXT("The number of enemy planes summoned per round increases by 4"))));
	UpgradeName->SetText(FText::FromString(FString(TEXT("More Money +="))));
	UpgradeText->SetText(FText::FromString(FString::FromInt(0)));
}

void UShopWidget::SetGoldText() {
	GoldText->SetText(FText::FromString(FString::FromInt(MyPlayer->UserGold)));
}

void UShopWidget::SetCrystalText() {
	CrystalText->SetText(FText::FromString(FString::FromInt(MyPlayer->UserCrystal)));
}

void UShopWidget::RemoveExplain() {
	ExpainWindow->SetVisibility(ESlateVisibility::Collapsed);
}