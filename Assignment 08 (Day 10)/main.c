#include <stdio.h>
#include "circle.h"
#include "square.h"
#include "rectangle.h"

int main() {
    double radius, side, length, width;
    
    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);
    printf("Area of the circle: %.2f\n", calculate_circle_area(radius));
    
    printf("Enter the side length of the square: ");
    scanf("%lf", &side);
    printf("Area of the square: %.2f\n", calculate_square_area(side));

    printf("Enter the length and width of the rectangle: ");
    scanf("%lf %lf", &length, &width);
    printf("Area of the rectangle: %.2f\n", calculate_rectangle_area(length, width));

    return 0;
}
