#pragma once
#include "KCore/KDef.h"
#include <string>
namespace KFile 
{
	class KLIB_EXPORT KSringFile
	{
	private:
		KSringFile() {};
		~KSringFile() {};
	public:
		static int Read(std::string &strbuff, const char* filePath);
	};
}