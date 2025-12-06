#pragma once
#include <vector>
#include "Card.h"

class Deck {
public:
    std::vector<Card> cards;

    Deck(int suitMode = 1);   // 1-suit mode or 2/4
    void shuffle();
    Card draw();
};