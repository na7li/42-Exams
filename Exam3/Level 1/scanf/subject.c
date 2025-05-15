
/*
Assignment name  : ft_scanf
Expected files   : ft_scanf.c
Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------


Write a function named `ft_scanf` that will mimic the real scanf with the following constraints:

- It will manage only the following conversions: s, d, and c
- You don't have to handle the options *, m and '
- You don't have to handle the maximum field width
- You don't have to handle the types modifier characters (h, hh, l, etc.)
- You don't have to handle the conversions beginning with %n$

Your function must be declared as follows:

int ft_scanf(const char *, ... );

You will find in this directory a file containing a part of the code you will need, you just have to complete it.

To test your program compare your results with the real scanf.

Hint : You may need to read the man of scanf.


/* Subject:
Mimic standard scanf function
*** OLD *** Allowed functions and globals: isspace, isdigit, va_start, va_arg, va_copy, va_end
Allowed functions: fgetc, ungetc, ferror, feof, isspace, isdigit, stdin, va_start, va_arg, va_copy, va_end
Realize only the conversations - s, d, c.
Dont have to handle the options *, m and '.
Dont have to handle the maximum field width
Dont have to handle the types modifier characters (h, hh, l...)
Dont have to handle the conversations beginning with %n$
Your function int ft_scanf(const char *format, ...);
void skip_input_space()
{
    // Input your code here
}

int scan_char(va_list ap)
{
    // Input your code here
}

int scan_int(va_list ap)
{
    // Input your code here
}

int scan_string(va_list ap)
{
    // Input your code here
}


*/