/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:54:34 by njaros            #+#    #+#             */
/*   Updated: 2022/07/22 16:05:10 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef vector_HPP
# define vector_HPP

# include <memory>
# include <new>
# include <iterator>
# include <cstddef>
# include <cstring>
# include <iostream>

/* TASKS LIST
- throw exception in constructor if n > max_size.
- retype properly all the exceptions.
- do the useless const member fonctions.
- do the reverse iterator.
-
-
*/

class	InvalidIndexException : public std::exception
		{
			public :
				char const	*what( void ) const throw() { return ("This index is out of border."); }
		};

namespace ft
{

template < typename T, class Alloc = std::allocator<T> >

class vector
{

	public :

		typedef T													value_type;
		typedef Alloc												allocator_type;
		typedef T													*pointer;
		typedef const T												*const_pointer;
		typedef T													&reference;
		typedef const T												&const_reference;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;

		class MyIterator : public std::iterator< std::random_access_iterator_tag, value_type >
		{

			public :

				MyIterator( void ) : _p(0) {}
				MyIterator( value_type *ptr ) : _p(ptr) {}
				MyIterator( const MyIterator &other ) : _p(other._p) {}
				~MyIterator( void ) {}

				bool	operator==( const MyIterator &other )
				{
					if (_p != other._p)
						return (0);
					return (1);
				}

				bool	operator!=( const MyIterator &other )
				{
					if (_p != other._p)
						return (1);
					return (0);
				}

				MyIterator	&operator=( const MyIterator &other )
				{
					this->_p = other._p;
					return (*this);
				}

				value_type	&operator*( void )
				{
					return (*_p);
				}

				value_type	*operator->( void )
				{
					return (_p);
				}

				MyIterator	&operator++( void )
				{
					this->_p += 1;
					return (*this);
				}

				MyIterator	operator++( int )
				{
					MyIterator	tmp(*this);
					this->_p += 1;
					return (tmp);
				}

				MyIterator	&operator--( void )
				{
					this->_p -= 1;
					return (*this);
				}

				MyIterator	operator--( int )
				{
					MyIterator	tmp(*this);
					this->_p -= 1;
					return (tmp);
				}

				MyIterator	&operator+( int val )
				{
					MyIterator	newIt;

					newIt._p = this->_p + val;
					return (newIt);
				}

				MyIterator	&operator-( int val )
				{
					MyIterator	newIt;

					newIt._p = this->_p - val;
					return (newIt);
				}

				int	operator-( const MyIterator &other )
				{
					return (this->_p - other._p);
				}

				int	operator+( const MyIterator &other )
				{
					return (this->_p + other._p);
				}

				bool	operator<( const MyIterator &other )
				{
					if (this->_p < other._p)
						return (1);
					return (0);
				}

				bool	operator<=( const MyIterator &other )
				{
					if (this->_p <= other._p)
						return (1);
					return (0);
				}

				bool	operator>( const MyIterator &other )
				{
					if (this->_p > other._p)
						return (1);
					return (0);
				}

				bool	operator>=( const MyIterator &other )
				{
					if (this->_p >= other._p)
						return (1);
					return (0);
				}

				value_type	operator[]( int val )
				{
					value_type	*toReturn;

					toReturn = _p + val;
					return (*toReturn);
				}

			private :

				value_type		*_p;

		};

		typedef MyIterator	iterator;

		vector( void ) : _firstPtr(0), _size(0), _capacity(0) {}

		vector( size_type n, value_type val ) :	_firstPtr(_alloc.allocate(n, 0)), _size(n), _capacity(n)
		{
			size_type	idx;
			_ptr = _firstPtr;

			idx = 0;
			while (idx++ < _size)
			{
				_alloc.construct(_ptr, val);
				_ptr++;
			}
		}

		vector( size_type n ) : _firstPtr(_alloc.allocate(n, 0)), _size(n), _capacity(n)
		{
			memset(_firstPtr, 0, n * sizeof(value_type));
		}

		template < class InputIterator >
		vector( InputIterator first, InputIterator last )
		{
			if (first >= last)
				throw ("last must be higher than first.");
			_size = last - first;
			if (_size > _alloc.max_size())
				throw ("larger than max_size()");
			_capacity = _size;
			_firstPtr = _alloc.allocate(_size, 0);
			_ptr = _firstPtr;
			while (first != last)
			{
				_alloc.construct(_ptr, *first);
				first++;
				_ptr++;
			}
		}

		vector( const vector &other ) : _firstPtr(_alloc.allocate(other._size, 0)), _size(other._size), _capacity(other._size)
		{
			_it = other.begin();
			_ptr = _firstPtr;
			while (_it != other.end())
			{
				_alloc.construct(_ptr, *_it);
				_ptr++;
				_it++;
			}
		}

		~vector( void )
		{
			_alloc.deallocate(_firstPtr, _size);
		}


// ITERATORS

		MyIterator	begin( void )
		{
			MyIterator	begin(_firstPtr);

			return (begin);
		}

		MyIterator	end( void )
		{
			MyIterator	end(&_firstPtr[_size]);

			return (end);
		}

// CAPACITY

		size_type	size( void )		const	{return (_size);}
		size_type	max_size( void )	const	{return (_alloc.max_size());}
		size_type	capacity( void )	const	{return (_capacity);}
		bool		empty( void )		const	{return (_size == 0);}
		void		resize( size_type n )
		{
			if (n == _size)
				return ;
			if (n < _size)
			{
				while (_size > n)
				{
					_size--;
					_alloc.destroy(&_firstPtr[_size]);
				}
			}
			else
			{
				_size = n;
				if (_size > _capacity)
				{
					_alloc.allocate(_size - _capacity, &_firstPtr[_capacity - 1]);
					memset(&_ptr[_capacity], 0, (_size - _capacity) * sizeof(value_type));
					std::cout<< "pouet" << std::endl;
					_capacity = _size;
				}
			}
		}
		void		resize( size_type n, value_type &val )
		{
			if (n == _size)
				return ;
			if (n < _size)
			{
				while (_size > n)
				{
					_size--;
					_alloc.destroy(&_firstPtr[_size]);
					memset(&_firstPtr[_size], 0, sizeof(value_type));
				}
			}
			else
			{
				if (n > _capacity)
				{
					_alloc.allocate(n - _capacity, &_firstPtr[_capacity - 1]);
					_capacity = n;
				}
				_ptr = &_firstPtr[_size];
				while (_size < _capacity)
				{
					_alloc.construct(_ptr, val);
					_ptr++;
					_size++;
				}
			}
		}
		void		reserve( size_type n )
		{
			if (n > _capacity)
			{
				_alloc.allocate(n - _capacity, &_firstPtr[_capacity - 1]);
				memset(&_firstPtr[_capacity], 0, (n - _capacity) * sizeof(value_type));
				_capacity = n;
			}
		}
		void		shrink_to_fit( void )
		{
			if (_size < _capacity)
			{
				_alloc.deallocate(&_firstPtr[_size], _capacity - _size);
				_capacity = _size;
			}
		}

// ELEMENT ACCESS

		reference		operator[]( size_type idx )	{return (this->_firstPtr[idx]);}
		reference		at( size_type n )
		{
			if (n >= _size)
			{
				throw InvalidIndexException();
			}
			return (_firstPtr[n]);
		}
		reference		front( void )				{return (*_firstPtr);}
		reference		back( void )				{return (_firstPtr[_size - 1]);}
		pointer			data( void )				{return (_firstPtr);}
		const_pointer	data( void )	const 		{return (_firstPtr);}

// MODIFIERS

		vector		&operator=( vector const &other )
		{
			size_type	idx;

			this->reserve(other._size);
			_ptr = _firstPtr;
			idx = 0;
			_it = other.begin();
			while (idx < _size)
			{
				_alloc.destroy(_ptr);
				if (_it != other.end())
				{
					_alloc.construct(_ptr, *_it);
					_it++;
				}
				_ptr++;
				idx++;
			}
			while (_it != other.end())
				_alloc.construct(_ptr++, *(_it++));
			_size = other._size;
			return (*this);
		}
		template < class InputIterator >
		void		assign( InputIterator first, InputIterator last )
		{
			size_type	s;
			size_type	idx;

			if (first >= last)
				throw ("last must be higher than first.");
			s = last - first;
			if (s > _alloc.max_size())
				throw ("larger than max_size()");
			this->reserve(s);
			_ptr = _firstPtr;
			idx = 0;
			while (idx < _size)
			{
				_alloc.destroy(_ptr);
				if (first != last)
				{
					_alloc.construct(_ptr, *first);
					first++;
				}
				_ptr++;
				idx++;
			}
			while (first != last)
				_alloc.construct(_ptr++, *(first++));
			_size = s;
		}
		void		assign( size_type n, const value_type &val )
		{
			size_type	idx;

			this->reserve(n);
			_ptr = _firstPtr;
			idx = 0;
			while (idx < _size)
			{
				_alloc.destroy(_ptr);
				if (idx < n)
					_alloc.construct(_ptr, val);
				_ptr++;
				idx++;
			}
			_size = n;
			while (idx++ < _size)
				_alloc.construct(_ptr++, val);
		}
		void		push_back( const value_type &val )
		{
			checkCapacityAvailable(1);
			_alloc.construct(&_firstPtr[_size], val);
			_size += 1;
		}
		void		pop_back( void )
		{
			_size -= 1;
			_alloc.destroy(&_firstPtr[_size]);
		}
		void		insert( MyIterator position, const value_type &val )
		{
			_ptr = &(*position);
			checkCapacityAvailable(1);
			copyBlock(position, this->end(), position + 1);
			_alloc.destroy(_ptr);
			_alloc.construct(_ptr, val);
			_size += 1;
		}
		void		insert( MyIterator position, size_type n, const value_type &val )
		{
			_it = position + n;
			checkCapacityAvailable(n);
			copyBlock(position, this->end(), position + n);
			while (position != _it)
			{
				_alloc.destroy(&(*position));
				_alloc.construct(&(*position), val);
				position++;
			}
			_size += n;
		}
		template < class InputIterator >
		void		insert( MyIterator position, InputIterator first, InputIterator last )
		{
			size_type	addSize;

			if (first >= last)
				throw ("last must be higher than first.");
			addSize = last - first;
			_it = position + addSize;
			checkCapacityAvailable(addSize);
			copyBlock(position, this->end(), position + addSize);
			while (first != last)
			{
				_alloc.destroy(&(*position));
				_alloc.construct(&(*position), *first);
				first++;
				position++;
			}
			_size += addSize;
		}
		iterator	erase( iterator position )
		{
			if (position < this->begin() || position >= this->end())
				throw ("erase : the iterator you gave is out of border");
			_alloc.destroy(&(*position));
			copyBlock(position + 1, this->end(), position);
			_size -= 1;
			if (position != this->end())
				_alloc.destroy(&(*this->end()));
			return (position);
		}
		iterator	erase( iterator first, iterator last )
		{
			size_type	delSize;

			if (first >= last)
				throw ("erase : last must be higher than first.");
			if (first < this->begin())
				throw ("erase : the iterator 'first' you gave is out of border");
			if (last > this->end())
				throw ("erase : the iterator 'last' you gave is out of border");
			delSize = last - first;
			_it = first;
			while (_it != last)
			{
				_alloc.destroy(&(*_it));
				_it++;
			}
			copyBlock(last, this->end(), first);
			_it = this->end() - 1;
			_size -= delSize;
			if (first != this->end())
			{
				while (delSize--)
					_alloc.destroy(&(*_it--));
			}
			return (first);
		}
		void		swap( vector &other )
		{
			vector	tmp(this);

			this = other;
			other = tmp;
		}

// ALLOCATOR

		allocator_type	get_allocator( void )	const
		{
			allocator_type	copy(_alloc);

			return (copy);
		}

	private :

		value_type		_x;
		allocator_type	_alloc;
		pointer			_firstPtr;
		pointer			_ptr;
		MyIterator		_it;
		size_type		_size;
		size_type		_capacity;
		void			checkCapacityAvailable( size_type n )
		{
			while (_size + n > _capacity)
			{
				_alloc.allocate(_capacity, &_firstPtr[_capacity - 1]);
				_capacity *= 2;
			}
		}
		template < class InputIterator >
		MyIterator		copyBlock( InputIterator start, InputIterator end, MyIterator here )
		{
			if (here == start || start == end)
				return (here);
			if (here < start)
			{
				while (start != end)
				{
					*here = *start;
					here++;
					start++;
				}
			}
			else
			{
				here += end - start - 1;
				while (end-- != start)
				{
					*here = *end;
					here--;
				}
			}
			return (here);
		}

};

// NON MEMBERS OPERATIONS

template < class T, class Alloc >
bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	typename ft::vector<T>::iterator itL;
	typename ft::vector<T>::iterator itR;

	if (lhs.size() != rhs.size())
		return (0);
	itL = lhs.begin();
	itR = rhs.begin();
	while (itL != lhs.end())
	{
		if (*itL != *itR)
			return (0);
		itL++;
		itR++;
	}
	return (1);
}

template < class T, class Alloc >
bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)	{return (!(lhs == rhs));}

template < class T, class Alloc >
bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	typename ft::vector<T>::iterator itL;
	typename ft::vector<T>::iterator itR;

	itL = lhs.begin();
	itR = rhs.begin();
	while (itL != lhs.end() && itR != rhs.end())
	{
		if (*itL != *itR)
			return (*itL < *itR);
		itR++;
		itL++;
	}
	return (lhs.size() < rhs.size());
}

template < class T, class Alloc >
bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)	{return (!(lhs < rhs));}

template < class T, class Alloc >
bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
{
	typename ft::vector<T>::iterator itL;
	typename ft::vector<T>::iterator itR;

	itL = lhs.begin();
	itR = rhs.begin();
	while (itL != lhs.end() && itR != rhs.end())
	{
		if (*itL != *itR)
			return (*itL > *itR);
		itR++;
		itL++;
	}
	return (lhs.size() > rhs.size());
}

template < class T, class Alloc >
bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)	{return (!(lhs > rhs));}

template < class T, class Alloc >
void	swap(ft::vector<T, Alloc>& x, ft::vector<T, Alloc>& y)
{
	ft::vector<T>	tmp(x);

	x = y;
	y = tmp;
}

}

#endif