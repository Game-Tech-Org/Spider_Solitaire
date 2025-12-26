#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class t>
class stackk {
    int siz;
    t *ptr;
    int top;

public:
    stackk(int s = 200) {
        siz = s;
        top = -1;
        ptr = new t[siz];
    }

    bool isempty() {
        return top == -1;
    }

    bool isfull() {
        return top == siz - 1;
    }

    void push(t var) {
        if (isfull()) {
            cout << "stack full\n";
            return;
        }
        ptr[++top] = var;
    }

    t pop() {
        if (isempty()) {
            cout << "stack empty\n";
            return ptr[0];
        }
        return ptr[top--];
    }

    t Top() {
        return ptr[top];
    }

    int count() {
        return top + 1;
    }
};

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

stackk<card> table[10];
stackk<card> stockpile(150);

int stockcount = 0;

void makecards() {
    for (int s = 0; s < 8; s++) {
        for (int v = 1; v <= 13; v++) {
            stockpile.push(card(v, false));
            stockcount++;
        }
    }
}

void shufflecards() {
    card temp[150];
    int k = 0;

    while (!stockpile.isempty()) {
        temp[k++] = stockpile.pop();
        stockcount--;
    }

    srand(time(0));

    for (int i = 0; i < k; i++) {
        int r = rand() % k;
        card c = temp[i];
        temp[i] = temp[r];
        temp[r] = c;
    }

    for (int i = 0; i < k; i++) {
        stockpile.push(temp[i]);
        stockcount++;
    }
}

void initialdeal() {
    for (int col = 0; col < 10; col++) {
        int cards = (col < 4) ? 6 : 5;

        for (int i = 0; i < cards; i++) {
            card c = stockpile.pop();
            stockcount--;
            table[col].push(c);
        }

        card topc = table[col].pop();
        topc.faceup = true;
        table[col].push(topc);
    }
}

void showtable() {
    cout << "\n--- table ---\n";

    for (int i = 0; i < 10; i++) {
        cout << i << ": ";
        stackk<card> temp = table[i];

        while (!temp.isempty()) {
            card c = temp.pop();
            if (c.faceup)
                cout << c.value << " ";
            else
                cout << "X ";
        }
        cout << endl;
    }

    cout << "stock left: " << stockcount << endl;
}

void movecard(int from, int to) {
    if (table[from].isempty()) {
        cout << "nothing to move\n";
        return;
    }

    card c = table[from].pop();
    table[to].push(c);

    if (!table[from].isempty()) {
        card t = table[from].pop();
        t.faceup = true;
        table[from].push(t);
    }
}

void dealmore() {
    if (stockcount < 10) {
        cout << "not enough stock\n";
        return;
    }

    for (int i = 0; i < 10; i++) {
        card c = stockpile.pop();
        stockcount--;
        c.faceup = true;
        table[i].push(c);
    }
}

int main() {
    makecards();
    shufflecards();
    initialdeal();

    char ch;

    while (true) {
        showtable();

        cout << "\nm = move, d = deal, q = quit\n";
        cin >> ch;

        if (ch == 'm') {
            int a, b;
            cout << "from: ";
            cin >> a;
            cout << "to: ";
            cin >> b;
            movecard(a, b);
        }
        else if (ch == 'd') {
            dealmore();
        }
        else if (ch == 'q') {
            break;
        }
    }

    return 0;
}
