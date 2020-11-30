/**
 *  Unit Test for classes defined in generic_types.h
 */

#include <iostream>
#include <assert.h>

#include "../generic_types.h"

// TODO: Stuff this in a macros example file
#ifdef TEST_VERBOSE 
#define DEBUG_PRINT_FUNC printf("T- Passed %s\n", __FUNCTION__); 
#else
#define DEBUG_PRINT_FUNC (void)0; // No-op
#endif

#define SETUP() printf("T- Running %s", __FUNCTION__)
#define TEARDOWN(status) \
  if(!status) { \
    printf(" -- TEST FAILED\n"); return status; \
  } else { \
    printf(" -- passed.\n"); return status; \
  }


/** Test custom types */
static bool test_shape_1()
{
  SETUP();
  cgen::Shape s = cgen::Shape("A");
  assert(s.category == "A");
  TEARDOWN(true)
}

static bool test_circle()
{
  SETUP();
  cgen::Circle c = cgen::Circle(15);
  assert(c.category == "circle");
  assert(c.radius == 15);
  assert(c.d() == 30);
  assert(abs(c.area() - 706.5) <= 1e-9);
  TEARDOWN(true)
}

static bool test_person()
{
  SETUP();
  cgen::Person p = cgen::Person("Glen");
  assert(p.name == "Glen");
  TEARDOWN(true)
}

/** Test ArrayContainer */
static bool test_array_container()
{
  SETUP();
  cgen::ArrayContainer<cgen::Shape> ac = cgen::ArrayContainer<cgen::Shape>(20);
  assert(ac.size() == 0);
  assert(ac.capacity() == 20);
  assert(ac._items[0] == NULL);
  assert(ac._items[19] == NULL);

  /* test add() */
  assert(ac._items[0] == NULL);
  ac.add(new cgen::Shape("Artie"));
  assert(ac.size() == 1);
  assert(ac._items[0] != NULL);
  ac.add(new cgen::Shape("Betty"));
  ac.add(new cgen::Shape("Chaby"));
  assert(ac.size() == 3);
  assert(ac.capacity() == 20);

  /* test pop() */
  cgen::Shape* s = ac.pop();
  assert(s->category == "Chaby");
  assert(ac.size() == 2);
  assert(ac.capacity() == 20);
  assert(ac._items[3] == NULL);

  /* test add() capacity check */
  int c=0;
  while(ac.add((cgen::Shape*)0xDEADBEEF))
  { 
    assert(++c <= 18);
  }
  assert(ac.size() == ac.capacity());
  assert(ac.size() == 20);
  cgen::Shape* s_bad = ac.pop();
  assert(s_bad == (cgen::Shape*)0xDEADBEEF);
  TEARDOWN(true)
}

static bool test_array_clear()
{
  SETUP();
  cgen::ArrayContainer<cgen::Shape> ac = cgen::ArrayContainer<cgen::Shape>(20);
  ac.add(new cgen::Shape("Artie"));
  ac.add(new cgen::Shape("Betty"));
  ac.add(new cgen::Shape("Chaby"));
  ac.add(new cgen::Shape("LAST"));
  assert(ac.capacity() == 20);
  assert(ac.size() == 4);
  assert(ac._items[5] == NULL);
  assert(ac._items[19] == NULL);

  cgen::Shape* s = ac.pop();
  assert(s->category == "LAST");

  /* test clear() */
  ac.clear();
  assert(ac.size() == 0);
  cgen::Shape* s_bad2 = ac.pop();
  assert(s_bad2 == NULL);

  for( int i = 0; i < 20; i++)
  {
    cgen::Shape* tmp_s = ac._items[i];
    assert(tmp_s == NULL);
  }
  assert(s != NULL);
  assert(s->category == "LAST");
  TEARDOWN(true);
}

/** Test StackContainer */
static bool test_linked_list_stack()
{
  SETUP();
  cgen::StackContainer<cgen::Person> lsc = cgen::StackContainer<cgen::Person>();
  assert(lsc.size() == 0);
  assert(lsc.pop() == NULL);

  /* Test add() and pop() */
  auto p = new cgen::Person("Alice");
  lsc.add(p);
  assert(lsc.size() == 1);
  assert(p == lsc.pop());

  lsc.add(p);
  lsc.add(new cgen::Person("Bob"));
  lsc.add(new cgen::Person("Chuck"));
  assert(lsc.size() == 3);

  TEARDOWN(true);
}

static bool test_linked_list_clear()
{
  SETUP();
  /* Test clear() */
  auto lsc = cgen::StackContainer<cgen::Person>();
  for (int i = 0; i < 5; i++)
  {
    lsc.add((cgen::Person*)0xDEADBEEF);
  }
  lsc.clear();
  for (int i = 0; i < 5; i++)
  {
    auto p = lsc.pop();
    assert(p == (cgen::Person*)0xDEADBEEF);
  }
  TEARDOWN(true);
}

static bool test_linked_list_iterator()
{
  SETUP();
  auto lsc = cgen::StackContainer<cgen::Person>();
  assert(lsc.size() == 0);
  // assert(lsc.begin()._
  for( auto iter = lsc.begin(); iter != lsc.end(); ++iter )
  {
    assert(false); // SHOULD NOT GET HERE
  }
  const char* names[] = { "Alice", "Bob", "Chuck", "Dan" };
  int n_size = sizeof(names)/sizeof(char*);
  assert(n_size == 4);
  for( int i = 0; i < n_size; i++)
  {
    lsc.add(new cgen::Person(names[i]));
  }
  int count = 0;
  for( auto iter = lsc.begin(); iter != lsc.end(); ++iter )
  {
    ++count;
    /* Test operator*() */
    assert((*iter).name == names[n_size - count]);
    /* Test operator->() */
    // assert(iter->name == names[n_size - count]);
  }
  TEARDOWN(true);
}

static bool test_linked_list_stack_with_shape_and_circle()
{
  SETUP();

  TEARDOWN(false);
}


int main()
{
  printf("Running tests...\n");
  bool result = (
    test_shape_1()
   ,test_circle()
   ,test_person()
   ,test_array_container()
   ,test_array_clear()
   ,test_linked_list_stack()
   ,test_linked_list_iterator()
   ,test_linked_list_clear()
   // ,test_linked_list_stack_with_shape_and_circle()
  );
  if( !result )
  {
    printf("TESTS FAILED\n");
  }
  else
  {
    printf("TESTS PASSED\n");
  }
  return !result;
}

