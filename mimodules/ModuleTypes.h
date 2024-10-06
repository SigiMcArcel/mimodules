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

	typedef enum class ModuleIOSyncMode_e
	{
		SyncModeNone, //read and write will not called
		SyncModeManager, //Managers timer calls read write
		SyncModeModuleFree, //The module has his own timer, and call it as soon as possible
		SyncModeModuleCyclic //The modul has his own timer and call it cylic
	}ModuleIOSyncMode;

}