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
    int number;
    bool positive;
    vector<int>straight;
    vector<int>reverse;
    vector<int>additional;
public:
    MyNumber(int number);
    void print();
    void summary_difference(MyNumber term);
};

MyNumber::MyNumber(int number) : positive(true), number(number)
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
    cout << "Straight   : ";
    vec_print(straight);
    cout << "Reverse    : ";
    vec_print(reverse);
    cout << "Additional : ";
    vec_print(additional);
    cout << endl;
}
void MyNumber::summary_difference(MyNumber term)
{   
    vector<int>result;
    cout << "----------------------------------------------" << endl;
    print();
    term.print();
    if (summary_alg(reverse, term.reverse, result)) oneplus(result);
    if (result[0]) inversion(result);
    cout << "Straight result    : ";
    vec_print(result);
    if (result[0]) inversion(result); 
    cout << "Reverse result     : ";
    vec_print(result);
    result.clear();
    summary_alg(additional, term.additional, result);
    cout << "Additional result  : ";
    vec_print(result);
    cout << "-----------------------------------------------" << endl;
}

void summary(int first, int second) //summary is ready
{
    MyNumber term1(first), term2(second);
    term1.summary_difference(term2);
}                         
void difference(int first, int second) //difference is ready
{
    MyNumber term1(first), term2(-second);
    term1.summary_difference(term2);
}
void MyNumber::difference(MyNumber term)
{
    MyNumber exchange(-term.number);
    summary(exchange);
}


int main()
{
    int term1, term2;
    cout << "Enter term1 and term2 for operations : ";
    cin >> term1 >> term2;
    cout << "Summary : " << term1 << " + " << term2 << " :" << endl;
    summary(term1, term2);
    cout << "Difference : " << term1 << " - " << term2 << " :" << endl;
    difference(term1, term2);
    return 0;
}
