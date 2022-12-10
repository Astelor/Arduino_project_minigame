#ifndef __MINIGAME__H
#define __MINIGAME__H

class MiniGame{
    public:
        void generateKey();
        char* commitAnswer(char* answer);
        char* getAnsKey();
        char getABs();

    private:
        char AnswerKey[4];
        char ABs[4];
        char b[4];
};

#endif