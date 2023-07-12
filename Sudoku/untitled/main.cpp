#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

vector<int> vect;

for (int i = 0; i < 4; ++i){

    vect[i] = i*2;
    cout << vect[i];
}
/*

for (int i = 0; i < 4; i++){

   cout << vect[i];
} */

vect[2] = 609;

cout << vect[3];
    return 0;
}
