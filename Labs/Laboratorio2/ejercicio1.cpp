#include <iostream>
using namespace std;

int main() {
    unsigned short shortVar = 5;
    unsigned long  longVar  = 65535;
    long           sVar     = -65535;

    cout << "shortVar:\t" << shortVar << endl;
    cout << " Address of shortVar:\t" << &shortVar << "\n";

    cout << "longVar:\t" << longVar << endl;
    cout << " Address of longVar:\t" << &longVar << "\n";

    cout << "sVar:\t" << sVar << endl;
    cout << " Address of sVar:\t" << &sVar << "\n";

    return 0;
}