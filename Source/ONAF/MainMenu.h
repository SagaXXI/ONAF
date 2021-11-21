// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class ONAF_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	protected:

	void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* ContinueBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* QuitBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SettingsBtn;

	//Create settings widget 
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowSettings();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SubmenuWidgets", meta = (BlueprintProtected = true))
	TSubclassOf<class UUserWidget> SettingsWidget;
	
	UFUNCTION()
	void OnContinueClicked();

	UFUNCTION()
	void OnQuitClicked();

	UFUNCTION()
	void OnSettingsClicked();
};
