#include <vector>
#include <iostream>
#include <list>
using namespace std;

typedef struct	s_token
{
	int		a;
	char	c;
}				t_token;

void print_wbracket(list<t_token>::iterator &b)
//void print_wbracket(int &b)
{
//	int *a = b;
	b++;
	cout << (*b).a << endl;
	cout << (*b).c << endl;
//	++b;
}

int main()
{
	list<t_token>s;
	t_token	tmp;

	tmp.a = 1;
	tmp.c = 'o';
    s.push_back(tmp);
	tmp.a = 2;
	tmp.c = 'k';
	s.push_back(tmp);
    // s.push_back(22);
    // s.push_back(33);
    // s.push_back(55);
//    for (list<int>::iterator it=s.begin();it!=s.end();it++){
//        cout<<*it<<endl;
	for (auto it = s.begin(); it!= s.end(); it++) {
		print_wbracket(it);
//    for (auto& it : s){
 // 		print_wbracket(&it);
    }
}

// g++ -std=c++11 iter_list.cpp
