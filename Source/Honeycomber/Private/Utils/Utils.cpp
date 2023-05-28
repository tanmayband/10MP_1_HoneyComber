#include "Utils/Utils.h"

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


const TMap<EResourceType, FString> EnumUtils::ResourceToEventName = {
		{EResourceType::HONEY, "EventHoney"},
		{EResourceType::WAX, "EventWax"},
		{EResourceType::ITEM, "EventItem"}
};