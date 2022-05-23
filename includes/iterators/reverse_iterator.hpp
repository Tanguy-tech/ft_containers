/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:07:19 by tbillon           #+#    #+#             */
/*   Updated: 2022/05/23 15:05:00 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP


#include "iterator_traits.hpp"

namespace ft
{
    template< class Iterator >
    class reverse_iterator
    {
        
        public:
            typedef Iterator                                    iterator_type;
            typedef typename Iterator::iterator_category        iterator_category;
            typedef typename Iterator::value_type               value_type;
            typedef typename Iterator::difference_type          difference_type;
            typedef typename Iterator::pointer                  pointer;
            typedef typename Iterator::reference                reference;
        
        private:
            Iterator    _current;

        /****************************** CONSTRUCTORS *********************/
        public:
            reverse_iterator(): _current() {}                                                       //* default constructor that construct a reverse_iterator object.
            explicit reverse_iterator(iterator_type it): _current(it) {}                            //* construct some reverse_iterator object form some original iterator 'it'.
            explicit reverse_iterator(pointer ptr) : _current(iterator_type(ptr)) {}
            template< class Iter >
            reverse_iterator(const reverse_iterator<Iter>& rev_it): _current(rev_it.base()) {}      //* copy / type-cast constructor. Keeps the same sense of iteration as 'rev_it'.

        /****************************** DESTRUCTOR *********************/
            ~reverse_iterator() {}
        /****************************** BASE *****************************/
            iterator_type base() const {return this->_current;}                                     //* return a copy of the base iterator which iterates in the opposite direction.

        /****************************** OPERATORS ************************/
            reverse_iterator &operator=(const reverse_iterator & rhs)
            {
                this->_current = rhs.base();
                return (*this);
            }
            
            reference operator*() const {
                Iterator tmp = this->_current;
                return *--tmp;
            }

            pointer operator->() const {return &(this->operator*());}

            reverse_iterator operator++() {--this->_current; return *this;}
            reverse_iterator operator++(int) {
                reverse_iterator tmp = *this;
                this->_current--;
                return tmp;
            }

            reverse_iterator &operator--() {++this->_current; return *this;}
            reverse_iterator operator--(int) {
                reverse_iterator tmp = *this;
                this->_current++;
                return tmp;
            }

            reverse_iterator operator+(difference_type n) const {return reverse_iterator(_current - n);}
            reverse_iterator operator-(difference_type n) const {return reverse_iterator(_current + n);}
            difference_type		operator-(reverse_iterator const & b)
            {
                return(b._current.base() - this->_current.base());
            }

            reverse_iterator &operator+=(difference_type n) {_current -= n; return *this;}
            reverse_iterator &operator-=(difference_type n) {_current += n; return *this;}
            
            reference operator[](size_t n) const {return(*(this->_current - n - 1));}

            friend bool	operator<(reverse_iterator const &a, reverse_iterator const &ref) {return ((a._current) > (ref._current));}
            friend bool	operator<=(reverse_iterator const &a, reverse_iterator const &ref) {return ((a._current) >= (ref._current));}
            friend bool	operator>(reverse_iterator const &a, reverse_iterator const &ref) {return ((a._current) < (ref._current));}
            friend bool	operator>=(reverse_iterator const &a, reverse_iterator const &ref) {return ((a._current) <= (ref._current));}
            friend bool	operator==(reverse_iterator const &a, reverse_iterator const &ref) {return ((a._current) == (ref._current));}
            friend bool	operator!=(reverse_iterator const &a, reverse_iterator const &ref) {return ((a._current) != (ref._current));}
    };

    /****************************** NON-MEMBER FUNCTION OVERLOADS ****************/
    /****************************** RELATIONNAL OPERATORS ************************/
	template < class Iterator >
	bool	operator<(reverse_iterator<Iterator> const &a, reverse_iterator<Iterator> const &ref) {return ((a._current) > (ref._current));}

	template < class Iterator1, class Iterator2 >
	bool	operator<(reverse_iterator<Iterator1> const &a, reverse_iterator<Iterator2> const &ref) {return ((a.base()) > (ref.base()));}

	template < class Iterator >
	bool	operator<=(reverse_iterator<Iterator> const &a, reverse_iterator<Iterator> const &ref) {return ((a._current) >= (ref._current));}

	template < class Iterator1, class Iterator2 >
	bool	operator<=(reverse_iterator<Iterator1> const &a, reverse_iterator<Iterator2> const &ref) {return ((a.base()) >= (ref.base()));}

	template < class Iterator >
	bool	operator>(reverse_iterator<Iterator> const &a, reverse_iterator<Iterator> const &ref) {return ((a._current) < (ref._current));}

	template < class Iterator1, class Iterator2 >
	bool	operator>(reverse_iterator<Iterator1> const &a, reverse_iterator<Iterator2> const &ref) {return ((a.base()) < (ref.base()));}

	template < class Iterator >
	bool	operator>=(reverse_iterator<Iterator> const &a, reverse_iterator<Iterator> const &ref) {return ((a._current) <= (ref._current));}

	template < class Iterator1, class Iterator2 >
	bool	operator>=(reverse_iterator<Iterator1> const &a, reverse_iterator<Iterator2> const &ref) {return ((a.base()) <= (ref.base()));}

	template < class Iterator >
	bool	operator==(reverse_iterator<Iterator> const &a, reverse_iterator<Iterator> const &ref) {return ((a._current) == (ref._current));}
	
	template < class Iterator1, class Iterator2 >
	bool	operator==(reverse_iterator<Iterator1> const &a, reverse_iterator<Iterator2> const &ref) {return ((a.base()) == (ref.base()));}

	template < class Iterator >
	bool	operator!=(reverse_iterator<Iterator> const &a, reverse_iterator<Iterator> const &ref) {return ((a._current) != (ref._current));}

	template < class Iterator1, class Iterator2 >
	bool	operator!=(reverse_iterator<Iterator1> const &a, reverse_iterator<Iterator2> const &ref) {return ((a.base()) != (ref.base()));}

    template < class Iterator >
	reverse_iterator<Iterator>	operator+(int n, reverse_iterator<Iterator> it)
	{
		return(it + n);
	}
} // namespace ft

#endif