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

int main() {
    cout << "spider solitaire - stack version" << endl;
    cout << "using classes and stacks" << endl;

    cout << "columns created: 10" << endl;
    cout << "stock is empty for now" << endl;

    return 0;
}
