#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class card {
public:
    int value;
    bool faceup;

    card() {
        value = 0;
        faceup = false;
    }

    card(int v, bool f) {
        value = v;
        faceup = f;
    }
};

stack<card> table[10];
stack<card> stockpile;

void makecards() {
    for (int s = 0; s < 8; s++) {
        for (int v = 1; v <= 13; v++) {
            card c(v, false);
            stockpile.push(c);
        }
    }
}

void shufflecards() {
    vector<card> temp;

    while (!stockpile.empty()) {
        temp.push_back(stockpile.top());
        stockpile.pop();
    }

    srand(time(0));

    for (int i = 0; i < temp.size(); i++) {
        int r = rand() % temp.size();
        card t = temp[i];
        temp[i] = temp[r];
        temp[r] = t;
    }

    for (int i = 0; i < temp.size(); i++) {
        stockpile.push(temp[i]);
    }
}

void initialdeal() {
    for (int col = 0; col < 10; col++) {
        int cards;

        if (col < 4)
            cards = 6;
        else
            cards = 5;

        for (int i = 0; i < cards; i++) {
            card c = stockpile.top();
            stockpile.pop();
            table[col].push(c);
        }

        if (!table[col].empty()) {
            table[col].top().faceup = true;
        }
    }
}

int main() {
    cout << "spider solitaire - stack version" << endl;

    makecards();
    shufflecards();
    initialdeal();

    cout << "cards dealt to table" << endl;
    cout << "remaining cards in stock: " << stockpile.size() << endl;

    return 0;
}
