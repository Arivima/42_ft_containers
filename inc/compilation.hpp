/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compilation.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:45:40 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 15:38:51 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>compilation.hpp============================================================================
#ifndef COMPILATION_HPP
# define COMPILATION_HPP

// INCLUSION AND NAMESPACE
    #if (COMPILE_MODE == 1)         //* std
        #include <vector>
        #include <map>
        #include <stack>
        #include <set>
        namespace ft = std;
        #define COMPILE_MODE_TXT "Testing STD"
    #else                           //* ft
        #include "utils.hpp"
        #include "vector.hpp"
        #include "map.hpp"
        #include "stack.hpp"
        #include "set.hpp"
        #define COMPILE_MODE_TXT "Testing FT"
    #endif

// templated functions
        template <class vector_type, class value_type>
        void FillVectorDataType(vector_type* data, value_type A, value_type B, value_type C, value_type D, value_type E, value_type F, value_type G, value_type H){
            data->push_back(A);
            data->push_back(B);
            data->push_back(C);
            data->push_back(D);
            data->push_back(E);
            data->push_back(F);
            data->push_back(G);
            data->push_back(H);
        }

// DEFINES (access to data)
        #define value1 0
        #define value2 1
        // test_iterators
        # define val1 2
        # define val2 3
        # define val3 4
        # define val4 5
        # define val5 6
        # define val6 7

#endif
// ============================================================================<<compilation.hpp============================================================================


    //* Type classification https://en.cppreference.com/w/cpp/language/type
        //* std::is_fundamental https://en.cppreference.com/w/cpp/language/types
//             void     std::is_void
//             std::nullptr_t   std::is_null_pointer
            //* std::is_arithmetic
                //* integral std::is_integral
//?                     /*OK*/  typedef char                
//                     /*NOK*/  typedef signed char         
//                     /*NOK*/  typedef unsigned char       
//                     /*NOK*/  typedef short               
//                     /*NOK*/  typedef unsigned short      
//?                     /*NOK*/  typedef int                 
//                     /*NOK*/  typedef unsigned int        
//                     /*NOK*/  typedef long                
//                     /*NOK*/  typedef unsigned long       
//                     /*NOK*/  typedef long long           
//                     /*NOK*/  typedef unsigned long long  
                //* floating point   std::is_floating_point
//?                     /*NOK*/  typedef float               
//?                     /*NOK*/  typedef double              
//                     /*NOK*/  typedef long double         
    // objects
//?         /*NOK*/  typedef std::string         
//         /*NOK*/  typedef ft::myClass      

        // compound types (see also std::is_compound):
            // reference types (see also std::is_reference):
            // pointer types (see also std::is_pointer):
            // pointer-to-member types (see also std::is_member_pointer):
            // array types (see also std::is_array);
            // function types (see also std::is_function);
            // enumeration types (see also std::is_enum);
            // class types:
                // non-union types (see also std::is_class);
                // union types (see also std::is_union)