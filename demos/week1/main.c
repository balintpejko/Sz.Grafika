#include "cube.h"

#include <stdio.h>

int main() {
    Cuboid my_brick;
    
    // Adatok beállítása
    set_size(&my_brick, 5.0, 5.0, 10.0);

    // Eredmények kiíratása
    printf("Teglatest adatai (%.2f, %.2f, %.2f):\n", my_brick.a, my_brick.b, my_brick.c);
    printf("Felszin: %.2f\n", calc_surface(&my_brick));
    printf("Terfogat: %.2f\n", calc_volume(&my_brick));

    if (has_square_face(&my_brick)) {
        printf("A teglatestnek van negyzet alaku lapja.\n");
    } else {
        printf("A teglatestnek nincs negyzet alaku lapja.\n");
    }

    return 0;
}