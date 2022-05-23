/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:21:42 by tbillon           #+#    #+#             */
/*   Updated: 2022/04/04 10:10:10 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <type_traits>

namespace ft
{
    template < typename T > struct is_intergal {};
    
    template < class T > struct is_integral {static const bool val = false;};
    
    template <> struct is_integral<bool> {static const bool val = true;};
    
    template <> struct is_integral<char> {static const bool val = true;};
    template <> struct is_integral<char16_t> {static const bool val = true;};
    template <> struct is_integral<char32_t> {static const bool val = true;};
    template <> struct is_integral<wchar_t> {static const bool val = true;};
    template <> struct is_integral<signed char> {static const bool val = true;};
    template <> struct is_integral<unsigned char> {static const bool val = true;};

    template <> struct is_integral<int> {static const bool val = true;};
    template <> struct is_integral<unsigned int> {static const bool val = true;};

    template <> struct is_integral<short> {static const bool val = true;};
    template <> struct is_integral<unsigned short> {static const bool val = true;};
    
    template <> struct is_integral<long> {static const bool val = true;};
    template <> struct is_integral<unsigned long> {static const bool val = true;};
    
    template <> struct is_integral<long long> {static const bool val = true;};
    template <> struct is_integral<unsigned long long> {static const bool val = true;};
} // namespace ft


#endif