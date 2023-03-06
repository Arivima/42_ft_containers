/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_RandomAccess.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:45:56 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/03 12:20:15 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>iterator_RandomAccess.hpp============================================================================
#ifndef     ITERATOR_RANDOMACCESS_HPP
#define     ITERATOR_RANDOMACCESS_HPP

#include "header.hpp"
#include "utils.hpp"

namespace userdefined
{
    //* LegacyRandomAccessIterator
    template<typename T>
    class RandomAccessIterator
    {
    public: // Member types
        typedef typename ft::random_access_iterator_tag             iterator_category;   // tag //! ici gives error because used ft instead of std
        typedef typename ft::iterator_traits<T*>::value_type        value_type;         // T
        typedef typename ft::iterator_traits<T*>::difference_type   difference_type;    // distance std::ptrdiff_t
        typedef typename ft::iterator_traits<T*>::pointer           pointer;            // T*
        typedef typename ft::iterator_traits<T*>::reference         reference;          // T&
        typedef          pointer                                    iterator_type;      // T*

    protected:
        iterator_type _current;
    public: // Member functions
        /*Default Constructor*/ RandomAccessIterator ()
                                : _current()
                                {
                                    // print((DEBUG_IT || DEBUG_RIT), GREEN, "RandomAccessIterator Default Constructor\t| _current()");
                                }
        /*Fill Constructor*/    RandomAccessIterator (iterator_type x)
                                : _current(x)
                                {
                                    // print((DEBUG_IT || DEBUG_RIT), GREEN, "RandomAccessIterator iterator_type Constructor\t| _current(x)");
                                }
        /*Copy Constructor*/    RandomAccessIterator (const RandomAccessIterator< typename ft::remove_const<value_type>::type > & other)
                                : _current(other.base())
                                {
                                    // print((DEBUG_IT || DEBUG_RIT), GREEN, "RandomAccessIterator Template Copy Constructor\t| _current(other._current)");
                                }

        /*Destructor*/  virtual ~RandomAccessIterator () {
                                    // print((DEBUG_IT || DEBUG_RIT), RED, "RandomAccessIterator Destructor");
                                } 
        
        // Base 
        iterator_type           base        () const {
            return this->_current;}
        
        // Copy Assignment
        template< class U >
        RandomAccessIterator&   operator=   (RandomAccessIterator<U>& other) {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator=\t| this->_current = other.base()\t| return *this;");
            this->_current = other.base();
            return *this;
        }
        
        
        // Access Operators
        reference               operator*   () const {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator*\t| return (*this->base());");
            return (*this->base());
        }
        
        pointer                 operator->  () const {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator->\t| return (&(*this->base()));");
            return std::addressof(operator*());
            // return (*(&this->_current));
        }
        
        reference               operator[]  (const difference_type n) const {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator[]\t| return (this->base()[n]);");
            return (this->base()[n]);
        }
        
        
        // Arithmetic Operators
        RandomAccessIterator&   operator++  () {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator++\t| ++this->_current;\t| return *this;");
            ++this->_current;
            return *this;
        }
        
        RandomAccessIterator&   operator--  () {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator--\t| --this->_current;\t| return *this;");
            --this->_current;
            return *this;
        }
        
        RandomAccessIterator    operator++  (int) {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator++(int)\t| RandomAccessIterator tmp(*this);\t| ++(this->_current);\t| return tmp;");
            RandomAccessIterator tmp(*this);
            ++this->_current;
            return tmp;
        }
        
        RandomAccessIterator    operator--  (int) {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator--(int):\t| RandomAccessIterator tmp(*this);\t| --(this->_current);return tmp;");
            RandomAccessIterator tmp(*this);
            --this->_current;
            return tmp;
        }
        
        RandomAccessIterator    operator+   (const difference_type & n) const { 
            // print(DEBUG_IT,  BBLUE, "Calling Iterator+n\t| return RandomAccessIterator(this->base() + n);");
             return RandomAccessIterator(this->base() + n);
        }
        
        RandomAccessIterator    operator-   (const difference_type & n) const { 
            // print(DEBUG_IT,  BBLUE, "Calling Iterator-n\t| return RandomAccessIterator(this->base() - n);");
            return RandomAccessIterator(this->base() - n);
        }            
        
        RandomAccessIterator&   operator+=  (const difference_type & n) {
            // print(DEBUG_IT,  BBLUE, "Calling Iterator+=\t| this->_current += n;\t| return *this;");
            this->_current += n;
            return *this;
        }  
        
        RandomAccessIterator&   operator-=  (const difference_type & n){
            // print(DEBUG_IT,  BBLUE, "Calling Iterator-=\t| this->_current -= n;\t| return *this;");
            this->_current -= n;
            return *this;
        }
    };


    // Non Member functions
    template< class Iterator1, class Iterator2 >
    bool operator== (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator==\t| return (lhs.base() == rhs.base());");
        return (lhs.base() == rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator!= (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator!=\t| return (lhs.base() != rhs.base());");
        return (lhs.base() != rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<  (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator<\t| return (lhs.base() < rhs.base());");
        return (lhs.base() < rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator<= (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator<=\t| return (lhs.base() <= rhs.base());");
        return (lhs.base() <= rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>  (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator>\t| return (lhs.base() > rhs.base());");
        return (lhs.base() > rhs.base());
    }

    template< class Iterator1, class Iterator2 >
    bool operator>= (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator>=\t| return (lhs.base() >= rhs.base());");
        return (lhs.base() >= rhs.base());
    }

    template< class Iter >
    userdefined::RandomAccessIterator<Iter> operator+ (const typename userdefined::RandomAccessIterator<Iter>::difference_type n, const userdefined::RandomAccessIterator<Iter>& it)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator+it\t| return (userdefined::RandomAccessIterator<Iter>(it.base() + n));");
        return (userdefined::RandomAccessIterator<Iter>(it.base() + n));
    }

    template< class Iterator1, class Iterator2 >
    typename userdefined::RandomAccessIterator<Iterator1>::difference_type operator- (const userdefined::RandomAccessIterator<Iterator1>& lhs, const userdefined::RandomAccessIterator<Iterator2>& rhs)
    {
        // print(DEBUG_IT,  BBLUE, "Calling Iterator-it\t| return (rhs.base() - lhs.base());");
        return (lhs.base() - rhs.base());
    }

}
# endif
// ============================================================================>>iterator_RandomAccess.hpp============================================================================

