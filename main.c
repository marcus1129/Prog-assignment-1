#include <stdio.h>
#include <stdlib.h>

typedef struct math{
    appropriateMathOp(int enumerator);
    add(add)(int, int)*
    sub(sub)(int, int)*
}

int generateNumberSets[][](int difficulty){
    int totalNumberSet[][];
    int numberSet1[];
    int numberSet2[];
    if(difficulty == 1){
        randomGenerate2DigitNumbers(numberSet1, numberSet2);
    }
    else if(difficulty == 2){
        randomGenerate3DigitNumbers(numberSet1, numberSet2);
    }
}

int interface[][](int difficulty, int arrayOfAnswerCorrectness[]*, questionCount){
    int questionNumbers[][] = generateNumberSets(diffculty, questionCount);
    char str[100];
    math obj;
    for(int i = 0; i < questionCount; i++){
        printf("%i + %i", questionCount[i][1], questionCount[i][2]);
        gets(str);
        if(str == mkstr(obj->appropriateMathOp(opType))){
            printf("Correct");
            arrayOfAnswerCorrectness[i] = 1;
        }
        else{
            printf("Incorrect");
            arrayOfAnswerCorrectness[i] = 0;
        }
    }
}

int main()
{
    int questionCount;
    int opType = getOpType();
    int difficulty = getDifficulty();
    interface(opType, difficulty, arrayOfAnswerCorrectness*, questionCount);
    endTest(opType, difficulty, arrayOfAnswerCorrectness*, questionCount);



    return 0;
}
