#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//Options is the command line options that can be added.
#define OPTIONS "asctl"

//Main function
int main(int argc, char **argv) {
    int opt = 0;
    bool asinb = false;
    bool acosb = false;
    bool atanb = false;
    bool logn = false;
    if (argc == 1) {
        printf("Program usage: ./mathlib-test -[asctl]\n");
        printf("  -a   Runs all tests (arcsin, arccos, arctan, log)\n");
        printf("  -s   Runs arcsin tests\n");
        printf("  -c   Runs arccos tests\n");
        printf("  -t   Runs arctan tests\n");
        printf("  -l   Runs log tests\n");
    }
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            asinb = true;
            acosb = true;
            atanb = true;
            logn = true;
            break;

        case 's': asinb = true; break;
        case 'c': acosb = true; break;
        case 't': atanb = true; break;
        case 'l': logn = true; break;
        default: break;
        }
    }

    if (asinb) {
        double arcs;
        double libs;
        double Difference;
        printf("  x            arcSin           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double x = -1; x < 1; x += 0.1) {
            arcs = arcSin(x);
            libs = asin(x);
            Difference = arcs - libs;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcs, libs, Difference);
        }
    }

    if (acosb) {
        double arcb;
        double libb;
        double Difference;
        printf("  x            arcCos           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double x = -1; x < 1; x += 0.1) {
            arcb = arcCos(x);
            libb = acos(x);
            Difference = arcb - libb;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arcb, libb, Difference);
        }
    }

    if (atanb) {
        double arct;
        double libt;
        double Difference;
        printf("  x            arcTan           Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double x = 1; x < 10; x += 0.1) {
            arct = arcTan(x);
            libt = atan(x);
            Difference = arct - libt;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, arct, libt, Difference);
        }
    }

    if (logn) {
        double logn;
        double libl;
        double Difference;
        printf("  x            Log              Library        Difference\n");
        printf("  -            ------           -------        ----------\n");
        for (double x = 1; x < 10; x += 0.1) {
            logn = Log(x);
            libl = log(x);
            Difference = logn - libl;
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", x, logn, libl, Difference);
        }
    }

    return 0;
}
