// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuSystem/MenuWidgetBase.h"
#include "MainMenu.generated.h"


class USystemButton;
class UWidgetSwitcher;
class UButton;
class UEditableText;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORM_API UMainMenu : public UMenuWidgetBase
{
	GENERATED_BODY()
	
public:
	// 위젯 생성자 : 놀랍게도 이거 CreateWidget 이 아니라 AddToViewport 해야 실행이 된다. 이걸 해야 UObject로 관리가 되는 것 같다.
	//virtual void NativeConstruct() override;

	// 위젯 소멸자
	virtual void NativeDestruct() override;

	// 기본적인 버튼 이벤트 동적 바인딩은 여기서 수행해야 한다.
	virtual bool Initialize() override;
	
private:
	// 호스팅 시작
	UFUNCTION()
	void HostServer();

	// Join 메뉴에 진입
	UFUNCTION()
	void OpenJoinMenu();

	// 실제 호스트 서버에 Join
	UFUNCTION()
	void JoinRoom();

	UFUNCTION()
	void QuitGame();

	// 메인 메뉴로 돌아가기
	UFUNCTION()
	void GoBack();

private:
	// 예를 들어 위젯 그룹처럼 특정 유형의 위젯이 아니라 어떤 위젯이든 상관 없는 경우에는 최상위 위젯 클래스인 UWidget 을 쓰면 좋다.
	UPROPERTY(Meta = (BindWidget))
	UWidget* MainMenu;

	UPROPERTY(Meta = (BindWidget))
	UWidget* JoinMenu;

	UPROPERTY(Meta = (BindWidget))
	USystemButton* WBP_SystemButton_CreateRoom;

	UPROPERTY(Meta = (BindWidget))
	USystemButton* WBP_SystemButton_JoinMenu;

	UPROPERTY(Meta = (BindWidget))
	USystemButton* WBP_SystemButton_QuitGame;

	UPROPERTY(Meta = (BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(Meta = (BindWidget))
	UButton* Button_Back;

	UPROPERTY(Meta = (BindWidget))
	USystemButton* WBP_SystemButton_Join;

	UPROPERTY(Meta = (BindWidget))
	UEditableText* EditableText_IpAddr;


};
