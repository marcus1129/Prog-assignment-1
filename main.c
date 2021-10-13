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
        else{
            printf("OPTYPE ERROR \n");
            break;
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
    printf("Choose what type of exercises you want, enter \'1\' for addition, \'2\' for subtraction or \'3\' for seaching the database. \n");
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

void writeToDB(int opType, int difficulty, int *arrayOfAnswers, char *filePath){
    FILE *fp;
    fp = fopen(filePath, "a");
    int temp = 0;

    fprintf(fp, "Q{o%d;d%d;a", opType, difficulty);
    for(int x = 0; x < 10; x++){
        temp += arrayOfAnswers[x];
    }
    fprintf(fp, "%d;}", temp);

    fclose(fp);
}

void readFromDB(char *filePath2){
    char *buffer = calloc(1, sizeof(char[100]));
    int totalQuestionCount = 0;
    FILE *fp2;
    fp2 = fopen(filePath2, "r");
    int n = 1000;
    int tempOpType;
    int opType1Counter = 0;
    int opType2Counter = 0;


    fgets(buffer, n, fp2);
    for(int z = 0; z < 100; z++){
        if(buffer[z] == 'Q'){
            totalQuestionCount = totalQuestionCount + 1;
        }
    }

    int quizCounter = 0;
    char tempArr[10];
    int totalOp1Correct = 0;
    int totalOp2Correct = 0;
    int allCorrect = 0;
    int fiftyPlus = 0;
    int fiftyTo75 = 0;


    for(int z = 0; z < 100; z++){
        if(buffer[z] == 'o'){
            if(buffer[z+1] == '1'){
                opType1Counter++;
                if(buffer[z+8] != ';'){
                    totalOp1Correct += 10;
                }
                else{
                    totalOp1Correct += (buffer[z+7]-'0');
                }
            }
            if(buffer[z+1] == '2'){
                opType2Counter++;
                if(buffer[z+8] != ';'){
                    totalOp2Correct += 10;
                }
                else{
                    totalOp2Correct += (buffer[z+7]-'0');
                }
            }
        }
        else if(buffer[z] == 'a'){
            if(buffer[z+1] == '1' && buffer[z+2] == '0'){
                allCorrect++;
            }
            if(buffer[z+1] > '5'){
                fiftyPlus++;
            }
            if(buffer[z+1] > '5' && buffer[z+1] < '8'){
                fiftyTo75++;
            }
        }
    }

    int totalOp1Percent = (float)totalOp1Correct/((float)opType1Counter*10.f)*100.f;
    int totalOp2Percent = (float)totalOp2Correct/((float)opType2Counter*10.f)*100.f;

    printf("Total quizzes taken: %d \n", totalQuestionCount);
    printf("Total addition quizzes taken: %d with a total correct percentage: %d \n", opType1Counter, totalOp1Percent);
    printf("Total subtraction quizzes taken: %d with a total correct percentage: %d \n", opType2Counter, totalOp2Percent);
    printf("Total quizzes with more than 50%% correct: %d \n", fiftyPlus);
    printf("Total quizzes with more than 100%% correct: %d \n", allCorrect);
    printf("Total quizzes with 50%% to 75%% correct: %d \n", fiftyTo75);


    fclose(fp2);
}

size_t main()
{
    int arrayOfAnswers[questionCount];
    char filePath[] = "DB.txt";

    //Gets what type of question the user wants
    int opType = getOpType();
    
    if(opType == 3){
        readFromDB("DB.txt");
    }
    else{
        //Gets what difficulty level the user wants
        int difficulty = getDifficulty();

        //Conducts the test
        interface(opType, difficulty, arrayOfAnswers);

        //Wraps up data
        endTest(opType, difficulty, arrayOfAnswers);

        //Stores data
        writeToDB(opType, difficulty, arrayOfAnswers, filePath);
    }
    return 0;
}
