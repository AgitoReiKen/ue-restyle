// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once
#include "Themes/ThemeInterfaces.h"


class FRestyleDefaultTheme final : public IRestyleThemeInterface
{
public:
	virtual ~FRestyleDefaultTheme() override;
	FRestyleDefaultTheme();
	virtual FName GetId() override;
	virtual void Register() override;
	virtual void Unregister() override;
	virtual TSharedPtr<ISubjectRestyleInterface> GetSubjectFactoryProvider(ERestyleSubject ForSubject) override;
	virtual bool IsRegistered(ERestyleSubject Subject) override;
private:  
	bool OnSettingsChanged();
	TSharedPtr<INodeRestyleInterface> NodeFactoryProvider;
	TSharedPtr<IPinRestyleInterface> PinFactoryProvider;
	TSharedPtr<IWireRestyleInterface> WireFactoryProvider;
};
