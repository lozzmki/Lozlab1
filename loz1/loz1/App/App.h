#ifndef APP_H
#define APP_H

#include <Windows.h>

//应用程序主体，进行各种依赖项的初始化和程序循环
class App{
public:
	App(HINSTANCE);
	virtual ~App(){}

	void Run();

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	inline HINSTANCE GetInstance(){return m_hInstance;}
	inline HWND GetWnd(){return m_hWnd;}

protected:
	void Initialize();
	void MainProcess();
	void CleanUp();

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	bool m_bExit;
};

extern App* g_App;

#endif