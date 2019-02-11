#include "alloc.h"
#include <iostream>
#include <iterator>
#include "lib.h"
#include <map>
#include <memory>

int main(int, char *[]) {

	auto m1 = std::map<int, int>{};
	for (int i = 0; i < 10; ++i) {
		m1[i] = (int)fact(i);
	}

	auto m2 = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>> >{};
     for (int i = 0; i < 10; ++i) {
         m2[i] = (int)fact(i);
     }
	for (auto mm : m2) {
		 std::cout << mm.first << " " << mm.second << std::endl;
	 }
	 
	 auto v3 = std::make_unique < MyContainer<logging_allocator<MyStruct>>>();
	 for (int i = 0; i < 10; ++i) {
		 v3->Add(i);
	 }
	 for (ptr_iterator<MyStruct>* it = v3->begin(); !(it->end()); it->next() ) {
		 std::cout << (*it)->i << std::endl;
	 }
}
