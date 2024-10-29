#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define CODE_LEN 4
#define MAX_DIGIT 8
#define BUFFER_SIZE 10  // Enough to handle extra characters including newline

int string_length(char* str_check) {
    size_t len = 0;
    while (*str_check != '\0') {
        str_check++;
        len++;
    }
    return len;
}

// Function to generate a random code with unique digits
void generate_random_code(int* secret_code) {
    int used_digits[MAX_DIGIT + 1] = {0};
    srand(time(NULL));
    for (int i = 0; i < CODE_LEN;) {
        int new_digit = rand() % (MAX_DIGIT + 1);
        if (!used_digits[new_digit]) {
            secret_code[i] = new_digit;
            used_digits[new_digit] = 1;
            i++;
        }
    }
}

// Validates input: checks if it consists of 4 digits between 0 and MAX_DIGIT
int validate_input(char* buffer) {
    for (int i = 0; i < CODE_LEN; i++) {
        if (buffer[i] < '0' || buffer[i] > '0' + MAX_DIGIT) {
            return 0;
        }
    }
    return 1;
}

// Ensures that all digits in the code are unique
int check_unique_digits(int* code) {
    int used_digits[MAX_DIGIT + 1] = {0};
    for (int i = 0; i < CODE_LEN; i++) {
        if (used_digits[code[i]]) {
            return 0;
        }
        used_digits[code[i]] = 1;
    }
    return 1;
}

// Function to read input using read syscall, returns the length of valid input
int read_input(char* buffer) {
    char c;
    int index = 0;

    // Read character by character until newline or buffer is full
    while (index < CODE_LEN && read(STDIN_FILENO, &c, 1) > 0) {
        if (c == '\n') break;
        buffer[index++] = c;
    }

    // If input exceeds 4 characters, flush remaining characters
    if (index == CODE_LEN && read(STDIN_FILENO, &c, 1) > 0 && c != '\n') {
        while (read(STDIN_FILENO, &c, 1) > 0 && c != '\n');
        return index + 1;
    }

    if (index == 0) return 0;  // Handle Ctrl+D
    buffer[index] = '\0';
    return index;
}

// Function to handle user inputs and check the secret code
void my_mastermind(int* secret_code, int attempts) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    char buffer[BUFFER_SIZE] = {0};
    int round = 0;

    int round_printed = 0;
    while (attempts > 0) {
        if (!round_printed) {
            round_printed = 1;
            printf("---\nRound %d\n", round);
        }

        int input_len = read_input(buffer);
        if (input_len == 0) {  // Handle Ctrl+D or EOF
            return;
        }

        // If input is not exactly 4 characters, display error
        if (input_len != CODE_LEN || !validate_input(buffer)) {
            printf("Wrong input!\n");
            continue;
        }

        int guess[CODE_LEN];
        for (int i = 0; i < CODE_LEN; i++) {
            guess[i] = buffer[i] - '0';
        }

        // Check if guess contains unique digits
        if (!check_unique_digits(guess)) {
            printf("Wrong input!\n");
            continue;
        }

        int well_placed = 0, misplaced = 0;
        int used_digits[CODE_LEN] = {0};

        // Check well-placed and misplaced digits
        for (int i = 0; i < CODE_LEN; i++) {
            if (guess[i] == secret_code[i]) {
                well_placed++;
            }
            else {
                for (int j = 0; j < CODE_LEN; j++) {
                    if (guess[i] == secret_code[j] && !used_digits[j]) {
                        misplaced++;
                        used_digits[j] = 1;
                        break;
                    }
                }
            }
        }

        if (well_placed == CODE_LEN) {
            printf("Congratz! You did it!\n");
            return;
        }

        printf("Well placed pieces: %d\n", well_placed);
        printf("Misplaced pieces: %d\n", misplaced);
        round_printed = 0;
        attempts--;
        round++;
    }
}


int main(int argc, char* argv[]) {
    int secret_code[CODE_LEN] = {0};
    int attempts = 10;  // Default attempt count
    int specified_code = 0;

    // Parsing command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            // Validate custom code length and content
            if (string_length(argv[i+1]) != CODE_LEN || !validate_input(argv[i+1])) {
                printf("Wrong input!\n");
                return 0;
            }
            for (int j = 0; j < CODE_LEN; j++) {
                secret_code[j] = argv[i+1][j] - '0';
            }
            if (!check_unique_digits(secret_code)) {
                printf("Wrong input!\n");
                return 0;
            }
            specified_code = 1;
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            attempts = *argv[i+1] - '0'; // atoi() could also be used
            if (attempts <= 0) { 
                printf("Wrong input!\n");
                return 0;
            }
        }
    }

    // Generate random code if not specified
    if (!specified_code) {
        generate_random_code(secret_code);
    }

    // Start the game
    my_mastermind(secret_code, attempts);
    return 0;
}
