# 1 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
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
# 14 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
# 15 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino" 2
# 16 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino" 2
# 17 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino" 2
# 18 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino" 2
# 19 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino" 2

/*initialize keypad*/
Keypad mykeypad = Keypad( ((char*)keys), rowPins, colPins, ROWS, COLS );
/*initialize led monitor*/
int dataPin=12,clkPin=10,csPin=11;
LedControl monitor=LedControl(dataPin,clkPin,csPin,1);
/*initilize minigame*/
MiniGame nAnB;
//MiniGame ultiNumber;

/*====================================

 * Helper functions:

 * Integration of Keypad & LedControl

 *====================================*/
# 34 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
/*Dynamic user input from myKeypad*/
char userInput[7]={};
/*The digits of current userInput, from 1~8, 0 = no avalible input*/
int displayCount=0;
/*The highest digit that can be displayed, from 1~8*/
int userInCap=4;
/*Display the char array in userInput

 * int type:

 * 1= display char*result, a 4 digit char array

 * 2= display pulled from userInput, no char array input needed

 */
# 45 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
void userDisplay(int type=2,const char *result="XXXX"){
    switch (type)
    {
    case 1:
        for(int i=0;i<4;i++){
        monitor.setChar(0,((i-7)>0?(i-7):-(i-7)),result[i],false);
        }
        break;
    case 2:
        for(int i=0;i<displayCount;i++){
            monitor.setChar(0,((i-7)>0?(i-7):-(i-7)),userInput[i],false);
        }
        break;
    default:
        break;
    }
}
/*

 * Clear displayCount and userInput

 * int type(additional action):

 * 1= default value, no clearDisplay

 * 0= do clearDisplay

*/
# 68 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
void userDisClear(int type =1){
    switch (type)
    {
    case 0:
        displayCount=0;
        userInput[7]={};
        monitor.clearDisplay(0);
        break;
    case 1:
        displayCount=0;
        userInput[7]={};
        break;
    default:
        break;
    }

}
/*Backspace the userInput by one, then display it*/
void userDisDel(){
    if(displayCount!=0){
        userInput[displayCount]={};
            displayCount--;
        monitor.clearDisplay(0);
        userDisplay(2);
    }
}
/*Menu display sets*/
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

/*===========

 * Main Code

 *===========*/
# 109 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
void setup(){
 Serial.begin(9600);
    monitor.shutdown(0,false);
    monitor.setIntensity(0,8);
    monitor.clearDisplay(0);
}
/*

 * Decides if it's the start of a new game

 * true= yes->menu; false= no->stays in the current game

 */
# 119 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
bool newGame=true;
/*Only required when there's more than 1 game*/
int gameMode=0;
void loop(){
 char key = mykeypad.getKey();
    if(newGame){
        /*MENU SCREEN, nothing will happen before the user select a game*/
        menuDisplay();
        if(key=='A'){
            /*press A to play nAnB*/
            gameMode=0;
            userDisClear(0);
            nAnB.generateKey();
            Serial.println(nAnB.getAnsKey());
            newGame=false;
        }
        /*else if(key=='B'){

            //press B to play Guess the Number

            //TBA...

            gameMode=1;

            userDisClear(0);

        }*/
# 141 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
    }
    else{if(key){
        Serial.println(key);
        if(key=='*'){
            /*Backspace the userInput by one, then display it*/
            userDisDel();
        }
        else if(key=='A'){
            /*Show answerKey for 1 second, then jump back to menu*/
            char* temp;
            temp=nAnB.getAnsKey();
            userDisplay(1,temp);
            Serial.println(temp);
            delay(1000);
            userDisClear(0);
            newGame=true;
        }
        else if(key=='#'){
            /*Submit answer*/
            if(displayCount==4){ //checks if the user gives a 4 digit answer
                monitor.clearDisplay(0);
                char* temp;
                temp=nAnB.commitAnswer(userInput);
                userDisplay(1,temp); //display the ABs
                userDisClear(); //clear userInput
                if(temp[0]=='4'){ //4A-> you won the game!-> jump back to menu
                    delay(1000);
                    monitor.clearDisplay(0);
                    newGame=true;
                }
            }
        }
        else if(key!='A'&&key!='B'&&key!='C'&&key!='D'){
            if(displayCount!=userInCap){
                if(displayCount==0){
                    monitor.clearDisplay(0);
                }
                userInput[displayCount]=key;
                displayCount++;
                userDisplay(2);
            }
        }
    }}
}
