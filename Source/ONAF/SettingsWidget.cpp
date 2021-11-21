// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsWidget.h"

#include "MainMenu.h"
#include "SecurityGuardController.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"

void USettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//Checking player controller ref
	check(GetOwningPlayer());
	
	if(TooltipsBox)
	{
		TooltipsBox->OnCheckStateChanged.AddDynamic(this, &USettingsWidget::TooltipsStateChanged);
		TooltipsBox->SetCheckedState(ECheckBoxState::Checked);
	}

	if(ExitBtn)
	{
		ExitBtn->OnClicked.AddDynamic(this, &USettingsWidget::ExitClicked);
	}
	
}

void USettingsWidget::TooltipsStateChanged(bool bIsChecked)
{
	bNeedTooltips = bIsChecked;
}

void USettingsWidget::ExitClicked()
{
	this->RemoveFromParent();
	MainMenuRef->AddToViewport();
}
