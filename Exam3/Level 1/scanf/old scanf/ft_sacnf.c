#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void skip_input_space()
{
    // Skip any leading whitespace
    int ch = fgetc(stdin);
    while (isspace(ch))
        ch = fgetc(stdin);
    ungetc(ch, stdin); // Put the first non-whitespace character back
}

int scan_char(va_list ap)
{
    skip_input_space(); // Skip any whitespace before reading a character
    int ch = fgetc(stdin);
    if (ch == EOF)
        return 0; // No input

    char *ptr = va_arg(ap, char *); // Get the character pointer
    *ptr = (char)ch;

    return 1; // Success
}

int scan_int(va_list ap)
{
    skip_input_space(); // Skip any whitespace before reading a number

    int result = 0;
    int sign = 1; // Default to positive

    int ch = fgetc(stdin);
    if (ch == EOF)
        return 0; // No input

    // Check if the number is negative
    if (ch == '-')
    {
        sign = -1;
        ch = fgetc(stdin); // Read the next character
    }
    else if (ch == '+')
    {
        ch = fgetc(stdin); // Skip over the '+'
    }

    // Read digits
    while (isdigit(ch))
    {
        result = result * 10 + (ch - '0'); // Build the integer
        ch = fgetc(stdin); // Read the next character
    }

    // If no digits were found, return 0
    if (result == 0 && ch != '0')
    {
        ungetc(ch, stdin); // Push back the non-digit character
        return 0;
    }

    // Apply the sign to the result
    result *= sign;

    // Store the result in the argument
    int *ptr = va_arg(ap, int *);
    *ptr = result;

    return 1; // Success
}

int scan_string(va_list ap)
{
    skip_input_space(); // Skip any leading whitespace

    char *ptr = va_arg(ap, char *); // Get the string pointer
    int ch = fgetc(stdin);
    if (ch == EOF)
        return 0; // No input

    int index = 0;
    // Read characters until we hit whitespace or EOF
    while (!isspace(ch) && ch != EOF)
    {
        ptr[index++] = (char)ch;
        ch = fgetc(stdin);
    }

    ptr[index] = '\0'; // Null-terminate the string

    // If no characters were read, return 0
    if (index == 0)
        return 0;

    return 1; // Success
}

int ft_scanf(const char *format, ...)
{
    va_list ap;
    int count = 0;
    int format_len = 0;

    va_start(ap, format);

    while (format[format_len] != '\0') {
        if (format[format_len] == '%' && format[format_len + 1] != '\0') 
        {
            format_len++; // Move past the '%'

            if (format[format_len] == 'd') {
                if (scan_int(ap))
                    count++;
            }
            else if (format[format_len] == 's') {
                if (scan_string(ap))
                    count++;
            }
            else if (format[format_len] == 'c') {
                if (scan_char(ap))
                    count++;
            }
        }
        format_len++;
    }

    va_end(ap);
    return count; // Return the number of successful conversions
}


int main()
{
    int num;
    char ch;
    char str[100];

    // Test 1: %d %s %c
    printf("Test 1: %%d %%s %%c\n");
    printf("Enter input: 42 \"Hello World\" a\n");
    int result1 = ft_scanf("%d %s %c", &num, str, &ch);
    printf("Returned value: %d\n", result1);
    printf("num = %d, str = \"%s\", ch = '%c'\n\n", num, str, ch);

    // Test 2: %d
    printf("Test 2: %%d\n");
    printf("Enter input:  123\n");
    int result2 = ft_scanf("%d", &num);
    printf("Returned value: %d\n", result2);
    printf("num = %d\n\n", num);

    // Test 3: %d %s
    printf("Test 3: %%d %%s\n");
    printf("Enter input: abc\n");
    int result3 = ft_scanf("%d %s", &num, str);
    printf("Returned value: %d\n", result3);
    printf("num = %d, str = \"%s\"\n\n", num, str);

    return 0;
}



// #include <stdarg.h>

// void skip_input_space()
// {
//     // Input your code here
// }

// int scan_char(va_list ap)
// {
//     // Input your code here
// }

// int scan_int(va_list ap)
// {
//     // Input your code here
// }

// int scan_string(va_list ap)
// {
//     // Input your code here
// }

// int ft_scanf(const char *format, ... )
// {

// }