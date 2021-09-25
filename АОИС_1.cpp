#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int Size = 32;

void oneplus(vector<int>&additional)
{
    bool mind = true;
    int i = additional.size() - 1;
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
            if (i == -1) i = additional.size() - 1;
        }
    }
}
void vec_print(vector<int>term)
{
    for (int i = 0; i < term.size(); i++)
    {
        cout << term[i];
    }
    cout << endl;
}
bool summary_alg(vector<int>termone, vector<int>termtwo, vector<int>&result)
{
    bool mind = false;
    int i = termone.size() - 1;
    while (i != -1)
    {
        if (!mind && termone[i] == 0 && termtwo[i] == 0)
        {
            result.insert(result.begin(), 0);
        }
        else if (!mind && (termone[i] == 1 && termtwo[i] == 0 || termone[i] == 0 && termtwo[i] == 1))
        {
            result.insert(result.begin(), 1);
        }
        else if (!mind && termone[i] == 1 && termtwo[i] == 1)
        {
            result.insert(result.begin(), 0);
            mind = true;
        }
        else if (mind && termone[i] == 0 && termtwo[i] == 0)
        {
            result.insert(result.begin(), 1);
            mind = false;
        }
        else if (mind && (termone[i] == 1 && termtwo[i] == 0 || termone[i] == 0 && termtwo[i] == 1))
        {
            result.insert(result.begin(), 0);
        }
        else if (mind && termone[i] == 1 && termtwo[i] == 1)
        {
            result.insert(result.begin(), 1);
        }
        i--;
    }
    return mind;
}
void inversion(vector<int>&term)
{
    for (size_t i = 1; i < term.size(); i++)
    {
        term[i] = abs(term[i] - 1);
    }
}

class MyNumber
{
    bool positive;
    vector<int>straight;
    vector<int>reverse;
    vector<int>additional;
public:
    MyNumber(int number);
    void print();
    void summary(MyNumber term);
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
        inversion(reverse);
        inversion(additional);
        oneplus(additional);
    }
}
void MyNumber::print()
{
    cout << "Straight :   ";
    vec_print(straight);
    cout << "Reverse :    ";
    vec_print(reverse);
    cout << "Additional : ";
    vec_print(additional);
    cout << endl;
}
void MyNumber::summary(MyNumber term)
{   
    vector<int>result;
    cout << "----------------------------------------------" << endl;
    print();
    cout << " + " << endl << endl;
    term.print();
    cout << "=" << endl << endl;
    if (summary_alg(reverse, term.reverse, result)) oneplus(result);
    cout << "Reverse summary result    : ";
    vec_print(result);
    result.clear();
    summary_alg(additional, term.additional, result);
    cout << "Additional summary result : ";
    vec_print(result);
    if (result[0]) {
        inversion(result);
        oneplus(result);
    }
    cout << "Straight summary result   : ";
    vec_print(result);
    cout << "-----------------------------------------------" << endl;
}

int main()
{
    MyNumber f(-100), b(23);
    f.summary(b);
    return 0;
}
