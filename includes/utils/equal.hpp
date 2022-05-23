/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:02:15 by tbillon           #+#    #+#             */
/*   Updated: 2022/03/31 15:47:55 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

#include <algorithm>

namespace ft
{
    template <class InputIterator1, class InputIterator2>
        bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
        {
            while (first1 != last1)
            {
                if (!(*first1 == *first2))
                    return false;
                ++first1; ++first2;
            }
            return true;
        }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
        bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
        {
            while (first1 != last1)
            {
                if (!pred(*first1,*first2))
                    return false;
                ++first1; ++first2;
            }
            return true;
        }
} // namespace ft


#endif