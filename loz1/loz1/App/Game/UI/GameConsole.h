#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include<CEGUI\CEGUI.h>

class Game;

class GameConsole{
public:
	//һЩԤ�ò�����ʹ������������
	typedef struct{int code;} ConsoleManipulaor;

	GameConsole();
	virtual ~GameConsole();

	GameConsole& operator <<(std::string);
	GameConsole& operator <<(int);
	GameConsole& operator <<(double);
	GameConsole& operator <<(ConsoleManipulaor);

	inline void flush(){m_obuffer="";}

	bool handleCmdInput(const CEGUI::EventArgs&);
	bool handleHideEvent(const CEGUI::EventArgs&);
	

	void linkGame(Game* pGame){m_pLinkedGame = pGame;}

	void showConsole();

	static const ConsoleManipulaor out;

protected:
	std::string m_obuffer;

	void updateScroll();

	//���ӵ�����Ϸ��ʹ����̨���Կ�����Ϸ
	Game* m_pLinkedGame;
};

extern GameConsole* g_pConsole;

#define g_Console (*g_pConsole)
#define console_out GameConsole::out

#endif