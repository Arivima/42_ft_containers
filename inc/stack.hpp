/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:23 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/03 17:15:42 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>stack.hpp============================================================================
// Stack class is referenced from: 
    // https://en.cppreference.com/w/cpp/container/stack
    // https://cplusplus.com/reference/stack/stack/
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Stack structure:
    /// Member types
            //  container_type; value_type; size_type;  reference;  const_reference;
    /// Member functions
            // Basics           // Constructors | Destructor | operator= 
            // ElementAccess    // top
            // Capacity         // empty | size
            // Modifiers        // push | pop
    /// Non Member functions
            // comparison operators ==, !=, <, <=, >, >=
// --------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef     STACK_HPP
# define    STACK_HPP

#include "vector.hpp"
#include "header.hpp"

namespace ft
{   
	template <
        class T,
        class Container = ft::vector<T>
        >
	class stack
	{
		public:                 // Definition               // Member type
			typedef             Container                   container_type;
			typedef typename    Container::value_type       value_type;
			typedef typename    Container::size_type        size_type;
			typedef typename    Container::reference        reference;
			typedef typename    Container::const_reference  const_reference;
		protected:
			container_type      c;
        //* Member functions
		public:
        //* Canonical
            /*Default*/         explicit stack  (const container_type& cont = container_type()) : c(cont) {}
            /*Copy*/            stack           (const stack& other )                           : c(other.c) {}
            /*Destructor*/      ~stack() {}
            /*Cpy Ass.*/ stack& operator=(const stack& other)               {this->c = other.c; return *this;}
        //* Element Access
            value_type&         top()                                       {return c.back();}
            const value_type&   top()   const                               {return c.back();}
        //* Capacity
            bool                empty() const                               {return c.empty();}
            size_type           size()  const                               {return c.size();}
        //* Modifiers
            void                push(const value_type& val)                 {this->c.push_back(val);}
            void                pop()                                       {this->c.pop_back();}
        //* Operators
			template <class Type, class _Container >
			friend bool operator==(const stack<Type, _Container >& lhs, const stack<Type, _Container >& rhs);
			template <class Type, class _Container >
			friend bool operator< (const stack<Type, _Container >& lhs, const stack<Type, _Container >& rhs);
	};
	//* Non member functions
    template< class T, class Container >
    bool operator==(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs){return (lhs.c == rhs.c);}
    template< class T, class Container >
    bool operator!=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs){return !(lhs == rhs);}
    template< class T, class Container >
    bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs){return (lhs.c <  rhs.c);}
    template< class T, class Container >
    bool operator<=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs){return !(rhs < lhs);}
    template< class T, class Container >
    bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs){return (rhs < lhs);}
    template< class T, class Container >
    bool operator>=(const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs){return !(lhs < rhs);}
}
#endif
// ============================================================================<<stack.hpp============================================================================
