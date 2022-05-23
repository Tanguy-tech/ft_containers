/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 08:48:59 by tbillon           #+#    #+#             */
/*   Updated: 2022/05/09 08:16:56 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef> // size_t, ptrdiff 
#include <memory> // std::allocator
#include <stdexcept> // std::lenght_error
#include "../iterators/iterator_traits.hpp"
#include "../iterators/random_access_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/equal.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
    template< class T, class Alloc = std::allocator<T> >
    class vector
    {
        public:
            typedef T                                       value_type;
            typedef Alloc                                   allocator_type;
            typedef T&                                      reference;
            typedef const T&                                const_reference;
            typedef typename Alloc::pointer                 pointer;
            typedef typename Alloc::const_pointer           const_pointer;
            typedef ft::random_access_iterator<T>           iterator;    
            typedef ft::random_access_iterator<const T>     const_iterator;
            typedef ft::reverse_iterator<iterator>          reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
            typedef std::ptrdiff_t                          difference_type;
            typedef size_t                                  size_type;

        private:
            pointer         _ptrVec;
            size_type       _capacity;
            size_type       _size;
            allocator_type  _allocator;

        /****************************** CONSTRUCTORS *************************/
        public:
            /**** DEFAULT ****/                            //* Default constructor - declared explicit so it cannot be used for implicit conversion or copy-initialization
            explicit vector(const allocator_type &alloc = allocator_type()) : _ptrVec(nullptr), _capacity(0), _size(0), _allocator(alloc) {}
            
            /**** FILL ****/                               //* Fill constructor 
            explicit vector(size_type n,
                const value_type &val = value_type(),
                const allocator_type &alloc = allocator_type()) : _capacity(n), _size(n), _allocator(alloc)
            {
                _ptrVec = _allocator.allocate(n);
                for (size_type i = 0; i < n; i++)
                    _allocator.construct(_ptrVec + i, val); //* Constructs an object of type T in allocated uninitialized storage pointed to by _ptrVec, using placement-new.
            }

            /**** RANGE ****/                              //* Range constructor - Constructs a container with as many elements as the range [first,last), with each element emplace-constructed from its corresponding element in that range, in the same order.
            template< class InputIterator >
            vector(InputIterator first,
                InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::val, InputIterator>::type* = nullptr,
                const allocator_type &alloc = allocator_type()) : _ptrVec(nullptr), _capacity(0), _size(0), _allocator(alloc)
            {
                _ptrVec = _allocator.allocate(0);
				assign(first, last);
            }

            /**** COPY ****/                               //* Copy constructor
            vector(const vector &cpy): _capacity(cpy._capacity), _size(cpy._size), _allocator(cpy._allocator)
            {
                this->_ptrVec = this->_allocator.allocate(this->_capacity);
                for (size_type i = 0; i < this->_size; i++)
                    this->_allocator.construct(this->_ptrVec + i, cpy._ptrVec[i]);
            }

        /****************************** DESTRUCTOR ***************************/
            virtual ~vector(){
                if (this->_ptrVec)
                {
                    for (size_type i = _size; i < _size; i++)
                        delete(&_ptrVec[i]);
                }
                this->clear();
            }

        /***************************** OPERATOR = ****************************/
            void operator=(const vector& x)
            {
                for (std::size_t i = 0; i < this->_size; i++)
                    this->_allocator.destroy(this->_ptrVec + i);
                this->_allocator.deallocate(this->_ptrVec, this->_capacity);
                this->_size = x._size;
                this->_capacity = x._capacity;
                this->_allocator = x._allocator;
                this->_ptrVec = this->_allocator.allocate(this->_capacity);
                for (std::size_t i = 0; i < this->_size; i++)
                    this->_allocator.construct(this->_ptrVec + i, x._ptrVec[i]);
                
            }

        /****************************** ELEMENT ACCESS ***********************/
            reference operator[] (size_type n) {return(*(_ptrVec + n));}
            const_reference operator[] (size_type n) const {return(*(_ptrVec + n));}

            reference at(size_type n)
            {
                if (n >= this->_size)
                    throw std::out_of_range("Vector reference index is out of range.");
                return this->_ptrVec[n];
            }

            const_reference at(size_type n) const 
            {
                if (n >= this->_size)
                    throw std::out_of_range("Vector reference index is out of range.");
                return this->_ptrVec[n];
            }

            reference front() {return this->_ptrVec[0];}
            const_reference front() const {return this->_ptrVec[0];}

            reference back() {return this->_ptrVec[_size - 1];}
            const_reference back() const {return this->_ptrVec[_size - 1];}
        /****************************** CAPACITY *****************************/
            size_type size() const {return this->_size;}
            size_type max_size() const {return this->_allocator.max_size();}

            void reserve(size_type n)
			{
				size_t	nb = this->_capacity == 0 ? 1 : this->_capacity;

                if (n > this->max_size())
                {
                    throw(std::length_error("vector"));
                }
                if (n > this->_capacity)
                {
                    T*	array;

                    while(nb < n)
                        nb *= 2;
                    array = this->_allocator.allocate(nb);
                    for (size_t i = 0; i < this->_size; i++)
                    {
                        this->_allocator.construct(array + i, this->_ptrVec[i]);
                        this->_allocator.destroy(this->_ptrVec + i);
                    }
                    this->_allocator.deallocate(this->_ptrVec, this->_capacity);
                    this->_ptrVec = array;
                    this->_capacity = nb;
                }
			};

            void resize(size_type n, value_type val = value_type())
            {
                if (n < this->_size)
                {
                    for (size_t i = n; i < this->_size; i++)
                    {
                        this->_allocator.destroy(this->_ptrVec + i);
                    }
                }
                else
                {
                    if (n > this->_capacity)
                        reserve(n);
                    if (n > this->_size)
                    {
                        for (size_t i = this->_size; i < n; i++)
                            this->_allocator.construct(this->_ptrVec + i, val);
                    }
                }
                this->_size = n;
            }

            size_type   capacity() const {return this->_capacity;}

            bool    empty() const {return (this->_size == 0 ? true : false);}
        /****************************** ITERATORS *****************************/
            iterator    begin() {return iterator(this->_ptrVec);}
            const_iterator  begin() const {return const_iterator(this->_ptrVec);}

            iterator    end() {return iterator(this->_ptrVec + this->_size);}
            const_iterator  end() const {return const_iterator(this->_ptrVec + this->_size);}

            reverse_iterator    rbegin() {return reverse_iterator(this->end());}
            const_reverse_iterator rbegin() const {return const_reverse_iterator(this->end());}

            reverse_iterator    rend() {return reverse_iterator(this->begin());}
            const_reverse_iterator rend() const {return const_reverse_iterator(this->begin());}

        /****************************** MODIFIERS ****************************/
            iterator erase(iterator pos)
			{
				iterator idx_tmp = pos;
                size_t      i = 0;
				for (iterator it = this->begin(); it < pos; it++)
                    i++;
                this->_allocator.destroy(this->_ptrVec + i);
                while(pos + 1 < this->end())
                {
                    *pos = *(pos + 1);
                    pos++;
                }
                this->_size--;
                return(idx_tmp);
			};
            
			iterator erase(iterator begin, iterator end)
			{
				size_t	n = end - begin;
                size_t	i = 0;

                if (begin > end)
                    throw(std::length_error("vector"));
                for (iterator it = this->begin(); it < end; it++)
                    i++;
                while (end > begin)
                {
                    end--;
                    i--;
                    this->_allocator.destroy(this->_ptrVec + i);
                }
                i = 0;
                while (begin + n + i < this->end())
                {
                    *(begin + i) = *(begin + i + n);
                    i++;
                }
                this->resize(this->_size - n);
                return (begin);
			};
            
            void clear(void)
			{
				erase(begin(), end());
			};

            iterator insert(iterator pos, const value_type &val) //single elem
			{
				size_t	i = 0;
                size_t	e = this->_size;

                for (iterator it = this->begin(); it < pos; it++)
                {
                    i++;
                }
                this->reserve(this->_size + 1);
                this->_size += 1;
                while(e > i)
                {
                    this->_ptrVec[e] = this->_ptrVec[e - 1];
                    e--;
                }
                this->_allocator.construct(this->_ptrVec + i, val);
                return (iterator(this->_ptrVec + i));
			};
            
			void insert(iterator pos, size_type n, const value_type &val) //fill 
			{
				size_t	i = 0;
                size_t	e = this->_size - 1 + n;

                for (iterator it = this->begin(); it < pos; it++)
                {
                    i++;
                }
                this->reserve(this->_size + n);
                this->_size += n;
                while(e >= i + n)
                {
                    this->_ptrVec[e] = this->_ptrVec[e - n];
                    e--;
                }
                while (e >= i && e != static_cast<size_t>(-1))
                {
                    this->_allocator.construct(this->_ptrVec + e, val);
                    e--;
                }
			};

            template <class InputIterator>
			void insert(iterator pos, InputIterator begin, InputIterator end,
                typename ft::enable_if<!ft::is_integral<InputIterator>::val, InputIterator>::type* = nullptr) // range
			{
				size_t 	n = 0;
                size_t 	_pos = 0;
                size_t 	i = 0;

                for(InputIterator tmp = begin; tmp != end; tmp++)
                        n++;
                for(iterator tmp = this->begin(); tmp != pos; tmp++)
                        _pos++;
                this->reserve(this->_size + n);
                pos = this->begin() + _pos;
                for(iterator tmp = this->end() + n - 1; tmp >= pos + n; tmp--)
                    *tmp = *(tmp - n);
                for (InputIterator tmp = begin; tmp != end; tmp++)
                {
                    this->_allocator.construct(&pos[i], *(tmp));
                    i++;
                }
                this->_size += n;
			};
            
            template <class InputIterator>
			void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::val, InputIterator>::type* = nullptr)
			{
				InputIterator	last2 = last;
                size_t			s = 0;

                while(last2 != first)
                {
                    last2--;
                    s++;
                }
                this->resize(0);
                this->reserve(s);
                this->_size = s;
                while (first != last)
                {
                    this->_allocator.construct(this->_ptrVec + (this->_size - s), *first);
                    s--;
                    first++;
                }
            };
            
			void assign(size_type n, const value_type &val)
			{
				this->resize(0);
                this->reserve(n);
                this->_size = n;
                for (size_t i = 0; i < n; i++)
                {
                    this->_allocator.construct(this->_ptrVec + i, val);
                }
			};

            void			push_back (const value_type& val)
			{
                this->resize(this->_size + 1, val);
			}

            void pop_back(void)
            {
                if (this->_size > 0)
				    this->resize(this->_size - 1);
            }

            void    swap(vector &x)
            {
                if (x == *this)
                    return ;
                
                pointer tmp_ptrVec = x._ptrVec;
                size_type tmp_size = x._size;
                size_type tmp_capacity = x._capacity;
                allocator_type tmp_alloc = x._allocator;

                x._ptrVec = this->_ptrVec;
                x._size = this->_size;
                x._capacity = this->_capacity;
                x._allocator = this->_allocator;

                this->_ptrVec = tmp_ptrVec;
                this->_size = tmp_size;
                this->_capacity = tmp_capacity;
                this->_allocator = tmp_alloc;
            }

            /****************************** ALLOCATOR ****************************/

            allocator_type  get_allocator() const {allocator_type cpy = this->_allocator; return cpy;}
    };

    template<typename T>
    bool operator==(vector<T> const &lhs, vector<T> const &rhs) 
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); i++)
            if (lhs[i] != rhs[i])
                return (false);
	    return (true);
    }

    template<typename T>
    bool operator!=(vector<T> const &lhs, vector<T> const &rhs) {return (!(lhs == rhs));}

    template<typename T>
    bool operator<(vector<T> const &lhs, vector<T> const &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<typename T>
    bool operator>(vector<T> const &lhs, vector<T> const &rhs) {return (rhs < lhs);}

    template<typename T>
    bool operator<=(vector<T> const &lhs, vector<T> const &rhs) {return (!(rhs < lhs));}

    template<typename T>
    bool operator>=(vector<T> const &lhs, vector<T> const &rhs) {return (!(lhs < rhs));}

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {x.swap(y);}
    
} // namespace ft

#endif