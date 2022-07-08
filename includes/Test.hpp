#ifndef TEST_HPP
# define TEST_HPP

# include <memory>
# include <new>
# include <iterator>
# include <cstddef>


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

				value_type	operator*( void )
				{
					return (*_p);
				}

				MyIterator	&operator++( void )
				{
					this->_p += 1;
					return (*this);
				}

				MyIterator	operator++( int )
				{
					MyIterator	tmp(*this);
					operator++;
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
					operator--();
					return (tmp);
				}

				void	operator+( int val )
				{
					this->_p += val;
				}

				void	operator-( int val )
				{
					operator+( -val );
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

		Test(unsigned int n) :	_ptr(_alloc.allocate(n, 0)), _useless_ptr(_ptr),\
								_ref(*_ptr), _useless_ref(_ref),\
								_size(n)
		{}

		~Test( void )
		{
			_alloc.deallocate(_ptr, _size);
		}

		T	&operator[]( unsigned int idx ) const
		{
			if (idx >= this->_size)
			{
				throw InvalidIndexException();
			}
			return (this->_ptr[idx]);
		}

		difference_type	getDif( void ) const
		{
			return (this->_dif);
		}

		MyIterator	begin( void )
		{
			MyIterator	begin(_ptr);

			return (begin);
		}

		MyIterator	end( void )
		{
			MyIterator	end(&_ptr[_size]);

			return (end);
		}

	private :

		value_type		_x;
		allocator_type	_alloc;
		pointer			_ptr;
		const_pointer	_useless_ptr;
		reference		_ref;
		const_reference	_useless_ref;
		MyIterator		_it;
		difference_type	_dif;
		size_type		_size_t;
		unsigned int	_size;

};

#endif