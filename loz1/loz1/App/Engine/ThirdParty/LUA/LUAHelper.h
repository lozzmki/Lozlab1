#ifndef LUAHELPER_H
#define LUAHELPER_H

extern "C"{
	#include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include<string>

namespace LUA{

	bool initLUA();

	void pushInt(int val);
	void pushDouble(double val);
	void pushString(std::string str);

	int popInt();
	double popDouble();
	std::string popString();

	void pushTableInt(std::string key, int val);
	void pushTableDouble(std::string key, double val);
	void pushTableString(std::string key, std::string str);

#define luasubtable(key, code){\
		lua_pushstring(g_lua, (key).c_str());\
		lua_newtable(g_lua);\
		{code}\
		lua_settable(g_lua,-3);\
	}
}
extern lua_State* g_lua;

#endif