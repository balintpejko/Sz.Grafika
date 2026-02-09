#include "cube.h"

#include <math.h>

void set_size(Cuboid* cuboid, double a, double b, double c) {
    if (a > 0 && b > 0 && c > 0) {
        cuboid->a = a;
        cuboid->b = b;
        cuboid->c = c;
    } else {
        printf("Hiba: Az oldalak hossza csak pozitiv szam lehet!\n");
        cuboid->a = 0;
        cuboid->b = 0;
        cuboid->c = 0;
    }
}

double calc_volume(const Cuboid* cuboid) {
    return cuboid->a * cuboid->b * cuboid->c;
}

double calc_surface(const Cuboid* cuboid) {
    return 2 * (cuboid->a * cuboid->b + 
                cuboid->a * cuboid->c + 
                cuboid->b * cuboid->c);
}

bool has_square_face(const Cuboid* cuboid) {
    return (cuboid->a == cuboid->b || 
            cuboid->a == cuboid->c || 
            cuboid->b == cuboid->c);
}