// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"
#include "ItemDataStructure.h"
#include "Engine/DataTable.h"

UItemData::UItemData() {
	// 아이템 데이터 테이블 생성
	static ConstructorHelpers::FObjectFinder<UDataTable> ITEM_DATA_TABLE(
		TEXT("DataTable'/Game/DataTable/ItemDataTable'"));
	if (ITEM_DATA_TABLE.Succeeded()) {
		ItemDataTable = ITEM_DATA_TABLE.Object;
	}
}

void UItemData::SetItemData(FName _ItemName) {
	FItemDataStructure* ItemDataStructures;
	//ItemDataTable->FindRow<FItemDataStructure>(_ItemName, FString(""));
	ItemDataStructures = ItemDataTable->FindRow<FItemDataStructure>(_ItemName, FString(""));
	ItemImage = ItemDataStructures->ItemImage;
	ItemName = ItemDataStructures->ItemName;
}