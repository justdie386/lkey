#include <lua.h>
#include <lauxlib.h>
#include <string.h>
#include <Windows.h>
#include <ctype.h>
#define false (1==0)
#define true  (1==1)


int simulateCapitalKey(var){

    INPUT input_shift_press = {0};
    input_shift_press.type = INPUT_KEYBOARD;
    input_shift_press.ki.wVk = VK_SHIFT;

    INPUT input_a_press = {0};
    input_a_press.type = INPUT_KEYBOARD;
    input_a_press.ki.wVk = var;

    INPUT input_shift_release = {0};
    input_shift_release.type = INPUT_KEYBOARD;
    input_shift_release.ki.wVk = VK_SHIFT;
    input_shift_release.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input_shift_press, sizeof(INPUT));
    SendInput(1, &input_a_press, sizeof(INPUT));
    SendInput(1, &input_shift_release, sizeof(INPUT));

  return 0;

}
int simulateKey(var)
{
	INPUT input = {0};
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = var; // set the virtual key code to 'A'
	SendInput(1, &input, sizeof(INPUT));
	input.ki.dwFlags = KEYEVENTF_KEYUP; // release the 'A' key
    SendInput(1, &input, sizeof(INPUT));
	return 0;
}


int write(lua_State *L)
{
	if (lua_isnumber(L, 1))
	{
		return luaL_error(L, "Expecting a single letter, not a number");
	}
	size_t len;
	const char *str = luaL_checklstring(L, 1, &len);
	for (int i = 0; i < len; i++)
	{
		char c = str[i];
		if (isupper(c))
		{
			simulateCapitalKey(c);
		}else{
			char cap = toupper(c);
			simulateKey(cap);
		}
	}
}

int luaopen_main(lua_State *L)
{
	struct luaL_reg M[] =
		{
			{"write", write},
			{NULL, NULL}};

	luaL_register(L, "example", M);
	return 1;
}