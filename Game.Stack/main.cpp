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
            stockpile.push(card(v, false));
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
        card x = temp[i];
        temp[i] = temp[r];
        temp[r] = x;
    }

    for (int i = 0; i < temp.size(); i++) {
        stockpile.push(temp[i]);
    }
}

void initialdeal() {
    for (int col = 0; col < 10; col++) {
        int cards = (col < 4) ? 6 : 5;

        for (int i = 0; i < cards; i++) {
            table[col].push(stockpile.top());
            stockpile.pop();
        }

        if (!table[col].empty()) {
            table[col].top().faceup = true;
        }
    }
}

void showtable() {
    cout << "\n--- table state ---\n";

    for (int i = 0; i < 10; i++) {
        cout << "col " << i << ": ";

        stack<card> temp = table[i];

        while (!temp.empty()) {
            card c = temp.top();
            temp.pop();

            if (c.faceup)
                cout << c.value << " ";
            else
                cout << "X ";
        }
        cout << endl;
    }
}

int main() {
    cout << "spider solitaire\n";

    makecards();
    shufflecards();
    initialdeal();
    showtable();

    cout << "\nstock left: " << stockpile.size() << endl;
    return 0;
}
