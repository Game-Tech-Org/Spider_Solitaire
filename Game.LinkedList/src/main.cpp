#include <iostream>
#include "./core/SpiderSolitaire.h"
using namespace std;

int main() {
    cout << "Welcome to Spider Solitaire!\n";
    cout << "Goal: Create 8 complete sequences (K to A)\n\n";

    SpiderSolitaire game;
    game.play();

    return 0;
}