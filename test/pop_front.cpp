#include <iostream>
#include <list>
#include <string>
int main ()
{
  std::list<std::string*> mylist;
  std::string *s1 = new std::string("100");
  std::string *s2 = new std::string("200");
  std::string *s3 = new std::string("300");
  mylist.push_back (s1);
  mylist.push_back (s2);
  mylist.push_back (s3);

  // std::string *s4  = new std::string("400");
  // delete s4;
  // delete s4;
  std::cout << "Popping out the elements in mylist:";
  if (!mylist.empty())
  // while (!mylist.empty())
  {
    std::cout << ' ' << *mylist.front();
    // mylist.pop_front();
	delete mylist.front();
	// mylist.pop_front();
  }

  std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';
  int i = 0;
  // while (!mylist.empty())
  // while (!mylist.empty())
  // std::cout << *mylist.end() << std::endl;
  for (auto e = mylist.begin(); e != mylist.end(); e++)
  {
    std::cout << ' ' << *mylist.front();
	i++;
	if (i == 10)
		break;
    // mylist.pop_front();
	// delete mylist.front();
	// mylist.pop_front();
  }
  // while (1)
  	// ;
  return 0;
}
