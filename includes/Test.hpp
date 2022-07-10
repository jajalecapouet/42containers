#ifndef TEST_HPP
# define TEST_HPP

# include <memory>
# include <new>
# include <iterator>
# include <cstddef>
# include <cstring>

/* TASKS LIST
- throw exception in constructor if n > max_size
- do the useless const member fonctions
- do the reverse iterator
-
-
*/

class	InvalidIndexException : public std::exception
		{
			public :
				char const	*what( void ) const throw() { return ("This index is out of border."); }
		};

template < typename T, class Alloc = std::allocator<T> >

class Test
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

				MyIterator ( void ) : _p(0) {}
				MyIterator ( value_type *ptr ) : _p(ptr) {}
				MyIterator ( const MyIterator &other ) : _p(other._p) {}
				~MyIterator ( void ) {}

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

		Test( void ) : _firstPtr(0), _size(0), _capacity(0) {}

		Test(size_type n, value_type val) :	_firstPtr(_alloc.allocate(n, 0)), _size(n), _capacity(n)
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

		Test(size_type n) : _firstPtr(_alloc.allocate(n, 0)), _size(n), _capacity(n)
		{
			memset(_firstPtr, 0, n * sizeof(value_type));
		}

		template < class InputIterator >
		Test( InputIterator first, InputIterator last )
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

		Test( const Test &other ) : _firstPtr(_alloc.allocate(other._size, 0)), _size(other._size), _capacity(other._size)
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

		~Test( void )
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
				if (n > capacity)
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

		Test	&operator=( Test const &other )
		{
			size_type	idx;
			iterator	it;

			this->reserve(other._size);
			_ptr = _firstPtr;
			idx = 0;
			it = other.begin();
			while (idx < _size)
			{
				_alloc.destroy(_ptr);
				if (it != other.end())
				{
					_alloc.construct(_ptr, *it);
					it++;
				}
				_ptr++;
				idx++;
			}
			while (it != other.end())
				_alloc.construct(_ptr++, *(it++));
			_size = other._size;
			return (*this);
		}
		template < class InputIterator >
		void	assign( InputIterator first, InputIterator last )
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
		void	assign( size_type n, const value_type &val )
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
		void	push_back( const value_type &val )
		{
			checkCapacityAvailable(1);
			_alloc.construct(&_firstPtr[_size], val);
			_size += 1;
		}
		void	pop_back( void )
		{
			_size -= 1;
			_alloc.destroy(&_firstPtr[_size]);
		}
		void	insert( MyIterator position, const value_type &val )
		{
			_ptr = &(*position);
			checkCapacityAvailable(1);
			copyBlock( position, this->end(), position + 1 );
			_alloc.destroy(_ptr);
			_alloc.construct(_ptr, val);
		}
		template < class InputIterator >
		void	insert( MyIterator position, InputIterator first, InputIterator last )
		{

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

#endif