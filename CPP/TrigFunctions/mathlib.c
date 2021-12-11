#include "mathlib.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define pi2 M_PI_2

//2 global variables
//Epsilon for difference checking
//pi for pi
double EPSILON = 1E-10;
double Pi = M_PI;

//Fuction for finding the absolute value of x
double Abs(double x) {
    if (x < 0) {
        return (-1 * x);
    }
    return (x);
}

//Code given by Professor Long on piazza @69
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= x / k;
        sum += term;
    }

    return sum;
}

//Code given by Professor Long on piazza @143
double Sqrt(double x) {
    double y = 1.0;
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}

//Finds arcSin using newtons method
double arcSin(double x) {
    double guess = 0.0, improvement = 1.0;
    while (Abs(x - sin(guess)) > EPSILON) {
        if (1 - x <= 0.2) {
            return (arcCos(Sqrt(1 - x * x)));
        } else if (1 - x >= 1.8) {
            return (-1 * arcCos(Sqrt(1 - x * x)));
        } else {
            improvement = x - sin(guess);
            improvement = improvement / cos(guess);
            guess = guess + improvement;
        }
    }
    return guess;
}

//Finds arcCos using trig identities
double arcCos(double x) {
    return (pi2 - arcSin(x));
}

//Finds arcTan using trig itentities
double arcTan(double x) {
    return (arcSin(x / Sqrt(x * x + 1.0)));
}

//Finds log usin newtons method
double Log(double x) {
    double guess = 1, improvement = 1;
    while (Abs(x - Exp(guess)) > EPSILON) {
        improvement = x - Exp(guess);
        improvement = improvement / Exp(guess);
        guess = guess + improvement;
    }
    return guess;
}
