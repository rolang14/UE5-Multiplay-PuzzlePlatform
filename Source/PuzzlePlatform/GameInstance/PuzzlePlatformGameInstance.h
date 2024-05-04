// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzlePlatformGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UPuzzlePlatformGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// 게임 인스턴스 생성자
	UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer);

	// 필요한 값 세팅용 함수
	virtual void Init() override;

	// 게임을 호스트하는 명령어
	UFUNCTION(Exec)
	void Host();

	// 호스트 중인 게임 서버에 참여하는 명령어
	UFUNCTION(Exec)
	void JoinServer(const FString& IpAddress);
};
