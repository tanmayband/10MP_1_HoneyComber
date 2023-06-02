#include "Utils/Utils.h"
#include "Utils.h"

FString EnumUtils::GetResourceName(EResourceType resourceType)
{
	FString resourceName;
	switch (resourceType)
	{
	case EResourceType::HONEY:
		resourceName = "Honey jars";
		break;
	case EResourceType::WAX:
		resourceName = "Wax jars";
		break;
	default:
		break;
	}
	return resourceName;
};

const EResourceType* EnumUtils::EventToResourceName(FString eventName)
{
	const EResourceType* foundResource = ResourceToEventName.FindKey(eventName);
	return foundResource;
};

const TMap<EResourceType, FString> EnumUtils::ResourceToEventName = {
		{EResourceType::HONEY, "EventHoney"},
		{EResourceType::WAX, "EventWax"},
		{EResourceType::ITEM, "EventItem"}
};
