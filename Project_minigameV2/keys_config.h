//keypad setup for 4x4 Matrix Keypad
#ifndef __KEY_CONFIG_H__
#define __KEY_CONFIG_H__

const byte ROWS=4;
const byte COLS=4;
char keys[ROWS][COLS]= //row column
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}

};
byte rowPins[ROWS]={9,8,7,6};
byte colPins[COLS]={5,4,3,2};
#endif