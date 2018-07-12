#ifndef MUTANTSTACK_HPP

# define MUTANTSTACK_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

template <typename T>
class	MutantStack : public std::stack<T>
{
	private:
		typedef std::stack<T>	_st;
	public:
		MutantStack() {}
		~MutantStack() {}
		MutantStack( const MutantStack & cpy) : _st(cpy) {}
		using	_st::operator = ;
		typedef typename _st::container_type::iterator	iterator;
		iterator	begin()
		{
			return _st::c.begin();
		}
		iterator	end()
		{
			return _st::c.end();
		}
};

#endif
