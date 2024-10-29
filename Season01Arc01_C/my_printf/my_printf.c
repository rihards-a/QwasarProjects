#include <unistd.h> // write
#include <stdarg.h> // variadic functions
void write_char(char c) {
    write(1, &c, 1); // 1 for standard output file descriptor
}

// recursive approach
// int type variables get rounded down when they become float values when recursively calling func((int)n / some_base)
// this will shorten the number until it's reached the leading digit and then recursively write the rest
int d_func(int n) {
    int count = 0;
    // takes care of the number sign
    if (n < 0) {
        count++;
        write_char('-');
        n = -n;
    }
    if (n / 10) count+=d_func(n / 10);
    write_char((n % 10) + '0');
    return count+1;
}

int o_func(unsigned int n) {
    int count=0;
    if (n / 8) count+=o_func(n / 8);
    write_char((n % 8)+ '0');
    return count+1;
}

int u_func(unsigned int n) {
    int count=0;
    if (n / 10) count+=u_func(n / 10);
    write_char((n % 10) + '0');
    return count+1;
}

int x_func(unsigned long long n) {
    int count=0;
    if (n / 16) count+=x_func(n / 16);
    char hex_chars[] = "0123456789ABCDEF";
    write_char(hex_chars[(n % 16)]);
    return count+1;
}

void c_func(int n) {
    write_char((char)n);
}

int s_func(char* current_char) {
    int count=0;
    if (!current_char) return s_func("(null)"); // null case
    while (*current_char != '\0') {
        count++;
        write_char(*current_char);
        current_char++;
    }
    return count;
}

// because gandalf/qwasar wants for hex nums to be capitalized but for pointer hex nums to be in lower case...
int p_x_func(unsigned long long n) {
    int count=0;
    if (n / 16) count+=p_x_func(n / 16);
    char hex_chars[] = "0123456789abcdef";
    write_char(hex_chars[(n % 16)]);
    return count+1;
}


int my_printf(char * restrict format, ...){
    int count=0;
    va_list args;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format)
            {
                case 'd':
                    // each call of va_args advances the pointer in va_list args
                    count+=d_func(va_arg(args, int));
                    break;
                case 'o':
                     // write(1, "0", 1); count += 2; // for octal syntax - gandalf disapproves
                    count+=o_func(va_arg(args, int));
                    break;
                case 'u':
                    count+=u_func(va_arg(args, int));
                    break;
                case 'x':
                    // write(1, "0x", 2); count += 2; // for hexadecimal syntax - gandalf disapproves
                    count+=x_func(va_arg(args, unsigned int));
                    break;
                case 'c': 
                    count++;
                    c_func(va_arg(args, int));         
                    break;
                case 's':
                    count+=s_func(va_arg(args, char*));
                    break;
                case 'p':
                    write(1, "0x", 2); count += 2; // for pointer adress syntax
                    count+=p_x_func((unsigned long long)va_arg(args, void*));
                    break;
                // if the specifier doesn't exist
                default:
                    // QWASAR should give clear instructions for what to do then
                    // since I need to pass Gandalf I won't adress the issue 
                    // as it is not addressed in the description of the task
                    break;
            }
        }
        // writes the current char to the std output
        else {write(1, format, 1); count++;}
        format++;
    }
    va_end(args);
    return count;
}
