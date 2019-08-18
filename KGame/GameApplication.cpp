#include "GameApplication.h"
using namespace KMath;



GameApplication::GameApplication(int width, int height, const std::wstring title)
	:KGLWindowApplication(width, height, title)
{

}


GameApplication::~GameApplication()
{

}

int GameApplication::Initialize() 
{
	KGLWindowApplication::Initialize();
	
	m_scene = new KScene();

	LoadScene(m_scene);

	return KR_SUCCESS;
}

void GameApplication::Finalize()
{
	KGLWindowApplication::Finalize();
}

int GameApplication::Render()
{
	float color[] = { 0.0f, 0.0f, 0.0f };
	glClearColor(color[0], color[1], color[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scene->Render();
	
	eglSwapBuffers(m_display, m_surface);

	return KR_SUCCESS;
}

int GameApplication::LoadScene(KScene *scene)
{
	KModel *model = new KModel;
	model->LoadFile("../Assets/Models/DamagedHelmet.gltf");
	model->SetSizeScale(10.0f);

	KTexture *tex = new KTexture("../Assets/Textures/Default_albedo.png");
	KMaterial *material = new KBlinnMaterial();
	SettingUserMaterial(material, tex->txtID);

	KShader *shader = new KShader(
		"../Assets/Shader/blinn.vsh",
		"../Assets/Shader/blinn.fsh");
	material->BindShader(shader);
	model->BlindMaterial(material);
	m_scene->AddModel(model);

	return KR_SUCCESS;
}

void GameApplication::SettingUserMaterial(KMaterial *material, GLuint text)
{
	BlinnMaterialPack material_pack;
	material_pack.ambient_k = 0.1f;
	material_pack.diffuse_k = 1.0f;
	material_pack.specular_k = 0.45f;
	material_pack.shininess = 0.5f;
	material_pack.texID = text;
	material->SetProperty(GRAPH_MATERIAL_BLINN_PROP_PACK, &material_pack);
}

void GameApplication::FrameMessageFun(MSG &msg)
{
	static int downx = 0, downy = 0;
	KCamera *camera = m_scene->GetCamera();
	char key;
	switch (msg.message) {
	case WM_CHAR:
		switch (msg.wParam)
		{
		case 'w':
		case 'W':
			camera->WalkForward(1.0f);
			break;
		case 's':
		case 'S':
			camera->WalkBackward(1.0f);
			break;
		case 'a':
		case 'A':
			camera->WalkLeftward(1.0f);
			break;
		case 'd':
		case 'D':
			camera->WalkRightward(1.0f);
			break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (msg.wParam)
		{
		case VK_LEFT:
			m_scene->RotationY(-1.0f);
			break;
		case VK_RIGHT:
			m_scene->RotationY(1.0f);
			break;
		case VK_UP:
			m_scene->RotationX(-1.0f);
			break;
		case VK_DOWN:
			m_scene->RotationX(1.0f);
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		downx = LOWORD(msg.lParam);
		downy = HIWORD(msg.lParam);
		printf("Press At:(%d,%d)\n", downx, downy);
		break;
	case WM_LBUTTONUP:
		break;
	default:
		break;
	}
}