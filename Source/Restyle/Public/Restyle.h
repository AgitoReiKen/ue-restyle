// Alexander (AgitoReiKen) Moskalenko (C) 2022

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyle.h"
#include "RestyleSettings.h"

#include "Themes/ThemeInterfaces.h"

UENUM()
enum class ERestyleThemeChange
{
	Added,
	Removed
};

struct FSubjectProviderChange
{
	ERestyleSubject Subject;
	FName Id;
	ERestyleThemeChange Change;
};

struct RestyleThemeSPtrKeyFuncs : BaseKeyFuncs<TSharedPtr<IRestyleThemeInterface>,
                                               TSharedPtr<IRestyleThemeInterface>, false>
{
	typedef typename TTypeTraits<TSharedPtr<IRestyleThemeInterface>>::ConstPointerType KeyInitType;
	typedef typename TCallTraits<TSharedPtr<IRestyleThemeInterface>>::ParamType ElementInitType;

	/**
	 * @return The key used to index the given element.
	 */
	static FORCEINLINE KeyInitType GetSetKey(ElementInitType Element)
	{
		return Element;
	}

	/**
	 * @return True if the keys match.
	 */
	static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)
	{
		return A->GetId() == B->GetId();
	}


	/** Calculates a hash index for a key. */
	static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)
	{
		return GetTypeHash(Key);
	}

	/** Calculates a hash index for a key. */
	template <typename ComparableKey>
	static FORCEINLINE uint32 GetKeyHash(ComparableKey Key)
	{
		return GetTypeHash(Key);
	}
};

class RESTYLE_API FRestyleModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	void Load();
	virtual void ShutdownModule() override;
public:
	void RegisterTheme(TSharedPtr<IRestyleThemeInterface> Theme);
	void UnregisterTheme(const FName& Id);
	void SetSubjectProvider(ERestyleSubject Subject, const FName& Id);
	TSharedPtr<ISubjectRestyleInterface> TryGetSubjectProvider(const FName& ThemeId, ERestyleSubject Subject);
	TSharedPtr<IRestyleThemeInterface> GetThemeById(const FName& Id);
	TArray<FName> GetAvailableSubjectProviderOptions(ERestyleSubject Subject);
private:
	/**
	 * @brief 
	 * @param Subject uses from SubjectProviders[Subject]
	 * @param Provider not null
	 * @param bRegister if (true) { Register } else UnRegister 
	 */
	void SetFactory(ERestyleSubject Subject, TSharedPtr<ISubjectRestyleInterface> Provider, bool bRegister = true);
	void RegisterCommands();
	void UnregisterCommands();
	void RegisterSettings();
	void UnregisterSettings();
	void RegisterDefaultThemes();

	void CmdRestyle(const TArray<FString>& Args);
	bool OnSettingsChanged();
	void UpdateThemes();
	TMap<FName, ERestyleThemeChange> DetectThemeChanges();
	TSet<TSharedPtr<IRestyleThemeInterface>, RestyleThemeSPtrKeyFuncs> AvailableThemes;
	TMap<ERestyleSubject, FName> SubjectProviders;
	/**
	 * @brief Previous means before user updated the settings
	 */
	TMap<ERestyleSubject, FName> PreviousSubjectProviders;
	FConsoleCommandWithArgsDelegate CmdRestyle_Delegate;
	FRunnableThread* DelayLoadThread;
};

class RESTYLE_API FDelayLoadRunnable : public FRunnable
{
public:
	virtual uint32 Run() override;
};