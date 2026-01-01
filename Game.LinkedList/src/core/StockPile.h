#pragma once
#include "Linklist.h"
#include "Card.h"

class StockPile {
private:
    LinkedList<Card> cards;

public:
    StockPile() {}

    void addCard(Card c) {
        cards.insertAtTail(c);
    }

    int size() const {
        return cards.size();
    }

    bool isEmpty() const {
        return cards.isEmpty();
    }

    Card drawCard() {
        Card c = cards.getTail();
        cards.deleteFromTail();
        return c;
    }

    void display() const {
        cout << "Stock: " << cards.size() / 10 << " deals remaining" << endl;
    }
};// Updated by breera at Fri Dec 26 22:18:51 PST 2025
"// Updated by breera - $(date)" 
