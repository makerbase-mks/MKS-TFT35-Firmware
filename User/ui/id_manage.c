#include "stdint.h"
#include "gui.h"
#include "id_manage.h"

#define ID_USED 	1
#define ID_NOT_USED	0

static int32_t nextId = GUI_ID_USER;

static ID_STACK gId_stack[100];

void init_win_id()
{
	uint32_t i; 
	for(i = 0; i < sizeof(gId_stack) / sizeof(ID_STACK); i++)
	{
		gId_stack[i].flag = ID_NOT_USED;
		gId_stack[i].id = GUI_ID_USER + i;
	}
	//HAL_Delay(50);
}

uint32_t alloc_win_id()
{
	int32_t curId = nextId;
	uint32_t i; 
	
	for(i = 0; i < sizeof(gId_stack) / sizeof(ID_STACK); i++)
	{
		if(gId_stack[i].flag == ID_NOT_USED)
		{
			gId_stack[i].flag == ID_USED;
			return gId_stack[i].id;
		}
	}
	return 0;
}

void del_win_id(int32_t id)
{
	uint32_t i; 
	
	for(i = 0; i < sizeof(gId_stack) / sizeof(ID_STACK); i++)
	{
		if(gId_stack[i].id == id)
		{
			gId_stack[i].flag = ID_NOT_USED;
		}
	}
}


