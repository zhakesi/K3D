#pragma once
#include "KIRuntime.h"

namespace KCore {
	KInterface KLIB_EXPORT KIApplication
	{
	public:
			virtual int Initialize() = 0;
			virtual void Finalize() = 0;

			virtual int Run() = 0;
	};
}