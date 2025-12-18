[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=22076317)
# FERA - Ferrari AI Assistant

*FERA is a **menu-driven command line application** that helps users select the perfect Ferarri model best suited for needs, based on a buyer quiz.* *It also estimates finance costs for a 2 year plan, taking into account loans from the bank, the buyer's deposit and APR.*

*FERA uses a **rule-based scoring system**:*

*1. The user completes the quiz which has* **4 key charateristics of the 5 models available**.
*2. Each model is evaluated individually using the **scoring function** based on the user's answers to the quiz.*
*3. The model with the highest total score is selected as the **recommended model**.*

# Menu Overview

## Menu item 1
*Displays a list of five Ferrari models with the following features:*
- Engine horsepower (cv)
- Number of seats
- A description of the car's vibe 

## Menu item 2
*The buyer quiz prompts the user with three simple yes or no questions to score their preferences for the recommendations.*

## Menu Item 3
*It uses the scoring system to display the recommended model with its specification and vibe.*

## Menu Item 4
*It uses **simple interest** for a 24 month plan, accepts user's input of price, deposit and APR and outputs the monthly repayment, total repayment and loan amount from the bank.*

## Menu Item 5
*It logs the user out, saves their recommendation and quiz answers into a separate file to review later if the user wishes.*


This is the basic code for a command line application which you should use for your Unit 2 project.

The code has separated the menu handling code in `main.c` and the function implementations in `funcs.c`. You should add your code to `funcs.c` (or you can create new files if you wish), and update `main.c` to call your functions from the menu.


### 1 Run code

You can build the code as we have been using in the labs with 
`gcc main.c funcs.c -o main.out -lm` (the `-lm` is required to link the math library). You can also use `make -B` to force a rebuild using the provided `Makefile`.

Then run the code with `./main.out`


### 2 The assignment

Please read the assignment brief on the Minerva page for details of what you need to implement. 



### 3 Test command

The `test.sh` script is provided to check that your code compiles correctly. This is what the autograder will use to check your submission. You can run it with `bash test.sh` or `./test.sh` or just `make test`. 

You do not need to modify this script, but you can look at it to see what it does.


### 4 Submit Solution

Use the same method as previous labs to commit and push your code to your GitHub repository for the autograder to check. 

In your final journal post, please include a link to your GitHub repository containing your code  *and* a zip file of your code as an attachment.
