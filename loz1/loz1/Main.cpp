#include "App\App.h"
#include "App\Utilities\Common.h"

//Launcher define

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd){

	g_App = new App(hInstance);
	g_App->Run();
	return 0;
}