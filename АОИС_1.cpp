#include "АОИС _1.h"

using namespace std;

const int after_point_size = 5;
const int Size = 32;

bool checker(string number)
{
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] != '1' && number[i] != '2' && number[i] != '3' && number[i] != '4' && number[i] != '5' && number[i] != '6' && number[i] != '7' && number[i] != '8' && number[i] != '9')
            return false;
    }
    return true;
}
void oneplus(vector<int>&term)
{
    bool mind = true;
    int i = term.size() - 1;
    while (mind)
    {
        if (!term[i])
        {
            term[i] = 1;
            mind = false;
        }
        else if (term[i]) {
            term[i] = 0;
            i--;
            if (i == -1) i = term.size() - 1;
        }
    }
}
void vec_print(vector<int>term)
{
    for (int i = 0; i < term.size(); i++)
    {
        cout << term[i];
    }
}
bool summary_alg(vector<int>first, vector<int>second, vector<int>&result)
{
    bool mind = false;
    int i = first.size() - 1;
    while (i != -1)
    {
        if (!mind && !first[i] && !second[i])
        {
            result.insert(result.begin(), 0);
        }
        else if (!mind && (first[i] && !second[i] || !first[i]  && second[i]))
        {
            result.insert(result.begin(), 1);
        }
        else if (!mind && first[i] && second[i])
        {
            result.insert(result.begin(), 0);
            mind = true;
        }
        else if (mind && !first[i] && !second[i])
        {
            result.insert(result.begin(), 1);
            mind = false;
        }
        else if (mind && (first[i] && !second[i] || !first[i] && second[i]))
        {
            result.insert(result.begin(), 0);
        }
        else if (mind && first[i] && second[i])
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
    for (int i = 1; i < term.size(); i++)
    {
        term[i] = abs(term[i] - 1);
    }
}
void difference_alg(vector<int>&first, vector<int>second)
{
    if (first.size() > second.size()) {
        while (second.size() != first.size())
        {
            second.insert(second.begin(), 0);
        }
    }
    vector<int>result;
    for (int i = first.size() - 1; i >= 0; i--)
    {
        if (first[i] && second[i]) result.insert(result.begin(), 0);
        else if (first[i] && !second[i]) result.insert(result.begin(), 1);
        else if(!first[i] && !second[i]) result.insert(result.begin(), 0);
        else if (!first[i] && second[i]) {
            result.insert(result.begin(), 1);
            int nearpositive = i;
            while (!first[nearpositive])
            {
                first[nearpositive] = 1;
                nearpositive--;
            }
            first[nearpositive] = 0;
        }
    }
    while (result.size() > 0 && !result[0])
    {
        result.erase(result.begin());
    }
    first = result;
}
bool signchecker(vector<int>first, vector<int>second)
{
    if (first.size() < second.size()) return false;
    else if (first.size() > second.size()) {
        while (second.size() != first.size())
        {
            second.insert(second.begin(), 0);
        }
    }
    for (int i = 0; i < first.size(); i++)
    {
        if (!first[i] && second[i]) return false;
        else if (first[i] && !second[i]) return true;
    }
    return true;
}

vector<int> digitization(int number)
{
    vector<int> result;
    while (true)
    {
        if (!number)
        {
            result.insert(result.begin(), 0);
            break;
        }
        if (number != 1) {
            result.insert(result.begin(), number % 2);
        }
        else {
            result.insert(result.begin(), 1);
            break;
        }
        number /= 2;
    }
    return result;
}

MyNumber::MyNumber(int number) : positive(true), number(number)
{
    if (number < 0) {
        positive = false;
        number = abs(number);
    }
    straight = binary = digitization(number);
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
    cout << endl << "Reverse    : ";
    vec_print(reverse);
    cout << endl << "Additional : ";
    vec_print(additional);
    cout << endl << endl;
}

MyNumber summary(int first, int second)
{
    MyNumber first_term(first), second_term(second), result_obj;
    vector<int>result_vec;
    if (summary_alg(first_term.reverse, second_term.reverse, result_vec)) oneplus(result_vec);
    result_obj.reverse = result_vec;
    if (result_vec[0]) inversion(result_vec);
    result_obj.straight = result_vec;
    result_vec.clear();
    summary_alg(first_term.additional, second_term.additional, result_vec);
    result_obj.additional = result_vec;
    return result_obj;
}
MyNumber difference(int first, int second)
{
    return summary(first, -second);
}
vector<int> multiplication(int first, int second)
{
    bool sign = true;
    if ((first < 0 && second > 0) || (first > 0 && second < 0)) sign = false;
    MyNumber first_term(first), second_term(second);
    vector<int> result(first_term.binary.size(), 0), term = first_term.binary;
    int expected = 0;
    for (int i = second_term.binary.size() - 1; i >= 0; i--)
    {
        if (second_term.binary[i]) {
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
    while (result.size() != Size - 1)
    {
        result.insert(result.begin(), 0);
    }
    if (sign) result.insert(result.begin(), 0);
    else result.insert(result.begin(), 1);
    return result;
}
pair<vector<int>, vector<int>> division(int first, int second)
{
    if (!first) {
        pair<vector<int>, vector<int>> result({ 0 }, { 0,0,0,0,0 });
        return result;
    }

    bool sign = true;
    if ((first < 0 && second > 0) || (first > 0 && second < 0)) sign = false;
    MyNumber first_term(first), second_term(second);
    vector<int>beforepoint, afterpoint, first_term_clone;
    int pointer = 0;
    while (!(signchecker(first_term_clone, second_term.binary)))
    {
        if (pointer < first_term.binary.size()) {
            first_term_clone.push_back(first_term.binary[pointer]);
            pointer++;
        }
        else if (pointer >= first_term.binary.size())
        {
            if (!beforepoint.size()) {
                beforepoint.push_back(0);
                pointer++;
            }
            else  afterpoint.push_back(0);
            first_term_clone.push_back(0);
        }
    }
    while (afterpoint.size() < after_point_size)
    {
        if (signchecker(first_term_clone, second_term.binary))
        {
            if (pointer < first_term.binary.size())
            {
                beforepoint.push_back(1);
                difference_alg(first_term_clone, second_term.binary);
                first_term_clone.push_back(first_term.binary[pointer]);
                pointer++;
            }
            else if (pointer == first_term.binary.size())
            {
                beforepoint.push_back(1);
                difference_alg(first_term_clone, second_term.binary);
                if (!first_term_clone.size()) break;
                else {
                    pointer++;
                    first_term_clone.push_back(0);
                }
            }
            else if (pointer > first_term.binary.size())
            {
                afterpoint.push_back(1);
                difference_alg(first_term_clone, second_term.binary);
                if (!first_term_clone.size()) break;
                else {
                    first_term_clone.push_back(0);
                }
            }

        }
        else if (!(signchecker(first_term_clone, second_term.binary)))
        {
            if (pointer < first_term.binary.size()) {
                beforepoint.push_back(0);
                first_term_clone.push_back(first_term.binary[pointer]);
                pointer++;
            }
            else if (pointer == first_term.binary.size())
            {
                beforepoint.push_back(0);
                first_term_clone.push_back(0);
                pointer++;
            }
            else if (pointer > first_term.binary.size())
            {
                afterpoint.push_back(0);
                first_term_clone.push_back(0);
            }
        }
    }
    while (beforepoint.size() != Size - 1)
    {
        beforepoint.insert(beforepoint.begin(), 0);
    }
    while (afterpoint.size() != 5)
    {
        afterpoint.push_back(0);
    }
    if (sign) beforepoint.insert(beforepoint.begin(), 0);
    else beforepoint.insert(beforepoint.begin(), 1);
    pair<vector<int>, vector<int>>output(beforepoint, afterpoint);
    return output;
}
pair<vector<int>, vector<int>> summary_floating_point(int first, int second)
{
    first = abs(first);
    second = abs(second);
    MyNumber first_term(first), second_term(second);
    pair<vector<int>, int> pair_one(first_term.binary, first_term.binary.size()), pair_two(second_term.binary, second_term.binary.size());
    while (pair_one.first.size() != pair_two.first.size())
    {
        if (pair_one.first.size() < pair_two.first.size()) pair_one.first.push_back(0);
        else pair_two.first.push_back(0);
    }
    while (pair_one.second != pair_two.second)
    {
        if (pair_one.second < pair_two.second) {
            pair_one.first.insert(pair_one.first.begin(), 0);
            pair_one.first.erase(pair_one.first.begin() + (pair_one.first.size() -  1));
            pair_one.second++;
        }
        else {
            pair_two.first.insert(pair_two.first.begin(), 0);
            pair_two.first.erase(pair_two.first.begin() + (pair_two.first.size() - 1));
            pair_two.second++;
        }
    }
    if (sum_for_mult(pair_one.first, pair_two.first)) {
        pair_one.first.insert(pair_one.first.begin(), 1);
        pair_one.second++;
    }
    pair<vector<int>, vector<int>> result(pair_one.first, digitization(pair_one.second));
    return result;
}


///////////////////////////////////////////////////////test functions////////////////////////////////////////
bool comparewithclass(MyNumber &Test, vector<int>&teststraight, vector<int>&testreverse, vector<int>&testadditional)
{
    if (Test.straight != teststraight) return false;
    if (Test.reverse != testreverse) return false;
    if (Test.additional != testadditional) return false;
    return true;
}
/////// constructor tests /////////////////////
bool Test1()
{
    vector<int> teststraight{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1 };
    vector<int> testreverse{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1 };
    vector<int> testadditional{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1 };
    MyNumber Test(13);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 1 Correct!" << endl;
        return true;
    }
    cout << "Test 1 Incorrect!" << endl;
    return false;
}
bool Test2()
{
    vector<int> teststraight{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,0};
    vector<int> testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,0,1,1,1,1};
    vector<int> testadditional{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0};
    MyNumber Test(-1232);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 2 Correct!" << endl;
        return true;
    }
    cout << "Test 2 Incorrect!" << endl;
    return false;
}
bool Test3()
{
    vector<int> teststraight(32, 0);
    vector<int> testreverse(32, 0);
    vector<int> testadditional(32, 0);
    MyNumber Test(0);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 3 Correct!" << endl;
        return true;
    }
    cout << "Test 3 Incorrect!" << endl;
    return false;
}
bool Test4()
{
    vector<int> teststraight{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0};
    vector<int> testreverse{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 };
    vector<int> testadditional{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0 };
    MyNumber Test(14);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 4 Correct!" << endl;
        return true;
    }
    cout << "Test 4 Incorrect!" << endl;
    return false;
}
bool Test5()
{
    vector<int> teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0 };
    vector<int> testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1 };
    vector<int> testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0 };
    MyNumber Test(-22);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 5 Correct!" << endl;
        return true;
    }
    cout << "Test 5 Incorrect!" << endl;
    return false;
}
///////////////summary////////////////////////
bool Test6()
{
    vector<int>equaltest{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1};
    MyNumber Test = summary(123, 28);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 6 Correct!" << endl;
        return true;
    }
    cout << "Test 6 Incorrect!" << endl;
    return false;
}
bool Test7()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1 };
    MyNumber Test = summary(-123, 28);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 7 Correct!" << endl;
        return true;
    }
    cout << "Test 7 Incorrect!" << endl;
    return false;
}
bool Test8()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1 };
    MyNumber Test = summary(123, -28);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 8 Correct!" << endl;
        return true;
    }
    cout << "Test 8 Incorrect!" << endl;
    return false;
}
bool Test9()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,0,0 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,0,1 };
    MyNumber Test = summary(-123, -28);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 9 Correct!" << endl;
        return true;
    }
    cout << "Test 9 Incorrect!" << endl;
    return false;
}
bool Test10()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1 };
    MyNumber Test = summary(612, 1237);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 10 Correct!" << endl;
        return true;
    }
    cout << "Test 10 Incorrect!" << endl;
    return false;
}
bool Test11()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,1 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,0 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,1,1,1 };
    MyNumber Test = summary(612, -1237);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 11 Correct!" << endl;
        return true;
    }
    cout << "Test 11 Incorrect!" << endl;
    return false;
}
bool Test12()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,1 };
    MyNumber Test = summary(-612, 1237);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 12 Correct!" << endl;
        return true;
    }
    cout << "Test 12 Incorrect!" << endl;
    return false;
}
bool Test13()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1 };
    MyNumber Test = summary(-612, -1237);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 13 Correct!" << endl;
        return true;
    }
    cout << "Test 13 Incorrect!" << endl;
    return false;
}
bool Test14()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0 };
    MyNumber Test = summary(14, 22);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 14 Correct!" << endl;
        return true;
    }
    cout << "Test 14 Incorrect!" << endl;
    return false;
}
bool Test15()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 };
    MyNumber Test = summary(14, -22);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 15 Correct!" << endl;
        return true;
    }
    cout << "Test 15 Incorrect!" << endl;
    return false;
}
bool Test16()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 };
    MyNumber Test = summary(-14, 22);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 16 Correct!" << endl;
        return true;
    }
    cout << "Test 16 Incorrect!" << endl;
    return false;
}
bool Test17()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0 };
    MyNumber Test = summary(-14, -22);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 17 Correct!" << endl;
        return true;
    }
    cout << "Test 17 Incorrect!" << endl;
    return false;
}
////////////////difference//////////////////////////
bool Test18()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,1,1 };
    MyNumber Test = difference(1899, 212);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 18 Correct!" << endl;
        return true;
    }
    cout << "Test 18 Incorrect!" << endl;
    return false;
}
bool Test19()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1 };
    MyNumber Test = difference(1899, -212);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 19 Correct!" << endl;
        return true;
    }
    cout << "Test 19 Incorrect!" << endl;
    return false;
}
bool Test20()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,1};
    MyNumber Test = difference(-1899, 212);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 20 Correct!" << endl;
        return true;
    }
    cout << "Test 20 Incorrect!" << endl;
    return false;
}
bool Test21()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,1,0,1,1,1 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,0,1,0,0,0 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,1,1,0,1,0,0,1 };
    MyNumber Test = difference(-1899, -212);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 21 Correct!" << endl;
        return true;
    }
    cout << "Test 21 Incorrect!" << endl;
    return false;
}
bool Test22()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0 };
    vector<int>testreverse { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,0,1,0 };
    MyNumber Test = difference(314, 872);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 22 Correct!" << endl;
        return true;
    }
    cout << "Test 22 Incorrect!" << endl;
    return false;
}
bool Test23()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0 };
    MyNumber Test = difference(314, -872);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 23 Correct!" << endl;
        return true;
    }
    cout << "Test 23 Incorrect!" << endl;
    return false;
}
bool Test24()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0 };
    vector<int>testreverse { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,0,1 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,0,1,1,1,1,0 };
    MyNumber Test = difference(-314, 872);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 24 Correct!" << endl;
        return true;
    }
    cout << "Test 24 Incorrect!" << endl;
    return false;
}
bool Test25()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,1,0 };
    MyNumber Test = difference(-314, -872);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 25 Correct!" << endl;
        return true;
    }
    cout << "Test 25 Incorrect!" << endl;
    return false;
}
bool Test26()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 };
    MyNumber Test = difference(14, 22);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 26 Correct!" << endl;
        return true;
    }
    cout << "Test 26 Incorrect!" << endl;
    return false;
}
bool Test27()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0 };
    MyNumber Test = difference(14, -22);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 27 Correct!" << endl;
        return true;
    }
    cout << "Test 27 Incorrect!" << endl;
    return false;
}
bool Test28()
{
    vector<int>teststraight{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0 };
    vector<int>testreverse{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1 };
    vector<int>testadditional{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0 };
    MyNumber Test = difference(-14, 22);
    if (comparewithclass(Test, teststraight, testreverse, testadditional)) {

        cout << "Test 28 Correct!" << endl;
        return true;
    }
    cout << "Test 28 Incorrect!" << endl;
    return false;
}
bool Test29()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 };
    MyNumber Test = difference(-14, -22);
    if (comparewithclass(Test, equaltest, equaltest, equaltest)) {

        cout << "Test 29 Correct!" << endl;
        return true;
    }
    cout << "Test 29 Incorrect!" << endl;
    return false;
}
////////////////multiplication//////////////////
bool Test30()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,0 };
    if (equaltest == multiplication(145, 540)) {
        cout << "Test 30 Correct!" << endl;
        return true;
    } 
    cout << "Test 30 Incorrect!" << endl;
    return false;
}
bool Test31()
{
    vector<int>equaltest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,0 };
    if (equaltest == multiplication(145, -540)) {
        cout << "Test 31 Correct!" << endl;
        return true;
    }
    cout << "Test 31 Incorrect!" << endl;
    return false;
}
bool Test32()
{
    vector<int>equaltest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,0 };
    if (equaltest == multiplication(-145, 540)) {
        cout << "Test 32 Correct!" << endl;
        return true;
    }
    cout << "Test 32 Incorrect!" << endl;
    return false;
}
bool Test33()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,0,0 };
    if (equaltest == multiplication(-145, -540)) {
        cout << "Test 33 Correct!" << endl;
        return true;
    }
    cout << "Test 33 Incorrect!" << endl;
    return false;
}
bool Test34()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0 };
    if (equaltest == multiplication(816, 94)) {
        cout << "Test 34 Correct!" << endl;
        return true;
    }
    cout << "Test 34 Incorrect!" << endl;
    return false;
}
bool Test35()
{
    vector<int>equaltest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0 };
    if (equaltest == multiplication(816, -94)) {
        cout << "Test 35 Correct!" << endl;
        return true;
    }
    cout << "Test 35 Incorrect!" << endl;
    return false;
}
bool Test36()
{
    vector<int>equaltest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0 };
    if (equaltest == multiplication(-816, 94)) {
        cout << "Test 36 Correct!" << endl;
        return true;
    }
    cout << "Test 36 Incorrect!" << endl;
    return false;
}
bool Test37()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0 };
    if (equaltest == multiplication(-816, -94)) {
        cout << "Test 37 Correct!" << endl;
        return true;
    }
    cout << "Test 37 Incorrect!" << endl;
    return false;
}
bool Test38()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0 };
    if (equaltest == multiplication(14, 22)) {
        cout << "Test 38 Correct!" << endl;
        return true;
    }
    cout << "Test 38 Incorrect!" << endl;
    return false;
}
bool Test39()
{
    vector<int>equaltest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0};
    if (equaltest == multiplication(14, -22)) {
        cout << "Test 39 Correct!" << endl;
        return true;
    }
    cout << "Test 39 Incorrect!" << endl;
    return false;
}
bool Test40()
{
    vector<int>equaltest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0 };
    if (equaltest == multiplication(-14, 22)) {
        cout << "Test 40 Correct!" << endl;
        return true;
    }
    cout << "Test 40 Incorrect!" << endl;
    return false;
}
bool Test41()
{
    vector<int>equaltest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0 };
    if (equaltest == multiplication(-14, -22)) {
        cout << "Test 41 Correct!" << endl;
        return true;
    }
    cout << "Test 41 Incorrect!" << endl;
    return false;
}
///////////////////////////division///////////
bool Test42()
{
    vector<int>beforetest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1 };
    vector<int>aftertest{ 0,0,1,0,1 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(1890, 17)) {
        cout << "Test 42 Correct!" << endl;
        return true;
    }
    cout << "Test 42 Incorrect!" << endl;
    return false;
}
bool Test43()
{
    vector<int>beforetest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1 };
    vector<int>aftertest{ 0,0,1,0,1 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(1890, -17)) {
        cout << "Test 43 Correct!" << endl;
        return true;
    }
    cout << "Test 43 Incorrect!" << endl;
    return false;
}
bool Test44()
{
    vector<int>beforetest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1 };
    vector<int>aftertest{ 0,0,1,0,1 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(-1890, 17)) {
        cout << "Test 44 Correct!" << endl;
        return true;
    }
    cout << "Test 44 Incorrect!" << endl;
    return false;
}
bool Test45()
{
    vector<int>beforetest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1 };
    vector<int>aftertest{ 0,0,1,0,1 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(-1890, -17)) {
        cout << "Test 45 Correct!" << endl;
        return true;
    }
    cout << "Test 45 Incorrect!" << endl;
    return false;
}
bool Test46()
{
    vector<int>beforetest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 0,0,1,1,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(16, 78)) {
        cout << "Test 46 Correct!" << endl;
        return true;
    }
    cout << "Test 46 Incorrect!" << endl;
    return false;
}
bool Test47()
{
    vector<int>beforetest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 0,0,1,1,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(16, -78)) {
        cout << "Test 47 Correct!" << endl;
        return true;
    }
    cout << "Test 47 Incorrect!" << endl;
    return false;
}
bool Test48()
{
    vector<int>beforetest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 0,0,1,1,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(-16, 78)) {
        cout << "Test 48 Correct!" << endl;
        return true;
    }
    cout << "Test 48 Incorrect!" << endl;
    return false;
}
bool Test49()
{
    vector<int>beforetest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 0,0,1,1,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(-16, -78)) {
        cout << "Test 49 Correct!" << endl;
        return true;
    }
    cout << "Test 49 Incorrect!" << endl;
    return false;
}
bool Test50()
{
    vector<int>beforetest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 1,0,1,0,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(14, 22)) {
        cout << "Test 50 Correct!" << endl;
        return true;
    }
    cout << "Test 50 Incorrect!" << endl;
    return false;
}
bool Test51()
{
    vector<int>beforetest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 1,0,1,0,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(14, -22)) {
        cout << "Test 51 Correct!" << endl;
        return true;
    }
    cout << "Test 51 Incorrect!" << endl;
    return false;
}
bool Test52()
{
    vector<int>beforetest{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 1,0,1,0,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(-14, 22)) {
        cout << "Test 52 Correct!" << endl;
        return true;
    }
    cout << "Test 52 Incorrect!" << endl;
    return false;
}
bool Test53()
{
    vector<int>beforetest{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    vector<int>aftertest{ 1,0,1,0,0 };
    pair<vector<int>, vector<int>> sample(beforetest, aftertest);
    if (sample == division(-14, -22)) {
        cout << "Test 53 Correct!" << endl;
        return true;
    }
    cout << "Test 53 Incorrect!" << endl;
    return false;
}
bool Test54()
{
    vector<int>mant_test{ 1,0,0,1,0,0 };
    vector<int>exp_test{ 1,1,0 };
    pair<vector<int>, vector<int>> sample(mant_test, exp_test);
    if (sample == summary_floating_point(22, 14)) {
        cout << "Test 54 Correct!" << endl;
        return true;
    }
    cout << "Test 54 Incorrect!" << endl;
    return false;
}
bool Test55()
{
    vector<int>mant_test{ 1,0,0,1,0,0 };
    vector<int>exp_test{ 1,1,0 };
    pair<vector<int>, vector<int>> sample(mant_test, exp_test);
    if (sample == summary_floating_point(14, 22)) {
        cout << "Test 55 Correct!" << endl;
        return true;
    }
    cout << "Test 55 Incorrect!" << endl;
    return false;
}
bool Test56()
{
    vector<int>mant_test{ 1,0,0,1,0,1,0,1,0,0,0 };
    vector<int>exp_test{ 1,0,1,1 };
    pair<vector<int>, vector<int>> sample(mant_test, exp_test);
    if (sample == summary_floating_point(1114, 78)) {
        cout << "Test 56 Correct!" << endl;
        return true;
    }
    cout << "Test 56 Incorrect!" << endl;
    return false;
}
bool Test57()
{
    vector<int>mant_test{ 1,1,0,1,0,1,1,1,0,1,1 };
    vector<int>exp_test{ 1,0,1,1 };
    pair<vector<int>, vector<int>> sample(mant_test, exp_test);
    if (sample == summary_floating_point(45, 1678)) {
        cout << "Test 57 Correct!" << endl;
        return true;
    }
    cout << "Test 57 Incorrect!" << endl;
    return false;
}
int tests()
{
    int correctcounter = 0;
    correctcounter += Test1();
    correctcounter += Test2();
    correctcounter += Test3();
    correctcounter += Test4();
    correctcounter += Test5();
    correctcounter += Test6();
    correctcounter += Test7();
    correctcounter += Test8();
    correctcounter += Test9();
    correctcounter += Test10();
    correctcounter += Test11();
    correctcounter += Test12();
    correctcounter += Test13();
    correctcounter += Test14();
    correctcounter += Test15();
    correctcounter += Test16();
    correctcounter += Test17();
    correctcounter += Test18();
    correctcounter += Test19();
    correctcounter += Test20();
    correctcounter += Test21();
    correctcounter += Test22();
    correctcounter += Test23();
    correctcounter += Test24();
    correctcounter += Test25();
    correctcounter += Test26();
    correctcounter += Test27();
    correctcounter += Test28();
    correctcounter += Test29();
    correctcounter += Test30();
    correctcounter += Test31();
    correctcounter += Test32();
    correctcounter += Test33();
    correctcounter += Test34();
    correctcounter += Test35();
    correctcounter += Test36();
    correctcounter += Test37();
    correctcounter += Test38();
    correctcounter += Test39();
    correctcounter += Test40();
    correctcounter += Test41();
    correctcounter += Test42();
    correctcounter += Test43();
    correctcounter += Test44();
    correctcounter += Test45();
    correctcounter += Test46();
    correctcounter += Test47();
    correctcounter += Test48();
    correctcounter += Test49();
    correctcounter += Test50();
    correctcounter += Test51();
    correctcounter += Test52();
    correctcounter += Test53();
    correctcounter += Test54();
    correctcounter += Test55();
    correctcounter += Test56();
    correctcounter += Test57();
    cout << "Tests passed : " << correctcounter << endl;
    return correctcounter;
}

void own_example ()
{
    cout << "Enter term1 and term2 for operations : ";
    string term_one, term_two;
    cin.ignore();
    getline(cin, term_one);
    getline(cin, term_two);
    if (!checker(term_one)) {
        cout << "Enter something possible to work with" << endl;
        return;
    }
    if (!checker(term_two)) {
        cout << "Enter something possible to work with" << endl;
        return;
    }
    int term1 =  stoi(term_one), term2 = stoi(term_two);
    cout << endl << "Summary : " << endl;
    summary(term1, term2).print();
    cout << "Difference : " << endl;
    difference(term1, term2).print();
    cout << "Multiplication : " << endl;
    vector<int> multout = multiplication(term1, term2);
    vec_print(multout);
    cout << endl << endl << "Division : " << endl;
    if (!term2) cout << "Error!" << endl;
    else {
        pair<vector<int>, vector<int>>divout = division(term1, term2);
        vec_print(divout.first);
        cout << ",";
        vec_print(divout.second);
    }
    cout << endl << endl << "Floating point summary : " << endl;
    pair<vector<int>, vector<int>> sumout = summary_floating_point(term1, term2);
    cout << "0,";
    vec_print(sumout.first);
    cout << "*2^";
    vec_print(sumout.second);
    cout << endl;
}
//////////////////////////////////////////////////////////////////


