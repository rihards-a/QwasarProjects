# Welcome to My Mastermind
***

## Task
Mastermind is a code-breaking game where the player has 10 attempts to guess a secret code composed of 4 distinct digits between 0 and 8. 
After each guess, feedback is provided indicating how many digits are correctly placed and how many are correct but misplaced.
The challenge lies in preventing all the possible errors in inputs.

## Description
This project implements the Mastermind game in C. The program generates a random secret code or accepts a custom code via a command-line argument. 
The player enters guesses through standard input, and the program provides feedback after each guess. The number of attempts can also be customized. 
The solution uses the read() syscall for input handling, ensuring compliance with the project constraints.
It handles input validation, including checking for Ctrl+D (EOF) and incorrect guesses.

## Installation
To install and run the project, use the following commands:
make        # To compile the project
make clean  # To remove object files
make fclean # To remove object files and the executable
make re     # To clean and recompile the project

## Usage
Run the program with the following syntax:
./my_mastermind [-c "CODE"] [-t ATTEMPTS]
-c "CODE": (optional) Specify a custom 4-digit code. If not provided, a random code is generated.
-t ATTEMPTS: (optional) Specify the number of attempts. The default is 10.
