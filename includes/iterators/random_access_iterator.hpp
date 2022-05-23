/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:53:37 by tbillon           #+#    #+#             */
/*   Updated: 2022/04/27 08:18:33 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

    template <class T2>
	class reverse_random_iterator;
    
    template< typename T >
    class random_access_iterator
    {
        public:
            typedef std::random_access_iterator_tag     iterator_category;
            typedef std::ptrdiff_t                      difference_type;
            typedef random_access_iterator              iterator;
            typedef T                                   value_type;
            typedef size_t                              size_type;
            typedef T*                                  pointer;
            typedef T&                                  reference;
            typedef const T*                            const_pointer;
            typedef const T&                            const_reference;
        
        private:
            pointer _ptr;

        /****************************** CONSTRUCTORS *********************/
        public:
            random_access_iterator() : _ptr(nullptr) {}
            random_access_iterator(pointer rai): _ptr(rai) {}
            random_access_iterator(const random_access_iterator<typename std::remove_const<T>::type > & ref ) : _ptr(ref.base()) {}
			random_access_iterator(const reverse_random_iterator<typename std::remove_const<T>::type > & ref ) : _ptr(ref.base()) {}
        
        /****************************** BASE *****************************/
            pointer base() const {return _ptr;}

        /****************************** OPERATORS ************************/
            random_access_iterator<T> &operator=(const random_access_iterator<typename std::remove_const<T>::type > &rhs)
			{
				this->_ptr = rhs.base();
				return (*this);
			}
            
            reference operator*() const {return *_ptr;}

            pointer operator->() const {return &(operator*());}

            random_access_iterator &operator++() {++_ptr; return *this;}
            random_access_iterator operator++(int) {
                random_access_iterator tmp = *this;
                ++_ptr;
                return tmp;
            }

            random_access_iterator &operator--() {--_ptr; return *this;}
            random_access_iterator operator--(int) {
                random_access_iterator tmp = *this;
                --_ptr;
                return tmp;
            }

            random_access_iterator operator+(difference_type n) const {return random_access_iterator(_ptr + n);}
            random_access_iterator operator-(difference_type n) const {return random_access_iterator(_ptr - n);}
            difference_type		   operator-(random_access_iterator const &b) {return(this->_ptr - b._ptr);}

            random_access_iterator operator+=(difference_type n) {_ptr += n; return *this;}
            random_access_iterator operator-=(difference_type n) {_ptr -= n; return *this;} 

            reference operator[](size_t n) const {return *(this->_ptr + n);}

            bool				operator<(random_access_iterator const & ref) {return ((this->_ptr) < (ref._ptr));}
			bool				operator<=(random_access_iterator const & ref) {return ((this->_ptr) <= (ref._ptr));}
			bool				operator>(random_access_iterator const & ref) {return ((this->_ptr) > (ref._ptr));}
			bool				operator>=(random_access_iterator const & ref) {return ((this->_ptr) >= (ref._ptr));}
			bool				operator==(random_access_iterator const & ref) {return ((this->_ptr) == (ref._ptr));}
			bool				operator!=(random_access_iterator const & ref) {return ((this->_ptr) != (ref._ptr));}

            template < class T2 >
			friend size_t operator-(random_access_iterator<T2> const & a, random_access_iterator<T2> const & b);
			friend bool	operator<(random_access_iterator const & a, random_access_iterator const & ref) {return ((a._ptr) < (ref._ptr));}
			friend bool	operator<=(random_access_iterator const & a, random_access_iterator const & ref) {return ((a._ptr) <= (ref._ptr));}
			friend bool	operator>(random_access_iterator const & a, random_access_iterator const & ref) {return ((a._ptr) > (ref._ptr));}
			friend bool	operator>=(random_access_iterator const & a, random_access_iterator const & ref) {return ((a._ptr) >= (ref._ptr));}
			friend bool	operator==(random_access_iterator const & a, random_access_iterator const & ref) {return ((a._ptr) == (ref._ptr));}
			friend bool	operator!=(random_access_iterator const & a, random_access_iterator const & ref) {return ((a._ptr) != (ref._ptr));}

        /****************************** DESTRUCTOR *************************/
            virtual ~random_access_iterator() {}
    };

    template < class T >
	size_t		operator-(random_access_iterator<T> const &a, random_access_iterator<T> const &b)
	{
		return(a._ptr - b._ptr);
	}

	template < class T >
	random_access_iterator<T>		operator+(int n, random_access_iterator<T> it)
	{
	return(it + n);
	}

	template < class T >
	bool	operator<(random_access_iterator<T> const &a, random_access_iterator<T> const &ref) {return ((a._ptr) < (ref._ptr));}

	template < class T >
	bool	operator<=(random_access_iterator<T> const &a, random_access_iterator<T> const &ref) {return ((a._ptr) <= (ref._ptr));}

	template < class T >
	bool	operator>(random_access_iterator<T> const &a, random_access_iterator<T> const &ref) {return ((a._ptr) > (ref._ptr));}

	template < class T >
	bool	operator>=(random_access_iterator<T> const &a, random_access_iterator<T> const &ref) {return ((a._ptr) >= (ref._ptr));}

	template < class T >
	bool	operator==(random_access_iterator<T> const &a, random_access_iterator<T> const &ref) {return ((a._ptr) == (ref._ptr));}
	
	template < class T >
	bool	operator!=(random_access_iterator<T> const &a, random_access_iterator<T> const &ref) {return ((a._ptr) != (ref._ptr));}


} // namespace ft


#endif