/* Your code here! */
/* Your code here! */
#include "dsets.h"
void DisjointSets::addelements(int num) {
  for (int i = 0; i < num; i++) {
    elems.push_back(-1);
  }
}

int DisjointSets::find(int elem) {
  if (elems[elem]>= 0) {
    int result = find(elems[elem]);
    elems[elem] = result;
    return result;
  }

  return elem;
}
void DisjointSets::setunion(int a, int b) {
  int first = find(a);
  int second = find(b);
  if (first == second) return;
  int newNum = elems[first] + elems[second];
  if (elems[first] > elems[second]) {
    elems[first] = second;
    elems[second] = newNum;
  } else {
    elems[first] = newNum;
    elems[second] = first;
  }
}
int DisjointSets::size(int elem) {
  return -(elems[find(elem)]);
}
