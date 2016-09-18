#include<dinput.h>
#include"GameInput.h"
#include "../../Utilities/Common.h"
#include "../../App.h"

GameInput* g_Input = 0;

GameInput::GameInput(){}
GameInput::GameInput(HINSTANCE hInstance, HWND hWnd){
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput,NULL);

	m_pInput->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);
	m_pMouse->SetCooperativeLevel(hWnd,DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	FAILPROCESS(m_pMouse->Acquire()){
		//MSGBOX("acquire mouse failed");
		m_pMouse->Acquire();
	}

	
	FAILPROCESS(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboard, NULL)){
		MSGBOX("blast");
	}

	
	m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND );

	
	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);

	
	FAILPROCESS(m_pKeyboard->Acquire()){
		//MSGBOX("acquire keyboard failed");
		m_pKeyboard->Acquire();
	}

	::ZeroMemory(m_KeyboardState, sizeof(m_KeyboardState));
	
}

GameInput::~GameInput(){
	CleanUp();
}

void GameInput::UpdateInput(){

	if(m_pMouse){
		memcpy(&m_LastMouseState, &m_MouseState, sizeof(DIMOUSESTATE));
		FAILPROCESS(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_MouseState)){
			//MSGBOX("UPDATE MOUSE FAILED");
			FAILPROCESS(m_pMouse->Acquire()){
				//MSGBOX("acquire mouse failed");
				m_pMouse->Acquire();
			}
		}

		POINT _mousepoint;
		GetCursorPos(&_mousepoint);
		ScreenToClient(g_App->GetWnd(), &_mousepoint);

		m_LastMousePos = m_MousePos;
		m_MousePos.x=_mousepoint.x;	m_MousePos.y = _mousepoint.y;
	}
	
	if(m_pKeyboard){

		memcpy(m_LastKeyboardState, m_KeyboardState, sizeof(BYTE)*256);
		FAILPROCESS(m_pKeyboard->GetDeviceState(256, (LPVOID)&m_KeyboardState)){
			//MSGBOX("UPDATE KEYBOARD FAILED");
			FAILPROCESS(m_pKeyboard->Acquire()){
				//MSGBOX("acquire keyboard failed");
				m_pKeyboard->Acquire();
			}
		}

	}
	
}

void GameInput::CleanUp(){
	m_pMouse->Unacquire();
	m_pKeyboard->Unacquire();

	SAFE_RELEASE(m_pMouse);
	SAFE_RELEASE(m_pKeyboard);
	SAFE_RELEASE(m_pInput);
}