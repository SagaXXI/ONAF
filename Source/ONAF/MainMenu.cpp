// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "SettingsWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if(ContinueBtn)
	{
		ContinueBtn->OnClicked.AddDynamic(this, &UMainMenu::OnContinueClicked);
	}

	if(QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);
	}

	if(SettingsBtn)
	{
		SettingsBtn->OnClicked.AddDynamic(this, &UMainMenu::OnSettingsClicked);
	}
	//Checking the player controller because we will be using it a lot in the code of this class
	check(GetOwningPlayer());
}

void UMainMenu::OnContinueClicked()
{
	GetOwningPlayer()->bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayer());
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameLevel"));
}

void UMainMenu::OnQuitClicked()
{
	GetOwningPlayer()->ConsoleCommand("quit");
}

void UMainMenu::OnSettingsClicked()
{
	//Creates settings widget
	ShowSettings();
}

void UMainMenu::ShowSettings()
{
	//If settings widget is not shown yet, then creating it
	USettingsWidget* Settings = CreateWidget<USettingsWidget>(this, SettingsWidget, TEXT("Settings"));
	if(Settings)
	{
		Settings->MainMenuRef = this;
		this->RemoveFromParent();
		Settings->AddToViewport();
		/*UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(
		this, GameOver);
		SetShowMouseCursor(true);*/
		UWidgetBlueprintLibrary::SetInputMode_UIOnly(GetOwningPlayer(), Settings);
	}
}