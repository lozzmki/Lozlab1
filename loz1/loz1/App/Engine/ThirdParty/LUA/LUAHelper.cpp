#include "LUAHelper.h"

lua_State* g_lua = 0;

namespace LUA{

	bool initLUA(){
		g_lua = luaL_newstate();

		if(!g_lua)return false;
		return true;
	}

	//pop functions
	int popInt(){
		int temp= (int)lua_tointeger(g_lua,1);
		lua_pop(g_lua,1);
		return temp;
	}
	double popDouble(){
		double temp= (double)lua_tonumber(g_lua,1);
		lua_pop(g_lua, 1);
		return temp;
	}
	std::string popString(){
		std::string temp = lua_tostring(g_lua,1);
		lua_pop(g_lua,1);
		return temp;
	}

	//push functions
	void pushInt(int val){
		lua_pushinteger(g_lua, val);
	}
	void pushDouble(double val){
		lua_pushnumber(g_lua, val);
	}
	void pushString(std::string str){
		lua_pushstring(g_lua, str.c_str());
	}

	//table functions
	void pushTableInt(std::string key, int val){
		lua_pushstring(g_lua, key.c_str());
		lua_pushinteger(g_lua, val);
		lua_settable(g_lua, -3);
	}
	void pushTableDouble(std::string key, double val){
		lua_pushstring(g_lua, key.c_str());
		lua_pushnumber(g_lua, val);
		lua_settable(g_lua, -3);
	}
	void pushTableString(std::string key, std::string str){
		lua_pushstring(g_lua, key.c_str());
		lua_pushstring(g_lua, str.c_str());
		lua_settable(g_lua, -3);
	}




}