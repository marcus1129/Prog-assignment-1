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
    //Calculates the answer based on the math type
    if(opType == 1){
        return a + b;
    }
    else if(opType == 2){
        return a - b;
    }
}


void generateNumberSets(int difficulty){
    //Random seed
    srand(time(0));

    //Generates 2 random sets of numbers based on difficulty
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

    //Clears command prompt
    system("cls");

    //Prints every question and evaluates the users answer
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
        //Evaluates if user's input is correct
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
    //Gets and returns a user input
    gets(str);
    return atoi(str);
}

int getDifficulty(){
    char str[1];
    printf("Choose what type of exercises you want, enter \'1\' for 1 digit or \'2\' for 2 digits \n");
    //Gets and returns a user input
    gets(str);
    return atoi(str);
}

void endTest(int opType, int difficulty, int *arrayOfAnswers){
    //Counts how many answers were correct
    for(int i = 0; i < questionCount; i++){
        if(arrayOfAnswers[i] == 0b00000001){
            correctCounter++;
        }
    }

    //Calculates how many answers were incorrect
    inCorrectCounter = (float)questionCount - correctCounter;

    //Calculates what percentage was correct
    correctPercent = (correctCounter/(float)questionCount)*100.0;

    //Creates a string based on math type
    if(opType == 1){
        strcpy(opTypeString, "addition");
    }
    else if(opType == 2){
        strcpy(opTypeString, "subtraction");
    }
    printf("You answered %d questions correct and %d questions incorrect.\nThats %d percent with a math type of %s and a difficulty of %d", (int)correctCounter, (int)inCorrectCounter, (int)correctPercent, opTypeString, difficulty);
}

void writeToDB(int opType, int difficulty, int *arrayOfAnswers, char *filePath){
    //Opens file
    FILE *fp;
    fp = fopen(filePath, "a");
    int temp = 0;

    //Prints quiz data to the file
    fprintf(fp, "Q{o%d;d%d;a", opType, difficulty);
    for(int x = 0; x < 10; x++){
        temp += arrayOfAnswers[x];
    }
    fprintf(fp, "%d;}", temp);

    //Closes file
    fclose(fp);
}

void readFromDB(char *filePath2, int searchType){
    //Allocates buffer
    char *buffer = calloc(1, sizeof(char[100]));

    int totalQuestionCount = 0;

    //Opens file
    FILE *fp2;
    fp2 = fopen(filePath2, "r");

    int n = 1000;
    int tempOpType;
    int opType1Counter = 0;
    int opType2Counter = 0;

    //Reads from file
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
    int requestedOpType;
    int requestedPercent;
    int requestTotal = 0;
    char temp[1];

    //Gets what user wants to search for
    if(searchType == 1){
        printf("Enter \'1\' to search for addition quizzes or \'2\' to search for subtraction quizzes: \n");
        gets(temp);
        requestedOpType = atoi(temp);
        printf("Enter the requested percent: \n");
        gets(temp);
        requestedPercent = atoi(temp);
    }

    //Loops through every character in file
    for(int z = 0; z < 100; z++){
        //If character is an o we have found the opType
        if(buffer[z] == 'o'){
            if(buffer[z+1] == '1'){
                if(requestedOpType == 1){
                    if(buffer[z+8] != ';'){
                        if(requestedPercent <= 100){
                            requestTotal++;
                        }
                    }
                    else{
                        if(requestedPercent <= (buffer[z+7]-'0')*10){
                            requestTotal++;
                        }
                    }
                }
                opType1Counter++;
                if(buffer[z+8] != ';'){
                    totalOp1Correct += 10;
                }
                else{
                    totalOp1Correct += (buffer[z+7]-'0');
                }
            }
            if(buffer[z+1] == '2'){
                if(requestedOpType == 2){
                    if(buffer[z+8] != ';'){
                        if(requestedPercent <= 100){
                            requestTotal++;
                        }
                    }
                    else{
                        if(requestedPercent <= (buffer[z+7]-'0')*10){
                            requestTotal++;
                        }
                    }
                }
                opType2Counter++;
                if(buffer[z+8] != ';'){
                    totalOp2Correct += 10;
                }
                else{
                    totalOp2Correct += (buffer[z+7]-'0');
                }
            }
        }
        //If we have found the character a we have found the amount of correct answers
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

    FILE *fp3;
    fp3 = fopen("logs.txt", "a");

    //Outputs result based on what the user wanted
    if(searchType == 1){
        printf("There is %d quiz(zes) that fullfill your requirements. \n", requestTotal);
    }
    else if(searchType == 2){
        printf("Total quizzes taken: %d \n", totalQuestionCount);
        printf("Total addition quizzes taken: %d with a total correct percentage: %d \n", opType1Counter, totalOp1Percent);
        printf("Total subtraction quizzes taken: %d with a total correct percentage: %d \n", opType2Counter, totalOp2Percent);
        printf("Total quizzes with more than 50%% correct: %d \n", fiftyPlus);
        printf("Total quizzes with 100%% correct: %d \n", allCorrect);
        printf("Total quizzes with 50%% to 75%% correct: %d \n", fiftyTo75);
        fprintf(fp3, "\\\\\n");
        fprintf(fp3, "Total quizzes taken: %d \n", totalQuestionCount);
        fprintf(fp3, "Total addition quizzes taken: %d with a total correct percentage: %d \n", opType1Counter, totalOp1Percent);
        fprintf(fp3, "Total subtraction quizzes taken: %d with a total correct percentage: %d \n", opType2Counter, totalOp2Percent);
        fprintf(fp3, "Total quizzes with more than 50%% correct: %d \n", fiftyPlus);
        fprintf(fp3, "Total quizzes with 100%% correct: %d \n", allCorrect);
        fprintf(fp3, "Total quizzes with 50%% to 75%% correct: %d \n", fiftyTo75);
    }

    fclose(fp2);
    fclose(fp3);
}

size_t main()
{
    int arrayOfAnswers[questionCount];

    //Gets what type of question the user wants
    int opType = getOpType();
    
    //Reads from database
    if(opType == 3){
        printf("Enter 1 to search for data or 2 to get all data: \n");
        char tempInput[1];
        gets(tempInput);
        //Takes user input and file path to database to find the data the user wants
        readFromDB("DB.txt", atoi(tempInput));
    }
    else{
        //Gets what difficulty level the user wants
        int difficulty = getDifficulty();

        //Conducts the test, using the opType, difficulty and an array that will be filled with the users answers
        interface(opType, difficulty, arrayOfAnswers);

        //Wraps up data
        endTest(opType, difficulty, arrayOfAnswers);

        //Stores data
        writeToDB(opType, difficulty, arrayOfAnswers, "DB.txt");
    }
    return 0;
}
