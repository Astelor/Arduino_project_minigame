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

/*initialize keypad*/
Keypad mykeypad = Keypad( ((char*)keys), rowPins, colPins, ROWS, COLS );
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
# 33 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
/* Dynamic user input from myKeypad 0~7*/
char userInput[8]={};

/* The digits of current userInput, from 1~8, 0 = no avalible input*/
int displayCount=0;

/* The highest digit that can be displayed, from 1~8 */


/* Display the char array in userInput, 0~3

 * type 0= full 4; 1=displaycount

 */
# 45 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
void userDisplay(int type,const char *result){
    int temp=(type==0)? 4:displayCount;
    for(int i=0;i<4;i++){
        if(i>=temp){dimDigit(i);}
        else{monitor.setChar(0,((i-7)>0?(i-7):-(i-7)),result[i],false);}
    }
}

/* clear displayCount and userInput

 * int type(additional action):

 * 1--> dim digit 0~3

 */
# 57 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
void userDisClear(int type){
    displayCount=0;
    *userInput=(char)0;
    if(type==1){dimDigit(0);dimDigit(1);dimDigit(2);dimDigit(3);}
}

/* dim the designated digit (0~7)*/
void dimDigit(int num){
    for(int i=0;i<8;i++){
        monitor.setLed(0,((num-7)>0?(num-7):-(num-7)),i,false);
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
    dimDigit(((i-7)>0?(i-7):-(i-7)));
    monitor.setLed(0,i,1,true);
    delay(100);
  }
  monitor.setLed(0,7,6,true);delay(100);
  monitor.setLed(0,7,5,true);delay(100);
  for(int i=7;i>=0;i--){
    monitor.setLed(0,i,4,true);
    delay(100);
  }
  monitor.setLed(0,0,3,true);delay(100);
  monitor.setLed(0,0,2,true);delay(100);
}

/*Animation for showing answer in advance*/
void seeAnsDisplay(){
    for(int i=0;i<8;i++){
        dimDigit(((i-7)>0?(i-7):-(i-7)));
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

/*=========================

 * Main Code

 *=========================*/
# 123 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
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
# 135 "e:\\!Github_Coding\\Arduino_project_minigame\\Arduino_project_minigame\\Project_minigameV2\\Project_minigameV2.ino"
bool newGame=true;

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
                userDisClear(0);monitor.clearDisplay(0);
                nAnB.generateKey();
                Serial.println(nAnB.getAnsKey());
                newGame=false;
                break;
            }
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
                    if(displayCount==4){ //checks if the user gives a 4 digit answer
                        userDisplay(0,nAnB.commitAnswer(userInput));//display the ABs
                        userDisClear(0); //clear userInput
                        if(nAnB.getABs()[0]=='4'){ //4A-> you won the game!-> jump back to menu
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
                        dimDigit(displayCount-1);
                        displayCount--;
                        userDisplay(1,userInput);
                    }
                }
                else if(key>='0'&&key<='9'){
                    /*type in the numbers*/
                    if(displayCount<4){//1~4
                        displayCount++;
                        userInput[displayCount-1]=key;
                        userDisplay(1,userInput);
                    }
                }
            }
        }
    }
}
