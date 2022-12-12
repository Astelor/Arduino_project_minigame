#include "MiniGame.h"
#include <Arduino.h>

//gameMode 0: nAnB

void MiniGame::generateKey(){
    unsigned long myTime;
    myTime=millis();
    srand(myTime);
    for(int i=0; i<4; i++) {AnswerKey[i]=(rand()%10)+'0';}
}

char* MiniGame::commitAnswer(char* answer){
    b[0]=AnswerKey[0];b[1]=AnswerKey[1];
    b[2]=AnswerKey[2];b[3]=AnswerKey[3];
    int x=0, y=0;
    for(int i=0; i<4; i++)
    {
        if(answer[i]==b[i])
        {
            x++;
            answer[i]='X';
            b[i]='X';
        }
    }
    for(int i=0; i<4; i++)
    {
        if(answer[i]=='X') continue;
        for(int j=0; j<4; j++)
        {
            if(answer[i]==b[j])
            {
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
/*
//TBA...
//gameMode 1: ultimate Number!
void MiniGame::generateKey_1(){
    unsigned long myTime;
    myTime=millis();
    srand(myTime);
    AnswerKey_1=rand()%100;
}
void commitNumber(int num){
    if(num==AnswerKey_1){

    }
}
*/