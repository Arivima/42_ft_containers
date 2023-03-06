/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:42 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/03 11:46:43 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>utils.hpp============================================================================
#ifndef UTILS_HPP
# define UTILS_HPP

#include "header.hpp"

#include <type_traits>

// --------------------------------------- 
// On this file:
//  std::swap
//  std::remove_const
//  std::enable_if
//  std::integral_constant
//  std::bool_constant // false_type // true_type
//  std::is_same
//  std::is_integral
//  std::iterator_tags
//  std::is_iterator
//  std::iterator_traits
//  std::lexicographical_compare
//  std::equal
//  std::pair, std::make_pair(), std::is_pair
// --------------------------------------- 

namespace ft
{
//*--------------------------------------- std::swap
//Exchanges the given values. 1) Swaps the values a and b.
        template< class T >
        void swap( T& a, T& b ){
            T c = a;
            a = b;
            b = c;
        }

//*--------------------------------------- std::remove_const
// Provides the member typedef type which is the same as T, except its topmost const is removed.
        template<class T>                       struct remove_const             { typedef T type; };
        template<class T>                       struct remove_const <const T>   { typedef T type; };

//*--------------------------------------- std::enable_if
// The type T is enabled as member type enable_if::type if Cond is true. Otherwise, enable_if::type is not defined.
        template<bool Cond, class T = void>     struct enable_if                {};
        template<class T>                       struct enable_if    <true, T>   { typedef T type; };

//*--------------------------------------- std::integral_constant
// std::integral_constant wraps a static constant of specified type. It is the base class for the C++ type traits.
        template< class T, T v > 
        struct integral_constant{
            // Member constants // (public static member constant)
            static const T                      value = v;
            // Member types
            typedef T                           value_type;
            typedef ft::integral_constant<T, v> type;
            // Member functions
            operator value_type() const         {return value;}
        };

//*--------------------------------------- std::bool_constant // std::truetype //  std::false_type
// types used as a compile-time boolean with true / false value.
        //* version 3
        template <bool B>
        struct  bool_constant : public integral_constant<bool, B>{};

        typedef bool_constant<true>     true_type;
        typedef bool_constant<false>    false_type;
        
        //* version 1
            // template<bool B>
            //     using bool_constant = integral_constant<bool, B>;
            // using true_type  = bool_constant<true>;
            // using false_type = bool_constant<false>;
        //* version 2
            // typedef integral_constant<bool, true>     true_type;
            // typedef integral_constant<bool, false>    false_type;

//*--------------------------------------- std::is_same
// If T and U name the same type (taking into account const/volatile qualifications), provides the member constant value equal to true. Otherwise value is false.
// Commutativity is satisfied, i.e. for any two types T and U, is_same<T, U>::value == true if and only if is_same<U, T>::value == true.
// The behavior of a program that adds specializations for is_same or is_same_v (since C++17) is undefined.
        template<class T, class U>              struct is_same          : std::false_type {};
        template<class T>                       struct is_same<T, T>    : std::true_type {};

//*--------------------------------------- std::is_integral
        // TRUE = bool, char, char8_t (since C++20), char16_t, char32_t, wchar_t, short, int, long, long long, 
        // TRUE = any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. 
            // can also be written => template <class T>  struct is_integral				: public ft::integral_constant<T, false> {};

        template <class T>  struct is_integral                      : public false_type {};
        template <>         struct is_integral<bool>                : public true_type {};
        template <>         struct is_integral<char>                : public true_type {};
        template <>         struct is_integral<signed char>         : public true_type {};
        template <>         struct is_integral<unsigned char>       : public true_type {};
        template <>         struct is_integral<char16_t>            : public true_type {}; // C++11
        template <>         struct is_integral<char32_t>            : public true_type {}; // C++11
        template <>         struct is_integral<wchar_t>             : public true_type {}; // deprecated
        template <>         struct is_integral<short>               : public true_type {};
        template <>         struct is_integral<unsigned short>      : public true_type {};
        template <>         struct is_integral<int>                 : public true_type {};
        template <>         struct is_integral<unsigned int>        : public true_type {};
        template <>         struct is_integral<long>                : public true_type {};
        template <>         struct is_integral<unsigned long>       : public true_type {};
        template <>         struct is_integral<long long>           : public true_type {};
        template <>         struct is_integral<unsigned long long>  : public true_type {};

// //*--------------------------------------- std::IteratorTags
// Defines the category of an iterator. Each tag is an empty type.
// For every LegacyIterator type It, a typedef std::iterator_traits<It>::iterator_category must be defined to 
// be an alias to one of these tag types, to indicate the most specific category that It is in.

    struct input_iterator_tag { };                                              // LegacyInputIterator
    struct output_iterator_tag { };                                             // LegacyOutputIterator
    struct forward_iterator_tag : public input_iterator_tag { };                // LegacyForwardIterator
    struct bidirectional_iterator_tag : public forward_iterator_tag { };        // LegacyBidirectionalIterator
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };  // LegacyRandomAccessIterator
    struct contiguous_iterator_tag : public random_access_iterator_tag { };

//*--------------------------------------- std::is_iterator
        template < typename T >                     struct is_iterator_tagged   : public false_type {};
        template <>                                 struct is_iterator_tagged   < ft::input_iterator_tag>           : public true_type {};
        template <>                                 struct is_iterator_tagged   < std::input_iterator_tag>          : public true_type {};
        template <>                                 struct is_iterator_tagged   < ft::output_iterator_tag>          : public true_type {};
        template <>                                 struct is_iterator_tagged   < std::output_iterator_tag>         : public true_type {};
        template <>                                 struct is_iterator_tagged   < ft::forward_iterator_tag>         : public true_type {};
        template <>                                 struct is_iterator_tagged   < std::forward_iterator_tag>        : public true_type {};
        template <>                                 struct is_iterator_tagged   < ft::bidirectional_iterator_tag>   : public true_type {};
        template <>                                 struct is_iterator_tagged   < std::bidirectional_iterator_tag>  : public true_type {};
        template <>                                 struct is_iterator_tagged   < ft::random_access_iterator_tag>   : public true_type {};
        template <>                                 struct is_iterator_tagged   < std::random_access_iterator_tag>  : public true_type {};

// //*--------------------------------------- std::iterator_traits
// std::iterator_traits is the type trait class that provides uniform interface to the properties of LegacyIterator types. 
// This makes it possible to implement algorithms only in terms of iterators.
// The template can be specialized for user-defined iterators so that the information about the iterator can be retrieved even if the type 
// does not provide the usual typedefs.
// Not used 

    template< class Iter >
    struct iterator_traits {
        typedef	typename Iter::difference_type   difference_type;
        typedef	typename Iter::value_type        value_type;
        typedef	typename Iter::pointer           pointer;
        typedef	typename Iter::reference         reference;
        typedef	typename Iter::iterator_category iterator_category;
    };

    template< class T >
    struct iterator_traits<T*> {
        typedef	std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef	T*                              pointer;
        typedef	T&                              reference;
        typedef	ft::random_access_iterator_tag     iterator_category;
    };

    template< class T >
    struct iterator_traits<const T*> {
        typedef	std::ptrdiff_t                  difference_type;
        typedef const T                         value_type;
        typedef	const T*                        pointer;
        typedef	const T&                        reference;
        typedef	ft::random_access_iterator_tag     iterator_category;
    };

//*--------------------------------------- std::distance
        template< class InputIt >
        typename ft::iterator_traits<InputIt>::difference_type      distance(InputIt first, InputIt last)
        {
            typename ft::iterator_traits<InputIt>::difference_type dist;

            dist = 0;
            for (; first != last; first++)
                dist++;
            return dist;
        }

//*--------------------------------------- std::lexicographical_compare
// As implemented on cppreference.com
// Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
// Returns true if the first range is lexicographically less than the second, otherwise false (including when all the elements of both ranges are equivalent).
// Lexicographical comparison is an operation with the following properties:
    // Two ranges are compared element by element.
    // The first mismatching element defines which range is lexicographically less or greater than the other.
    // If one range is a prefix of another, the shorter range is lexicographically less than the other.
    // If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
    // An empty range is lexicographically less than any non-empty range.
    // Two empty ranges are lexicographically equal.

    /*1*/ template< class InputIt1, class InputIt2 >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ){
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2){
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
    // /*3*/ template< class InputIt1, class InputIt2, class Compare >
    // bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp ){
    //     for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2){
    //         if (comp(*first1, *first2)) return true;
    //         if (comp(*first2, *first1)) return false;
    //     }
    //     return (first1 == last1) && (first2 != last2);
    // }

// --------------------------------------- std::equal
// As implemented on cppreference.com
// Returns true if the range [first1, last1) is equal to the range [first2, first2 + (last1 - first1)), and false otherwise.
// Two ranges are considered equal if they have the same number of elements and, for every iterator i in the range [first1,last1), 

    /*1*/ template< class InputIt1, class InputIt2 >
    bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ){
        for (; first1 != last1; ++first1, ++first2){
            if (!(*first1 == *first2)) {
                return false;
            }
        }
        return true;
    }
    // /*3*/ template< class InputIt1, class InputIt2, class BinaryPredicate >
    // bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p ){
    //     for (; first1 != last1; ++first1, ++first2) {
    //         if (!p(*first1, *first2)) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }

// --------------------------------------- std::pair and std::make_pair()
    template< class T1, class T2> 
    struct pair{
    // Member types
        typedef T1  first_type;
        typedef T2  second_type;
    // Member objects
        first_type  first;
        second_type second;
    // Member functions
        pair()                          : first(), second(){}
        pair(const T1& x, const T2& y)  : first(x), second(y){}
        // pair(const T1& x,  T2& y)       : first(x), second(y){}
        pair(const pair & p)            : first(p.first), second(p.second){}

        template< class U1, class U2 >
        pair(const pair<U1, U2>& p)     : first(p.first), second(p.second){}
        
        pair&   operator=(const pair& rhs){
            this->first = rhs.first;
            this->second = rhs.second;
            return (*this);
        }
    };
    // Non-member functions
    template <class T1, class T2>
    bool    operator==(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return lhs.first==rhs.first && lhs.second==rhs.second; 
    }
    template <class T1, class T2>
    bool    operator!=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return !(lhs==rhs);
    }
    template <class T1, class T2>
    bool    operator<(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); ;
    }
    template <class T1, class T2>
    bool    operator<=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return !(rhs<lhs);
    }
    template <class T1, class T2>
    bool    operator>(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return rhs<lhs;
    }
    template <class T1, class T2>
    bool    operator>=(const pair<T1, T2>&lhs, const pair<T1, T2>&rhs){
        return !(lhs<rhs);
    }
    template< class T1, class T2 >
    ft::pair<T1, T2>    make_pair( T1 t, T2 u ){
        return (ft::pair<T1, T2>(t, u));
    }
	template< class T >
	struct is_pair :  public false_type{};

	template< class T1 , class T2 >
	struct is_pair< ft::pair< T1 , T2 > > :  public true_type{};

}

#endif // UTILS_HPP
// ============================================================================<<utils.hpp============================================================================
