#include <iostream>
#include <list>

#define MAX 10

using namespace std;

int main()
{
    list<int> listA;
    list<int>::iterator itr;

    //create list of 0 to 100
    for(int i=0; i<=MAX; i++)
        listA.push_back(i);

    //remove even numbers
    for(itr = listA.begin(); itr != listA.end(); ++itr)
    {
        if ( *itr % 2 == 0 )
        {
//            cout << *itr << endl;
            itr = listA.erase(itr);    //comment this line out and it will print properly
        }
    }

	for (itr = listA.begin(); itr != listA.end(); ++itr)
		cout << *itr << endl;
}
