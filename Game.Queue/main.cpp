#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;

// ==================== QUEUE CLASS ====================
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* frontPtr;
    Node* rearPtr;
    int count;

public:
    Queue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(T val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        } else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        Node* temp = frontPtr;
        T val = temp->data;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) {
            rearPtr = nullptr;
        }
        delete temp;
        count--;
        return val;
    }

    T front() const {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return frontPtr->data;
    }

    bool isEmpty() const {
        return frontPtr == nullptr;
    }

    int size() const {
        return count;
    }

    // Helper: Get element at index (inefficient but necessary for queue-only constraint)
    T getAt(int index) const {
        if (index < 0 || index >= count) {
            throw runtime_error("Index out of bounds");
        }
        Node* temp = frontPtr;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Helper: Display all elements (for debugging)
    void display() const {
        Node* temp = frontPtr;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ==================== CARD CLASS ====================
class Card {
private:
    int rank;      // 1-13 (Ace to King)
    bool faceUp;

public:
    Card() : rank(0), faceUp(false) {}
    Card(int r) : rank(r), faceUp(false) {}

    int getRank() const { return rank; }
    bool isFaceUp() const { return faceUp; }
    void setFaceUp(bool up) { faceUp = up; }

    string getDisplay() const {
        if (!faceUp) return "[##]";

        string ranks[] = {"", " A", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "10", " J", " Q", " K"};
        return "[" + ranks[rank] + "]";
    }
};

// ==================== GAME CLASS ====================
class SpiderSolitaire {
private:
    Queue<Card> deck;
    Queue<Card> tableau[10];  // 10 columns
    Queue<Card> stock;        // Remaining cards to deal
    Queue<Card> foundation;   // Completed sequences
    int score;
    int moves;
    bool gameWon;

    void initializeDeck() {
        // Spider Solitaire uses 2 decks (104 cards) - simplified to 1 suit
        for (int deck = 0; deck < 2; deck++) {
            for (int suit = 0; suit < 4; suit++) {
                for (int rank = 1; rank <= 13; rank++) {
                    this->deck.enqueue(Card(rank));
                }
            }
        }
    }

    void shuffleDeck() {
        // Convert queue to array for shuffling
        int size = deck.size();
        Card* cards = new Card[size];

        for (int i = 0; i < size; i++) {
            cards[i] = deck.dequeue();
        }

        // Shuffle
        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Card temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }

        // Put back in deck
        for (int i = 0; i < size; i++) {
            deck.enqueue(cards[i]);
        }

        delete[] cards;
    }

    void dealInitialCards() {
        // Deal 54 cards to tableau: 6 cards to first 4 columns, 5 to remaining 6
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 6; j++) {
                if (!deck.isEmpty()) {
                    Card c = deck.dequeue();
                    if (j == 5) c.setFaceUp(true);  // Last card face up
                    tableau[i].enqueue(c);
                }
            }
        }

        for (int i = 4; i < 10; i++) {
            for (int j = 0; j < 5; j++) {
                if (!deck.isEmpty()) {
                    Card c = deck.dequeue();
                    if (j == 4) c.setFaceUp(true);  // Last card face up
                    tableau[i].enqueue(c);
                }
            }
        }

        // Remaining cards go to stock
        while (!deck.isEmpty()) {
            stock.enqueue(deck.dequeue());
        }
    }

public:
    SpiderSolitaire() : score(500), moves(0), gameWon(false) {
        srand(time(0));
    }

    void startNewGame() {
        score = 500;
        moves = 0;
        gameWon = false;

        // Clear all queues
        while (!foundation.isEmpty()) foundation.dequeue();
        for (int i = 0; i < 10; i++) {
            while (!tableau[i].isEmpty()) tableau[i].dequeue();
        }
        while (!stock.isEmpty()) stock.dequeue();
        while (!deck.isEmpty()) deck.dequeue();

        initializeDeck();
        shuffleDeck();
        dealInitialCards();
    }

    void displayBoard() {
        system("cls");

        // Header with animation
        cout << "\n";
        cout << "    ###############################################\n";
        cout << "    #                                             #\n";
        cout << "    #        SPIDER SOLITAIRE (QUEUE-BASED)       #\n";
        cout << "    #                                             #\n";
        cout << "    ###############################################\n\n";

        cout << "    Score: " << score << "  |  Moves: " << moves << "  |  Stock: " << stock.size() << " cards\n";
        cout << "    " << string(47, '_') << "\n\n";

        // Find max height
        int maxHeight = 0;
        for (int i = 0; i < 10; i++) {
            if (tableau[i].size() > maxHeight) maxHeight = tableau[i].size();
        }

        // Column headers
        cout << "      ";
        for (int i = 0; i < 10; i++) {
            cout << " " << i + 1 << "   ";
        }
        cout << "\n      ";
        for (int i = 0; i < 10; i++) {
            cout << "---- ";
        }
        cout << "\n";

        // Display tableau
        for (int row = 0; row < maxHeight; row++) {
            cout << "      ";
            for (int col = 0; col < 10; col++) {
                if (row < tableau[col].size()) {
                    cout << tableau[col].getAt(row).getDisplay() << " ";
                } else {
                    cout << "     ";
                }
            }
            cout << "\n";
        }

        cout << "\n    " << string(47, '_') << "\n";
        cout << "    Completed Sequences: " << foundation.size() / 13 << " / 8\n";
    }

    void displayMenu() {
        system("cls");
        cout << "\n\n";
        cout << "        ###############################################\n";
        cout << "        #                                             #\n";
        cout << "        #          SPIDER SOLITAIRE GAME              #\n";
        cout << "        #                                             #\n";
        cout << "        ###############################################\n\n";

        Sleep(100);
        cout << "                ________________________________\n";
        cout << "               |                                |\n";
        cout << "               |    1. Start New Game           |\n";
        cout << "               |________________________________|\n\n";
        Sleep(100);
        cout << "                ________________________________\n";
        cout << "               |                                |\n";
        cout << "               |    2. Continue Game            |\n";
        cout << "               |________________________________|\n\n";
        Sleep(100);
        cout << "                ________________________________\n";
        cout << "               |                                |\n";
        cout << "               |    3. View High Scores         |\n";
        cout << "               |________________________________|\n\n";
        Sleep(100);
        cout << "                ________________________________\n";
        cout << "               |                                |\n";
        cout << "               |    4. Exit                     |\n";
        cout << "               |________________________________|\n\n";

        cout << "        Enter your choice: ";
    }

    bool checkForCompleteSequence(int col) {
        if (tableau[col].size() < 13) return false;

        // Check last 13 cards for complete sequence K to A
        int startIdx = tableau[col].size() - 13;
        for (int i = 0; i < 13; i++) {
            Card c = tableau[col].getAt(startIdx + i);
            if (!c.isFaceUp() || c.getRank() != 13 - i) {
                return false;
            }
        }

        // Complete sequence found! Remove it
        Queue<Card> temp;
        int removeCount = tableau[col].size() - 13;

        // Keep cards before sequence
        for (int i = 0; i < removeCount; i++) {
            temp.enqueue(tableau[col].dequeue());
        }

        // Remove sequence to foundation
        for (int i = 0; i < 13; i++) {
            foundation.enqueue(tableau[col].dequeue());
        }

        // Put remaining cards back
        while (!tableau[col].isEmpty()) {
            temp.enqueue(tableau[col].dequeue());
        }
        while (!temp.isEmpty()) {
            tableau[col].enqueue(temp.dequeue());
        }

        // Flip top card if exists
        if (!tableau[col].isEmpty()) {
            Card top = tableau[col].getAt(tableau[col].size() - 1);
            top.setFaceUp(true);
        }

        score += 100;
        return true;
    }

    void dealFromStock() {
        if (stock.isEmpty()) {
            cout << "\n    No more cards in stock!\n";
            Sleep(1500);
            return;
        }

        // Deal one card to each column
        for (int i = 0; i < 10; i++) {
            if (!stock.isEmpty()) {
                Card c = stock.dequeue();
                c.setFaceUp(true);
                tableau[i].enqueue(c);
            }
        }
        moves++;
        score -= 5;
    }

    void makeMove() {
        displayBoard();
        cout << "\n    Commands: [M]ove card, [D]eal from stock, [B]ack to menu\n";
        cout << "    Enter command: ";

        char cmd;
        cin >> cmd;

        if (cmd == 'D' || cmd == 'd') {
            dealFromStock();
            for (int i = 0; i < 10; i++) {
                checkForCompleteSequence(i);
            }
        } else if (cmd == 'M' || cmd == 'm') {
            cout << "    From column (1-10): ";
            int from;
            cin >> from;
            from--;

            if (from < 0 || from > 9 || tableau[from].isEmpty()) {
                cout << "    Invalid column!\n";
                Sleep(1500);
                return;
            }

            cout << "    To column (1-10): ";
            int to;
            cin >> to;
            to--;

            if (to < 0 || to > 9 || to == from) {
                cout << "    Invalid column!\n";
                Sleep(1500);
                return;
            }

            // Simplified move: only move top card
            Card fromCard = tableau[from].getAt(tableau[from].size() - 1);

            if (!fromCard.isFaceUp()) {
                cout << "    Cannot move face-down card!\n";
                Sleep(1500);
                return;
            }

            // Check if move is valid
            bool validMove = false;
            if (tableau[to].isEmpty()) {
                validMove = true;  // Can move to empty column
            } else {
                Card toCard = tableau[to].getAt(tableau[to].size() - 1);
                if (toCard.getRank() == fromCard.getRank() + 1) {
                    validMove = true;  // Can place on card of one higher rank
                }
            }

            if (validMove) {
                // Remove from source
                Queue<Card> temp;
                int size = tableau[from].size();
                for (int i = 0; i < size - 1; i++) {
                    temp.enqueue(tableau[from].dequeue());
                }
                Card moving = tableau[from].dequeue();

                while (!temp.isEmpty()) {
                    tableau[from].enqueue(temp.dequeue());
                }

                // Flip top card of source if exists
                if (!tableau[from].isEmpty()) {
                    Card top = tableau[from].getAt(tableau[from].size() - 1);
                    top.setFaceUp(true);
                }

                // Add to destination
                tableau[to].enqueue(moving);

                moves++;
                score -= 1;

                checkForCompleteSequence(to);
            } else {
                cout << "    Invalid move!\n";
                Sleep(1500);
            }
        }

        // Check win condition
        if (foundation.size() == 104) {
            gameWon = true;
        }
    }

    void saveGame() {
        ofstream file("savegame.txt");
        if (file.is_open()) {
            file << score << " " << moves << "\n";

            // Save tableau
            for (int i = 0; i < 10; i++) {
                file << tableau[i].size() << " ";
                for (int j = 0; j < tableau[i].size(); j++) {
                    Card c = tableau[i].getAt(j);
                    file << c.getRank() << " " << c.isFaceUp() << " ";
                }
                file << "\n";
            }

            // Save stock
            file << stock.size() << " ";
            file.close();
        }
    }

    void loadGame() {
        ifstream file("savegame.txt");
        if (file.is_open()) {
            file >> score >> moves;

            for (int i = 0; i < 10; i++) {
                int size;
                file >> size;
                while (!tableau[i].isEmpty()) tableau[i].dequeue();

                for (int j = 0; j < size; j++) {
                    int rank, faceUp;
                    file >> rank >> faceUp;
                    Card c(rank);
                    c.setFaceUp(faceUp);
                    tableau[i].enqueue(c);
                }
            }

            int stockSize;
            file >> stockSize;
            file.close();

            cout << "\n    Game loaded successfully!\n";
            Sleep(1500);
        } else {
            cout << "\n    No saved game found!\n";
            Sleep(1500);
        }
    }

    void displayScores() {
        system("cls");
        cout << "\n\n";
        cout << "        ###############################################\n";
        cout << "        #                                             #\n";
        cout << "        #            HIGH SCORES                      #\n";
        cout << "        #                                             #\n";
        cout << "        ###############################################\n\n";

        ifstream file("scores.txt");
        if (file.is_open()) {
            cout << "        Rank    Score    Moves\n";
            cout << "        " << string(30, '-') << "\n";

            int rank = 1;
            int sc, mv;
            while (file >> sc >> mv && rank <= 10) {
                cout << "         " << rank << ".      " << sc << "       " << mv << "\n";
                rank++;
            }
            file.close();
        } else {
            cout << "        No scores yet!\n";
        }

        cout << "\n\n        Press any key to return...";
        cin.ignore();
        cin.get();
    }

    void saveScore() {
        ofstream file("scores.txt", ios::app);
        if (file.is_open()) {
            file << score << " " << moves << "\n";
            file.close();
        }
    }

    void playGame() {
        while (!gameWon) {
            makeMove();
        }

        system("cls");
        cout << "\n\n";
        cout << "        ###############################################\n";
        cout << "        #                                             #\n";
        cout << "        #          CONGRATULATIONS!                   #\n";
        cout << "        #              YOU WON!                       #\n";
        cout << "        #                                             #\n";
        cout << "        ###############################################\n\n";
        cout << "        Final Score: " << score << "\n";
        cout << "        Total Moves: " << moves << "\n\n";

        saveScore();

        cout << "        Press any key to continue...";
        cin.ignore();
        cin.get();
    }

    void run() {
        int choice;
        bool running = true;

        while (running) {
            displayMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    startNewGame();
                    playGame();
                    break;
                case 2:
                    loadGame();
                    playGame();
                    break;
                case 3:
                    displayScores();
                    break;
                case 4:
                    saveGame();
                    cout << "\n    Thanks for playing! Goodbye!\n";
                    running = false;
                    break;
                default:
                    cout << "\n    Invalid choice!\n";
                    Sleep(1000);
            }
        }
    }
};

// ==================== MAIN ====================
int main() {
    SpiderSolitaire game;
    game.run();
    return 0;
}
