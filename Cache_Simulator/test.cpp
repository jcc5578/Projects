#include <iostream>

using namespace std;

int main()
{
    int static freq = 0;
    for(int i = 0; i < 4; i++)
    {
        freq+=1;
    }
    cout << freq << endl;
    freq = 0;
    cout << freq << endl;
}