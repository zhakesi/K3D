#pragma once
#include "KDef.h"

namespace KCore {
	KInterface KLIB_EXPORT KIRuntime {
	public:
		virtual ~KIRuntime() {};

		virtual int Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void Tick() = 0;
	};
}
