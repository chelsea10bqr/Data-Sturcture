#include "List.h"
#include <iostream>
int main() {
  List<int> newlist;  List<int> s;
  newlist.insertBack(6);
  newlist.insertBack(4);
  newlist.insertBack(7);
  newlist.insertBack(2);
  newlist.insertBack(9);
  newlist.insertBack(1);
  newlist.insertBack(3);
  newlist.insertBack(5);
  newlist.insertBack(8);
    newlist.print(std::cout);
    cout<<endl;
  newlist.sort();
  newlist.print(std::cout);
  cout<<endl;

  return 0;
}
