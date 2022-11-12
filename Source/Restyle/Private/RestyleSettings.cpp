// Alexander (AgitoReiKen) Moskalenko (C) 2022
#include "RestyleSettings.h"
#include "Restyle.h"
#include "Interfaces/IPluginManager.h"

TArray<FName> URestyleSettings::GetNodeProviders()
{
	auto& Restyle = FModuleManager::Get().GetModuleChecked<FRestyleModule>("Restyle");
	return Restyle.GetAvailableSubjectProviderOptions(ERestyleSubject::Node);
}

TArray<FName> URestyleSettings::GetPinProviders()
{
	auto& Restyle = FModuleManager::Get().GetModuleChecked<FRestyleModule>("Restyle");
	return Restyle.GetAvailableSubjectProviderOptions(ERestyleSubject::Pin);
}

TArray<FName> URestyleSettings::GetWireProviders()
{
	auto& Restyle = FModuleManager::Get().GetModuleChecked<FRestyleModule>("Restyle");
	return Restyle.GetAvailableSubjectProviderOptions(ERestyleSubject::PinConnection);
}
