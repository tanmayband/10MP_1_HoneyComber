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
enum class EVisitorType : uint8
{
	VISITOR,
	CUSTOMER,
	PROTECTOR,
	PROTESTER
};

UENUM()
enum class EDialogueType : uint8
{
	CHAT,
	ASK,
	GIVE
};

UENUM()
enum class EFrameActionType : uint8
{
	PUT_BACK,
	SCRAPE_DUMP,
	SCRAPE_INSERT
};

UENUM()
enum class EFrameAcceptorType : uint8
{
	BEEHIVE,
	DRAINER,
	CENTRIFUGE
};