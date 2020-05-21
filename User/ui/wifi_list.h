#ifndef _BUILD_TEXT
#define _BUILD_TEXT
typedef struct list_menu_disp
{
	char *title;
	char *file_pages;
}list_menu_def;
extern list_menu_def list_menu;	

typedef struct keyboard_menu_disp
{
	char *title;
	char *apply;
	char *password;
	char *letter;
	char *digital;
	char *symbol;
	char *space;
	char *send;
}keyboard_menu_def;
extern keyboard_menu_def keyboard_menu;	

typedef struct tips_menu_disp
{
	char *pointBold;
	char *joining;
	char *failedJoin;
	char *wifiConected;
}tips_menu_def;
extern tips_menu_def tips_menu;	



#endif