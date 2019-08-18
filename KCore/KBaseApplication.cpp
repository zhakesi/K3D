#include "../Include/KCore/KBaseApplication.h"
#include <iostream>

namespace KCore 
{
	// Parse command line, read configuration, initialize all sub modules
	int KBaseApplication::Initialize()
	{
		m_quit = false;

		return 0;
	}

	// Finalize all sub modules and clean up all runtime temporary files.
	void KBaseApplication::Finalize()
	{
	}

	int KBaseApplication::Run()
	{
		return KR_SUCCESS;
	}

	void KBaseApplication::Quit() 
	{
		m_quit = true;
	}
}
