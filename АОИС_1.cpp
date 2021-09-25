#include <iostream>
#include <vector>
#include <cmath>
#include <stack>


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
    void summary_straight(MyNumber term, string comment);
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
        oneplus(additional);
    }
}
void MyNumber::print()
{
    cout << "Straight :   ";
    vec_print(straight);
    cout << endl << "Reverse :    ";
    vec_print(reverse);
    cout << endl << "Additional : ";
    vec_print(additional);
}
void MyNumber::summary_straight(MyNumber term, string comment)
{   
    vector<int>termone, termtwo;
    if (comment == "straight") termone = straight, termtwo = term.straight;
    else if (comment == "reverse") termone = reverse, termtwo = term.reverse;
    else if (comment == "additional") termone = additional, termtwo = term.additional;
    bool mind = false;
    int i = straight.size() - 1;
    vector<int>result;
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
    cout << "straight1 : ";
    vec_print(straight); 
    cout << "straight2 : ";
    if (comment == "additional") oneplus(result);
    vec_print(term.straight);
    cout << "result :    ";
    vec_print(result);
}

int main()
{
    MyNumber f(13), b(-4);
    f.summary_straight(b, "straight");
    return 0;
}
