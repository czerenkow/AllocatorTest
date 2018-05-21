#include <random>
#include <memory>
#include <cassert>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_set>

#include "ext/memory/include/foonathan/memory/container.hpp" // for list, list_node_size
#include "ext/memory/include/foonathan/memory/memory_pool.hpp" // for memory_pool


struct test_item
{
	int id;
	char a, b;
	int c, d, e, f; 
};

namespace std 
{
	template<>
	struct hash<test_item>
	{
		std::size_t operator()(const test_item& e) const
		{
			return static_cast<std::size_t>(e.id);
		}
	};
	
	template<>
	struct equal_to<test_item>
	{
		bool operator()(const test_item& lhs, const test_item& rhs) const
		{
			return lhs.id == rhs.id && 
				lhs.a == rhs.a && 
				lhs.b == rhs.b && 
				lhs.c == rhs.c && 
				lhs.d == rhs.d && 
				lhs.e == rhs.e && 
				lhs.f == rhs.f;
		}

	};
};


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

template<typename T, typename A>
int main_test_unordered_set(std::unordered_set<T, std::hash<T>, std::equal_to<T>, A>& set)
{
	int acc = 0;
	for (std::size_t n = 0; n < 20; n++)
	{
		for (std::size_t i = 0; i < cap / 2; i++) 
		{
			set.emplace(T {i*n, 'a', 'b', 1, 2, 3, 4});
			acc++;
		}
	
		set.erase(set.begin(), set.end());
		/*			
		for (std::size_t i = 0; i < cap / 2; i++)
		{
			auto it = set.find({i, 'a', 'b', 1, 2, 3, 4});
			if (it != set.end())
			{
				set.erase(it);
				acc++;
			}
		}
		*/
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


void test_unordered_set_1()
{
    foonathan::memory::memory_pool<> pool(foonathan::memory::unordered_set_node_size<test_item>::value, cap);
    foonathan::memory::unordered_set<test_item, decltype(pool)> set(32, std::hash<test_item> {}, std::equal_to<test_item> {}, pool); 
	std::cout << main_test_unordered_set(set) << '\n';
}


void test_unordered_set_2()
{
	std::unordered_set<test_item, std::hash<test_item>, std::equal_to<test_item>> set(32); 
	std::cout << main_test_unordered_set(set) << '\n';
}

int main()
{
//   test_1();
   test_unordered_set_1();
//   test_unordered_set_2();
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
