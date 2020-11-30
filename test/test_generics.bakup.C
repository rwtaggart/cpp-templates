/** 
 *  Simple test main function
 */

#include <iostream>

#include "generic_types.h"

int main()
{
  cgen::Shape s = cgen::Shape("A");
  printf("(I): Shape category: %s\n", s.category);

  cgen::Circle c = cgen::Circle(15);
  printf("(I): Shape category: %s, radius: %d\n", c.category, c.radius);
  printf("(D): Circle diameter: %d, area: %f\n", c.d(), c.area());

  cgen::Person p = cgen::Person("Glen");
  printf("(I): Person's name: %s\n", p.name);

  cgen::ArrayContainer<cgen::Shape> ac = cgen::ArrayContainer<cgen::Shape>(20);
  printf("(D): ArrayContainer.size(): %d\n", ac.size());

  cgen::StackContainer<cgen::Person> sc = cgen::StackContainer<cgen::Person>();
  sc.add(new cgen::Person("Al"));
  sc.add(new cgen::Person("Ben"));
  sc.add(new cgen::Person("Chris"));
  printf("(I): StackContainer.size(): %d\n", sc.size());

  auto p1 = sc.pop();
  printf("(I): Popped someone: %p, %s, %d\n", p1, p1->name, sc.size());

  int i=0;
  for( auto it = sc.begin(); it != sc.end(); ++it)
  {
    printf("(I): indx: %d, item: %p, name: %s\n", i, &(*it), (*it).name);
    ++i;
  }
  printf("(D): compare sizes: %d, %d\n", i, sc.size());
  auto p2 = sc.pop();
  printf("(I): Popped someone: %p, %s, %d\n", p2, p2->name, sc.size());
  sc.clear();
  printf("(I): Cleared StackContainer: %d\n", sc.size());
  
  return 0;
}

