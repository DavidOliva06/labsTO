#include <iostream>
using namespace std;

int main() {
    int localVariable = 5;
    int * pLocal = &localVariable;
    int * pHeap = new int;
    //int *pHeap = NULL;
    if (pHeap == NULL)
    {
        cout << "Error! No memory for pHeap!!";
        return 0;
    }
    *pHeap = 7;
    cout << "localVariable: " << localVariable << "\n";
    cout << "*pLocal: " << *pLocal << "\n";
    cout << "*pHeap: " << *pHeap << "\n";
    delete pHeap;

    pHeap = new int;
    if (pHeap == NULL)
    {
        cout << "Error! No memory for pHeap!!";
        return 0;
    }
    *pHeap = 9;
    cout << "*pHeap: " << *pHeap << "\n";
    delete pHeap;

    return 0;
}