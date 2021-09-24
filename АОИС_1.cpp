#include <iostream>
#include <vector>
#include <cmath>
#include <stack>

using namespace std;

const int Size = 32;

class MyNumber
{
private:
    bool positive;
    vector<int>straight;
    vector<int>reverse;
    vector<int>additional;

public:
    MyNumber(int number);
    void print();
};

MyNumber::MyNumber(int number) : positive(true)
{
    if (number < 0) {
        positive = false;
        number = abs(number);
    }
    while (true)
    {
        if (number != 1) straight.insert(straight.begin(), number % 2);
        else {
            straight.insert(straight.begin(), 1);
            break;
        }
        number /= 2;
    }
    int zeroamount = Size - straight.size() - 1;
    for (int i = 0; i < zeroamount; i++)
    {
        straight.insert(straight.begin(), 0);
    }
    if (positive) {
        straight.insert(straight.begin(), 0);
        reverse = straight;
        additional = straight;
    }
    else {
        straight.insert(straight.begin(), 1);
        reverse = straight;
        additional = straight;
        for (int i = 1; i < straight.size(); i++)
        {
            if (straight[i] == 1) additional[i] = reverse[i] = 0;
            else additional[i] = reverse[i] = 1;
        }
        bool mind = true;
        int i = 31;
        while (mind)
        {
            if (additional[i] == 0)
            {
                additional[i] = 1;
                mind = false;
            }

            else if (additional[i] == 1) {
                additional[i] = 0;
                i--;
            }
            if (i == -1) i = 31;
        }
    }
}
void MyNumber::print()
{
    cout << "Straight :   ";
    for (int i = 0; i < straight.size(); i++)
    {
        cout << straight[i];
    }
    cout << endl << "Reverse :    ";
    for (int i = 0; i < reverse.size(); i++)
    {
        cout << reverse[i];
    }
    cout << endl << "Additional : ";
    for (int i = 0; i < additional.size(); i++)
    {
        cout << additional[i];
    }
}

int main()
{
    MyNumber f(-10);
    f.print();
    return 0;
}
