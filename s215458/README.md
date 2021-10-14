# Prog assignment 1
 First assignment of university programming first semester



## File structure

DB.txt is a file containing data that the program uses, this is not meant for user interaction, logs.txt however contains user readable logs.



## Required program functions:

<ul>
    <li>Train students in addition and subtraction</li>
    <li>Contain 2 different difficulty levels</li>
    <li>Let the user choose between addition and subtraction</li>
    <li>Generate 10 problems</li>
    <li>Take an answer from the user</li>
    <li>Check if the answer is correct</li>
</ul>



## Things to keep track of

<ul>
    <li>How many test, the user has completed</li>
    <li>What type of test are they</li>
    <li>How many answers were correct for each test</li>
</ul>

## Database structure

All of the above data must be easily searchable in the database, likely by stuct/class-like data structure.



## Program structure

We firstly need a function that can check whether the answer is correct or not, this could be done with a function for each  question type, all contained within a struct through function pointers, these functions would take two arraypointers of 10 numbers each as parameters.

We need an end test function to wrap up and store all the data.

We need a question generation function, that takes the difficulty as a parameter.

User initiation of the quiz will be handled in main, and question in and outputs, will be handled in an interface function.