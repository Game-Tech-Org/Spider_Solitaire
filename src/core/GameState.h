#pragma once
#include "Deck.h"
#include "Column.h"

class GameState {
public:
    Deck deck;
    Column columns[10];

    GameState();
    void dealInitial();
    bool isValidMove(int colFrom, int index, int colTo);
    void applyMove(int colFrom, int index, int colTo);

    bool addNewRow();
    bool checkCompletedRuns();
    bool isGameWon();
};