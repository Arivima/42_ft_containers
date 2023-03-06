/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_reverse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:45:59 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/03 11:46:01 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>iterator_reverse_iterator.hpp============================================================================
#ifndef     ITERATOR_REVERSE_HPP
#define     ITERATOR_REVERSE_HPP

#include "header.hpp"
#include "utils.hpp"


namespace ft
{
    template<typename Iterator>
    class reverse_iterator
    {
    public:
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;  // tag
        typedef typename ft::iterator_traits<Iterator>::value_type        value_type;         // T
        typedef typename ft::iterator_traits<Iterator>::difference_type   difference_type;    // distance std::ptrdiff_t
        typedef typename ft::iterator_traits<Iterator>::pointer           pointer;            // T*
        typedef typename ft::iterator_traits<Iterator>::reference         reference;          // T&
        typedef          Iterator                                         iterator_type;      // T*
    protected:
        iterator_type _current;
        
    public: // Member functions
        /*Default Constructor*/ reverse_iterator ()
                                : _current() 
                                {
                                    // print(DEBUG_RIT, GREEN, "reverse_iterator Default Constructor");
                                }
        /*Fill Constructor*/    explicit reverse_iterator (iterator_type x)
                                : _current(x) 
                                {
                                    // print(DEBUG_RIT, GREEN, "reverse_iterator iterator_type Constructor");
                                }
        /*Copy Constructor*/    template< class Iter >
                                reverse_iterator (const ft::reverse_iterator<Iter>& other)
                                : _current(other.base()) 
                                {
                                    // print(DEBUG_RIT, GREEN, "reverse_iterator Template Copy Constructor");
                                }
        /*Destructor*/  virtual ~reverse_iterator ()                 
                                {
                                    // print(DEBUG_RIT, RED, "reverse_iterator Destructor");
                                }

        // Base 
        iterator_type           base () const {
            return this->_current ;
        }
        
        // Copy Assignment
        template< class U > 
        reverse_iterator&   operator=   (const reverse_iterator<U>& other) {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator=");
            this->_current = other.base();
            return *this;
        }
        
        
        // Access Operators
        reference               operator*   () const {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator*\t| iterator_type tmp = this->_current;\t| return (*--tmp);");
            iterator_type tmp = this->_current;
            return (*--tmp);
        }
        
        pointer                 operator->  () const {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator->\t| return &(operator*())");
			return &(operator*());
        }

        reference               operator[]  (const difference_type n) const {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator[]\t| return (this->_current[-n-1]);");
            return (this->_current[-n-1]);
        }
        
        
        // Arithmetic Operators
        reverse_iterator&   operator++  () {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator++\t| --this->_current;\t| return *this;");
            --this->_current;
            return *this;
        }
        
        reverse_iterator&   operator--  () {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator--\t| ++this->_current;\t| return *this;");
            ++this->_current;
            return *this;
        }
        
        reverse_iterator    operator++  (int) {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator++(int)\t| reverse_iterator tmp(*this);\t| ++(*this);\t| return tmp;");
            reverse_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        reverse_iterator    operator--  (int) {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator--(int)\t| reverse_iterator tmp(*this);\t| --(*this);\t| return tmp;");
            reverse_iterator tmp(*this);
            --(*this);
            return tmp;
        }
        
        reverse_iterator    operator+   (const difference_type n) const {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator+n\t| return reverse_iterator(this->base() - n);");
            return reverse_iterator(this->base() - n);
        }
        
        reverse_iterator    operator-   (const difference_type n) const {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator-n\t| return reverse_iterator(this->base() + n);");
            return reverse_iterator(this->base() + n);
        }            
        
        reverse_iterator&   operator+=  (const difference_type n) {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator+=\t| this->_current -= n;\t| return *this;");
            this->_current -= n;
            return *this;
        }  
        
        reverse_iterator&   operator-=  (const difference_type n) {
            // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator-=\t| this->_current += n;\t| return *this;");
            this->_current += n;
            return *this;
        }
    };

    
    // Non Member functions
    template< class Iterator1, class Iterator2 >
    bool operator== (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator==\t| return (lhs.base() == rhs.base());");
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator!=\t| return (lhs.base() != rhs.base());");
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<  (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator<\t| return (lhs.base() < rhs.base());");
        return (lhs.base() > rhs.base());

    }

    template< class Iterator1, class Iterator2 >
    bool operator<= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator<=\t| return (lhs.base() <= rhs.base());");
        return (lhs.base() >= rhs.base());

    }

    template< class Iterator1, class Iterator2 >
    bool operator>  (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator>\t| return (lhs.base() > rhs.base());");
        return (lhs.base() < rhs.base());

    }

    template< class Iterator1, class Iterator2 >
    bool operator>= (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator>=\t| return (lhs.base() >= rhs.base());");
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator >
    ft::reverse_iterator<Iterator> operator+ (const typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& it)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator+it\t| return (ft::reverse_iterator<Iterator>(it.base() + n));");
        return (it + n);
    }

    template< class Iterator1, class Iterator2 >
    typename ft::reverse_iterator<Iterator1>::difference_type operator- (const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        // print(DEBUG_RIT,  BMAGENTA, "Calling Reverse Operator-it\t| return (rhs.base() - lhs.base());");
        return(rhs.base() - lhs.base());
    }
}
# endif
// ============================================================================>>iterator_reverse_iterator.hpp============================================================================
