#pragma once

class Card {
public:
    int rank;   // 1–13
    int suit;   // 0–3
    bool faceUp;

    Card(int r = 0, int s = 0, bool f = false)
        : rank(r), suit(s), faceUp(f) {}
};