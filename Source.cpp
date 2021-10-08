#include "¿Œ»— _1.h"

using namespace std;

void main()
{
    cout << "1)Tests :: 2)Our own numbers" << endl;
    int choise;
    cin >> choise;
    switch (choise)
    {
    case 1: 
        tests();
        break;
    case 2:
        own_example();
        break;
    default: cout << "Enter something possible to work with!" << endl;
        break;
    }   
    system("pause");
}