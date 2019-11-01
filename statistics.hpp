#pragma once

#include "btree.hpp"
#include <iostream>

using namespace std;

namespace atk
{
	template < typename S, size_t L > struct StatisticalGraph : public array<S,L-1>
	{
		
	};

	template < typename S, size_t L > struct StatisticalLookup : public _OrderedArray<pair<S, S>, L>
	{
		using _OrderedArray<pair<S, S>, L>::elements;

		void Validate()
		{
			array<bool, L> v = { false };

			for (auto i = 0; i < _OrderedArray<pair<S, S>, L>::count; i++)
			{
				if (v[elements[i].first])
					throw "BAD";

				v[elements[i].first] = true;
			}
		}

		template <typename U > size_t GenerateStatisticalGraph(StatisticalGraph<S,L> & g, const array<U, L> & in)
		{
			size_t total = 0;
			for (size_t i = 0; i < in.size() - 1; i++)
				total += g[i] = _graph(elements[i], elements[i + 1], in);

			return total;
		}

		template <typename U > void Print(const array<U, L> & in)
		{
			for (const auto & i : elements)
				_print(string_view((const char *)in.data() + i.first, i.second));
		}

		template <typename U > void PrintGraph(const array<U, L> & in, size_t l = 1)
		{
			cout << "Graph [" << L << "]" << endl;

			int total = 0;
			for (size_t i = 0; i < in.size() - 1; i++)
			{
				auto c = _graph(elements[i], elements[i + 1], in);

				if (c >= l)
				{
					total += c;

					cout << (int)c << endl;
				}
			}

			cout << "[" << total << "]" << endl;
		}

		template <typename U > void PrintGraphContentsAscii(const array<U, L> & in, size_t l =1)
		{
			cout << "Graph [" << L << "]" << endl;

			int total = 0;
			for (size_t i = 0; i < in.size() - 1; i++)
			{
				auto c = _graph(elements[i], elements[i + 1], in);

				if (c >= l)
				{
					total += c;

					cout << "[" << (int)elements[i].first << ":" << (int)c << "] " << string_view((const char*)&in[elements[i].first], c) << endl;
				}
			}

			cout << "[" << total << "]" << endl;
		}

	private:
		void _print(const string_view v)
		{
			char buffer[3];
			buffer[2] = 0;

			for (auto & i : v)
			{
				sprintf(buffer, "%02X", i);
				cout << buffer << " ";
			}
			cout << endl;
		}

		template <typename U > S _graph(const pair<S, S> &f, const pair<S, S> & s, const array<U, L> & in)
		{
			S i = 0;
			for (; i < min(f.second, s.second); i++)
			{
				if (in[f.first + i] != in[s.first + i])
					break;
			}

			return i;
		}
	};

	template < typename S = uint8_t, typename U = uint8_t, size_t L = 0> void GenerateStatisticalLookup(const array<U, L> & in, StatisticalLookup<S, L> & lookup)
	{
		S c = 0;
		for (const auto & i : in)
		{
			lookup.Insert(make_pair(c, (S)L - c), [&](const pair<S, S> & l, const pair<S, S> & r)
			{
				return memcmp(&in[l.first], &in[r.first], min(l.second, r.second) * sizeof(U));
			});
			c++;
		}
	}
}
