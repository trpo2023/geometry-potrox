#include <stdio.h>
#include <libgeometry/geometry.h>
#include <libgeometry/libcalculate.h>

int main()
{
    double ar, perim;
    char figure[64];

    while (1) 
    {
        fgets(figure, 64, stdin);
        if (figure[0] == 'q') 
        {
            return 0;
        }
        if (circle(figure) == 0) 
        {
            perim = perimeter(figure);
            ar = area(figure);

            printf("\nArea : %f\n Perimeter :%f\n", ar, perim);
        }
    }
    return 0;
}
