	#include <lua.h>
	#include <lauxlib.h>
	#include <string.h>
	#include <Windows.h>
	#include <ctype.h>

	void simulateKey(DWORD vk)
	{
		INPUT input;
		ZeroMemory(&input, sizeof(input));
		input.type = INPUT_KEYBOARD;
		input.ki.wVk = vk;
		SendInput(1, &input, sizeof(input));
		input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(input));
	}

	int multiply( lua_State *L )
	{
		if ( ! lua_isnumber( L, 1 ) )
		{
			return luaL_error( L, "Expecting first parameter to be typeof: number" );
		}

		if ( ! lua_isnumber( L, 2 ) )
		{
			return luaL_error( L, "Expecting second parameter to be typeof: number" );
		}
	
		int multiply = lua_tonumber( L, 1 ) * lua_tonumber( L, 2 );
		lua_pushnumber( L, multiply );
		return 1;
	}
	int write(lua_State* L) {
		if (lua_isnumber(L, 1)) {
			return luaL_error(L, "Expecting a single letter, not a number");
		}
		size_t len;
		const char* str = luaL_checklstring(L, 1, &len);
		for (int i = 0; i < len; i++) {
			char c = str[i];
			if (isupper(c)) {
				keybd_event(VK_SHIFT, 0, 0, 0);
				keybd_event(c, 0, 0, 0);
				keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); // Release Shift key
			} else {
				keybd_event(c, 0, 0, 0);
				keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); // Release Shift key
			}
		}
		return 0;
	}
	int press( lua_State *L){
	 size_t len;
	 const char* str = luaL_checklstring(L, 1, &len);
			simulateKey(str[0]);
		}
	int hold( lua_State *L){
	size_t len;
		const char* str = luaL_checklstring(L, 1, &len);
			while(1) {
				keybd_event(str[0], 0, 0, 0); // Press down
				Sleep(1); // Wait a short period of time
		}
	}
	/**
	* Register mappings.
	*/
	int luaopen_main( lua_State *L )
	{
		struct luaL_reg M[] =
		{
		{"write", write},
		{"press", press},
		{"hold", hold},
		{NULL,NULL}
		};

		luaL_register( L, "example", M );
		return 1;
	}