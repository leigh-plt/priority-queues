#include <utility>
#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <math.h>
#include <string>
#include <type_traits>

#include "binary_heap.hpp"
using string=std::string;

struct People {
  string Name;
  string Surname;
  double height;
};
// some tricks for using external class pointers
struct refPeople {
  People* ref;
};

inline bool operator> (const refPeople& a, const refPeople& b){
    return a.ref->height > b.ref->height;
}

inline bool operator< (const refPeople& a, const refPeople& b){
    return a.ref->height < b.ref->height;
}

inline bool operator== (const refPeople& a, const refPeople& b){
    return (a.ref->Name == b.ref->Name) && (a.ref->Surname == b.ref->Surname);
}

int main() { // int argc, char const *argv[]

  std::array<int, 15> v{1,3,5,7,2,-4,8,17,1,21,9,0,12,7,11};
  std::cout << "Test array: ";
  for (size_t i=0;i<v.size();++i)
    std::cout << v[i] << " ";
  std::cout << std::endl;
  min_binary_heap<int> k;
  std::cout << "Size of heap: " << k.size() << std::endl;
  for (auto el: v) k.push(el);
  std::cout << "Size of heap: " << k.size() << std::endl;
  std::cout << "Min of heap: " << k.front() << std::endl;
  if (k.replace(-4, 22))
    std::cout << "Replaced! -4 and 22, min: " << k.front() << std::endl;
  if (k.replace(27, 22))
    { std::cout << "Replaced! 27 and 22, min: " << k.front() << std::endl; }
  else std::cout << "Not replaced!"  << std::endl;
  if (k.remove(1))
    std::cout << "Delete! 1 " << std::endl;
  auto q = k.end();
  std::cout << "Extract elements: ";
  for (; !k.empty();)
    std::cout << k.get_pop_front() << " ";
  std::cout << std::endl;

  std::cout << "Heap elements: ";
  for (auto p = k.begin();p!=q;++p)
    std::cout << *p << " ";
  std::cout << std::endl;
  std::cout << "Size of heap: " << k.size() << std::endl;

  std::cout << std::endl;
  std::vector<People> pls = {
    {"Viola", "Spurling", 1.68},
    {"Damian", "Nigel", 1.73},
    {"Philip", "Jernigan", 1.75},
    {"Braiden", "Boone", 1.63},
    {"Nichole", "Selby", 1.66},
    {"Shirley", "Mynatt", 1.87},
    {"Arnold", "Stark", 1.90},
    {"Patty", "Howland", 1.62},
    {"Christina", "Summers", 1.74},
    {"Melantha", "Wilkinson", 1.73},
  };

  std::cout << std::boolalpha;
  std::cout << "People is trivially copyable: "<< std::is_trivially_copyable<People>::value << '\n';
  std::cout << "String is trivially copyable: "<< std::is_trivially_copyable<string>::value << '\n';
  std::cout << "refPeople is trivially copyable: "<< std::is_trivially_copyable<refPeople>::value << '\n';

  max_binary_heap<refPeople> heap_people;
  for (size_t i = 0;i<pls.size();i++) {
    // std::cout << "Added: " << pls[i].Surname << " " << pls[i].height << std::endl;
    heap_people.push({&pls[i]});
  };
  std::cout << std::endl << "People by height (max->min): " << std::endl;
  for (; !heap_people.empty();){
    auto p = heap_people.get_pop_front();
    std::cout << p.ref->Name << " " << p.ref->Surname << " " << p.ref->height << std::endl;
  };

  return 0;
}
