#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

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
bool sum_for_mult(vector<int>&result, vector<int>term)
{
    vector<int>exchange = result;
    result.clear();
    return (summary_alg(exchange, term, result));
    
}
void inversion(vector<int>&term)
{
    for (size_t i = 1; i < term.size(); i++)
    {
        term[i] = abs(term[i] - 1);
    }
}
void difference_alg(vector<int>&term1, vector<int>term2)
{
    if (term1.size() > term2.size()) {
        while (term2.size() != term1.size())
        {
            term2.insert(term2.begin(), 0);
        }
    }
    vector<int>result;
    for (int i = term1.size() - 1; i >= 0; i--)
    {
        if (term1[i] && term2[i]) result.insert(result.begin(), 0);
        else if (term1[i] && !term2[i]) result.insert(result.begin(), 1);
        else if(!term1[i] && !term2[i]) result.insert(result.begin(), 0);
        else if (!term1[i] && term2[i]) {
            result.insert(result.begin(), 1);
            int nearpositive = i;
            while (!term1[nearpositive])
            {
                term1[nearpositive] = 1;
                nearpositive--;
            }
            term1[nearpositive] = 0;
        }
    }
    while (result.size() > 0 && !result[0])
    {
        result.erase(result.begin());
    }
    term1 = result;
}
bool signchecker(vector<int>term1, vector<int>term2)
{
    if (term1.size() < term2.size()) return false;
    else if (term1.size() > term2.size()) {
        while (term2.size() != term1.size())
        {
            term2.insert(term2.begin(), 0);
        }
    }
    for (int i = 0; i < term1.size(); i++)
    {
        if (!term1[i] && term2[i]) return false;
        else if (term1[i] && !term2[i]) return true;
    }
    return true;
}

class MyNumber
{ 
    int number;
    bool positive;
    vector<int>binary;
    vector<int>straight;
    vector<int>reverse;
    vector<int>additional;
public:
    MyNumber() {};
    MyNumber(int number);
    void print();
    friend MyNumber summary(int first, int second);
    friend MyNumber difference(int first, int second);
    friend pair<vector<int>, bool> multiplication(int first, int second);
    friend pair< pair<vector<int>, vector<int>>, bool> division(int first, int second);
};
MyNumber::MyNumber(int number) : positive(true), number(number)
{
    if (number < 0) {
        positive = false;
        number = abs(number);
    }
    while (true)
    {
        if (!number)
        {
            straight.insert(straight.begin(), 0);
            binary.insert(binary.begin(), 0);
            break;
        }
        if (number != 1) {
            straight.insert(straight.begin(), number % 2);
            binary.insert(binary.begin(), number % 2);
        }
        else {
            straight.insert(straight.begin(), 1);
            binary.insert(binary.begin(), 1);
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
    /*cout << "Binary     : ";
    vec_print(binary);*/
    cout << "Straight   : ";
    vec_print(straight);
    cout << "Reverse    : ";
    vec_print(reverse);
    cout << "Additional : ";
    vec_print(additional);
    cout << endl;
}

MyNumber summary(int first, int second)
{
    MyNumber term1(first), term2(second), result_obj;
    vector<int>vec_result;
    if (summary_alg(term1.reverse, term2.reverse, vec_result)) oneplus(vec_result);
    result_obj.reverse = vec_result;
    if (vec_result[0]) inversion(vec_result);
    result_obj.straight = vec_result;
    vec_result.clear();
    summary_alg(term1.additional, term2.additional, vec_result);
    result_obj.additional = vec_result;
    result_obj.print();
    return result_obj;
}
MyNumber difference(int first, int second)
{
    return summary(first, -second);
}
pair<vector<int>,bool> multiplication(int first, int second)
{
    bool sign = true;
    if ((first < 0 && second > 0) || (first > 0 && second < 0)) sign = false;
    MyNumber term1(first), term2(second);
    vector<int> result(term1.binary.size(), 0), term = term1.binary;
    int expected = 0;
    for (int i = term2.binary.size() - 1; i >= 0; i--)
    {
        if (term2.binary[i]) {
            for (int i = 0; i < expected; i++)
            {
                result.insert(result.begin(), 0);
            }
            if (sum_for_mult(result, term)) {
                result.insert(result.begin(), 1);
                expected = 0;
            }
            else expected = 1;
        }
        else {
            expected++;
        }
        term.push_back(0);
    }
    pair <vector<int>, bool> output(result, sign);
    return output;
}
pair< pair<vector<int>, vector<int>>, bool> division(int first, int second)
{
    bool sign = true;
    if ((first < 0 && second > 0) || (first > 0 && second < 0)) sign = false;
    MyNumber term1(first), term2(second);
    vector<int>prevpoint, afterpoint, term1clone;
    int pointer = 0;
    while (!(signchecker(term1clone, term2.binary)))
    {
        if (pointer < term1.binary.size()) {
            term1clone.push_back(term1.binary[pointer]);
            pointer++;
        }
        else if (pointer >= term1.binary.size())
        {
            if (!prevpoint.size()) {
                prevpoint.push_back(0);
                pointer++;
            }
            else  afterpoint.push_back(0);
            term1clone.push_back(0);
        }
    }
    while (afterpoint.size() < 5)
    {
        if (signchecker(term1clone, term2.binary))
        {
            if (pointer < term1.binary.size())
            {
                prevpoint.push_back(1);
                difference_alg(term1clone, term2.binary);
                term1clone.push_back(term1.binary[pointer]);
                pointer++;
            }
            else if (pointer == term1.binary.size())
            {
                prevpoint.push_back(1);
                difference_alg(term1clone, term2.binary);
                if (!term1clone.size()) break;
                else {
                    pointer++;
                    term1clone.push_back(0);
                }
            }
            else if (pointer > term1.binary.size())
            {
                afterpoint.push_back(1);
                difference_alg(term1clone, term2.binary);
                if (!term1clone.size()) break;
                else {
                    term1clone.push_back(0);
                }
            }

        }
        else if (!(signchecker(term1clone, term2.binary)))
        {
            if (pointer < term1.binary.size()) {
                prevpoint.push_back(0);
                term1clone.push_back(term1.binary[pointer]);
                pointer++;
            }
            else if (pointer == term1.binary.size())
            {
                prevpoint.push_back(0);
                term1clone.push_back(0);
                pointer++;
            }
            else if (pointer > term1.binary.size())
            {
                afterpoint.push_back(0);
                term1clone.push_back(0);
            }
        }
    }
    cout << "Before point : ";
    vec_print(prevpoint);
    cout << "After point : ";
    vec_print(afterpoint);
    pair<vector<int>, vector<int>> number(prevpoint, afterpoint);
    pair< pair<vector<int>, vector<int>>, bool> output(number, sign);
    return output;
}





int main()
{
    int term1, term2;
    cout << "Enter term1 and term2 for operations : ";
    cin >> term1 >> term2;
    cout << endl << "Summary : " << endl;
    summary(term1, term2);
    cout << "Difference : " << endl;
    difference(term1, term2);
    cout << "Multiplication : "  << endl;
    pair<vector<int>, bool> multout = multiplication(term1, term2);
    if (multout.second) cout << "Positive -> ";
    else cout << "Negative -> ";
    vec_print(multout.first);
    cout << endl << "Division : "  <<  endl;
    pair< pair<vector<int>, vector<int>>, bool> divout = division(term1, term2);
    if (divout.second) cout << "Positive ^|^";
    else cout << "Negative ^|^";
    /*vector<int> a{0, 0, 0}, b{1, 1};
    bool r =signchecker(a, b);
    cout << r;*/
}
