#pragma once

#include "Containers/UnrealString.h"
#include "Enums.h"

namespace EnumUtils
{
	FString GetResourceName(EResourceType resourceType)
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
	}
}
