#include<dinput.h>
#include"GameInput.h"
#include "../../Utilities/Common.h"
#include "../../App.h"

#include"../ThirdParty/CEGUI/CEGUIHelper.h"

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

	m_pKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_pKeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND );

	
	
	DIPROPDWORD inputProp;
                    // the header
                    inputProp.diph.dwSize       = sizeof(DIPROPDWORD);
                    inputProp.diph.dwHeaderSize = sizeof(DIPROPHEADER);
                    inputProp.diph.dwObj        = 0;
                    inputProp.diph.dwHow        = DIPH_DEVICE;
                    inputProp.dwData            = 16;

                    if (SUCCEEDED(m_pKeyboard->SetProperty(DIPROP_BUFFERSIZE, &inputProp.diph)))
                    {
                        m_pKeyboard->Acquire();
                    }

	
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
		/*
		memcpy(m_LastKeyboardState, m_KeyboardState, sizeof(BYTE)*256);
		FAILPROCESS(m_pKeyboard->GetDeviceState(256, (LPVOID)&m_KeyboardState)){
			//MSGBOX("UPDATE KEYBOARD FAILED");
			FAILPROCESS(m_pKeyboard->Acquire()){
				//MSGBOX("acquire keyboard failed");
				m_pKeyboard->Acquire();
			}
		}


		//testcode
		if(m_KeyboardState[DIK_ESCAPE]&0x80){
			::DestroyWindow(g_App->GetWnd());
		}

		*/
		DIDEVICEOBJECTDATA devDat;
		DWORD itemCount = 1;

		CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();

		HRESULT hr = m_pKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &devDat, &itemCount, 0);

		if(SUCCEEDED(hr)){
			if (itemCount > 0)
			{
				if (LOBYTE(devDat.dwData) & 0x80)
				{
					context.injectKeyDown((CEGUI::Key::Scan)devDat.dwOfs);
					//MSGBOX("s");
				}
				else
				{
					context.injectKeyUp((CEGUI::Key::Scan)devDat.dwOfs);
				}

			}
		}
		else
		{
			// try to re-acquire device if that was the cause of the error.
			if ((hr == DIERR_NOTACQUIRED) || (hr == DIERR_INPUTLOST))
			{
				//MSGBOX("fail");
				g_Input->m_pKeyboard->Acquire();
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