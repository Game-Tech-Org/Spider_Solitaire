#pragma once
#include <vector>
#include "Card.h"

class Column {
public:
    std::vector<Card> pile;

    void push(Card c);
    Card pop();
    Card top();

    bool canMove(int index); // index = start of sequence
    void moveSequence(Column& dest, int startIndex);

    bool isCompletedSequence(); // check K -> A same suit
};