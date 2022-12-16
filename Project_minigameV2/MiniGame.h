#ifndef __MINIGAME__H
#define __MINIGAME__H

class MiniGame{
    public:
        //gameMode 0: nAnB
        /*nAnB: Generate the answer key*/
        void generateKey();
        /* nAnB:
         * Submit the answer of 4 digit char array
         * Return a char array: ex. 2A2B
         */
        char* commitAnswer(char* answer);
        /*nAnB: Return the answer key unconditionally*/
        char* getAnsKey();
        /*nAnB: Return the ABs*/
        char* getABs();
        
        /*
        //TBA...
        //gameMode 1: ultimate Number!
        void generateKey_1();
        void commitNumber(int);
        int getLow();
        int getHigh();*/
    private:
        //gameMode 0: nAnB
        char ABs[4];
        char b[4];
        char AnswerKey[4];
        
        /*
        //TBA...
        //gameMode 1: ultimate Number!
        int AnswerKey_1;
        int rangeLow;
        int rangeHigh;*/
};

#endif