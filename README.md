# Priority-queues
C++ code for priority queues

# Templates:
 - max_binary_heap\<T>
 - min_binary_heap\<T>
 - binary_heap<T, Compare>
  
# Compile
with clang++ or g++
```
clang++ test_binary_heap.cpp -Wpedantic -o ./test -O2 -std=gnu++2a
```
# Test cpp outputs:
```
Test array: 1 3 5 7 2 -4 8 17 1 21 9 0 12 7 11
Size of heap: 0
Size of heap: 15
Min of heap: -4
Replaced! -4 and 22, min: 0
Not replaced!
Delete! 1
Extract elements: 0 1 2 3 5 7 7 8 9 11 12 17 21 22
Heap elements: 22 21 17 12 11 9 8 7 7 5 3 2 1 0
Size of heap: 0

People is trivially copyable: false
String is trivially copyable: false
refPeople is trivially copyable: true

People by height (max->min):
Arnold Stark 1.9
Shirley Mynatt 1.87
Philip Jernigan 1.75
Christina Summers 1.74
Melantha Wilkinson 1.73
Damian Nigel 1.73
Viola Spurling 1.68
Nichole Selby 1.66
Braiden Boone 1.63
Patty Howland 1.62
```
