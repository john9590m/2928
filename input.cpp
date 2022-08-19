#include <iostream>

using namespace std;

int main(void)
{
    int n=1000;
    cout << n << endl;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<4;j++) cout << rand()%2000000 - 1000000 << " ";
        cout <<endl;
    }
    cout << 1 << endl << 1 << endl;
}