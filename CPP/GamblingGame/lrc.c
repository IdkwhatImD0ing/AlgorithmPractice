#include "philos.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//Static variables
//pot balance represents balance in pot
//balance represents the indivdual balances of the players
//players represents number of total players in the game

static int32_t potBalance;
static int32_t balance[15];
static int32_t players;

int checkActivePlayers();
void addMoney();
void removeMoney();
void rollDie();

typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

//Main game loop
//first prompts user for seed and number of players
//then uses an infinite loop to simulate the game
//exiting the loop after only 1 player is left with a positive balance

int main(void) {

    int32_t seed;

    printf("Random Seed: ");
    scanf("%d", &seed);

    if (seed < 0) {
        printf("Pseudorandom seed must be non-negative (%d%s", seed, ").\n");
        exit(0);
    }

    printf("How many players? ");
    scanf("%d", &players);

    if (players < 1) {
        printf("Number of players must be from 1 to 14.\n");
        exit(0);
    }

    if (players > 14) {
        printf("Number of players must be from 1 to 14.\n");
        exit(0);
    }

    potBalance = 0;

    int32_t pos = 0;
    int32_t playerBalance;

    bool running = true;

    srandom(seed);

    for (int i = 0; i < 15; i++) {
        balance[0] = 0;
    }

    for (int i = 0; i < players; i++) {
        balance[i] = 3;
    }

    while (running) {
        playerBalance = balance[pos];
        if (playerBalance > 0) {
            printf("\n%s%s", philosophers[pos], " rolls... ");
            if (playerBalance == 1) {
                rollDie(pos);
            } else if (playerBalance == 2) {
                rollDie(pos);
                rollDie(pos);
            } else {
                rollDie(pos);
                rollDie(pos);
                rollDie(pos);
            }
        }

        if (checkActivePlayers() == 1) {
            running = false;
        }

        if (pos < players - 1) {
            pos++;
        } else {
            pos = 0;
        }
    }

    for (int i = 0; i < players; i++) {
        if (balance[i] != 0) {
            pos = i;
        }
    }

    printf("\n%s%s%d%s%d%s", philosophers[pos], " wins the $", potBalance, " pot with $",
        balance[pos], " left in the bank!\n");
}

int checkActivePlayers() {
    int32_t active = 0;
    for (int x = 0; x < players; x++) {
        if (balance[x] > 0) {
            active++;
        }
    }
    return active;
}

//AddMoney Function
//Adds 1$ to the player at the position argument

void addMoney(int position) {
    balance[position] = balance[position] + 1;
    return;
}

//RemoveMoney function
//Removes 1$ from the player at the position argument

void removeMoney(int position) {
    balance[position] = balance[position] - 1;
    return;
}

//Roll Die funtion
//Simulates rolling a die and does actions based on the results of the die roll
//Position argument contains the position of the player that is rolling the die

void rollDie(int position) {
    int32_t randomSide = (random() % 6);
    faces side = die[randomSide];
    if (side == LEFT) {
        if (position - 1 < 0) {
            addMoney(players - 1);
            printf("gives $1 to %s%s", philosophers[players - 1], " ");
        } else {
            addMoney(position - 1);
            printf("gives $1 to %s%s", philosophers[position - 1], " ");
        }
        removeMoney(position);
    } else if (side == RIGHT) {
        if (position + 1 >= players) {
            addMoney(0);
            printf("gives $1 to %s%s", philosophers[0], " ");
        } else {
            addMoney(position + 1);
            printf("gives $1 to %s%s", philosophers[position + 1], " ");
        }
        removeMoney(position);
    } else if (side == CENTER) {
        potBalance++;
        removeMoney(position);
        printf("puts $1 in the pot ");
    } else if (side == PASS) {
        printf("gets a pass ");
    }
    return;
}
