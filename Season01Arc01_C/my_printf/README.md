# Welcome to My Printf
***

## Task
The goal of this project is to implement a custom version of the printf function from the C Standard Library. 
This function handles formatted output, allowing for various specifiers such as 
%d, %o, %u, %x, %c, %s, %p to print integers, characters, strings, and pointers. 
Unlike the standard printf, this implementation is constrained to only use low-level functions like write() 
and manages variadic arguments without any external libraries or helpers.

## Description
This project implements the my_printf function, which works similarly to printf by interpreting format specifiers within a format string. 
The challenge lies in:
correctly handling the variable-length argument list (variadic arguments),
writing each data type to the standard output using write().

## Installation
To install and compile the project, run: make
To clean and recompile, run: make re

## Usage
Once compiled, the executable can be used as follows:
./my_printf "Format string with %d, %x, %s, etc." [arguments...]
Example:
./my_printf "Hex: %x, Dec: %d, String: %s" 255 255 "Hello"
will output> Hex: FF, Dec: 255, String: Hello
