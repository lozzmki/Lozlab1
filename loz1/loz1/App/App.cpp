#include"App.h"
#include"Utilities\Common.h"
#include"Engine\Video\Dx.h"
#include"Engine\ThirdParty\CEGUI\CEGUIHelper.h"
#include"Engine\ThirdParty\LUA\LUAHelper.h"
#include"Engine\Input\GameInput.h"

App* g_App = 0;

App::App(HINSTANCE hInstance){
	m_hInstance = hInstance;
	m_bExit = false;

}

void App::Run(){
	Initialize();
	while(!m_bExit){
		MainProcess();
	}
	CleanUp();
}

void App::Initialize(){
	
	WNDCLASSEX mywnd={
		sizeof(WNDCLASSEX),CS_CLASSDC,App::WndProc,0,0,
		GetModuleHandle( NULL ), NULL, LoadCursor(0, IDC_ARROW), NULL, NULL,
        L"D3D Tester", NULL
	};
	RegisterClassEx(&mywnd);

	m_hWnd = CreateWindow(_T("D3D Tester"), _T("eYEs"),
		WS_POPUP
		/*WS_POPUP*///WS_OVERLAPPEDWINDOW
		,100,100,1280,720,NULL,NULL,m_hInstance,NULL);

	g_d3d = new D3D();

	if(g_d3d->OnInit()){
	
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);
	}else{
		::MessageBox(0, _T("D3D初始化失败"), 0, 0);
		m_bExit = true;
	}

	g_GUI = new CEGUIHelper();

	g_Input = new GameInput(m_hInstance, m_hWnd);

	LUA::initLUA();
	/*
	CEFrame* frame= new CEFrame(0,"WindowsLook/FrameWindow", "testwindow", 
								CEGUI::UVector2( CEGUI::UDim( 0.25f, 0.0f ), CEGUI::UDim( 0.25f, 0.0f ) ),
								CEGUI::USize( CEGUI::UDim( 0.5f, 0.0f ), CEGUI::UDim( 0.5f, 0.0f ) )
								);
	CEPushButton* button= new CETestButton(frame->getWindow(), "WindowsLook/Button", "button",
											CEGUI::UVector2( CEGUI::UDim( 0.25f, 0.0f ), CEGUI::UDim( 0.25f, 0.0f )),
											CEGUI::USize( CEGUI::UDim( 0.5f, 0.0f ), CEGUI::UDim( 0.5f, 0.0f ) )
											);
	*/



	//隐藏硬件鼠标
	ShowCursor(false);
}

void App::MainProcess(){
	MSG msg;
	::ZeroMemory(&msg, sizeof(MSG));

	static float lastTime = (float)GetTickCount();
	static float delta = 0.001f;
	static int count = 0;
	while(msg.message != WM_QUIT){
		if(::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)){
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}else{
			float currTime = (float)GetTickCount();

			float timeDelta = (currTime - lastTime) * 0.001f;
			if(timeDelta<1e-4){
				count++;
			}else{
				if(count)delta = timeDelta / count;
				else delta = timeDelta;
				count = 0;
			}

			
			//update here
			g_Input->UpdateInput();
			g_GUI->injectInput();
			//逻辑写好后判断是否向逻辑发送输入

			g_d3d->StartRender();
			//test code
			g_d3d->testrender(delta);

			g_GUI->renderGUI();
			//testend

			//在这加入其它渲染

			g_d3d->EndAndPresent();

			lastTime = currTime;
		}
	}

	m_bExit = true;
}
void App::CleanUp(){
	UnregisterClass(_T("D3D Tester"), m_hInstance);
}

LRESULT CALLBACK App::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	static bool b_lPressed = false;

	switch(msg){
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		if(!b_lPressed){
			b_lPressed = true;

		}
		break;
	case WM_LBUTTONUP:
		b_lPressed = false;
		break;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE){
			::DestroyWindow(hwnd);
		}
		break;
	
	case WM_CHAR:

	//case WM_IME_CHAR:

		break;
	
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);

}