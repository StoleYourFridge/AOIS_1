#include "¿Œ»— _1.h"

using namespace std;

void main()
{
    int term1, term2;
    cout << "Enter term1 and term2 for operations : ";
    cin >> term1 >> term2;
    cout << endl << "Summary : " << endl;
    summary(term1, term2).print();
    cout << "Difference : " << endl;
    difference(term1, term2).print();
    cout << "Multiplication : " << endl;
    vector<int> multout = multiplication(term1, term2);
    vec_print(multout);
    cout << endl << "Division : " << endl;
    pair<vector<int>, vector<int>>divout = division(term1, term2);
    vec_print(divout.first);
    cout << ",";
    vec_print(divout.second);
    //tests();     
}