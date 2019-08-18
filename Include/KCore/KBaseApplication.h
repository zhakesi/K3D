#pragma once
#include "KIApplication.h"

namespace KCore {
	class KLIB_EXPORT KBaseApplication : public KIApplication
	{
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual int Run();
		virtual void Quit();
	protected:
		bool m_quit;
	};
}