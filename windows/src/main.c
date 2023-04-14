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
		}
	}
	return 0;
	}
	int press( lua_State *L){
	 size_t len;
	 const char* str = luaL_checklstring(L, 1, &len);
			simulateKey(str);
		}
	//int hold( lua_State *L){
	//size_t len;
	//	const char* str = luaL_checklstring(L, 1, &len);
	//		while(1) {
	//			keybd_event(str[0], 0, 0, 0);
	//			Sleep(1);
	//	}
//	}

	int luaopen_main( lua_State *L )
	{
		struct luaL_reg M[] =
		{
		{"write", write},
		{"press", press},
		{NULL,NULL}
		};
/
		luaL_register( L, "example", M );
		return 1;
	}