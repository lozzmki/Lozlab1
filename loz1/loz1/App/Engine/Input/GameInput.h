#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include<dinput.h>
#include"../../Utilities/Vector2D.h"

class GameInput{

public:
	GameInput();
	GameInput(HINSTANCE hInstance,HWND hWnd);
	virtual ~GameInput();


	void UpdateInput();
	void CleanUp();


	LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pMouse, m_pKeyboard;
	DIMOUSESTATE m_MouseState, m_LastMouseState;
	BYTE m_KeyboardState[256], m_LastKeyboardState[256];
	Vec2i m_MousePos, m_LastMousePos;

};

extern GameInput* g_Input;

#define KEYDOWN(p) (g_Input->m_KeyboardState[(p)]&0x80)
#define MOUSEDOWN(p) (g_Input->m_MouseState.rgbButtons[(p)]&0x80)
#define MOUSECLICK(p) (!(g_Input->m_LastMouseState.rgbButtons[(p)]&0x80) && (g_Input->m_MouseState.rgbButtons[(p)]&0x80))
#define MOUSEPRESS(p) ((g_Input->m_LastMouseState.rgbButtons[(p)]&0x80) && (g_Input->m_MouseState.rgbButtons[(p)]&0x80))
#define MOUSEUP(p) ((g_Input->m_LastMouseState.rgbButtons[(p)]&0x80) && !(g_Input->m_MouseState.rgbButtons[(p)]&0x80))
#define LBUTTON 0
#define RBUTTON 1




#endif