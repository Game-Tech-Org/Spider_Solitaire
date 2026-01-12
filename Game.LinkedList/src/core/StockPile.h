#pragma once
#include <ctime>
#include <cstdlib>
#include "Column.h"
#include "StockPile.h"
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

void DrawTextWithShadow(const char* text, int x, int y, int size, Color shadow, Color main) {
    DrawText(text, x+2, y+2, size, shadow);
    DrawText(text, x, y, size, main);
}

// ========== Game ==========
class SpiderSolitaire {
private:
    Column columns[10];
    StockPile stock;
    int completedSeq, moves, selCol, selCard;
    bool gameWon;
    string msg;
    float msgTimer;
    Texture2D cardImg[13], cardBack, bg;  // Only 13 card images for single suit
    
    void createDeck() {
        LinkedList<Card> all;
        
        // Create 8 decks of single suit (Spades = suit 3) for 104 cards total
        for (int deck = 0; deck < 8; deck++) {
            for (int rank = 1; rank <= 13; rank++) {
                all.insertAtTail(Card(rank, 3)); // All Spades
            }
        }
        
        // Shuffle
        for (int i = all.size()-1; i > 0; i--) {
            int j = rand()%(i+1);
            Node<Card>* ni = all.getNodeAt(i);
            Node<Card>* nj = all.getNodeAt(j);
            if (ni && nj) { 
                Card t = ni->data; 
                ni->data = nj->data; 
                nj->data = t; 
            }
        }
        
        // Deal to columns (first 4 get 6 cards, rest get 5)
        for (int c = 0; c < 10; c++) {
            int numCards = (c < 4) ? 6 : 5;
            for (int i = 0; i < numCards; i++) {
                columns[c].addCard(all.getFront());
                all.deleteFromBeginning();
            }
            columns[c].flipTopCard();
        }
        
        // Remaining cards go to stock
        while (!all.isEmpty()) {
            stock.addCard(all.getFront());
            all.deleteFromBeginning();
        }
    }
    
public:
    SpiderSolitaire() : completedSeq(0), moves(0), gameWon(false), 
                        selCol(-1), selCard(-1), msgTimer(0) {
        srand(time(0));
    }
    
    void loadImages() {
        string rankNames[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        
        // Load only Spade cards (13 images)
        for (int rank = 0; rank < 13; rank++) {
            string filename = "Deck Images/Spade " + rankNames[rank] + ".jpeg";
            Image img = LoadImage(filename.c_str());
            if (img.data) {
                cardImg[rank] = LoadTextureFromImage(img);
                UnloadImage(img);
            } else {
                cardImg[rank].id = 0;
            }
        }
        
        Image back = LoadImage("Deck Images/card_back.jpeg");
        if (!back.data) back = LoadImage("Deck Images/back.jpeg");
        if (!back.data) back = GenImageColor(70, 90, DARKBLUE);
        cardBack = LoadTextureFromImage(back);
        UnloadImage(back);
        
        Image bgImg = LoadImage("Deck Images/background.jpeg");
        if (!bgImg.data) bgImg = GenImageColor(1020, 750, Color{34,139,34,255});
        bg = LoadTextureFromImage(bgImg);
        UnloadImage(bgImg);
    }
    
    void unloadImages() {
        for (int i = 0; i < 13; i++) 
            if (cardImg[i].id) UnloadTexture(cardImg[i]);
        UnloadTexture(cardBack);
        UnloadTexture(bg);
    }
    
    void newGame() {
        for (int i = 0; i < 10; i++) columns[i] = Column();
        stock = StockPile();
        completedSeq = moves = 0;
        gameWon = false;
        selCol = selCard = -1;
        createDeck();
        msg = "New game started! Build K-A sequences to win.";
        msgTimer = 3;
    }
    
    bool save() {
        ofstream f("savegame.dat");
        if (!f) return false;
        f << completedSeq << " " << moves << " " << gameWon << endl;
        for (int i = 0; i < 10; i++) { columns[i].save(f); f << endl; }
        stock.save(f);
        f.close();
        return true;
    }
    
    bool load() {
        ifstream f("savegame.dat");
        if (!f) return false;
        for (int i = 0; i < 10; i++) columns[i] = Column();
        stock = StockPile();
        f >> completedSeq >> moves >> gameWon;
        for (int i = 0; i < 10; i++) columns[i].load(f);
        stock.load(f);
        f.close();
        selCol = selCard = -1;
        msg = "Game loaded successfully!";
        msgTimer = 2;
        return true;
    }
    
    void dealFromStock() {
        if (stock.isEmpty()) { 
            msg = "Stock is empty!"; 
            msgTimer = 2; 
            return; 
        }
        
        if (stock.size() < 10) { 
            msg = "Need at least 10 cards to deal!"; 
            msgTimer = 2; 
            return; 
        }
        
        for (int i = 0; i < 10; i++) {
            Card c = stock.drawCard();
            c.flip();
            columns[i].addCard(c);
        }
        
        checkComplete();
        msg = "Cards dealt from stock!";
        msgTimer = 2;
        moves++;
    }
    
    void moveCards(int from, int to, int numCards) {
        if (from == to || from < 0 || to < 0 || from >= 10 || to >= 10) return;
        
        int startIdx = columns[from].size() - numCards;
        if (startIdx < 0) { 
            msg = "Not enough cards to move!"; 
            msgTimer = 2; 
            return; 
        }
        
        if (!columns[from].isValidSequence(startIdx)) { 
            msg = "Invalid sequence! Cards must be descending."; 
            msgTimer = 2; 
            return; 
        }
        
        Card movingCard = columns[from].getCardAt(startIdx);
        
        if (columns[to].isEmpty()) {
            LinkedList<Card> cards = columns[from].removeCards(startIdx);
            columns[from].removeCardsRange(startIdx);
            columns[to].addCards(cards);
            columns[from].flipTopCard();
            moves++;
            checkComplete();
        } else {
            Card targetCard = columns[to].getTopCard();
            if (!movingCard.canPlaceOn(targetCard)) { 
                msg = "Cannot place! Card must be 1 rank lower."; 
                msgTimer = 2; 
                return; 
            }
            
            LinkedList<Card> cards = columns[from].removeCards(startIdx);
            columns[from].removeCardsRange(startIdx);
            columns[to].addCards(cards);
            columns[from].flipTopCard();
            moves++;
            checkComplete();
        }
    }
    
    void checkComplete() {
        bool foundSequence = true;
        
        // Keep checking until no more sequences are found
        while (foundSequence) {
            foundSequence = false;
            
            for (int i = 0; i < 10; i++) {
                if (columns[i].checkAndRemoveCompleteSequence()) {
                    completedSeq++;
                    foundSequence = true;
                    
                    msg = TextFormat("Sequence removed from column %d! Total: %d/8", i+1, completedSeq);
                    msgTimer = 3;
                    
                    if (completedSeq >= 8) {
                        gameWon = true;
                        msg = "CONGRATULATIONS! YOU WON!";
                        msgTimer = 5;
                        return;
                    }
                    break;
                }
            }
        }
    }
    
    void handleInput() {
        Vector2 mp = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mp, {20,20,70,90})) { 
                dealFromStock(); 
                return; 
            }
            
            for (int c = 0; c < 10; c++) {
                int x = 120 + c * 90;
                int y = 150;
                
                if (!columns[c].isEmpty()) {
                    for (int cd = columns[c].size()-1; cd >= 0; cd--) {
                        if (CheckCollisionPointRec(mp, {(float)x, (float)(y+cd*25), 70, 90})) {
                            Card clickedCard = columns[c].getCardAt(cd);
                            
                            if (selCol == -1) {
                                if (clickedCard.isFaceUp()) {
                                    selCol = c;
                                    selCard = cd;
                                }
                            } else {
                                int numCards = columns[selCol].size() - selCard;
                                moveCards(selCol, c, numCards);
                                selCol = selCard = -1;
                            }
                            break;
                        }
                    }
                } else {
                    if (CheckCollisionPointRec(mp, {(float)x, (float)y, 70, 90}) && selCol != -1) {
                        int numCards = columns[selCol].size() - selCard;
                        moveCards(selCol, c, numCards);
                        selCol = selCard = -1;
                    }
                }
            }
        }
        
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            selCol = selCard = -1;
        }
        
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
            if (save()) { msg = "Game saved successfully!"; msgTimer = 2; }
        }
    }
    
    void update(float dt) { 
        if (msgTimer > 0) msgTimer -= dt;
    }
    
    void draw() {
        DrawTexturePro(bg, {0,0,(float)bg.width,(float)bg.height}, 
                      {0,0,1020,750}, {0,0}, 0, WHITE);
        
        DrawTextWithShadow("SPIDER SOLITAIRE", 290, 15, 38, Color{0,0,0,200}, Color{255,215,0,255});
        
        DrawRectangle(660, 20, 160, 32, Color{139,0,0,230});
        DrawRectangleLinesEx({660.0f, 20.0f, 160.0f, 32.0f}, 2.0f, Color{255,215,0,255});
        DrawTextWithShadow(TextFormat("Sequences: %d/8", completedSeq), 670, 26, 20, Color{0,0,0,180}, Color{255,255,255,255});
        
        DrawRectangle(660, 60, 160, 28, Color{100,0,0,230});
        DrawRectangleLinesEx({660.0f, 60.0f, 160.0f, 28.0f}, 2.0f, Color{255,215,0,200});
        DrawTextWithShadow(TextFormat("Moves: %d", moves), 690, 64, 18, Color{0,0,0,180}, YELLOW);
        
        stock.draw(20, 20, cardBack);
        DrawTextWithShadow("Stock", 26, 117, 16, Color{0,0,0,200}, WHITE);
        
        for (int i = 0; i < 10; i++) {
            columns[i].draw(120 + i*90, 150, i+1, selCol==i, selCard, cardImg, cardBack);
        }
        
        if (msgTimer > 0) {
            int w = MeasureText(msg.c_str(), 20);
            DrawRectangle(510-w/2-15, 505, w+30, 38, Color{0,0,0,230});
            DrawRectangleLinesEx({(float)(510-w/2-15), 505.0f, (float)(w+30), 38.0f}, 2.0f, Color{255,215,0,255});
            DrawTextWithShadow(msg.c_str(), 510-w/2, 513, 20, Color{0,0,0,180}, WHITE);
        }
        
        DrawTextWithShadow("Left Click: Select/Move  |  Right Click: Cancel  |  Ctrl+S: Save  |  ESC: Menu", 
                 120, 722, 15, Color{0,0,0,200}, Color{200,200,200,255});
        
        if (gameWon) {
            DrawRectangle(0, 0, 1020, 750, Color{0,0,0,230});
            DrawTextWithShadow("CONGRATULATIONS!", 260, 290, 48, Color{0,0,0,255}, Color{255,215,0,255});
            DrawTextWithShadow("YOU WON THE GAME!", 310, 350, 38, Color{0,0,0,255}, YELLOW);
            DrawTextWithShadow(TextFormat("Total Moves: %d", moves), 390, 410, 26, Color{0,0,0,255}, WHITE);
            DrawTextWithShadow("Press ESC to return to menu", 350, 460, 22, Color{0,0,0,255}, Color{180,180,180,255});
        }
    }
    
    bool isWon() const { return gameWon; }
};