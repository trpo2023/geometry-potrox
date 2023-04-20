#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libgeometry/geometry.h>

int print_error(int error_msg, int CurrentEl, char* strerr)
{
    switch (error_msg) {
    case 1:
        printf("Error at column 0: expected 'circle' instead of %s\n", strerr);
        return error_msg;

    case 2:
        printf("Error at column %d: expected '.' \n", CurrentEl);
        return error_msg;
    case 3:
        printf("Error at column %d: unexpected character\n", CurrentEl);
        return error_msg;
    case 4:
        printf("Error at column %d: expected number\n", CurrentEl);
        return error_msg;

    case 5:
        printf("Error at column %d: expected ' '\n", CurrentEl);
        return error_msg;
    case 6:
        printf("Error at column %d: expected '('\n", CurrentEl);
        return error_msg;

    case 7:
        printf("Error at column %d: expected ','\n", CurrentEl);
        return error_msg;
    case 8:
        printf("Error at column %d: expected ')'\n", CurrentEl);
        return error_msg;
    }
    return 0;
}

int check_num(char figure[], int* pointer)
{
    int CurrentEl = *pointer;

    char numstr[13] = "-.0123456789";

    int error_msg;

    while (figure[CurrentEl] == ' ') {
        CurrentEl++;
    }

    if (figure[CurrentEl] == '0') {
        if (figure[CurrentEl + 1] != '.'
            && strchr(numstr, figure[CurrentEl + 1]) != NULL) {
            return print_error(error_msg = 2, CurrentEl, 0);
        }
    }

    if (strchr(numstr, figure[CurrentEl]) == NULL) {
        return print_error(error_msg = 3, CurrentEl, 0);
    }

    while (strchr(numstr, figure[CurrentEl]) != NULL) {
        CurrentEl++;
    }

    if (figure[CurrentEl] == ',' || figure[CurrentEl] == ')') {
        return print_error(error_msg = 4, CurrentEl, 0);
    }

    if (figure[CurrentEl] != ' ') {
        return print_error(error_msg = 5, CurrentEl, 0);
    }

    while (figure[CurrentEl] == ' ') {
        CurrentEl++;
    }

    if (figure[CurrentEl] == '0') {
        if (figure[CurrentEl + 1] != '.'
            && strchr(numstr, figure[CurrentEl + 1]) != NULL) {
            return print_error(error_msg = 2, CurrentEl, 0);
        }
    }

    if (strchr(numstr, figure[CurrentEl]) == NULL) {
        return print_error(error_msg = 3, CurrentEl, 0);
    }

    while (strchr(numstr, figure[CurrentEl]) != NULL) {
        CurrentEl++;
    }

    while (figure[CurrentEl] == ' ') {
        CurrentEl++;
    }

    CurrentEl++;
    *pointer = CurrentEl;
    return 0;
}

int circle(char* figure)
{
    int error_msg;
    char str_circle[6] = "circle";
    char strnum[13] = "-.0123456789";

    for (int i = 0; i < 5; i++) {
        figure[i] = tolower(figure[i]);

        if (figure[i] != str_circle[i]) {
            char strerror[6];
            strncpy(strerror, figure, 6);
            strerror[6] = '\0';
            return print_error(error_msg = 1, 0, strerror);
        }
    }

    int CurrentEl = 7;

    if (figure[6] != '(') {
        return print_error(error_msg = 6, CurrentEl, 0);
    }

    if (check_num(figure, &CurrentEl) != 0) {
        return -1;
    }

    if (figure[CurrentEl - 1] != ',') {
        return print_error(error_msg = 7, CurrentEl, 0);
    }

    while (figure[CurrentEl] == ' ') {
        CurrentEl++;
    }

    if (figure[CurrentEl] == '0') {
        if (figure[CurrentEl + 1] != '.'
            && strchr(strnum, figure[CurrentEl + 1]) != NULL) {
            return print_error(error_msg = 2, CurrentEl, 0);
        }
    }

    if (strchr(strnum, figure[CurrentEl]) == NULL) {
        return print_error(error_msg = 3, CurrentEl, 0);
    }

    while (strchr(strnum, figure[CurrentEl]) != NULL) {
        CurrentEl++;
    }

    if (figure[CurrentEl] != ')') {
        return print_error(error_msg = 8, CurrentEl, 0);
    }
    return 0;
}