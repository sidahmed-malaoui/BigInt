#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "BigInt.h"
using namespace std;

int main()
{
    BigInt a("64177498496");
    BigInt b("-6435135");
    BigInt c("89453");

    cin >> a >> b;
    c = a ^ b;
    cout << c << endl;
    return 0;
}
