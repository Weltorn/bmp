#include "My_Engine.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrewInstance,
	PSTR szCmdLine, int iCmdShow)
{
	My_Engine* engine =new My_Engine(hinstance,WIN_CLASS,L"Engine");
	T_Engine::pEngine = engine;

	engine->SetFrame(10);
	engine->StartEngine();
	return 0;
}