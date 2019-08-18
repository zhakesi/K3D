#include <iostream>
#include <iostream>
#include <string>
#include "KCore/KImage.h"
#include "GameApplication.h"
#include "KFile/KAssimpFile.h"


int main()
{

	std::wstring title(L"KGame");
	
	GameApplication gameApp(1024, 720, title);
	
	gameApp.Initialize();
	
	gameApp.Run();
	
	gameApp.Finalize();
	
	return 0;
}
