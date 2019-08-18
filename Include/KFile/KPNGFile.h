#pragma once
#include "KCore/KDef.h"
#include "KCore/KImage.h"
#include <string>

namespace KFile
{
	class KLIB_EXPORT KPNGFile
	{
	private:
		KPNGFile() {};
		~KPNGFile() {};
	public:
		static int Read(KCore::KImage &img, const char* filePath);
	};
}