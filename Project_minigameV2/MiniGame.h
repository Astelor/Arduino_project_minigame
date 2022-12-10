#ifndef __MINIGAME__H
#define __MINIGAME__H

class MiniGame{
    public:
        //gameMode 0: nAnB
        void generateKey();
        char* commitAnswer(char* answer);
        char* getAnsKey();
        char getABs();
        //gameMode 1: ultimate Number!
        void generateKey_1();
        void commitNumber(int);
        int getLow();
        int getHigh();
    private:
        //gameMode 0: nAnB
        char AnswerKey[4];
        char ABs[4];
        char b[4];
        //gameMode 1: ultimate Number!
        int AnswerKey_1;
        int rangeLow;
        int rangeHigh;
};

#endif