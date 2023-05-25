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
			resourceName = "Honey";
			break;
		case EResourceType::WAX:
			resourceName = "Wax";
			break;
		default:
			break;
		}
		return resourceName;
	}
}
