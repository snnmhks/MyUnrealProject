// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "MyLevelScript.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h" // GetPlayerController »ç¿ë

void UShopWidget::NativeOnInitialized() {
	Super::NativeOnInitialized();

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

	Invest->OnHovered.AddDynamic(this, &UShopWidget::SetExplainInvest);
	Invest->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	Invest->OnPressed.AddDynamic(this, &UShopWidget::InvestGold);

	Energy->OnHovered.AddDynamic(this, &UShopWidget::SetExplainEnergy);
	Energy->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	Energy->OnPressed.AddDynamic(this, &UShopWidget::EnergyUpgrade);

	AutoAttack->OnHovered.AddDynamic(this, &UShopWidget::SetExplainAutoAttack);
	AutoAttack->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);

	MoreGold->OnHovered.AddDynamic(this, &UShopWidget::SetExplainMoreGold);
	MoreGold->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);
	MoreGold->OnPressed.AddDynamic(this, &UShopWidget::GoldUpgrade);

	MoreEnemy->OnHovered.AddDynamic(this, &UShopWidget::SetExplainMoreEnemy);
	MoreEnemy->OnUnhovered.AddDynamic(this, &UShopWidget::RemoveExplain);

	Finish->OnPressed.AddDynamic(this, &UShopWidget::EndUpgrade);
}

void UShopWidget::DamageUpgrade() {
	AMyCharacter *MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			SetSOFText(true);
			MyPlayer->BaseDamage += 5;
			UpgradeText->SetText(FText::AsNumber(MyPlayer->BaseDamage));
		}
		else {
			SetSOFText(false);
		}
		PlayAnimation(SOF);
	}
}

void UShopWidget::AttackSpeedUpgrade() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (10 > FMath::RandRange(0, 100)) {
			SetSOFText(true);
			MyPlayer->AttackSpeed += 0.1;
			UpgradeText->SetText(FText::AsNumber(MyPlayer->AttackSpeed));
		}
		else {
			SetSOFText(false);
		}
		PlayAnimation(SOF);
	}
}

void UShopWidget::DefenseUpgrade() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			SetSOFText(true);
			MyPlayer->BaseDefense += 1;
			UpgradeText->SetText(FText::AsNumber(MyPlayer->BaseDefense));
		}
		else {
			SetSOFText(false);
		}
		PlayAnimation(SOF);
	}
}

void UShopWidget::HealthUpgrade() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			SetSOFText(true);
			MyPlayer->MaxHP += 10;
			UpgradeText->SetText(FText::AsNumber(MyPlayer->MaxHP));
		}
		else {
			SetSOFText(false);
		}
		PlayAnimation(SOF);
	}
}

void UShopWidget::EnergyUpgrade() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserGold >= 20) {
		MyPlayer->GoldDiff(-20);
		SetGoldText();
		if (50 > FMath::RandRange(0, 100)) {
			SetSOFText(true);
			MyPlayer->MaxMP += 10;
			UpgradeText->SetText(FText::AsNumber(MyPlayer->MaxMP));
		}
		else {
			SetSOFText(false);
		}
		PlayAnimation(SOF);
	}
}

void UShopWidget::GoldUpgrade() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserCrystal >= 1) {
		MyPlayer->CrystalDiff(-1);
		SetCrystalText();
		MyPlayer->AddGoldPercent += 0.1f;
		UpgradeText->SetText(FText::AsNumber(MyPlayer->AddGoldPercent));
	}
}

void UShopWidget::InvestGold() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	if (MyPlayer->UserGold >= 10 && MyPlayer->InvestedGold < 100) {
		MyPlayer->GoldDiff(-10);
		MyPlayer->InvestedGold += 10;
		SetGoldText();
		UpgradeText->SetText(FText::AsNumber(MyPlayer->InvestedGold));
	}
}

void UShopWidget::EndUpgrade() {
	Cast<AMyLevelScript>(GetWorld()->GetLevelScriptActor())->EndShop();
}

void UShopWidget::SetExplainDamage() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(50));
	UpgradeTitle->SetText(FText::FromName("Damage"));
	ExplainUpgrade->SetText(FText::FromName("Plus All Damage +5"));
	UpgradeName->SetText(FText::FromName("Damage +="));
	UpgradeText->SetText(FText::AsNumber(MyPlayer->BaseDamage));
}

void UShopWidget::SetExplainAttackSpeed() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(20));
	UpgradeTitle->SetText(FText::FromName("Attack Speed"));
	ExplainUpgrade->SetText(FText::FromName("Attack speed increases by 10% \nMax Speed is 50%"));
	UpgradeName->SetText(FText::FromName("Attack Speed +="));
	UpgradeText->SetText(FText::AsNumber((MyPlayer->AttackSpeed - 1)*10));
}

void UShopWidget::SetExplainDefence() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(50));
	UpgradeTitle->SetText(FText::FromName("Defence"));
	ExplainUpgrade->SetText(FText::FromName("Damage received is reduced by 1"));
	UpgradeName->SetText(FText::FromName("Defence +="));
	UpgradeText->SetText(FText::AsNumber(MyPlayer->BaseDefense));
}

void UShopWidget::SetExplainHealth() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(50));
	UpgradeTitle->SetText(FText::FromName("Health"));
	ExplainUpgrade->SetText(FText::FromName("Maximum health increases by 10"));
	UpgradeName->SetText(FText::FromName("Health +="));
	UpgradeText->SetText(FText::AsNumber(MyPlayer->MaxHP));
}

void UShopWidget::SetExplainEnergy() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(50));
	UpgradeTitle->SetText(FText::FromName("Energy"));
	ExplainUpgrade->SetText(FText::FromName("Maximum energy increases by 10"));
	UpgradeName->SetText(FText::FromName("Energy +="));
	UpgradeText->SetText(FText::AsNumber(MyPlayer->MaxMP));
}

void UShopWidget::SetExplainAutoAttack() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(100));
	UpgradeTitle->SetText(FText::FromName("Auto Attack"));
	ExplainUpgrade->SetText(FText::FromName("Deals 10 damage to a nearby enemy every 5 seconds.\nMax Auto Attack is 5"));
	UpgradeName->SetText(FText::FromName("Auto Attack +="));
	UpgradeText->SetText(FText::AsNumber(0));
}

void UShopWidget::SetExplainMoreGold() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(100));
	UpgradeTitle->SetText(FText::FromName("More Gold"));
	ExplainUpgrade->SetText(FText::FromName("Gold acquisition amount increases by 10%"));
	UpgradeName->SetText(FText::FromName("More Gold ="));
	UpgradeText->SetText(FText::AsNumber(MyPlayer->AddGoldPercent));
}

void UShopWidget::SetExplainMoreEnemy() {
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(100));
	UpgradeTitle->SetText(FText::FromName("More Enemy"));
	ExplainUpgrade->SetText(FText::FromName("The number of enemy planes summoned per round increases by 4"));
	UpgradeName->SetText(FText::FromName("More Money +="));
	UpgradeText->SetText(FText::AsNumber(0));
}

void UShopWidget::SetExplainInvest() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	ExpainWindow->SetVisibility(ESlateVisibility::Visible);
	SuccessPercentText->SetText(FText::AsNumber(100));
	UpgradeTitle->SetText(FText::FromName("Invest"));
	ExplainUpgrade->SetText(FText::FromName("Heart Stone += Invest * (0.5 ~ 1.5)"));
	UpgradeName->SetText(FText::FromName("Invest ="));
	UpgradeText->SetText(FText::AsNumber(MyPlayer->InvestedGold));
}

void UShopWidget::SetGoldText() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	GoldText->SetText(FText::AsNumber(MyPlayer->UserGold));
}

void UShopWidget::SetCrystalText() {
	AMyCharacter* MyPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	CrystalText->SetText(FText::AsNumber(MyPlayer->UserCrystal));
}

void UShopWidget::SetSOFText(bool _SOF) {
	switch (_SOF) {
	case true:
		SuccessOrFail->SetText(FText::FromName("Success"));
		break;
	case false:
		SuccessOrFail->SetText(FText::FromName("Fail"));
		break;
	}

}

void UShopWidget::RemoveExplain() {
	if (IsPlayingAnimation()) {
		StopAnimation(SOF);
	}
	SuccessOrFail->SetText(FText::FromName(" "));
	ExpainWindow->SetVisibility(ESlateVisibility::Collapsed);
}

