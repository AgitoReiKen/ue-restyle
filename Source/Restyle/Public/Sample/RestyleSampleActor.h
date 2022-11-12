#pragma once

#include "CoreMinimal.h"
#include "RestyleSampleActor.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class URestyleSampleInterface : public UInterface
{
	GENERATED_BODY()
};

class IRestyleSampleInterface
{
	GENERATED_BODY()
public:
	virtual bool InterfaceImplementableEvent() = 0;
	virtual bool InterfaceNativeEvent() = 0;
};

DECLARE_DELEGATE_RetVal(bool, FRestyleSampleDelegate)
UCLASS(BlueprintType)
class ARestyleSample : public AActor, public IRestyleSampleInterface
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintAuthorityOnly)
	void ImplementableEventAuthority(bool bResult);

	UFUNCTION(BlueprintImplementableEvent, BlueprintInternalUseOnly)
	void ImplementableEventInternal(bool bResult);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool InterfaceImplementableEvent();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool InterfaceNativeEvent() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetProtectedProperty() const
	{
		return ProtectedProperty;
	}

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void AuthorityFunction()
	{
	}

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void BlueprintCosmeticFunction()
	{ 
	}

	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly)
	void BlueprintInternalUseOnlyFunction()
	{
	}
#if WITH_EDITORONLY_DATA
	UFUNCTION(BlueprintCallable)
	void EditorFunction()
	{
	}
#endif
	UFUNCTION(BlueprintCallable, Client, Reliable)
	void ClientReliableFunction();
	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void ClientUnreliableFunction();
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ServerReliableFunction();
	UFUNCTION(BlueprintCallable, Server, Unreliable)
	void ServerUnreliableFunction();
	UFUNCTION(BlueprintCallable, CallInEditor)
	void CallInEditorFunction()
	{
	}

	FRestyleSampleDelegate SampleDelegate;
private:
	UPROPERTY(BlueprintGetter=GetProtectedProperty)
	int ProtectedProperty;
};
