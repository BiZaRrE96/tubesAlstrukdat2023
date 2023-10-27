/**
Filename: pcolor.h
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
Modified at: 23/10/2023
**/

/**
Details

print_xxx(c) will print c with xxx color. Import this header to use the declared functions.
We only provide 8 colors. Feel free to modify/add colors if you want to.
**/

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define YELLOW "\x1B[33m"

#define START_RED printf("%s", RED)
#define START_GREEN printf("%s", GREEN)
#define START_BLUE printf("%s", BLUE)
#define START_YELLOW printf("%s", YELLOW)

#define STOP_COLOR printf("%s", NORMAL)

void print_red(char c);
void print_green(char c);
void print_blue(char c);

void print_red(char c)
{
    printf("%s%c", RED, c);
    printf("%s", NORMAL);
}

void print_green(char c)
{
    printf("%s%c", GREEN, c);
    printf("%s", NORMAL);
}

void print_blue(char c)
{
    printf("%s%c", BLUE, c);
    printf("%s", NORMAL);
}

void print_string_red(char c[])
{
    printf("%s%s", RED, c);
    printf("%s", NORMAL);
}

void print_string_green(char c[])
{
    printf("%s%s", GREEN, c);
    printf("%s", NORMAL);
}

void print_string_blue(char c[])
{
    printf("%s%s", BLUE, c);
    printf("%s", NORMAL);
}

void print_string_yellow(char c[])
{
    printf("%s%s", YELLOW, c);
    printf("%s", NORMAL);
}