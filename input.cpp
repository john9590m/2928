#include <iostream>

using namespace std;

int main(void)
{
    int n=100000;
    cout << n << endl;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<4;j++) cout << rand()%2000000 - 1000000 << " ";
        cout <<endl;
    }
    int m=100000;
    cout << m << endl;
    for (int i=0;i<m;i++) cout << rand()%100000 << " ";
}