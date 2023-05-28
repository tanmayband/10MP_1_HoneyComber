#pragma once

#include "Containers/UnrealString.h"
#include "Enums.h"

class EnumUtils
{
public:
	static FString GetResourceName(EResourceType resourceType);

	static const TMap<EResourceType, FString> ResourceToEventName;

	static const EResourceType* EventToResourceName(FString eventName);
};
