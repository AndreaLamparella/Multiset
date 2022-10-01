#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <limits> // epsilon()
#include <algorithm>

#include "multiset.h"
// #include "element_not_found.h"
//
// Dati custom
//

struct item {
  std::string id;
  int price;

  item() : id(), price() { }
  item(const std::string k, const int q) : id(k), price(q) { }
  friend std::ostream &operator<<(std::ostream &os, const item &rhs);
};

// item functions

inline bool operator<(const item &lhs, const item &rhs) {
  if (lhs.id < rhs.id) return true;
  if (lhs.id == rhs.id) {
    if (lhs.price < rhs.price)
      return true;
    else
      return false;
  }
  return false;
}

inline bool operator>(const item &lhs, const item &rhs) {
  return rhs < lhs;
}

inline bool operator==(const item &lhs, const item &rhs) {
  return lhs.id == rhs.id && lhs.price == rhs.price;
}

inline bool operator!=(const item &lhs, const item &rhs) {
  return !(lhs == rhs);
}


std::ostream &operator<<(std::ostream &os, const item &rhs) {
  os << rhs.id << "_" << rhs.price;
  return os;
}

// item functions - end

struct str_pair {
  std::string left, right;

  str_pair() : left(), right() { }
  str_pair(const std::string &a, const std::string &b) : left(a), right(b) { }
  friend std::ostream &operator<<(std::ostream &os,  const str_pair &rhs);
};

// str_pair functions

inline bool operator<(const str_pair &lhs, const str_pair &rhs) { 
  bool left =  std::lexicographical_compare(lhs.left.begin(), lhs.left.end(),
                                            rhs.left.begin(), rhs.left.end());
  bool right =  std::lexicographical_compare(lhs.right.begin(), lhs.right.end(),
                                            rhs.right.begin(), rhs.right.end());      
  if (!left){
    if (right) {
      return true;
    }
    else 
      return false;
  }
  return true;

}

inline bool operator>(const str_pair &lhs, const str_pair &rhs) { 
  return rhs < lhs; 
}

inline bool operator==(const str_pair &lhs, const str_pair &rhs) { 
  return lhs.left == rhs.left && lhs.right == rhs.right;
}

inline bool operator!=(const str_pair &lhs, const str_pair &rhs) { 
  return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os,  const str_pair &rhs) {
  os << "(" << rhs.left << " - " << rhs.right << ")";
  return os;
}

// str_pair functions - end

struct point2D {
  int x, y;

  point2D() : x(0), y(0) { }
  point2D(int c1, int c2) : x(c1), y(c2) { }
  friend std::ostream &operator<<(std::ostream &os,  const str_pair &rhs);  
};

// point2D functions

inline bool operator<(const point2D &lhs, const point2D &rhs) {
  if (lhs.x < rhs.x) return true;
  if (lhs.x == rhs.x) {
    if (lhs.y < rhs.y)
      return true;
    else
      return false;
  }
  return false;
}

inline bool operator>(const point2D &lhs, const point2D &rhs) {
  return rhs < lhs;
}

inline bool operator==(const point2D &lhs, const point2D &rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const point2D &lhs, const point2D &rhs) {
  return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os,  const point2D &rhs) {
  os << "(" << rhs.x << ", " << rhs.y << ")";
  return os;
}

// point2D functions - end

//
// Funtori
//

struct eql {
  bool operator()(const int x, const int y) const { return x == y; }
  bool operator()(const double x, const double y) const {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
  }
  bool operator()(const char x, const char y) const { return x == y; }

  bool operator()(const str_pair x, const str_pair y) const { return x == y; }
  bool operator()(const point2D x, const point2D y) const { return x == y; }
  bool operator()(const item x, const item y) const { return x == y; }

};


struct greater_than {
  bool operator()(const int x, const int y) const { return x > y; }
  bool operator()(const double x, const double y) const { return x > y; }
  bool operator()(const char x, const char y) const { return x > y; }

  bool operator()(const str_pair x, const str_pair y) const { return x > y; } 
  bool operator()(const point2D x, const point2D y) const { return x > y; }
  bool operator()(const item x, const item y) const { return x > y; }

};

struct less_than {
  bool operator()(const int x, const int y) const { return x < y; }
  bool operator()(const double x, const double y) const { return x < y; }
  bool operator()(const char x, const char y) const { return x < y; }

  bool operator()(const str_pair x, const str_pair y) const { return x < y; }
  bool operator()(const point2D x, const point2D y) const { return x < y; }
  bool operator()(const item x, const item y) const { return x < y; }

};

void item_test() {

  std::cout << "item_test()\n";

  multiset<item, less_than, eql> inventory;
  assert(inventory.size() == 0);

  std::cout << "Declaring the multiset inventory and attempting to erase an element from it\n";

  item foo("foo", 1);

  try {
    inventory.erase(foo);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << foo << "\n";       
  }

  std::vector<item> v {
                      item("cpu01", 4),
                      item("cpu02", 3),
                      item("cpu02", 1),
                      item("cpu02", 3),
                      item("gpu01", 5),
                      item("laptop", 10),
                      item("cpu02", 3),
                      item("gpu01", 5),
                      item("gpu02", 4) 
                     };
  
  std::cout << "Input data: ";

  // 
  // TEST: INSERT
  // 

  std::cout << "[ ";
  for (auto i : v) {
    inventory.insert(i);
    std::cout << i << " ";
  }
  std::cout << "]\n"
            << "The resulting multiset:\n" << inventory << "\n";
  auto ms_copy(inventory);

  std::cout << "Copy of the multiset before modifying the original\n"
            << ms_copy << "\n";

  // ordino v e lo uso per istanziare un set, il quale sarà quindi popolato con
  // dati ordinati
  std::sort(v.begin(), v.end());
  std::set<item> s(v.begin(), v.end());

  // patendo dal primo elemento del set controllo che:
  // 1. l'elemento sia presente
  // 2. le occorrenze dell'elemento siano quelle corrette (usando il vettore)
  
  for (auto i: s) {
    assert(inventory.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(inventory.occurs(i) == frequency);
  }

  auto max = *std::max_element(inventory.begin(), inventory.end()),
       min = *std::min_element(inventory.begin(), inventory.end());

  

  // 
  // TEST: ERASE
  // 

  item cpu02_3("cpu02", 3),
       cpu02_1("cpu02", 1);

  inventory.erase(max);
  inventory.erase(cpu02_3);
  inventory.erase(min);
  inventory.erase(cpu02_1);

  assert(inventory.size() == 5);
  assert(inventory.occurs(max) == 0);
  assert(inventory.occurs(min) == 0);
  assert(inventory.occurs(cpu02_3) == 2);

  try {
    inventory.erase(min);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << min << "\n";              
  }

  std::cout << "The multiset after erasing the elements: "
            << max << ", " << cpu02_3 << ", "
            << min << ", " << cpu02_1 <<"\n";

  std::cout << inventory << "\n";

  
  // propago le modifiche al vettore
  v.erase(v.begin() + 1);
  v.erase(v.begin() + 1);
  v.erase(--v.end());
  v.erase(v.begin());

  //
  // TEST: CTOR WITH ITERATORS
  //
  multiset<item, less_than, eql> ms_i(v.begin(), v.end());
  std::set<item> s1(v.begin(), v.end());
  assert(ms_i.size() == inventory.size());
  for (auto i: s1) {
    assert(ms_i.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms_i.occurs(i) == frequency);
  }

  //
  // TEST: operator==
  //
  assert(inventory == ms_i);

  // la copia di inventory risulta diversa dopo aver modificato inventory
  assert(!(inventory == ms_copy));


  std::cout << "The inventory copy did not changed after modifying the original object\n"
            << "ms_copy\t: " << ms_copy << "\n"
            << "inventory: " << inventory << "\n";
  

  //
  // TEST: BIDIRECTIONAL ITERATOR
  //

  std::cout << "Printing the multiset using the iterator\n";

  std::cout << "operator++()\n";
  auto i = inventory.begin(),
       e = inventory.end();
  while ( i != e ) {
    std::cout << *i << " ";
    ++i;
  }

  std::cout << "\noperator++(int)\n";
  i = inventory.begin();
  e = inventory.end();
  while ( i != e ) {
    std::cout << *i << " ";
    i++;
  }

/*
  std::cout << "\noperator--(int)\n";
  i = inventory.end();
  e = inventory.begin();
  while (i-- != e) {
    std::cout << *i << " ";
  }
  std::cout << "\n";
  std::cout << "\noperator--()\n";
  i = inventory.end();
  e = inventory.begin();
  while (i != e) {
    --i;
    std::cout << *i << " ";
  }

*/
  
  //
  // TEST: CONSTNESS
  //
  
  std::cout << "\n";

  const auto ms_const(inventory);

  // Su un oggetto const non posso richiamare funzioni non const

  // ms_const.insert(item("42", 42));
  // ms_const.remove(cpu02_1);

  // ma le restanti funzioni sono richiamabili
  
  assert(ms_const.contains(cpu02_3));
  assert(ms_const.occurs(item("cpu02", 3)) == 2);
  assert(ms_const.size() == 5);
  assert(ms_const == inventory);


  std::cout << ms_copy << "\n";

  std::cout << "END item_test()\n";
}

void point2D_test() {

  std::cout << "point2D_test()\n";

  //
  // TEST: DEFAULT CTOR
  //

  multiset<point2D, less_than, eql> ms;
  assert(ms.size() == 0);

  std::cout << "Declaring the multiset ms and attempting to erase an element from it\n";

  point2D dummy(4, 2);

  try {
    ms.erase(dummy);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": 42\n";       
  }

  std::vector<point2D> v {
                      point2D(0, 1),
                      point2D(1, 0),
                      point2D(4, 2),
                      point2D(5, 5),
                      point2D(4, 2),
                      point2D(4, 2),
                      point2D(1, 0),
                      point2D(5, 7)
                    };
  
  std::cout << "Input data: ";

  // 
  // TEST: INSERT
  // 

  std::cout << "[ ";
  for (auto i : v) {
    ms.insert(i);
    std::cout << i << " ";
  }
  std::cout << "]\n"
            << "The resulting multiset:\n" << ms << "\n";
  auto ms_copy(ms);

  std::cout << "Copy of the multiset before modifying the original\n"
            << ms_copy << "\n";

  // ordino v e lo uso per istanziare un set, il quale sarà quindi popolato con
  // dati ordinati
  std::sort(v.begin(), v.end());
  std::set<point2D> s(v.begin(), v.end());

  // patendo dal primo elemento del set controllo che:
  // 1. l'elemento sia presente
  // 2. le occorrenze dell'elemento siano quelle corrette (usando il vettore)
  
  for (auto i: s) {
    assert(ms.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms.occurs(i) == frequency);
  }

  auto max = *std::max_element(ms.begin(), ms.end()),
       min = *std::min_element(ms.begin(), ms.end());

  // 
  // TEST: ERASE
  // 

  ms.erase(max);
  ms.erase(dummy);
  ms.erase(min);
  ms.erase(dummy);
  assert(ms.size() == 4);
  assert(ms.occurs(max) == 0);
  assert(ms.occurs(min) == 0);
  assert(ms.occurs(dummy) == 1);

  try {
    ms.erase(min);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << min << "\n";              
  }

  std::cout << "The multiset after erasing the elements: "
            << max << ", " << dummy << ", " 
            << min << ", " << dummy << "\n";

  std::cout << ms << "\n";
  
  // propago le modifiche al vettore
  v.erase(v.begin() + 4);
  v.erase(v.begin() + 4);
  v.erase(--v.end());
  v.erase(v.begin());

  //
  // TEST: CTOR WITH ITERATORS
  //
  multiset<point2D, less_than, eql> ms_i(v.begin(), v.end());
  std::set<point2D> s1(v.begin(), v.end());
  assert(ms_i.size() == ms.size());
  for (auto i: s1) {
    assert(ms_i.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms_i.occurs(i) == frequency);
  }

  //
  // TEST: operator==
  //
  assert(ms == ms_i);

  // la copia di ms risulta diversa dopo aver modificato ms
  assert(!(ms == ms_copy));


  std::cout << "The copy of ms did not changed after modifying the original object\n"
            << "ms_copy\t: " << ms_copy << "\n"
            << "ms\t: " << ms << "\n";
  


  //
  // TEST: BIDIRECTIONAL ITERATOR
  //

  std::cout << "Printing the multiset using the iterator\n";

  std::cout << "operator++()\n";
  auto i = ms.begin(),
       e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    ++i;
  }

  std::cout << "\noperator++(int)\n";
  i = ms.begin();
  e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    i++;
  }

 

  std::cout << "\n";
  //
  // TEST: CONSTNESS
  //
  const auto ms_const(ms);

  // Su un oggetto const non posso richiamare funzioni non const

  // ms_const.insert(point2D(1, 1));
  // ms_const.remove(point2D(5, 5));

  // ma le restanti funzioni sono richiamabili

  assert(ms_const.contains(dummy));
  assert(ms_const.occurs(dummy) == 1);
  assert(ms_const.size() == 4);
  assert(ms_const == ms);


  std::cout << ms_copy << "\n";
  std::cout << "END point2D_test()\n";
}

void str_pair_test() {
  std::cout << "str_pair_test()\n";

  //
  // TEST: DEFAULT CTOR
  //

  multiset<str_pair, less_than, eql> ms;
  assert(ms.size() == 0);

  std::cout << "Declaring the multiset ms and attempting to erase an element from it\n";

  str_pair dummy("foo", "bar");


  try {
    ms.erase(dummy);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << dummy <<"\n";       
  }

  std::vector<str_pair> v {
                          str_pair("aa","a0"),
                          str_pair("aa","a1"),
                          str_pair("bc","xx"),
                          str_pair("aa","a0"),
                          str_pair("aa","a"),
                          str_pair("bc","xx"),
                          str_pair("bc","xy"),
                          };
  
  std::cout << "Input data: ";

  std::cout << "[ ";
  for (auto i : v) {
    ms.insert(i);
    std::cout << i << " ";
  }
  std::cout << "]\n"
            << "The resulting multiset:\n" << ms << "\n";
  auto ms_copy(ms);

  std::cout << "Copy of the multiset before modifying the original\n"
            << ms_copy << "\n";

  // ordino v e lo uso per istanziare un set, il quale sarà quindi popolato con
  // dati ordinati
  std::sort(v.begin(), v.end());
  std::set<str_pair> s(v.begin(), v.end());

  // patendo dal primo elemento del set controllo che:
  // 1. l'elemento sia presente
  // 2. le occorrenze dell'elemento siano quelle corrette (usando il vettore)
  
  for (auto i: s) {
    assert(ms.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms.occurs(i) == frequency);
  }

  // 
  // TEST: ERASE
  // 

  str_pair t0("bc","xx"),
           t1("bc", "xy"),
           t2("aa", "a");

  ms.erase(t0);
  ms.erase(t1); // --end
  ms.erase(t2); // begin
  ms.erase(t0); //

  assert(ms.size() == 3);
  assert(ms.occurs(str_pair("aa", "a1")) == 1);
  assert(ms.occurs(str_pair("aa", "a0")) == 2);

  try {
    ms.erase(t2);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << t2 << "\n";              
  }

  std::cout << "The multiset after erasing the elements: "
            << t0 << ", " << t1 << ", " 
            << t2 << ", " << t0 << "\n";

  std::cout << ms << "\n";

  // propago le modifiche al vettore
  v.erase(v.begin());
  v.erase(v.begin() + 4);
  v.erase(v.begin() + 4);
  v.erase(--v.end());

  //
  // TEST: CTOR WITH ITERATORS
  //
  multiset<str_pair, less_than, eql> ms_i(v.begin(), v.end());
  std::set<str_pair> s1(v.begin(), v.end());
  assert(ms_i.size() == ms.size());
  for (auto i: s1) {
    assert(ms_i.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms_i.occurs(i) == frequency);
  }

  //
  // TEST: operator==
  //
  assert(ms == ms_i);

  // la copia di ms risulta diversa dopo aver modificato ms
  assert(!(ms == ms_copy));


  std::cout << "The copy of ms did not changed after modifying the original object\n"
            << "ms_copy\t: " << ms_copy << "\n"
            << "ms\t: " << ms << "\n";
  

  //
  // TEST: BIDIRECTIONAL ITERATOR
  //

  std::cout << "Printing the multiset using the iterator\n";

  std::cout << "operator++()\n";
  auto i = ms.begin(),
       e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    ++i;
  }

  std::cout << "\noperator++(int)\n";
  i = ms.begin();
  e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    i++;
  }


  
  //
  // TEST: CONSTNESS
  //
  
  const auto ms_const(ms);

  // Su un oggetto const non posso richiamare funzioni non const

  // ms_const.insert(42);
  // ms_const.remove(8);

  // ma le restanti funzioni sono richiamabili

  assert(ms_const.size() == 3);
  assert(ms_const.occurs(str_pair("aa", "a1")) == 1);
  assert(ms_const.occurs(str_pair("aa", "a0")) == 2);
  assert(ms_const == ms);


  std::cout << ms_copy << "\n";

  std::cout << "END - str_pair_test()\n";
}

void char_test() {

  std::cout << "char_test()\n";

  //
  // TEST: DEFAULT CTOR
  //

  multiset<char, less_than, eql> ms;

  assert(ms.size() == 0);

  std::cout << "Declaring the multiset ms and attempting to erase an element from it\n";

  try {
    ms.erase('x');
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": 42\n";       
  }

  std::vector<char> v {'d', '8', '8', 'a', 'l', 'l', 'a', 'l', 'g', '0'};
  
  std::cout << "Input data: ";

  // 
  // TEST: INSERT
  // 

  std::cout << "[ ";
  for (auto i : v) {
    ms.insert(i);
    std::cout << i << " ";
  }
  std::cout << "]\n"
            << "The resulting multiset:\n" << ms << "\n";

  auto ms_copy(ms);

  std::cout << "Copy of the multiset before modifying the original\n"
            << ms_copy << "\n";

  // ordino v e lo uso per istanziare un set, il quale sarà quindi popolato con
  // dati ordinati
  std::sort(v.begin(), v.end());
  std::set<int> s(v.begin(), v.end());

  // patendo dal primo elemento del set controllo che:
  // 1. l'elemento sia presente
  // 2. le occorrenze dell'elemento siano quelle corrette (usando il vettore)
  
  for (auto i: s) {
    assert(ms.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms.occurs(i) == frequency);
  }


  // 
  // TEST: ERASE
  // 
  ms.erase('l');
  ms.erase('a');
  ms.erase('a');
  ms.erase('0');

  assert(ms.size() == 6);
  assert(ms.occurs('l') == 2);
  assert(ms.occurs('a') == 0);

  try {
    ms.erase('a');
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << 'a' << "\n";              
  }

  std::cout << "The multiset after erasing the elements: l, a, a, 0\n";

  std::cout << ms << "\n";

  // propago le modifiche al vettore
  v.erase(--v.end());
  v.erase(v.begin() + 3);
  v.erase(v.begin() + 3);
  v.erase(v.begin());

  //
  // TEST: CTOR WITH ITERATORS
  //
  multiset<char, less_than, eql> ms_i(v.begin(), v.end());
  std::set<char> s1(v.begin(), v.end());
  assert(ms_i.size() == ms.size());
  for (auto i: s1) {
    assert(ms_i.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms_i.occurs(i) == frequency);
  }

  //
  // TEST: operator==
  //
  assert(ms == ms_i);

  // la copia di ms risulta diversa dopo aver modificato ms
  assert(!(ms == ms_copy));


  std::cout << "The copy of ms did not changed after modifying the original object\n"
            << "ms_copy\t: " << ms_copy << "\n"
            << "ms\t: " << ms << "\n";

  //
  // TEST: BIDIRECTIONAL ITERATOR
  //

  std::cout << "Printing the multiset using the iterator\n";

  std::cout << "operator++()\n";
  auto i = ms.begin(),
       e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    ++i;
  }

  std::cout << "\noperator++(int)\n";
  i = ms.begin();
  e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    i++;
  }

  //
  // TEST: CONSTNESS
  //
  
  const auto ms_const(ms);

  // Su un oggetto const non posso richiamare funzioni non const

  // ms_const.insert('h');
  // ms_const.remove('l');

  // ma le restanti funzioni sono richiamabili

  assert(ms_const.contains('g'));
  assert(ms_const.occurs('g') == 1);
  assert(ms_const.size() == 6);
  assert(ms_const == ms);


  std::cout << ms_copy << "\n";

  std::cout << "END - char_test()\n";
  return;
}

void double_test() {

  std::cout << "double_test()\n";

  //
  // TEST: DEFAULT CTOR
  //

  multiset<double, less_than, eql> ms;

  assert(ms.size() == 0);

  std::cout << "Declaring the multiset ms and attempting to erase an element from it\n";

  try {
    ms.erase(42.42);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": 42.42\n";       
  }

  std::vector<double> v {5.72, 8.43, 8.43, 5.72, 10.2, 3.33, 3.33, 5.72, 10.2, 0.2};
  
  std::cout << "Input data: ";

  // 
  // TEST: INSERT
  // 

  std::cout << "[ ";
  for (auto i : v) {
    ms.insert(i);
    std::cout << i << " ";
  }
  std::cout << "]\n"
            << "The resulting multiset:\n" << ms << "\n";


  multiset<double, less_than, eql> ms_copy(ms);
  std::cout << "Copy of the multiset before modifying the original\n";
  std::cout << ms_copy << "\n";

  std::cout << "ms_copy - done\n";


  // ordino v e lo uso per istanziare un set, il quale sarà quindi popolato con
  // dati ordinati
  std::sort(v.begin(), v.end());
  std::set<double> s(v.begin(), v.end());
  
  // // patendo dal primo elemento del set controllo che:
  // // 1. l'elemento sia presente
  // // 2. le occorrenze dell'elemento siano quelle corrette (usando il vettore)
  
  for (auto i: s) {
    assert(ms.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms.occurs(i) == frequency);
  }



  auto max = *std::max_element(ms.begin(), ms.end()),
       min = *std::min_element(ms.begin(), ms.end());

  
  // 
  // TEST: ERASE
  // 

  // { <0.2, 1> <3.33, 2> <5.72, 3> <8.43, 2> <10.2, 2> }

  ms.erase(max);
  ms.erase(5.72);
  ms.erase(min);
  ms.erase(5.72);

  assert(ms.size() == 6);
  assert(ms.occurs(max) == 1);
  assert(ms.occurs(min) == 0);
  assert(ms.occurs(5.72) == 1);

  try {
    ms.erase(min);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << min << "\n";              
  }

  std::cout << "The multiset after erasing the elements: "
            << max << ", 5.72, " << min << ", 5.72\n";

  std::cout << ms << "\n";
  
  // propago le modifiche al vettore
  v.erase(v.begin() + 3);
  v.erase(v.begin() + 3);
  v.erase(--v.end());
  v.erase(v.begin());

  //
  // TEST: CTOR WITH ITERATORS
  //
  multiset<double, less_than, eql> ms_i(v.begin(), v.end());
  std::set<double> s1(v.begin(), v.end());
  assert(ms_i.size() == ms.size());
  for (auto i: s1) {
    assert(ms_i.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms_i.occurs(i) == frequency);
  }

  //
  // TEST: operator==
  //
  assert(ms == ms_i);

  // la copia di ms risulta diversa dopo aver modificato ms
  assert(!(ms == ms_copy));


  std::cout << "The copy of ms did not changed after modifying the original object\n"
            << "ms_copy\t: " << ms_copy << "\n"
            << "ms\t: " << ms << "\n";
  

  //
  // TEST: BIDIRECTIONAL ITERATOR
  //

  std::cout << "Printing the multiset using the iterator\n";

  std::cout << "operator++()\n";
  auto i = ms.begin(),
       e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    ++i;
  }

  std::cout << "\noperator++(int)\n";
  i = ms.begin();
  e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    i++;
  }


  
  //
  // TEST: CONSTNESS
  //
  
  const auto ms_const(ms);

  // Su un oggetto const non posso richiamare funzioni non const

  // ms_const.insert(42);
  // ms_const.remove(8);

  // ma le restanti funzioni sono richiamabili

  assert(ms_const.contains(10.2));
  assert(ms_const.occurs(10.2) == 1);
  assert(ms_const.size() == 6);
  assert(ms_const == ms);


  std::cout << ms_copy << "\n";
}

void int_test() {

  std::cout << "int_test()\n";

  //
  // TEST: DEFAULT CTOR
  //

  multiset<int, less_than, eql> ms;
  assert(ms.size() == 0);

  std::cout << "Declaring the multiset ms and attempting to erase an element from it\n";

  try {
    ms.erase(42);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": 42\n";       
  }

  std::vector<int> v {5, 8, 8, 5, 10, 3, 3, 5, 10, 0};
  
  std::cout << "Input data: ";

  // 
  // TEST: INSERT
  // 

  std::cout << "[ ";
  for (auto i : v) {
    ms.insert(i);
    std::cout << i << " ";
  }
  std::cout << "]\n"
            << "The resulting multiset:\n" << ms << "\n";
  auto ms_copy(ms);

  std::cout << "Copy of the multiset before modifying the original\n"
            << ms_copy << "\n";

  // ordino v e lo uso per istanziare un set, il quale sarà quindi popolato con
  // dati ordinati
  std::sort(v.begin(), v.end());
  std::set<int> s(v.begin(), v.end());

  // patendo dal primo elemento del set controllo che:
  // 1. l'elemento sia presente
  // 2. le occorrenze dell'elemento siano quelle corrette (usando il vettore)
  
  for (auto i: s) {
    assert(ms.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms.occurs(i) == frequency);
  }

  auto max = *std::max_element(ms.begin(), ms.end()),
       min = *std::min_element(ms.begin(), ms.end());

  

  // 
  // TEST: ERASE
  // 

  // { <0, 1> <3, 2> <5, 3> <8, 2> <10, 2> }

  ms.erase(max);
  ms.erase(5);
  ms.erase(min);
  ms.erase(5);

  assert(ms.size() == 6);
  assert(ms.occurs(max) == 1);
  assert(ms.occurs(min) == 0);
  assert(ms.occurs(5) == 1);

  try {
    ms.erase(min);
  } catch (const element_not_found &e) {
    std::cout << "Successfuly caught exception\n";
    std::cout << e.what() << ": " << min << "\n";              
  }

  std::cout << "The multiset after erasing the elements: "
            << max << ", 5, " << min << ", 5\n";

  std::cout << ms << "\n";
  
  // propago le modifiche al vettore
  v.erase(v.begin() + 3);
  v.erase(v.begin() + 3);
  v.erase(--v.end());
  v.erase(v.begin());

  //
  // TEST: CTOR WITH ITERATORS
  //
  multiset<int, less_than, eql> ms_i(v.begin(), v.end());
  std::set<int> s1(v.begin(), v.end());
  assert(ms_i.size() == ms.size());
  for (auto i: s1) {
    assert(ms_i.contains(i));
    int frequency = std::count(v.begin(), v.end(), i);
    assert(ms_i.occurs(i) == frequency);
  }

  //
  // TEST: operator==
  //
  assert(ms == ms_i);

  // la copia di ms risulta diversa dopo aver modificato ms
  assert(!(ms == ms_copy));


  std::cout << "The copy of ms did not changed after modifying the original object\n"
            << "ms_copy\t: " << ms_copy << "\n"
            << "ms\t: " << ms << "\n";
  

  //
  // TEST: BIDIRECTIONAL ITERATOR
  //

  std::cout << "Printing the multiset using the iterator\n";

  std::cout << "operator++()\n";
  auto i = ms.begin(),
       e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    ++i;
  }

  std::cout << "\noperator++(int)\n";
  i = ms.begin();
  e = ms.end();
  while ( i != e ) {
    std::cout << *i << " ";
    i++;
  }


  
  //
  // TEST: CONSTNESS
  //
  
  const auto ms_const(ms);

  // Su un oggetto const non posso richiamare funzioni non const

  // ms_const.insert(42);
  // ms_const.remove(8);

  // ma le restanti funzioni sono richiamabili

  assert(ms_const.contains(10));
  assert(ms_const.occurs(10) == 1);
  assert(ms_const.size() == 6);
  assert(ms_const == ms);


  std::cout << ms_copy << "\n";
  std::cout << "END int_test()\n";
}


int main(int argc, char *argv[]) {
  int_test();
  double_test();
  char_test();
  str_pair_test();
  point2D_test();
  item_test();

  multiset<int, less_than, eql> ms;
  std::vector< std::vector<int> > id(5, std::vector<int>(5));

  for (auto i : id) {
    for (auto x : i) {
      std::cout << x << " ";
    }
    std::cout << "\n";
  }

  return 0;
}

