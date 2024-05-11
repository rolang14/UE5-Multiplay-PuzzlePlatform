// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "MenuSystem/SystemButton.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"


// 소멸될 때 UI 및 플레이어 입력 후처리
void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	ClearWidget();
}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;
	if (!WBP_SystemButton_CreateRoom || !WBP_SystemButton_JoinMenu || !WBP_SystemButton_Join || !WBP_SystemButton_QuitGame || !Button_Back) return false;
	if (UButton* CreateRoomBtn = WBP_SystemButton_CreateRoom->ButtonHitArea) CreateRoomBtn->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	if (UButton* JoinRoomBtn = WBP_SystemButton_JoinMenu->ButtonHitArea) JoinRoomBtn->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	if (UButton* JoinBtn = WBP_SystemButton_Join->ButtonHitArea) JoinBtn->OnClicked.AddDynamic(this, &UMainMenu::JoinRoom);
	if (UButton* QuitGame = WBP_SystemButton_QuitGame->ButtonHitArea) QuitGame->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	Button_Back->OnClicked.AddDynamic(this, &UMainMenu::GoBack);

	return false;
}

void UMainMenu::HostServer()
{
	if (MenuInterface)
	{
		MenuInterface->StartHosting();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (WidgetSwitcher == nullptr || JoinMenu == nullptr) return;
	WidgetSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::JoinRoom()
{
	if (EditableText_IpAddr == nullptr) return;
	const FString& IpAddr = EditableText_IpAddr->GetText().ToString();
	if (MenuInterface)
	{
		MenuInterface->JoinServer(IpAddr);
	}
}

void UMainMenu::QuitGame()
{
	if (MenuInterface)
	{
		MenuInterface->QuitGame();
	}
}

void UMainMenu::GoBack()
{
	if (WidgetSwitcher == nullptr || MainMenu == nullptr) return;
	WidgetSwitcher->SetActiveWidget(MainMenu);
}
