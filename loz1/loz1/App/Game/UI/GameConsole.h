#ifndef GAMECONSOLE_H
#define GAMECONSOLE_H

#include<CEGUI\CEGUI.h>

class GameConsole{
public:
	GameConsole();
	virtual ~GameConsole();

	GameConsole& operator <<(std::string);
	GameConsole& operator <<(int);
	GameConsole& operator <<(double);
	void out(std::string);

	bool handleCmdInput(const CEGUI::EventArgs&);
	
	static const std::string endl;

};

extern GameConsole* g_pConsole;

#define g_Console (*g_pConsole)

#endif