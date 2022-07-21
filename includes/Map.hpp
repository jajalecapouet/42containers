/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:54:41 by njaros            #+#    #+#             */
/*   Updated: 2022/07/21 17:11:26 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include <memory>
# include <new>
# include <iterator>
# include <cstddef>
# include <cstring>
# include <utility>

template < class Key, class T, class Compare = std::less< Key >, class Alloc = std::allocator< std::pair< const Key, T > > >

class TestMap
{

	public :

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair< const key_type, mapped_type >	value_type;
		typedef Compare										key_compare;
		//typedef ???										value_compare; rien compris
		typedef Alloc										allocator_type;
		typedef allocator_type::reference					reference;
		typedef allocator_type::const_reference				const_reference;
		typedef allocator_type::pointer						pointer;
		typedef allocator_type::const_pointer				const_pointer;

		class MyIterator : public std::iterator< std::bidirectional_iterator_tag, value_type >
		{

			public :

				MyIterator( void ) : _p(0) {}
				MyIterator( value_type *ptr ) : _p(ptr)	{}
				MyIterator( const MyIterator &other ) : _p(other._p) {}
				~MyIterator( void )	{}

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
					
				}

				MyIterator	operator++( int )
				{
					
				}

				MyIterator	&operator--( void )
				{
					
				}

				MyIterator	operator--( int )
				{
				
				}

			private :

				value_type	*_p;

		}

		typedef MyIterator									iterator;

	private :

		TestMap		*_father;
		TestMap		*_leafLeft;
		TestMap		*_leafRight;

};