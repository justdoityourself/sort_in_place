#pragma once

//#include "Helper/Hash.hpp"

namespace atk
{

	template <typename T1, typename T2 = T1> struct KeyT
	{
		KeyT() {}

		template < typename T > KeyT(const T & t)
		{
			//HashT(*this, t);
		}

		int Compare(const KeyT & p)
		{
			if (first == p.first)
			{
				if (second == p.second)
					return 0;

				if (second > p.second)
					return 1;
				return -1;
			}
			else
			{
				if (first > p.first)
					return 1;
				return -1;
			}
		}

		bool operator==(const KeyT & p)
		{
			return Compare(p) == 0;
		}

		bool operator>(const KeyT & p)
		{
			return Compare(p) == 1;
		}

		T1 first;
		T2 second;
	};

	template < typename K, typename P > struct KeyPointerT : public K
	{
		KeyPointerT() {}

		template < typename T > KeyPointerT(const T & t) : K(t) {}

		using K::operator==;
		using K::operator>;
		P pointer = 0;
	};

	template < typename K, typename P > struct KeyPointerT2 : public K
	{
		KeyPointerT2() {}

		template < typename T > KeyPointerT2(const T & t) : K(t) {}

		using K::operator==;
		using K::operator>;
		P p1 = 0;
		P p2 = 0;
	};

	using Key16 = KeyT<uint64_t>;
	using Key24 = KeyT<Key16, uint64_t>;
	using Key32 = KeyT<Key16>;
	using KeyP = KeyPointerT<Key24, uint64_t>;
	using KeyP2 = KeyPointerT2<Key24, uint32_t>;
	using Key64 = KeyT<Key32>;
}