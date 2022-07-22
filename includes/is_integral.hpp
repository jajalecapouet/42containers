/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaros <njaros@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:38:18 by njaros            #+#    #+#             */
/*   Updated: 2022/07/22 16:03:00 by njaros           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{

template < class T, T v >
struct integral_constant
{

	static const T					value = v;
	typedef T						value_type;
	typedef integral_constant<T, v>	type;
	const operator T()				{return (v);}

};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

template <>
struct is_integral<bool> : public true_type						{}
template <>
struct is_integral<char> : public true_type						{}
template <>
struct is_integral<char16_t> : public true_type					{}
template <>
struct is_integral<char32_t> : public true_type					{}
template <>
struct is_integral<wchar_t> : public true_type					{}
template <>
struct is_integral<signed char> : public true_type				{}
template <>
struct is_integral<short int> : public true_type				{}
template <>
struct is_integral<int> : public true_type						{}
template <>
struct is_integral<long int> : public true_type					{}
template <>
struct is_integral<long long int> : public true_type			{}
template <>
struct is_integral<unsigned char> : public true_type			{}
template <>
struct is_integral<unsigned short int> : public true_type		{}
template <>
struct is_integral<unsigned int> : public true_type				{}
template <>
struct is_integral<unsigned long int> : public true_type		{}
template <>
struct is_integral<unsigned long long int> : public true_type	{}
template < class T >
struct is_integral<T> : public false_type						{}

}
#endif