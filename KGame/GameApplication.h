#pragma once
#include "KGraphic/KGraphic.h"

using namespace KGraphic;
class GameApplication : public KGLWindowApplication
{
public:
	GameApplication(int width, int height, const std::wstring title);
	~GameApplication();

	virtual int Initialize();
	virtual void Finalize();
	virtual int Render();
	virtual void FrameMessageFun(MSG &msg);
private:
	int LoadScene(KScene *scene);
	void SettingUserMaterial(KMaterial *material, GLuint text);
private:
	KScene *m_scene;
};

