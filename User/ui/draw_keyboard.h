#ifndef _DRAW_KEYBOARD_H_
#define _DRAW_KEYBOARD_H_


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

void draw_Keyboard();
void Clear_Keyboard();
void update_keyboard_disp(void);
void update_password_disp(void);
void update_join_state_disp(void);

//void disp_key_selected_state(void);

typedef enum
{
	UPPER_CASE_LETTER,
	LOWER_CASE_LETTER,
	DIGITLA,
	SYMBOL
}KEYBOARD_STYPE;
extern KEYBOARD_STYPE keyboard_stype;


#define  NUMBER_OF_PASSWORD 50//16
typedef struct
{
	uint8_t cnt;
	uint8_t dis_cnt;
	uint8_t password_value[NUMBER_OF_PASSWORD+2];
	uint8_t password_disp[NUMBER_OF_PASSWORD+2];
	uint8_t timer;
	uint32_t timer_count;
}KEY_VALUE_CALC;

extern KEY_VALUE_CALC key_value_calc;

#define TIMER_START 1
#define TIMER_STOP 0

#define NUMBER_OF_DIGITS 20

#define TEXT_PIONT_BOLD '`'

#define BUTTON_PRESS_BK_COLOR  0x00e0e1
#define BUTTON_PRESS_TEXT_COLOR  0x000000

/*typedef struct
{
	uint8_t ip_adrres;
	uint8_t subnet_mask;
	uint8_t defaut_gate_way;
	uint8_t name_server;
	uint8_t join_state;
}KEY_ENTER_STATE;
extern KEY_ENTER_STATE enter_state;

#define ENTER_STATE_OK 1
#define ENTER_STATE_NO 0

#define JOIN_STATE_OK 1
#define JOIN_STATE_NO 0*/

#if defined(__cplusplus)
}    /* Make sure we have C-declarations in C++ programs */
#endif


#endif





