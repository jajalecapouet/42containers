/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:16:37 by njaros            #+#    #+#             */
/*   Updated: 2022/07/21 17:40:27 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP


template < class T1, class T2 >

class Pair
{

	public :

		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		Pair( void ) : first(T1()), second(T2()) {}
		template<class U, class V> 
		Pair( const Pair< U, V >& other ) : first(other.first), second(other.second) {}
		Pair( const first_type &a, const second_type &b ) : first(a), second(b) {}

		Pair	&operator=( const Pair &other )
		{
			first = other.first;
			second = other.second;
		}

	private :
	
};

template <class T1, class T2>
bool operator== (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T1, class T2>
bool operator!= (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
{ return !(lhs==rhs); }

template <class T1, class T2>
bool operator<  (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T1, class T2>
bool operator<= (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
{ return !(rhs<lhs); }

template <class T1, class T2>
bool operator>  (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
{ return rhs<lhs; }

template <class T1, class T2>
bool operator>= (const Pair<T1,T2>& lhs, const Pair<T1,T2>& rhs)
{ return !(lhs<rhs); }

template < class T1, class T2 >
Pair< T1, T2 >	Make_pair(T1 x, T2 y)	{return (Pair<T1, T2>(x, y));}

#endif
