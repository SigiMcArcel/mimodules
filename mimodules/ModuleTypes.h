#pragma once
#include <string>

namespace mimodule
{
	typedef unsigned char ModuleChar;
	typedef std::string ModuleIOConfiguration;
	typedef uint16_t ModuleBitOffset;
	typedef uint16_t ModuleByteSize;
	enum class ModuleResult
	{
		Ok,
		ErrorRead,
		ErrorWrite,
		ErrorInit,
		ErrorConfInvalidParameter,
		ErrorConfInvalidParameterValue,
		ErrorControl,
		ErrorNotConfigured,
		ErrorNotImplemented,
		ErrorDescriptionNotMatch,
		ErrorConfigurationFileNotFound,
		ErrorInvalidBuffer,
		ErrorBufferRangeExceeded
	};
}