/* 
 * Project_minigameV2.ino is coded by Astelor
 * CodeSource.txt is coded by 吳捷宇 
 * MiniGame.cpp is a modification of CodeSouce, modified by Astelor
 * 
 * This picture was here for emotional support
 * https://cdn.frankerfacez.com/emoticon/335816/2
 * 
 * NOTE:
 * This project was coded using vscode, 
 * the compatibility with Arduino IDE has yet to be tested.
 */

#include <LedControl.h>
#include <Keypad.h>
#include "keys_config.h"
#include "MiniGame.h"
#include "pitches.h"

/*initialize keypad*/ 
Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/*initialize led monitor*/
int dataPin=12,clkPin=10,csPin=11;
LedControl monitor=LedControl(dataPin,clkPin,csPin,1);
/*initilize minigame*/
MiniGame nAnB;
//MiniGame ultiNumber;

/*=====================================/
 * Helper functions:
 * Integration of Keypad & LedControl
 *====================================*/

/* Dynamic user input from myKeypad 0~7*/
char userInput[8]={};

/* The digits of current userInput, from 1~8, 0 = no avalible input*/
int displayCount=0;

/* The highest digit that can be displayed, from 1~8 */
#define userInCap 4

/* Display the char array in userInput, 0~3
 * type 0= full 4; 1=displaycount
 */
void userDisplay(int type,const char *result){
    int temp=(type==0)? 4:displayCount;
    for(int i=0;i<4;i++){
        if(i>=temp){dimDigit(i);}
        else{monitor.setChar(0,abs(i-7),result[i],false);}
    }
}

/* Clear displayCount and userInput
 * int type(additional action):
 * 1--> do clearDisplay
 */
void userDisClear(int type){
    displayCount=0;
    *userInput=(char)0;
    if(type==1){dimDigit(0);dimDigit(1);dimDigit(2);dimDigit(3);}
}

/* Dim a digit on display 0~7*/
void dimDigit(int num){
    for(int i=0;i<8;i++){
        monitor.setLed(0,abs(num-7),i,false);
    }
}

/* Backspace the userInput by one, then display it */
void userDisDel(){
    if(displayCount>0){
        userInput[displayCount]={};
        dimDigit(displayCount-1);
        displayCount--;
        userDisplay(1,userInput);
    }
    else{
        return;
    }
}

/* Menu display sets */
void menuDisplay(){
    for(int i=0;i<8;i++){
        monitor.setLed(0,i,1,true);
        monitor.setLed(0,i,4,true);
    }
    monitor.setLed(0,0,2,true);
    monitor.setLed(0,0,3,true);
    monitor.setLed(0,7,6,true);
    monitor.setLed(0,7,5,true);
}

/*VICTORY SCREEN WOOOOOO*/
void victoryDisplay(){
  for(int i=0;i<8;i++){
    if(i==0){
      monitor.setLed(0,i,1,true);
    }
    else{
      monitor.setLed(0,i-1,1,false);
      monitor.setLed(0,i,1,true);
    }
    delay(100);
  }
  monitor.setLed(0,7,1,false);monitor.setLed(0,7,6,true);delay(100);
  monitor.setLed(0,7,6,false);monitor.setLed(0,7,5,true);delay(100);
  monitor.setLed(0,7,5,false);
  for(int i=7;i>=0;i--){
    if(i==7){
      
      monitor.setLed(0,i,4,true);
    }
    else{
      monitor.setLed(0,i+1,4,false);
      monitor.setLed(0,i,4,true);
    }
    delay(100);
  }
  monitor.setLed(0,0,4,false);monitor.setLed(0,0,3,true);delay(100);
  monitor.setLed(0,0,3,false);monitor.setLed(0,0,2,true);delay(100);
  monitor.setLed(0,0,2,false);
}

/*Animation for showing answer in advance*/
void seeAnsDisplay(){
    for(int i=0;i<8;i++){
        dimDigit(abs(i-7));
        monitor.setLed(0,i,7,true);
        delay(100);
    }
}

/*=========================
 * Main Code
 *=========================*/
void setup(){
	Serial.begin(9600);
    monitor.shutdown(0,false);
    monitor.setIntensity(0,8);
    monitor.clearDisplay(0);
    userDisClear(1);
    Serial.println("Version06");
}

/* Decides if it's the start of a new game
 * true= yes->menu; false= no->stays in the current game
 */
bool newGame=true;

/*Only required when there's more than 1 game*/
int gameMode=0;

char key=mykeypad.getKey();
void loop(){
	//char key = mykeypad.getKey();
    if(newGame){
        /*MENU SCREEN, nothing will happen before the user select a game*/
        monitor.clearDisplay(0);menuDisplay();
        while(true){
            key=mykeypad.waitForKey();
            delay(5);
            if(key=='A'){
                /*press A to play nAnB*/
                Serial.println(key);
                gameMode=0;
                userDisClear(0);monitor.clearDisplay(0);
                nAnB.generateKey();
                Serial.println(nAnB.getAnsKey());
                newGame=false;
                break;
            }
            /*else if(key=='B'){
                //press B to play Guess the Number
                //TBA...
                gameMode=1;
                userDisClear(0);
            }*/
        }
    }
    else{
        while(true){
            key=mykeypad.waitForKey();
            delay(5);
            if(key){
                Serial.println(key);
                if(key=='A'){
                    /*Show answerKey for 1 second, then jump back to menu*/
                    userDisplay(0,nAnB.getAnsKey());
                    Serial.println(nAnB.getAnsKey());
                    delay(1000);
                    userDisClear(0);
                    newGame=true;
                    seeAnsDisplay();
                    break;
                }
                else if(key=='#'){
                    /*Submit answer*/
                    if(displayCount==4){                            //checks if the user gives a 4 digit answer
                        userDisplay(0,nAnB.commitAnswer(userInput));//display the ABs
                        userDisClear(0);                            //clear userInput
                        if(nAnB.getABs()[0]=='4'){                  //4A-> you won the game!-> jump back to menu
                            delay(1000);
                            userDisClear(1);
                            newGame=true;
                            victoryDisplay();
                            break;
                        }
                    }
                }
                else if(key=='*'){
                    /*Backspace the userInput by one, then display it*/
                    userDisDel();
                }
                else if(key>='0'&&key<='9'){
                    /*type in the numbers*/
                    if(displayCount<userInCap){//1~4
                        displayCount++;
                        userInput[displayCount-1]=key;
                        userDisplay(1,userInput);
                    }
                }
            }
        }
    }
}
