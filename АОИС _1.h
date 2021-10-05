#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;

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
    friend vector<int> multiplication(int first, int second);
    friend pair<vector<int>, vector<int>>division(int first, int second);

    friend bool comparewithclass(MyNumber& Test, vector<int>& teststraight, vector<int>& testreverse, vector<int>& testadditional);
};

void oneplus(vector<int>& term);
void vec_print(vector<int>term);
bool summary_alg(vector<int>first, vector<int>second, vector<int>& result);
bool sum_for_mult(vector<int>& result, vector<int>term);
void inversion(vector<int>& term);
void difference_alg(vector<int>& first, vector<int>second);
bool signchecker(vector<int>first, vector<int>second);

MyNumber summary(int first, int second);
MyNumber difference(int first, int second);
vector<int> multiplication(int first, int second);
pair<vector<int>, vector<int>> division(int first, int second);

bool comparewithclass(MyNumber& Test, vector<int>& teststraight, vector<int>& testreverse, vector<int>& testadditional);
bool Test1();
bool Test2();
bool Test3();
bool Test4();
bool Test5();
bool Test6();
bool Test7();
bool Test8();
bool Test9();
bool Test10();
bool Test11();
bool Test12();
bool Test13();
bool Test14();
bool Test15();
bool Test16();
bool Test17();
bool Test18();
bool Test19();
bool Test20();
bool Test21();
bool Test22();
bool Test23();
bool Test24();
bool Test25();
bool Test26();
bool Test27();
bool Test28();
bool Test29();
bool Test30();
bool Test31();
bool Test32();
bool Test33();
bool Test34();
bool Test35();
bool Test36();
bool Test37();
bool Test38();
bool Test39();
bool Test40();
bool Test41();
bool Test42();
bool Test43();
bool Test44();
bool Test45();
bool Test46();
bool Test47();
bool Test48();
bool Test49();
bool Test50();
bool Test51();
bool Test52();
bool Test53();
int tests();