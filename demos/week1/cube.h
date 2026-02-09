#include <stdio.h>
#include <stdbool.h> // A bool típus használatához

// 1. Struktúra definíció
typedef struct {
    double a;
    double b;
    double c;
} Cuboid;

// 2. Beállító függvény
void set_size(Cuboid* cuboid, double a, double b, double c);

// 3. Térfogat számítása
double calc_volume(const Cuboid* cuboid);

// 4. Felszín számítása
double calc_surface(const Cuboid* cuboid);

// 5. Négyzet alakú lap vizsgálata
bool has_square_face(const Cuboid* cuboid);

