#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgeometry/libcalculate.h"

double findRadius(char* string)
{
    int length = 0;
    char radius[10];
    while (string[length] != ',') {
        length++;
    }

    length++;
    int currentEl = 0;
    while (string[length] != ')') {
        radius[currentEl] = string[length];
        currentEl++;
        length++;
    }
    radius[currentEl + 2] = '\0';
    double Radius = atof(radius);
    return Radius;
}

double perimeter(char string[])
{
    double radius = findRadius(string);
    double res = M_PI * radius * 2;
    return res;
}

double area(char string[])
{
    double radius = findRadius(string);
    double res = M_PI * radius * radius;
    return res;
}