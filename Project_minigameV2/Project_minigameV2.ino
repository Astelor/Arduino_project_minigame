/* 
 * Project_minigameV2.ino is coded by Astelor
 * CodeSource.cpp is coded by 吳捷宇 
 * MiniGame.cpp is a modification of CodeSouce, coded by Astelor
 * 
 * This picture was here for emotional support
 * https://cdn.frankerfacez.com/emoticon/335816/2
 * 
 * NOTE:
 * This project was coded using vscode, 
 * the compatibility with Arduino IDE has yet to be tested.*
 */

#include <LedControl.h>
#include <Keypad.h>
#include "keys_config.h"
#include "MiniGame.h"

/*initialize keypad*/ 
Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/*initialize led monitor*/
int dataPin=12,clkPin=10,csPin=11;
LedControl monitor=LedControl(dataPin,clkPin,csPin,1);
/*initilize minigame*/
MiniGame nAnB;
MiniGame guessNum;
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
void userDisplay(int len,const char *result){
    for(int i=0;i<8;i++){
        if(i>=len){dimDigit(i);}
        else{monitor.setChar(0,7-i,result[i],false);}
    }
}

/* clear displayCount and userInput
 * int len:
 * dim the length of digits
 */
void userDisClear(int len){
    displayCount=0;
    *userInput=(char)0;
    for(int i=0;i<len;i++){dimDigit(i);}
}

/* dim the designated digit (0~7)*/
void dimDigit(int num){
    for(int i=0;i<8;i++){
        monitor.setLed(0,abs(num-7),i,false);
    }
}


/*functions for gamemode 1*/
//idk, maybe I should refine the functioins for gamemode 0

/*===================cosmetics===================*/

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
    byte arr[]{
        0b11011100,//Y
        0b10111000,//o
        0b00111000,//u
        0b00000000,
        0b11101100,//W
        0b10111000,//o
        0b10101000,//n
        0b10000000,//-1
        0b10000000,//-2
        0b10000000,//-3
        0b10000000,//-4
        0b10000000,//-5
        0b10000000,//-6
        0b10000000,//-7
        0b10000000//-8
        //0b00000000
    };
    byte arr2[][8]{
    {
        0b01000010,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000010,
        0b00000110
    },
    {
        0b11000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000010,
        0b10000110
    },
    {
        0b01110010,
        0b00010010,
        0b00010010,
        0b00010010,
        0b00010010,
        0b00010010,
        0b00010010,
        0b00011110
    }
    };
    int length=15-1;
    for(int i=0;i<8;i++){
        for(int k=0;k<=i;k++){
            for(int j=0;j<8;j++){
                monitor.setLed(0,k,j,bitRead(arr[i-k],j)); //0~7
            }
        }
        delay(200);
    }
    for(int i=8;i<=length;i++){
        for(int k=0;k<8;k++){
            for(int j=0;j<8;j++){
                monitor.setLed(0,k,j,bitRead(arr[i-k],j)); //8~length
            }
        }
        delay(200);
    }
    delay(700);
    for(int i=0;i<3;i++){
        for(int k=0;k<8;k++){
            for(int j=0;j<8;j++){
                monitor.setLed(0,k,j,bitRead(arr2[i][7-k],j));
            }
        }
        delay(200);
    }
}

/*Animation for showing answer in advance*/
void seeAnsDisplay(){
    for(int i=0;i<8;i++){
        dimDigit(abs(i-7));
        monitor.setLed(0,i,7,true);
        delay(100);
        monitor.setLed(0,i-1,7,false);
    }delay(90);
    monitor.setLed(0,7,7,false);
    monitor.setLed(0,7,6,true);
    monitor.setLed(0,7,5,true);
    delay(90);
    for(int i=7;i>=0;i--){
        monitor.setLed(0,i,1,true);
        monitor.setLed(0,i,4,true);
        delay(90);
    }
    monitor.setLed(0,0,2,true);
    monitor.setLed(0,0,3,true);
}

/*Animation for out-of-range warning*/
void outaRangeDisplay(){
        byte arr[]{
        0b10111000,// o
        0b00111000,// u
        0b11110000,// t
        0b00000000,
        0b10111000,// o
        0b11100010,// F
        0b00000000,
        0b10100000,// r
        0b11101110,// A
        0b10101000,// n
        0b11011110,// g
        0b11110010,// E
        0b00000000};
        for(int i=0;i<8;i++){
        for(int k=0;k<=i;k++){
            for(int j=0;j<8;j++){
                monitor.setLed(0,k,j,bitRead(arr[i-k],j)); //0~7
            }
        }
        delay(200);
    }
    for(int i=8;i<=12;i++){
        for(int k=0;k<8;k++){
            for(int j=0;j<8;j++){
                monitor.setLed(0,k,j,bitRead(arr[i-k],j)); //8~12
            }
        }
        delay(200);
    }
    for(int i=1;i<8;i++){
        for(int k=0;k<8-i;k++){
            for(int j=0;j<8;j++){
                monitor.setLed(0,k+i,j,bitRead(arr[12-k],j)); //12~end
            }
        }
        delay(200);
    }
}
/*===================Main Code===================*/

void setup(){
	Serial.begin(9600);
    monitor.shutdown(0,false);
    monitor.setIntensity(0,8);
    monitor.clearDisplay(0);
    userDisClear(1);
    Serial.println("New added game");
}

/* Decides if it's the start of a new game
 * true= yes→menu; false= no→stays in the current game
 */
bool newGame=true;
int gamemode=0;
char key=mykeypad.getKey();
void loop(){
	//char key = mykeypad.getKey();
    //if(newGame){
    /*MENU SCREEN, nothing will happen before the user select a game*/
    monitor.clearDisplay(0);menuDisplay();
    while(newGame){
        key=mykeypad.waitForKey();
        delay(5);
        if(key=='A'){
            /*press A to play nAnB*/
            Serial.println(key);
            userDisClear(0);monitor.clearDisplay(0);
            nAnB.generateKey();
            Serial.println(nAnB.getAnsKey());
            newGame=false;gamemode=0;
            break;
        }
        else if(key=='B'){
            /*press B to play GuessTheNumber*/
            Serial.println(key);
            userDisClear(0);monitor.clearDisplay(0);
            guessNum.generateKey_1();
            Serial.println(guessNum.getAnsKey_1());
            newGame=false;gamemode=1;
            break;
        }
    }
    //}
    //else{
    while(gamemode==0 &&newGame==false){
        key=mykeypad.waitForKey();
        delay(5);
        if(key){
            Serial.println(key);
            if(key>='0'&&key<='9'){
                /*type in the numbers*/
                if(displayCount<userInCap){//1~4
                    displayCount++;
                    userInput[displayCount-1]=key;
                    userDisplay(displayCount,userInput);
                }
            }
            else if(key=='C'){
                /*Show answerKey for 1 second, then jump back to menu*/
                userDisplay(4,nAnB.getAnsKey());
                Serial.println(nAnB.getAnsKey());
                delay(1000);
                userDisClear(0);newGame=true;//reset
                seeAnsDisplay();
                break;
            }
            else if(key=='#'){
                /*Submit answer*/
                if(displayCount==4){                            //checks if the user gives a 4 digit answer
                    userDisplay(4,nAnB.commitAnswer(userInput));//display the ABs
                    userDisClear(0);                            //clear userInput
                    if(nAnB.getABs()[0]=='4'){                  //4A-> you won the game!-> jump back to menu
                        delay(1000);
                        userDisClear(0);
                        newGame=true;
                        victoryDisplay();
                        break;
                    }
                }
            }
            else if(key=='*'){
                /*Backspace the userInput by one, then display it*/
                if(displayCount>0){
                    userInput[displayCount]={};
                    dimDigit(--displayCount);
                    userDisplay(displayCount,userInput);
                }
            }
        }
    }
    char range[8]={"1-1000"}; //range of the guessing numbers, reset
    int lowLen=1;int highLen=4;int netLen=5; //reset
    while(gamemode==1 && newGame==false){
        key=mykeypad.waitForKey();
        delay(5);
        if(key){
            Serial.println(key);
            switch (key){
            case '0'...'9':{
                /*type in the numbers*/
                if(displayCount<userInCap){//1~4
                    displayCount++;
                    userInput[displayCount-1]=key;
                    userDisplay(displayCount,userInput);
                }
                break;
                }
            case 'C':{
                /*Show the answer. If key C is released, jump back to menu screen*/
                userDisplay(guessNum.length('A'),guessNum.getAnsKey_1_char());
                Serial.println(guessNum.getAnsKey_1());
                delay(50);
                while(true){
                    if(mykeypad.getKey()=='C'){break;}
                    else{delay(100);}
                }
                userDisClear(0);newGame=true;//reset
                seeAnsDisplay();//animation + reset
                break;
                }
            case 'D':{ //**display function**
                /*press to display the current number range*/
                for(int i=0;i<4;i++){dimDigit(i);}
                userDisplay(netLen+1,range);
                delay(50);
                while(true){
                    if(mykeypad.getKey()=='D'){break;}
                    else{delay(100);}
                }//hold the key to keep the display
                userDisplay(displayCount,userInput);
                break;
                }
            case '#':{
                /*submit answer*/
                int temp=guessNum.commitNumber(userInput,displayCount);
                switch (temp){
                case -1:{ //out-of-range
                    //NOTE: just display the curent range
                    outaRangeDisplay();
                    delay(150);
                    userDisClear(0);
                    userDisplay(netLen+1,range);
                    break;
                    }
                case 0:{  //valid number, display the updated range
                    *range=(char)0; userDisClear(0); //reset
                    lowLen=guessNum.length('L');
                    highLen=guessNum.length('H');
                    netLen=lowLen+highLen;
                    char*rangeL=guessNum.getLow();
                    char*rangeH=guessNum.getHigh();
                    for(int i=0;i<netLen+1;i++){
                        if(i<lowLen){range[i]=rangeL[i];}
                        else if(i==lowLen){range[i]='-';}
                        else{range[i]=rangeH[i-lowLen-1];}
                    }
                    userDisplay(netLen+1,range);
                    userDisClear(0);//reset
                    break;
                    }
                case 1:{  //correct number, end of game
                    userDisClear(0);newGame=true; //reset
                    delay(150);
                    victoryDisplay();
                    break;
                    }
                default:
                    break;
                }
                break;
            }
            case '*':{
                /*Backspace the userInput by one, then display it*/
                if(displayCount>0){
                    userInput[displayCount]={};
                    dimDigit(--displayCount);
                    userDisplay(displayCount,userInput);
                }
                break;
            default:
                break;
                }
            }
        }
    }
    //}
}
