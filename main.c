#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

struct int_stack {
	struct int_stack *next;
	int value;
};

struct int_stack *values = 0x0;

static int l_adder_push(lua_State *L)
{
	int v = lua_tointeger(L, -1);
	struct int_stack *i = malloc(sizeof(struct int_stack));
	i->value = v;
	i->next = values;
	values = i;
	return 0;
}

static int l_adder_sum(lua_State *L)
{
	int total = 0;
	struct int_stack *cur;
	cur = values;
	while(cur)
	{
		total += cur->value;
		cur = cur->next;
	}
	lua_pushinteger(L, total);
	return 1;
}

int main(int argc, char *argv[])
{
	lua_State *L = lua_open();

	luaL_openlibs(L);

	lua_newtable(L);
	lua_setglobal(L, "adder");

	lua_getglobal(L, "adder");
	lua_pushstring(L, "push");
	lua_pushcfunction(L, l_adder_push);
	lua_settable(L, -3);

	lua_getglobal(L, "adder");
	lua_pushstring(L, "sum");
	lua_pushcfunction(L, l_adder_sum);
	lua_settable(L, -3);

	luaL_dofile(L, "script.lua");

	//lua_close(L);	

	return 0;
}
