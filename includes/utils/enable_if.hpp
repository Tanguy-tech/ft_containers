/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:07:14 by tbillon           #+#    #+#             */
/*   Updated: 2022/03/31 11:04:50 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

#include <type_traits>

namespace ft {
    
    template<bool B, class T = void> struct enable_if {};

	template<class T> struct enable_if<true, T> { typedef T type; };
}

#endif