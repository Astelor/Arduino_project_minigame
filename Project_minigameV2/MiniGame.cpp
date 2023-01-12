#include "MiniGame.h"
#include <Arduino.h>

//gameMode 0: nAnB

void MiniGame::generateKey(){
    unsigned long myTime;
    myTime=millis();
    srand(myTime);
    for(int i=0; i<4; i++) {AnswerKey[i]=(rand()%10)+'0';ABs[i]='-';}
}

char* MiniGame::commitAnswer(char* answer){
    b[0]=AnswerKey[0];b[1]=AnswerKey[1];
    b[2]=AnswerKey[2];b[3]=AnswerKey[3];
    int x=0, y=0;
    for(int i=0; i<4; i++){
        if(answer[i]==b[i]){
            x++;
            answer[i]='X';
            b[i]='X';
        }
    }
    for(int i=0; i<4; i++){
        if(answer[i]=='X') continue;
        for(int j=0; j<4; j++){
            if(answer[i]==b[j]){
                y++;
                answer[i]='X';
                b[j]='X';
                break;
            }
        }
    }
    char xx=x+'0';
    char yy=y+'0';
    ABs[0]=xx;ABs[1]='A';
    ABs[2]=yy;ABs[3]='B';
    return ABs;
}

char* MiniGame::getAnsKey(){
    return AnswerKey;
}
char* MiniGame::getABs(){
    return ABs;
}

//gameMode 1: ultimate Number!
void MiniGame::generateKey_1(){
    unsigned long myTime;
    myTime=millis();
    srand(myTime);
    AnswerKey_1=rand()%1000+1;
    rangeSmall=1;rangeLarge=1000;
    int_to_char(AnswerKey_1,AnswerKey_1_char);
}

/*helper function*/
void MiniGame::int_to_char(int num, char* arr){
    int len=getLength(num); //get the digits of num
    *arr=(char)0;
    for(int i=len-1;i>=0;i--){
        int tens=(pow(10,len-i)+0.5);
        arr[i]='0'+(num%tens-num%(tens/10))/(tens/10);
    }
}
int MiniGame::commitNumber(char* answer,int len){
    int num=0;
    for(int i=0;i<len;i++){
        num+=(answer[i]-'0')*(int)(pow(10,len-i-1)+0.5);
    }
    if(num==AnswerKey_1){//correct answer
        return 1;
    }
    else if(num>=rangeLarge||num<=rangeSmall){//out-of-range
        return -1;
    }
    else if(num>AnswerKey_1){//incorrect, continue game
        rangeLarge=num;
        return 0;
    }
    else{
        rangeSmall=num;
        return 0;
    }
}
char* MiniGame::getLow(){
    int_to_char(rangeSmall,small);
    return small;
}
char* MiniGame::getHigh(){
    int_to_char(rangeLarge,large);
    return large;
}
/*
int MiniGame::getSmall(){
    return rangeSmall;
}
int MiniGame::getLarge(){
    return rangeLarge;
}*/
int MiniGame::getAnsKey_1(){
    return AnswerKey_1;
}
char* MiniGame::getAnsKey_1_char(){
    return AnswerKey_1_char;
}

/*helper function*/
int MiniGame::getLength(int num){
    for(int i=1;i<=4;i++){
        int tens=(pow(10,i)+0.5);
        if(num%tens==num){return i;}
    }
}
int MiniGame::length(char index){
    switch (index){
    case 'L':
        return getLength(rangeSmall);
        break;
    case 'H':
        return getLength(rangeLarge);
        break;
    case 'A':
        return getLength(AnswerKey_1);
        break;
    default:
        break;
    }
}