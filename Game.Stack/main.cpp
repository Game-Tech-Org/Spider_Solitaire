#include <iostream>
#include <stack>

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

int main() {
    cout << "spider solitaire - stack version" << endl;

    makecards();

    cout << "cards created in stockpile" << endl;
    cout << "total cards: " << stockpile.size() << endl;

    return 0;
}
