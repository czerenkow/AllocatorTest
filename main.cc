#include <random>
#include <memory>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>

#include "ext/memory/include/foonathan/memory/container.hpp" // for list, list_node_size
#include "ext/memory/include/foonathan/memory/memory_pool.hpp" // for memory_pool


constexpr std::size_t cap = 1024 * 1024 * 10;


template<typename T, typename A>
int main_test(std::list<T, A>& list)
{
	int acc = 0;
	for (std::size_t n = 0; n < 20; n++)
	{
		for (std::size_t i = 0; i < cap; i++)
		    list.push_back(i*2);
		for (std::size_t i = 0; i < cap; i++)
		{
			acc += list.back();
			list.pop_back();
		}
    }
    return acc;
}


void test_1()
{
    foonathan::memory::memory_pool<> pool(foonathan::memory::list_node_size<int>::value, cap);
    foonathan::memory::list<int, decltype(pool)> list(pool); 
	std::cout << main_test(list) << '\n';
}

void test_2()
{
	std::list<int> list;
	std::cout << main_test(list) << '\n';
}




int main()
{
//   test_1();
   test_2();
   /*
    list.push_back(82);
    list.push_back(12);
    list.push_back(3);
*/
/*
    for (const auto a: list)
    {
        std::cout << a << '\n';
    }
*/
    return 0;
}
