// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

struct FGraphPanelNodeFactory;
struct FGraphPanelPinConnectionFactory;
struct FGraphPanelPinFactory;

UENUM()
enum class ERestyleSubject
{
	Node,
	Pin,
	/* aka Wire */
	PinConnection
};

class ISubjectRestyleInterface
{
public:
	virtual ~ISubjectRestyleInterface() = default;
	/* Actually used to determine type of class */
	virtual ERestyleSubject GetSubject() = 0;

	/* Register settings */
	virtual void Register() = 0;

	/* Unregister settings */
	virtual void Unregister() = 0;

	/* Update whatever and whenever it needs to */
	virtual void Update() = 0;

	virtual bool IsRegistered() = 0;
};
 
class INodeRestyleInterface : public ISubjectRestyleInterface
{
public:
	virtual TSharedPtr<FGraphPanelNodeFactory> GetFactory() = 0;
};

class IPinRestyleInterface : public ISubjectRestyleInterface
{
public:
	virtual TSharedPtr<FGraphPanelPinFactory> GetFactory() = 0;
};

class IWireRestyleInterface : public ISubjectRestyleInterface
{
public:
	virtual TSharedPtr<FGraphPanelPinConnectionFactory> GetFactory() = 0;
};

class IRestyleThemeInterface
{
public:
	virtual ~IRestyleThemeInterface() = default;
	/**
	 * @return StaticId
	 */
	virtual FName GetId() = 0;
	/**
	 * @brief Called when the first <subject factory providers> was selected by user
	 */
	virtual void Register() = 0;
	/**
	 * @brief Called when last subject factory provider was deselected by user
	 */
	virtual void Unregister() = 0;
	 
	virtual TSharedPtr<ISubjectRestyleInterface> GetSubjectFactoryProvider(ERestyleSubject ForSubject) = 0;
};
