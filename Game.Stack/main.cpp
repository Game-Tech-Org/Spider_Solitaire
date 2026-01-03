#include <iostream>
#include <ctime>
using namespace std;

template <class t>
class stackk
{
    int siz;
    t* ptr;
    int top;

public:
    stackk(int s = 200)
    {
        siz = s;
        top = -1;
        ptr = new t[siz];
    }

    bool isempty()
    {
        if (top == -1)
            return true;
        return false;
    }

    bool isfull()
    {
        if (top == siz - 1)
            return true;
        return false;
    }

    void push(t var)
    {
        if (isfull())
            return;

        top = top + 1;
        ptr[top] = var;
    }

    t pop()
    {
        if (isempty())
            return ptr[0];

        t val = ptr[top];
        top = top - 1;
        return val;
    }

    t Top()
    {
        return ptr[top];
    }

    int count()
    {
        return top + 1;
    }
};

class card
{
public:
    int value;
    bool faceup;

    card()
    {
        value = 0;
        faceup = false;
    }

    card(int v, bool f)
    {
        value = v;
        faceup = f;
    }
};

stackk<card> table[10];
stackk<card> stockpile(150);
int stockcount = 0;

void makecards()
{
    for (int set = 0; set < 8; set++)
    {
        for (int val = 1; val <= 13; val++)
        {
            card c(val, false);
            stockpile.push(c);
            stockcount = stockcount + 1;
        }
    }
}

void shufflecards()
{
    card temp[150];
    int index = 0;

    while (!stockpile.isempty())
    {
        temp[index] = stockpile.pop();
        index = index + 1;
        stockcount = stockcount - 1;
    }

    srand(time(0));

    for (int i = 0; i < index; i++)
    {
        int r = rand() % index;
        card swap = temp[i];
        temp[i] = temp[r];
        temp[r] = swap;
    }

    for (int i = 0; i < index; i++)
    {
        stockpile.push(temp[i]);
        stockcount = stockcount + 1;
    }
}

void initialdeal()
{
    for (int col = 0; col < 10; col++)
    {
        int dealcount;

        if (col < 4)
            dealcount = 6;
        else
            dealcount = 5;

        for (int i = 0; i < dealcount; i++)
        {
            card c = stockpile.pop();
            table[col].push(c);
            stockcount = stockcount - 1;
        }

        card topcard = table[col].pop();
        topcard.faceup = true;
        table[col].push(topcard);
    }
}

void printcard(card c)
{
    if (c.faceup == true)
        cout << c.value << " ";
    else
        cout << "X ";
}

void showtable()
{
    cout << endl;
    cout << "---------------- TABLE ----------------" << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "Column " << i << " : ";

        stackk<card> temp = table[i];

        while (!temp.isempty())
        {
            card c = temp.pop();
            printcard(c);
        }

        cout << endl;
    }

    cout << endl;
    cout << "Stock Remaining : " << stockcount << endl;
    cout << endl;
}

bool validmove(int from, int to)
{
    if (table[from].isempty())
        return false;

    card moving = table[from].Top();

    if (!table[to].isempty())
    {
        card dest = table[to].Top();

        if (dest.value != moving.value + 1)
            return false;
    }

    return true;
}

void movecard(int from, int to)
{
    if (!validmove(from, to))
    {
        cout << "Invalid Move" << endl;
        return;
    }

    card c = table[from].pop();
    table[to].push(c);

    if (!table[from].isempty())
    {
        card t = table[from].pop();
        t.faceup = true;
        table[from].push(t);
    }
}

void dealmore()
{
    if (stockcount < 10)
    {
        cout << "Not enough cards in stock" << endl;
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        card c = stockpile.pop();
        c.faceup = true;
        table[i].push(c);
        stockcount = stockcount - 1;
    }
}

void showmenu()
{
    cout << "Press m to move card" << endl;
    cout << "Press d to deal more cards" << endl;
    cout << "Press q to quit" << endl;
}

int main()
{
    makecards();
    shufflecards();
    initialdeal();

    char choice;

    while (true)
    {
        showtable();
        showmenu();

        cin >> choice;

        if (choice == 'm')
        {
            int a, b;
            cin >> a >> b;
            movecard(a, b);
        }
        else if (choice == 'd')
        {
            dealmore();
        }
        else if (choice == 'q')
        {
            break;
        }
    }
}
