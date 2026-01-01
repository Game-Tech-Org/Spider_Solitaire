#pragma once
#include <ctime>
#include <cstdlib>
#include "Column.h"
#include "StockPile.h"

class SpiderSolitaire {
private:
    Column columns[10];
    StockPile stock;
    int completedSequences;

    void createDeck() {
        LinkedList<Card> allCards;
        
        // Create 8 decks (104 cards total)
        for (int deck = 0; deck < 8; deck++) {
            for (int rank = 1; rank <= 13; rank++) {
                allCards.insertAtTail(Card(rank));
            }
        }

        // Shuffle using Fisher-Yates algorithm
        for (int i = allCards.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            
            Node<Card>* nodeI = allCards.getNodeAt(i);
            Node<Card>* nodeJ = allCards.getNodeAt(j);
            
            if (nodeI && nodeJ) {
                Card temp = nodeI->data;
                nodeI->data = nodeJ->data;
                nodeJ->data = temp;
            }
        }

        // Deal 54 cards to columns
        for (int col = 0; col < 10; col++) {
            int numCards = (col < 4) ? 6 : 5;
            for (int i = 0; i < numCards; i++) {
                Card c = allCards.getFront();
                allCards.deleteFromBeginning();
                columns[col].addCard(c);
            }
            columns[col].flipTopCard();
        }

        // Remaining 50 cards to stock
        while (!allCards.isEmpty()) {
            Card c = allCards.getFront();
            allCards.deleteFromBeginning();
            stock.addCard(c);
        }
    }

public:
    SpiderSolitaire() : completedSequences(0) {
        srand(time(0));
        createDeck();
    }

    void displayGame() {
        cout << "\n========================================\n";
        cout << "        SPIDER SOLITAIRE\n";
        cout << "========================================\n";
        cout << "Completed Sequences: " << completedSequences << "/8\n";
        stock.display();
        cout << "----------------------------------------\n";

        for (int i = 0; i < 10; i++) {
            columns[i].display(i + 1);
        }
        cout << "========================================\n";
    }

    bool isGameWon() {
        return completedSequences == 8;
    }

    void dealFromStock() {
        if (stock.isEmpty()) {
            cout << "No cards left in stock!\n";
            return;
        }

        if (stock.size() < 10) {
            cout << "Not enough cards to deal!\n";
            return;
        }

        for (int i = 0; i < 10; i++) {
            Card c = stock.drawCard();
            c.flip();
            columns[i].addCard(c);
        }

        cout << "Dealt 10 cards from stock!\n";
    }

    void moveCards(int fromCol, int toCol, int numCards) {
        fromCol--;
        toCol--;

        if (fromCol < 0 || fromCol >= 10 || toCol < 0 || toCol >= 10) {
            cout << "Invalid column numbers!\n";
            return;
        }

        if (fromCol == toCol) {
            cout << "Cannot move to the same column!\n";
            return;
        }

        if (columns[fromCol].isEmpty()) {
            cout << "Source column is empty!\n";
            return;
        }

        int startIdx = columns[fromCol].size() - numCards;
        if (startIdx < 0) {
            cout << "Not enough cards in column!\n";
            return;
        }

        if (!columns[fromCol].canPlaceCards(startIdx)) {
            cout << "Cards are not in valid descending sequence!\n";
            return;
        }

        Card movingCard = columns[fromCol].removeCards(startIdx).getFront();

        if (!columns[toCol].isEmpty()) {
            Card targetCard = columns[toCol].getTopCard();
            if (!movingCard.canPlaceOn(targetCard)) {
                cout << "Cannot place cards - rank must be one less!\n";
                return;
            }
        }

        LinkedList<Card> cardsToMove = columns[fromCol].removeCards(startIdx);
        columns[fromCol].removeCardsRange(startIdx);
        columns[toCol].addCards(cardsToMove);
        columns[fromCol].flipTopCard();

        checkForCompleteSequences();
    }

    void checkForCompleteSequences() {
        for (int i = 0; i < 10; i++) {
            if (columns[i].checkCompleteSequence()) {
                completedSequences++;
                cout << "Complete sequence removed! Total: " << completedSequences << "/8\n";
            }
        }
    }

    void play() {
        string command;

        while (!isGameWon()) {
            displayGame();
            
            cout << "\nCommands:\n";
            cout << "  move <from> <to> <num>  - Move cards\n";
            cout << "  deal                    - Deal from stock\n";
            cout << "  quit                    - Exit game\n";
            cout << "\nEnter command: ";
            
            cin >> command;

            if (command == "move") {
                int from, to, num;
                cin >> from >> to >> num;
                moveCards(from, to, num);
            }
            else if (command == "deal") {
                dealFromStock();
            }
            else if (command == "quit") {
                cout << "Thanks for playing!\n";
                return;
            }
            else {
                cout << "Invalid command!\n";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }

        displayGame();
        cout << "\n🎉 CONGRATULATIONS! YOU WON! 🎉\n";
    }
};