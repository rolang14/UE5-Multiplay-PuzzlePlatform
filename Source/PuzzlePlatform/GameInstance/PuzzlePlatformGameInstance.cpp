// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PuzzlePlatformGameInstance.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuWidgetBase.h"


UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UMenuWidgetBase> MenuWidgetClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuWidgetClass.Class == nullptr) return;

	MainMenuWidgetClass = MenuWidgetClass.Class;

	static ConstructorHelpers::FClassFinder<UMenuWidgetBase> PauseWidgetClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
	if (PauseWidgetClass.Class == nullptr) return;

	PauseMenuWidgetClass = PauseWidgetClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

//void UPuzzlePlatformGameInstance::SetupPlayerInput()
//{
//	APlayerController* PlayerController = GetFirstLocalPlayerController();
//	if (PlayerController == nullptr) return;
//}

void UPuzzlePlatformGameInstance::LoadMainMenu()
{
	if (MainMenuWidgetClass == nullptr) return;

	UMenuWidgetBase* MainMenuWidget = CreateWidget<UMenuWidgetBase>(this, MainMenuWidgetClass);
	if (MainMenuWidget == nullptr) return;

	MainMenuWidget->SetMenuInterface(this);
	MainMenuWidget->SetUp();
}

void UPuzzlePlatformGameInstance::LoadPauseMenu()
{
	if (PauseMenuWidgetClass == nullptr) return;

	UMenuWidgetBase* PauseMenuWidget = CreateWidget<UMenuWidgetBase>(this, PauseMenuWidgetClass);
	if (PauseMenuWidget == nullptr) return;

	PauseMenuWidget->SetMenuInterface(this);
	PauseMenuWidget->SetUp();
}

void UPuzzlePlatformGameInstance::Host()
{
	// or GetEngine()
	if (GEngine)
	{
		// Key 가 -1 이면 기존 메세지를 Overwrite 하지 않고 새로운 메세지를 추가한다.
		// 반대로, 0이면 기존 메세지를 덮어쓰고 이 메세지를 출력한다.
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Ready for Hosting . . ."));
	}

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	// 리슨 서버로 호스팅
	World->ServerTravel(TEXT("/Game/PuzzlePlatform/Maps/PuzzleMap1?listen"));
}

void UPuzzlePlatformGameInstance::JoinServer(const FString& IpAddress)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Joining to %s ..."), *IpAddress));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->ClientTravel(IpAddress, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::LeaveGame()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Leave Game"));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr) return;

	// 이렇게 하면 서버 쪽에서는 자동으로 클라이언트의 연결을 해제하게 된다.
	PlayerController->ClientTravel(TEXT("/Game/PuzzlePlatform/Maps/MainMenu"), ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr) return;

	PlayerController->ConsoleCommand(TEXT("quit"));
}

void UPuzzlePlatformGameInstance::StartHosting()
{
	UE_LOG(LogTemp, Display, TEXT("Start Hosting in GameInstance . . ."));
	Host();
}
