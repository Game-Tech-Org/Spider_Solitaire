#pragma once
#include "Linklist.h"
#include "Card.h"
#include "raylib.h"
#include <fstream>

class StockPile {
private:
    LinkedList<Card> cards;
public:
    void addCard(Card c) { cards.insertAtTail(c); }
    int size() const { return cards.size(); }
    bool isEmpty() const { return cards.isEmpty(); }
    Card drawCard() { Card c = cards.getTail(); cards.deleteFromTail(); return c; }
    
    void draw(int x, int y, Texture2D cb) const {
        Rectangle r = {(float)x, (float)y, 70.0f, 90.0f};
        if (isEmpty()) {
            DrawRectangleRec(r, Color{50,50,50,255});
            DrawRectangleLinesEx(r, 2.0f, Color{100,100,100,255});
            DrawText("Empty", x+16, y+38, 14, Color{150,150,150,255});
        } else {
            DrawTexturePro(cb, {0.0f,0.0f,(float)cb.width,(float)cb.height}, r, {0.0f,0.0f}, 0.0f, WHITE);
            DrawRectangle(x, y+60, 70, 30, Color{0,0,0,200});
            int deals = (int)(cards.size() / 10);
            DrawText(TextFormat("%d", deals), x+28, y+67, 22, YELLOW);
        }
    }
    
    void save(ofstream& f) const {
        f << cards.size() << " ";
        for (int i = 0; i < cards.size(); i++) {
            Node<Card>* n = cards.getNodeAt(i);
            if (n) f << n->data.getRank() << " " << n->data.getSuit() << " ";
        }
    }
    
    void load(ifstream& f) {
        int cnt; f >> cnt;
        for (int i = 0; i < cnt; i++) {
            int r, s; 
            f >> r >> s;
            cards.insertAtTail(Card(r, s));
        }
    }
};