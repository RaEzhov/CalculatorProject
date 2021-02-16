#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
#include "tree.h"

int main() {
    complex double a = 5.0 + 3.0*I, b = 7 + 2*I, z;
    z = a / b;
    return 0;
}
