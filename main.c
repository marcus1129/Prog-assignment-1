#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int questionCount = 10;
int totalNumberSet[2][10];
float correctCounter = 0.f;
float inCorrectCounter;
float correctPercent;
char opTypeString[20];

/*typedef struct quiz{
    int opType;
    int arrayOfAnswers[questionCount];
}*/

/*void allocQuizArray(int numQuiz){
    QUIZ* quiz = malloc(numQuiz * sizeof *quiz);
}*/

int appropriateMathOp(int opType, int a, int b){
    if(opType == 1){
        return a + b;
    }
    else if(opType == 2){
        return a - b;
    }
}


void generateNumberSets(int difficulty){
    srand(time(0));
    if(difficulty == 1){
        for(int x = 0; x < questionCount; x++){
            totalNumberSet[0][x] = rand() % 10;
            totalNumberSet[1][x] = rand() % 10;
        }
    }
    else if(difficulty == 2){
        for(int x = 0; x < questionCount; x++){
            totalNumberSet[0][x] = rand() % 100;
            totalNumberSet[1][x] = rand() % 100;
        }
    }
}

int interface(int opType, int difficulty, int *arrayOfAnswers){
    generateNumberSets(difficulty);
    char str[4];
    system("cls");
    for(int i = 0; i < questionCount; i++){
        strcpy(str, "");
        if(opType == 1){
            printf("%d + %d \n", totalNumberSet[0][i], totalNumberSet[1][i]);
        }
        else if(opType == 2){
            printf("%d - %d \n", totalNumberSet[0][i], totalNumberSet[1][i]);
        }
        gets(str);
        if(atoi(str) == appropriateMathOp(opType, totalNumberSet[0][i], totalNumberSet[1][i])){
            printf("Correct \n\n");
            arrayOfAnswers[i] = 1;
        }
        else{
            printf("Incorrect, the correct answer is: %d \n \n", appropriateMathOp(opType, totalNumberSet[0][i], totalNumberSet[1][i]));
            arrayOfAnswers[i] = 0;
        }
    }
}

int getOpType(){
    char str[1];
    printf("Choose what type of exercises you want, enter \'1\' for addition or \'2\' for subtraction \n");
    gets(str);
    return atoi(str);
}

int getDifficulty(){
    char str[1];
    printf("Choose what type of exercises you want, enter \'1\' for 1 digit or \'2\' for 2 digits \n");
    gets(str);
    return atoi(str);
}

void endTest(int opType, int difficulty, int *arrayOfAnswers){
    for(int i = 0; i < questionCount; i++){
        if(arrayOfAnswers[i] == 0b00000001){
            correctCounter++;
        }
    }
    inCorrectCounter = (float)questionCount - correctCounter;
    correctPercent = (correctCounter/(float)questionCount)*100.0;
    if(opType == 1){
        strcpy(opTypeString, "addition");
    }
    else if(opType == 2){
        strcpy(opTypeString, "subtraction");
    }
    printf("You answered %d questions correct and %d questions incorrect.\nThats %d percent with a math type of %s and a difficulty of %d", (int)correctCounter, (int)inCorrectCounter, (int)correctPercent, opTypeString, difficulty);
}

/*storeData(int opType, int difficulty){
    objOfTypeQuizContainingAllData obj;
    writeToDB(obj);
    
}*/

size_t main()
{
    int arrayOfAnswers[questionCount];

    //Gets what type of question the user wants
    int opType = getOpType();

    //Gets what difficulty level the user wants
    int difficulty = getDifficulty();

    //Conducts the test
    interface(opType, difficulty, arrayOfAnswers);

    //Wraps up data
    endTest(opType, difficulty, arrayOfAnswers);

    //Stores data
    //storeData(opType, difficulty);
    //readFromDB(obj);
    return 0;
}
