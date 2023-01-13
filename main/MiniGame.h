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
        
        //gameMode 1: ultimate Number!
        /*GTN: Generate the answer key*/
        void generateKey_1();
        /* GTN: check the number
         * returns -1 if commited out-of-range number
         * returns 1 if commited-number=answerkey, end of game
         * returns 0 if not end of game
         */
        int commitNumber(char* answer,int);
        char* getLow();
        char* getHigh();
        //int getSmall();
        //int getLarge();
        int getAnsKey_1();
        char* getAnsKey_1_char();
        /* returns the length of the array
         * 'L': rangeLow 'H': rangeHigh 'A': AnsKey_1
         */
        int length(char);
    private:
        //gameMode 0: nAnB
        char ABs[4];
        char b[4];
        char AnswerKey[4];
        
        //gameMode 1: ultimate Number!
        void int_to_char(int, char*arr);
        int getLength(int);
        int AnswerKey_1;
        int rangeSmall;
        int rangeLarge;
        char AnswerKey_1_char[4];
        char small[4];
        char large[4];
};

#endif