// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/PuzzlePlatformGameInstance.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UPuzzlePlatformGameInstance::Host()
{
	// or GetEngine()
	if (GEngine)
	{
		// Key 가 -1 이면 기존 메세지를 Overwrite 하지 않고 새로운 메세지를 추가한다.
		// 반대로, 0이면 기존 메세지를 덮어쓰고 이 메세지를 출력한다.
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Host Message"));
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