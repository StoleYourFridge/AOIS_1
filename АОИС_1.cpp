#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int Size = 8;

class MyNumber
{
public:
    bool positive = true;
    vector<int>straight;
    vector<int>reverse;
    vector<int>additional;

public:
    MyNumber (int number)
    {
        if (number < 0) positive = false;
        number = abs(number);
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
        if (positive) straight.insert(straight.begin(), 0);
        else straight.insert(straight.begin(), 1);
    }

};

int main()
{
    MyNumber f(12);
    for (int i = 0; i < f.straight.size(); i++)
    {
        cout << f.straight[i];
    }
    return 0;
}
