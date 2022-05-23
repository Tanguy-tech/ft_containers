/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbillon <tbillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:33:49 by tanguy            #+#    #+#             */
/*   Updated: 2022/04/27 11:18:13 by tbillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        public:
            typedef Container   container_type;
            typedef T           value_type;
            typedef size_t      size_type;

        /****************************** CONSTRUCTORS *************************/
            explicit stack (const container_type& ctnr = container_type()) : ct(ctnr) {}

        /****************************** MEMBER FUNCTIONS *********************/
            bool                empty() const               {return this->ct.empty();}
            size_type           size() const				{ return this->ct.size();}
			value_type&         top()						{ return (this->ct.back());}
			const value_type&   top() const					{ return (this->ct.back());}
			void                push(const value_type& val)	{ this->ct.push_back(val);}
			void                pop()						{ this->ct.pop_back();}

        private:
        /****************************** RELATIONAL OPERATORS ******************/
            template <class Tc, class Containerc>
            friend bool operator==(const stack<Tc, Containerc>& lhs, const stack<Tc, Containerc>& rhs);

            template <class Tc, class Containerc>
            friend bool operator!=(const stack<Tc, Containerc>& lhs, const stack<Tc, Containerc>& rhs);

            template <class Tc, class Containerc>
            friend bool operator<(const stack<Tc, Containerc>& lhs, const stack<Tc, Containerc>& rhs);

            template <class Tc, class Containerc>
            friend bool operator<=(const stack<Tc, Containerc>& lhs, const stack<Tc, Containerc>& rhs);

            template <class Tc, class Containerc>
            friend bool operator>(const stack<Tc, Containerc>& lhs, const stack<Tc, Containerc>& rhs); 
            
            template <class Tc, class Containerc>
            friend bool operator>=(const stack<Tc, Containerc>& lhs, const stack<Tc, Containerc>& rhs);

        protected:
            container_type      ct; //* Conteneur sous-jacent
    };

    template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.ct == rhs.ct);}

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.ct != rhs.ct);}

	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.ct < rhs.ct);}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.ct <= rhs.ct);}

	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs){return (lhs.ct > rhs.ct);}

	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return (lhs.ct >= rhs.ct);}
    
} // namespace ft

#endif