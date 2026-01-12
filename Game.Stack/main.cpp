#include <iostream>
#include <ctime>
#include <fstream>

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
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool isfull()
    {
        if (top == siz - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void push(t var)
    {
        if (isfull())
        {
            return;
        }
        top = top + 1;
        ptr[top] = var;
    }

    t pop()
    {
        if (isempty())
        {
            return ptr[0];
        }
        t temp = ptr[top];
        top = top - 1;
        return temp;
    }

    t Top()
    {
        if (isempty())
        {
            return ptr[0];
        }
        return ptr[top];
    }

    int countt()
    {
        int currentCount = top + 1;
        return currentCount;
    }

    void clearr()
    {
        top = -1;
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
int completedsets = 0;

void checksequence(int col)
{
    int totalCards = table[col].countt();
    if (totalCards < 13)
    {
        return;
    }

    card temp[13];
    bool correct = true;

    for (int i = 0; i < 13; i++)
    {
        temp[i] = table[col].pop();
        if (temp[i].faceup == false || temp[i].value != (i + 1))
        {
            correct = false;
        }
    }

    if (correct == true)
    {
        completedsets = completedsets + 1;
        if (table[col].isempty() == false)
        {
            card t = table[col].pop();
            t.faceup = true;
            table[col].push(t);
        }
    }
    else
    {
        for (int i = 12; i >= 0; i--)
        {
            table[col].push(temp[i]);
        }
    }
}

void saveGame()
{
    ofstream out("spider_save.txt");
    if (!out)
    {
        return;
    }

    out << completedsets << " " << stockcount << endl;

    for (int i = 0; i < 10; i++)
    {
        int cnt = table[i].countt();
        out << cnt << " ";
        stackk<card> temp;
        for (int j = 0; j < cnt; j++)
        {
            temp.push(table[i].pop());
        }
        while (temp.isempty() == false)
        {
            card c = temp.pop();
            out << c.value << " " << c.faceup << " ";
            table[i].push(c);
        }
        cout << endl;
    }

    int scnt = stockpile.countt();
    out << scnt << " ";
    stackk<card> stemp;
    for (int j = 0; j < scnt; j++)
    {
        stemp.push(stockpile.pop());
    }
    while (stemp.isempty() == false)
    {
        card c = stemp.pop();
        out << c.value << " " << c.faceup << " ";
        stockpile.push(c);
    }
    out.close();
}

bool loadGame()
{
    ifstream in("spider_save.txt");
    if (!in)
    {
        return false;
    }

    in >> completedsets >> stockcount;

    for (int i = 0; i < 10; i++)
    {
        table[i].clearr();
        int cnt;
        in >> cnt;
        for (int j = 0; j < cnt; j++)
        {
            int v;
            bool f;
            in >> v >> f;
            table[i].push(card(v, f));
        }
    }

    stockpile.clearr();
    int scnt;
    in >> scnt;
    for (int j = 0; j < scnt; j++)
    {
        int v;
        bool f;
        in >> v >> f;
        stockpile.push(card(v, f));
    }
    in.close();
    return true;
}

void makecards()
{
    for (int i = 0; i < 8; i++)
    {
        for (int v = 1; v <= 13; v++)
        {
            card newCard(v, false);
            stockpile.push(newCard);
            stockcount = stockcount + 1;
        }
    }
}

void shufflecards()
{
    card temp[150];
    int k = 0;
    while (stockpile.isempty() == false)
    {
        temp[k] = stockpile.pop();
        k = k + 1;
    }

    srand(time(0));

    for (int i = 0; i < k; i++)
    {
        int r = rand() % k;
        card t = temp[i];
        temp[i] = temp[r];
        temp[r] = t;
    }

    for (int i = 0; i < k; i++)
    {
        stockpile.push(temp[i]);
    }
}

void initialdeal()
{
    for (int col = 0; col < 10; col++)
    {
        int dealcount;
        if (col < 4)
        {
            dealcount = 6;
        }
        else
        {
            dealcount = 5;
        }

        for (int i = 0; i < dealcount; i++)
        {
            table[col].push(stockpile.pop());
            stockcount = stockcount - 1;
        }

        card t = table[col].pop();
        t.faceup = true;
        table[col].push(t);
    }
}

void printcard(card c)
{
    if (c.faceup == true)
    {
        cout << c.value << " ";
    }
    else
    {
        cout << "X ";
    }
}

void showtable()
{
    cout << endl;
    cout << "================ SPIDER SOLITAIRE ================";
    cout << endl;
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "Column " << i << " : ";
        stackk<card> temp;
        int cnt = table[i].countt();
        for (int j = 0; j < cnt; j++)
        {
            temp.push(table[i].pop());
        }
        while (temp.isempty() == false)
        {
            card c = temp.pop();
            printcard(c);
            table[i].push(c);
        }
        cout << endl;
    }

    cout << endl;
    cout << "Completed Sets : " << completedsets << " / 8";
    cout << endl;
    cout << "Stock Remaining : " << stockcount;
    cout << endl;
    cout << endl;
}

void movecard(int from, int to)
{
    if (from < 0 || from > 9 || to < 0 || to > 9 || from == to || table[from].isempty() == true)
    {
        cout << "Invalid move" << endl;
        return;
    }

    card validSeq[104];
    int seqCount = 0;

    while (table[from].isempty() == false)
    {
        card current = table[from].Top();
        if (current.faceup == false)
        {
            break;
        }
        if (seqCount > 0 && current.value != validSeq[seqCount - 1].value + 1)
        {
            break;
        }
        validSeq[seqCount] = table[from].pop();
        seqCount = seqCount + 1;
    }

    int moveCount = 0;
    if (table[to].isempty() == true)
    {
        moveCount = seqCount;
    }
    else
    {
        int destVal = table[to].Top().value;
        for (int i = 0; i < seqCount; i++)
        {
            if (validSeq[i].value == destVal - 1)
            {
                moveCount = i + 1;
                break;
            }
        }
    }

    if (moveCount > 0)
    {
        for (int i = seqCount - 1; i >= moveCount; i--)
        {
            table[from].push(validSeq[i]);
        }
        for (int i = moveCount - 1; i >= 0; i--)
        {
            table[to].push(validSeq[i]);
        }

        if (table[from].isempty() == false)
        {
            card topCard = table[from].Top();
            if (topCard.faceup == false)
            {
                card t = table[from].pop();
                t.faceup = true;
                table[from].push(t);
            }
        }
        checksequence(to);
        saveGame();
    }
    else
    {
        for (int i = seqCount - 1; i >= 0; i--)
        {
            table[from].push(validSeq[i]);
        }
        cout << "Invalid move" << endl;
    }
}

void dealmore()
{
    if (stockcount < 10)
    {
        cout << "Not enough cards" << endl;
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        card c = stockpile.pop();
        c.faceup = true;
        table[i].push(c);
        stockcount = stockcount - 1;
    }

    for (int i = 0; i < 10; i++)
    {
        checksequence(i);
    }
    saveGame();
}

int main()
{
    char start;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "Choice: ";
    cin >> start;

    if (start == '2')
    {
        bool success = loadGame();
        if (success == false)
        {
            cout << "No save found. Starting new game." << endl;
            makecards();
            shufflecards();
            initialdeal();
        }
    }
    else
    {
        makecards();
        shufflecards();
        initialdeal();
    }

    char ch;
    while (true)
    {
        showtable();

        if (completedsets == 8)
        {
            cout << "CONGRATULATIONS! YOU WON" << endl;
            break;
        }

        cout << "m: move | d: deal | q: quit" << endl;
        cout << "Choice: ";
        cin >> ch;

        if (ch == 'm')
        {
            int a;
            int b;
            if (!(cin >> a >> b))
            {
                cout << "Invalid Input! Use numbers for columns." << endl;
                cin.clear();
                while (cin.get() != '\n')
                {

                }
                continue;
            }
            movecard(a, b);
        }
        else if (ch == 'd')
        {
            dealmore();
        }
        else if (ch == 'q')
        {
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
