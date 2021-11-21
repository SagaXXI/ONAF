// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
UCLASS()
class ONAF_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

	//Controls whether player need tooltips or not
	bool bNeedTooltips = true;
	
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCheckBox* TooltipsBox;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitBtn;

	void NativeConstruct() override;

	//Function used to control TooltipsBox state
	UFUNCTION()
	void TooltipsStateChanged(bool bIsChecked);

	UFUNCTION()
	void ExitClicked();

	public:
	//Reference to main menu widget
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMainMenu* MainMenuRef = nullptr;

};
