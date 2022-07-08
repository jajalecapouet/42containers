/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:28:42 by njaros            #+#    #+#             */
/*   Updated: 2022/07/01 18:28:30 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <new>

namespace ft = std;

template < typename T, class Alloc = std::allocator<T> >

class vector
{

	public :

		vector( const allocator_type &alloc = allocator_type() ) : value_type(T)
		{

		}

		vector( size_type n, const value_type &val = vlue_type(), const allocator_type &alloc = allocator_type() )
		{
			
		}

		template < class InputIterator >
		vector( InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type() )
		{

		}

		vector ( const vector &other )
		{

		}

		~vector ( void )
		{
			
		}

		vector &operator=( const vector &other )
		{

		}

//----------------------------------------------------------------//

		//BEGIN ITERATOR
		iterator	begin( void )
		{
			
		}

		const_iterator	begin( void )	const;
		{

		}

		iterator	end( void )
		{

		}

		const_iterator	end( void )	const
		{

		}

		reverse_iterator	rbegin( void )
		{

		}

		const_reverse_iterator	rbegin( void )	const
		{

		}

		reverse_iterator	rend( void )
		{

		}

		const_reverse_iterator	rend( void )	const
		{

		}

		const_iterator	cbegin( void )	const noexcept
		{

		}

		const_iterator	cend( void )	const noexcept
		{

		}

		const_reverse_iterator crbegin( void )	const noexcept
		{
			
		}

		const_reverse_iterator	crend( void )	const noexcept
		{

		}
		//END ITERATOR

		//BEGIN CAPACITY
		size_type	size( void )	const
		{
			
		}

		size_type	max_size( void )	const
		{

		}

		void	resize( size_type n )
		{

		}

		void	resize( size_type n, value_type val = value_type() )
		{

		}

		size_type	capacity( void )	const
		{

		}

		bool	empty( void )	const
		{

		}

		void	reserve( size_type n )
		{

		}

		void	shrink_to_fit( void )
		{
			
		}
		//END CAPACITY

		//BEGIN ELEMENT ACCESS
		reference	operator[]( size_type n )
		{

		}

		const_reference	operator[]( size_type n )	const
		{

		}

		reference	at( size_type n )
		{

		}

		const_reference	at( size_type n)	const
		{

		}

		reference	front( void )
		{

		}

		const_reference	front( void )	const
		{

		}

		reference	back( void )
		{

		}

		const_reference	back( void )	const
		{

		}

		value_type	*data( void )	noexcept
		{

		}

		const value_type	*data( void )	const noexcept
		{
			
		}
		//END ELEMENT ACCESS

		//BEGIN MODIFIERS
		template < class InputIterator >
		void	assign( InputIterator first, InputIterator last )
		{

		}

		void	assign( size_type n, const value_type &val )
		{

		}

		void	push_back( const value_type &val )
		{

		}

		void	pop_back( void )
		{

		}

		iterator	insert( iterator position, const value_type &val )
		{

		}

		void	insert( iterator position, size_type n, const value_type &val )
		{

		}

		template < class InputIterator >
		void	insert( iterator position, InputIterator first, InputIterator last )
		{

		}

		iterator	erase( iterator position )
		{

		}

		iterator	erase( iterator first, iterator last )
		{

		}

		void	swap( vector &other )
		{

		}

		void	clear( void )
		{

		}

		template < class... Args >
		iterator	emplace( const_iterator position, Args&&... Args)
		{

		}

		template < class... Args >
		void	emplace_back( Args&&... Args )
		{

		}
		//END MODIFIERS

		//BEGIN ALLOCATOR
		allocator_type	get_allocator()	const
		{

		}

		T											value_type;
		Alloc										allocator_type;
		allocator_type::reference					reference;
		allocator_type::const_reference				const_reference;
		allocator_type::pointer						pointer;
		allocator_type::const_pointeur				const_pointer;
		value_type::iterator						iterator;
		const value_type::iterator					const_iterator;
		reverse_iterator<iterator>					reverse_iterator;
		reverse_iterator<const_iterator>			const_reverse_iterator;
		iterator_traits<iterator>::difference_type	difference_type;
		iterator_traits<iterator>::difference_type	size_type;

	private :

		
		
};

template < class T, class Alloc = std::allocator<T> >
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{

	}
template < class T, class Alloc >
	bool	operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{

	}
template < class T, class Alloc >
	bool	operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{

	}
template < class T, class Alloc >
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{

	}
template < class T, class Alloc >
	bool	operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{

	}
template < class T, class Alloc >
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{

	}
template < class T, class Alloc >
	void	swap(vector(T,Alloc) &x, vector(T,Alloc) &y)
	{

	}

#endif