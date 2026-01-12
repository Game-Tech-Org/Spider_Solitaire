#pragma once
#include "Linklist.h"
#include "Card.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

class Column {
private:
    LinkedList<Card> cards;
public:
    void addCard(Card c) { cards.insertAtTail(c); }
    int size() const { return cards.size(); }
    bool isEmpty() const { return cards.isEmpty(); }
    Card getTopCard() { return cards.getTail(); }
    Card getCardAt(int idx) { 
        Node<Card>* n = cards.getNodeAt(idx); 
        return n ? n->data : Card(); 
    }
    
    void flipTopCard() {
        if (!isEmpty()) {
            Node<Card>* n = cards.getNodeAt(cards.size()-1);
            if (n && !n->data.isFaceUp()) n->data.flip();
        }
    }
    
    bool isValidSequence(int startIdx) {
        if (startIdx < 0 || startIdx >= cards.size()) return false;
        Node<Card>* startNode = cards.getNodeAt(startIdx);
        if (!startNode || !startNode->data.isFaceUp()) return false;
        
        for (int i = startIdx; i < cards.size()-1; i++) {
            Node<Card>* curr = cards.getNodeAt(i);
            Node<Card>* next = cards.getNodeAt(i+1);
            if (!curr || !next || !next->data.isFaceUp()) return false;
            if (!next->data.canPlaceOn(curr->data)) return false;
        }
        return true;
    }
    
    bool checkAndRemoveCompleteSequence() {
        if (cards.size() < 13) return false;
        for (int startIdx = 0; startIdx <= cards.size() - 13; startIdx++) {
            Node<Card>* kingNode = cards.getNodeAt(startIdx);
        
            if (!kingNode || !kingNode->data.isFaceUp() || kingNode->data.getRank() != 13) 
                continue;
            
            bool validSeq = true;
            
            for (int i = 0; i < 13; i++) {
                Node<Card>* node = cards.getNodeAt(startIdx + i);
                int expectedRank = 13 - i;  
                
                if (!node || !node->data.isFaceUp() || 
                    node->data.getRank() != expectedRank) {
                    validSeq = false;
                    break;
                }
            }
            
            if (validSeq) {
                cards.removeRange(startIdx, startIdx + 12);
                
                if (!isEmpty()) flipTopCard();
                
                return true;
            }
        }
        return false;
    }
    
    LinkedList<Card> removeCards(int startIdx) { 
        return cards.extractRange(startIdx, cards.size()-1); 
    }
    
    void removeCardsRange(int startIdx) { 
        cards.removeRange(startIdx, cards.size()-1); 
    }
    
    void addCards(LinkedList<Card>& cardList) { 
        cards.appendList(cardList); 
    }
    
    void draw(int x, int y, int colNum, bool isSel, int selIdx, Texture2D* ci, Texture2D cb) const {
        DrawText(TextFormat("%d", colNum), x+26, y-24, 20, Color{0,0,0,180});
        DrawText(TextFormat("%d", colNum), x+25, y-25, 20, Color{255,215,0,255});
        
        if (isEmpty()) {
            DrawRectangleLinesEx({(float)x, (float)y, 70, 90}, 2, Color{255,255,255,100});
        } else {
            for (int i = 0; i < cards.size(); i++) {
                Node<Card>* n = cards.getNodeAt(i);
                if (n) n->data.draw(x, y+i*25, isSel && i>=selIdx, ci, cb);
            }
        }
    }
    
    void save(ofstream& f) const {
        f << cards.size() << " ";
        for (int i = 0; i < cards.size(); i++) {
            Node<Card>* n = cards.getNodeAt(i);
            if (n) f << n->data.getRank() << " " << n->data.getSuit() << " " << n->data.isFaceUp() << " ";
        }
    }
    
    void load(ifstream& f) {
        int cnt; f >> cnt;
        for (int i = 0; i < cnt; i++) {
            int r, s, fu; 
            f >> r >> s >> fu;
            Card c(r, s);
            if (fu) c.flip();
            cards.insertAtTail(c);
        }
    }
};