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

    void push(t var)
    {
        top = top + 1;
        ptr[top] = var;
    }

    t pop()
    {
        t v = ptr[top];
        top = top - 1;
        return v;
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
int completed = 0;

void printcard(card c)
{
    if (c.faceup == true)
        cout << c.value << " ";
    else
        cout << "X ";
}

void checksequence(int col)
{
    if (table[col].count() < 13)
        return;

    stackk<card> temp;

    for (int i = 0; i < 13; i++)
    {
        card c = table[col].pop();
        temp.push(c);
    }

    bool correct = true;

    int expected = 13;

    while (!temp.isempty())
    {
        card c = temp.pop();

        if (c.faceup == false)
            correct = false;

        if (c.value != expected)
            correct = false;

        expected = expected - 1;
    }

    if (correct == true)
    {
        completed = completed + 1;
    }
    else
    {
        for (int i = 0; i < 13; i++)
        {
            table[col].push(temp.pop());
        }
    }

    if (!table[col].isempty())
    {
        card t = table[col].pop();
        t.faceup = true;
        table[col].push(t);
    }
}

void showtable()
{
    cout << endl;
    cout << "------------- TABLE STATUS -------------" << endl;

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
    cout << "Completed Sets : " << completed << " / 8" << endl;
    cout << "Stock Remaining : " << stockcount << endl;
    cout << endl;
}

void movecard(int from, int to)
{
    if (table[from].isempty())
        return;

    card moving = table[from].Top();

    if (!table[to].isempty())
    {
        card dest = table[to].Top();
        if (dest.value != moving.value + 1)
            return;
    }

    table[to].push(table[from].pop());

    if (!table[from].isempty())
    {
        card t = table[from].pop();
        t.faceup = true;
        table[from].push(t);
    }

    checksequence(to);
}

int main()
{
    cout << "Spider Solitaire Started" << endl;

    while (true)
    {
        showtable();

        if (completed == 8)
        {
            cout << "YOU WON THE GAME" << endl;
            break;
        }

        char ch;
        cin >> ch;

        if (ch == 'm')
        {
            int a, b;
            cin >> a >> b;
            movecard(a, b);
        }
        else if (ch == 'q')
        {
            break;
        }
    }
}
