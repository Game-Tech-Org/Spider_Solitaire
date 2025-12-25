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
    cout << "\n--- table ---\n";

    for (int i = 0; i < 10; i++) {
        cout << i << ": ";
        stack<card> temp = table[i];

        while (!temp.empty()) {
            if (temp.top().faceup)
                cout << temp.top().value << " ";
            else
                cout << "X ";
            temp.pop();
        }
        cout << endl;
    }
}

void movecard(int from, int to) {
    if (table[from].empty()) {
        cout << "nothing to move\n";
        return;
    }

    card c = table[from].top();
    table[from].pop();

    table[to].push(c);

    if (!table[from].empty()) {
        table[from].top().faceup = true;
    }
}

int main() {
    makecards();
    shufflecards();
    initialdeal();

    showtable();

    int a, b;
    cout << "\nmove from col: ";
    cin >> a;
    cout << "move to col: ";
    cin >> b;

    movecard(a, b);

    showtable();

    return 0;
}
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
    cout << "\n--- table ---\n";

    for (int i = 0; i < 10; i++) {
        cout << i << ": ";
        stack<card> temp = table[i];

        while (!temp.empty()) {
            if (temp.top().faceup)
                cout << temp.top().value << " ";
            else
                cout << "X ";
            temp.pop();
        }
        cout << endl;
    }
}

void movecard(int from, int to) {
    if (table[from].empty()) {
        cout << "nothing to move\n";
        return;
    }

    card c = table[from].top();
    table[from].pop();

    table[to].push(c);

    if (!table[from].empty()) {
        table[from].top().faceup = true;
    }
}

int main() {
    makecards();
    shufflecards();
    initialdeal();

    showtable();

    int a, b;
    cout << "\nmove from col: ";
    cin >> a;
    cout << "move to col: ";
    cin >> b;

    movecard(a, b);

    showtable();

    return 0;
}
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
    cout << "\n--- table ---\n";

    for (int i = 0; i < 10; i++) {
        cout << i << ": ";
        stack<card> temp = table[i];

        while (!temp.empty()) {
            if (temp.top().faceup)
                cout << temp.top().value << " ";
            else
                cout << "X ";
            temp.pop();
        }
        cout << endl;
    }
}

void movecard(int from, int to) {
    if (table[from].empty()) {
        cout << "nothing to move\n";
        return;
    }

    card c = table[from].top();
    table[from].pop();

    table[to].push(c);

    if (!table[from].empty()) {
        table[from].top().faceup = true;
    }
}

int main() {
    makecards();
    shufflecards();
    initialdeal();

    showtable();

    int a, b;
    cout << "\nmove from col: ";
    cin >> a;
    cout << "move to col: ";
    cin >> b;

    movecard(a, b);

    showtable();

    return 0;
}
