#pragma once

UENUM()
enum class EResourceType : uint8
{
	NONE,
	HONEY,
	WAX,
	ITEM
};

UENUM()
enum class EVisitorype : uint8
{
	VISITOR,
	CUSTOMER,
	PROTECTOR,
	PROTESTER
};

UENUM()
enum class EVisitorDialogue : uint8
{
	BUY,
	SELL,
	CHAT
};