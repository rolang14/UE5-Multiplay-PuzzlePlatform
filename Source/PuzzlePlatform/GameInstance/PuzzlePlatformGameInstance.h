// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "MenuSystem/MenuInterface.h"

#include "PuzzlePlatformGameInstance.generated.h"


class UMenuWidgetBase;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	// 게임 인스턴스 생성자
	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);

	// 필요한 값 세팅용 함수
	virtual void Init() override;

	// Not Necessary cuz Level BP declares this
	//UFUNCTION(BlueprintCallable)
	//void SetupPlayerInput();

	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(BlueprintCallable)
	void LoadPauseMenu();

	// 게임을 호스트하는 명령어
	UFUNCTION(Exec)
	void Host();

	// 호스트 중인 게임 서버에 참여하는 명령어
	UFUNCTION(Exec)
	virtual void JoinServer(const FString& IpAddress) override;

	// 현재 방을 떠나기
	UFUNCTION()
	virtual void LeaveGame() override;

	// 게임 프로그램 종료
	UFUNCTION()
	virtual void QuitGame() override;

private:
	virtual void StartHosting() override;

private:
	TSubclassOf<UMenuWidgetBase> MainMenuWidgetClass;
	TSubclassOf<UMenuWidgetBase> PauseMenuWidgetClass;
};
