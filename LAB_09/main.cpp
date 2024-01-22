#include <iostream>
#include <string>
#include "AVL.h"

using namespace std;

void test_AVL_tree();

int main()
{
    test_AVL_tree();
    return 0;
}

void test_AVL_tree()
{
     cout << "\n\nTesting AVL Tree" << endl;
    AVL<double> myAVL;
    double numbers[] = {7, 9, 13, 6, 4, 2, 5, 8, 1, 10, 3, 11, 12};

    for (int i = 0; i < 13; i++) {
        myAVL.insert(numbers[i]);
        cout << "After inserting " << numbers[i] << ": ";
        myAVL.print();
        cout << endl;
    }
    myAVL.remove(13);
    myAVL.print();
}
