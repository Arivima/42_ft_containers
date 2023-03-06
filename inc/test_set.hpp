/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:31 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 16:07:16 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>test_vector.hpp============================================================================
#ifndef TEST_SET_HPP
#define TEST_SET_HPP

/// INCLUDES
    #include "header.hpp"
    #include "compilation.hpp"

    #include <memory>
    #include <locale>

/// FUNCTIONS
    void testAllSet();

template <class set_type>
void    ftSetPrint(set_type *my_set)
{
    std::cout << MAGENTA "Printing Set "<< "| size: " << my_set->size() << std::endl;
    typename set_type::iterator begin = my_set->begin();
    typename set_type::iterator end = my_set->end();

    if (begin == end)
        std::cout << "Empty Set" << std::endl;
    for (; begin != end; begin++)
        std::cout<< "|" << (*begin);
    std::cout<< "|" RESET << std::endl;;
}

template <class set_type, class key_type >
void    ftFillSet(set_type * my_set, const ft::vector< key_type> & data_key)
{
    int i = 0;
    int n_loops = 100;
    int range_max = 10;
    std::cout << YELLOW "Filling set with " << n_loops << " random values from 0/null to " << range_max << RESET << std::endl;
    while (i < n_loops) {
        int rand = std::rand() % range_max;
        key_type     key = data_key[val1] * rand;
        rand = std::rand() % range_max;
        my_set->insert(key);
        i++;
    }    
    ftSetPrint<set_type>(my_set);
}


template <class set_type, class key_type>
void ftSetBasics(const ft::vector< key_type> & data_key){
    printTitle("TESTING BASICS", "General", LVL1, START);
    
    //* Basics
    // (constructor)    | constructs the set | Default, Range, Copy
    // (destructor)     | destructs the set
    printTitle("Testing Constructor", "General", LVL2, START);
        std::cout << "Default" << std::endl;    /*Default*/ set_type		my_set;                                     ftSetPrint<set_type>(&my_set);
        ftFillSet<set_type, key_type>(&my_set, data_key);
        std::cout << "Copy" << std::endl;       /*Copy*/    set_type		my_setCpy(my_set);                          ftSetPrint<set_type>(&my_setCpy);
        std::cout << "Range" << std::endl;      /*Range*/   set_type		my_setRange(my_set.begin(), my_set.end());  ftSetPrint<set_type>(&my_setRange);
    
    // operator=        | assigns values to the container
    printTitle("Testing operator=", "General", LVL2, START);
        /*Default*/ set_type		my_setEmpty;
        std::cout << "Before" << std::endl; ftSetPrint<set_type>(&my_setEmpty); ftSetPrint<set_type>(&my_setRange);
        /* = */     my_setEmpty = my_setRange;
        std::cout << "After" << std::endl; ftSetPrint<set_type>(&my_setEmpty); ftSetPrint<set_type>(&my_setRange);
    
    // get_allocator    | returns the associated allocator

    printTitle("testing basics", "General", LVL1, END);
}
template <class set_type, class key_type>
void ftSetIterators(set_type & my_set, const ft::vector< key_type> & ){
//* Iterators
// begin | returns an iterator to the beginning
// end | returns an iterator to the end
// rbegin | returns a reverse iterator to the beginning
// rend | returns a reverse iterator to the end
    printTitle("TESTING ITERATORS", "General", LVL1, START);
    {
        printTitle("Testing begin()", "General", LVL2, START);
        ftSetPrint<set_type>(&my_set);
        typename set_type::iterator   it = my_set.begin();
        typename set_type::iterator   itcpy(it);
        typename set_type::iterator   itcpy2;
        for (int i = 0; i < 10; i++) {
            std::cout << "++it | " << i << " | " << (*it)<< std::endl;
            ++it;
        }
        for (int i = 9; i >= 0; i--) {
            --it;
            std::cout << "--it | " << i << " | " << (*it)<< std::endl;
        }
        std::cout << "it is " << (*it);
        std::cout << " | itcpy2 is empty " << std::endl;
        itcpy2 = it;
        std::cout << "itcpy2 = it; " << std::endl;
        std::cout << "it is " << (*it);
        std::cout << " | itcpy2 is " << (*itcpy2)<< std::endl;
        std::cout << "itcpy2 == it: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != it: " << (itcpy2 != it) << std::endl;
        std::cout << "itcpy2 == itcpy: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != itcpy: " << (itcpy2 != it) << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << "it++ | " << i << " | " << (*itcpy)<< std::endl;
            itcpy++;
        }
        for (int i = 9; i >= 0; i--) {
            itcpy--;
            std::cout << "it-- | " << i << " | " << (*itcpy)<< std::endl;
        }
    }
    {
        printTitle("Testing end()", "General", LVL2, START);
        typename set_type::iterator   end = my_set.end();
        typename set_type::iterator   it;
        end--;

        std::cout << "end -- : " << (*end)<< std::endl;
        int i = 0;
        for (it = my_set.begin(); it != end ; it++) {
            std::cout << "| " << i++ << " : " << (*it);
        }
        if (it == end)
            std::cout << GREEN "\nit is end" RESET << std::endl;
        else
            std::cout << RED "\nit is not end" RESET << std::endl;
        printTitle("testing Reverse Iterators", "General", LVL1, END);
    }
    printTitle("TESTING REVERSE ITERATORS", "General", LVL1, START);
    {
        printTitle("Testing rbegin()", "General", LVL2, START);
        typename set_type::reverse_iterator   it = my_set.rbegin();
        typename set_type::reverse_iterator   itcpy(it);
        typename set_type::reverse_iterator   itcpy2;
        for (int i = 0; i < 10; i++) {
            std::cout << "++it | " << i << " | " << (*it)<< std::endl;
            ++it;
        }
        for (int i = 9; i >= 0; i--) {
            --it;
            std::cout << "--it | " << i << " | " << (*it)<< std::endl;
        }
        std::cout << "it is " << (*it);
        std::cout << " | itcpy2 is empty" << std::endl;
        itcpy2 = it;
        std::cout << "itcpy2 = it; " << std::endl;
        std::cout << "it is " << (*it);
        std::cout << " | itcpy2 is " << (*itcpy2)<< std::endl;
        std::cout << "itcpy2 == it: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != it: " << (itcpy2 != it) << std::endl;
        std::cout << "itcpy2 == itcpy: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != itcpy: " << (itcpy2 != it) << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << "it++ | " << i << " | " << (*itcpy)<< std::endl;
            itcpy++;
        }
        for (int i = 9; i >= 0; i--) {
            itcpy--;
            std::cout << "it-- | " << i << " | " << (*itcpy)<< std::endl;
        }
    }
    {
        printTitle("Testing rend()", "General", LVL2, START);
        typename set_type::reverse_iterator   end = my_set.rend();
        typename set_type::reverse_iterator   it;

        end--;
        std::cout << "end -- : " << (*end)<< std::endl;

        int i = 0;
        for (it = my_set.rbegin(); it != end ; it++) {
            std::cout << "| " << i++ << " | " << (*it);
        }
        if (it == end)
            std::cout << GREEN "\nit is end" RESET << std::endl;
        else
            std::cout << RED "\nit is not end" RESET << std::endl;
    }
    printTitle("testing Reverse Iterators", "General", LVL1, END);
}

template <class set_type, class key_type>
void ftSetCapacity(set_type & my_set, const ft::vector< key_type> & ){
//* Capacity
// empty | checks whether the container is empty
// size | returns the number of elements
// max_size | returns the maximum possible number of elements
    printTitle("TESTING CAPACITY", "General", LVL1, START);
    {
        printTitle("Testing Capacity functions : Empty, Size, Max_size", "General", LVL2, START);
        try {
            set_type numbers;
            std::cout << std::boolalpha;
            std::cout << "Initially, numbers.empty(): " << numbers.empty() << std::endl;
            std::cout << "Initially, numbers.size(): " << numbers.size() << std::endl;
            numbers.insert(value1);
            std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << std::endl;
            std::cout << "After adding elements, numbers.size(): " << numbers.size() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }             
        std::cout << "Printing TREE"<< std::endl; ftSetPrint<set_type>(&my_set);
    }     
    printTitle("testing Capacity", "General", LVL1, END);
}

template <class set_type, class key_type>
void ftSetModifiers(set_type & my_set, const ft::vector< key_type> & data_key){
    printTitle("TESTING CAPACITY", "General", LVL1, START);
//* Modifiers
// clear | clears the contents
        printTitle("Testing clear()", "General", LVL2, START);
        my_set.clear();
        std::cout << my_set.size() << std::endl;
// insert | inserts elements or nodes (since C++17)
        printTitle("Testing insert()", "General", LVL2, START);
        std::cout << BMAGENTA "1. Value" RESET << std::endl;
        {
            typename set_type::iterator it;
            ft::pair<typename set_type::iterator, bool> ret;
            ftSetPrint<set_type>(&my_set);
            std::cout << "Non existent" << std::endl;        
            ret = my_set.insert(value2);
            it = ret.first;
            ftSetPrint<set_type>(&my_set);
            std::cout << "it: " << (*it);        
            std::cout << " | ret: " << ret.second << std::endl;
            std::cout << "already existing" << std::endl;        
            ret = my_set.insert(value2);
            it = ret.first;
            ftSetPrint<set_type>(&my_set);
            std::cout << "it: " << (*it);        
            std::cout << " | ret: " << ret.second << std::endl;        
        }
        std::cout << BMAGENTA "2. Hint" RESET << std::endl;
        {
            ftSetPrint<set_type>(&my_set);
            typename set_type::iterator hint = my_set.end(); hint--;
            typename set_type::iterator ret;
            ret = my_set.insert(hint, value2);
            std::cout << "it: " << (*ret)<< std::endl;        
            ftSetPrint<set_type>(&my_set);
        }
        std::cout << BMAGENTA "3. Range" RESET << std::endl;
        {
            std::cout << "set 1" << std::endl;        
            ftSetPrint<set_type>(&my_set);
            std::cout << "set 2" << std::endl;        
            set_type		my_setcpy;
            ftFillSet<set_type, key_type>(&my_setcpy, data_key);
            typename set_type::iterator begin = my_setcpy.begin();
            typename set_type::iterator end = my_setcpy.end();
            std::cout << "set 1 + 2" << std::endl;        
            my_set.insert(begin, end);
            ftSetPrint<set_type>(&my_set);
        }
        //TODO functions are not protected aginst invalid range or inverted range => for endless loop
        // std::cout << BMAGENTA "3. Range" RESET << std::endl;
        // try {
        //     std::cout << "set 1" << std::endl;        
        //     ftSetPrint<set_type>(&my_set);
        //     std::cout << "set 2" << std::endl;        
        //     set_type		my_setcpy;
        //     ftFillSet<set_type, key_type>(&my_setcpy);
        //     typename set_type::iterator end = my_setcpy.begin();
        //     typename set_type::iterator begin = my_setcpy.end();
        //     std::cout << "set 1 + 2" << std::endl;        
        //     my_set.insert(begin, end);
        //     ftSetPrint<set_type>(&my_set);
        // }
        // catch (const std::exception &e) {
        //     std::cerr << e.what() << '\n';
        // }  
        // erase | erases elements
        printTitle("Testing erase()", "General", LVL2, START);
        std::cout << BMAGENTA "1. single iterator" RESET << std::endl;
        {
            set_type my_setcpy(my_set);
            std::cout << "Set before : " << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
            // erase min
            typename set_type::iterator it = my_setcpy.begin();
            std::cout << "erase min | trying to erase : " << (*it)<< " | ret : " << (*(my_setcpy.erase(it)))<< std::endl;
            std::cout << "Set after : " << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
            // erase middle
            it = my_setcpy.begin();
            for (size_t i = 0; i <= my_setcpy.size() / 2 ; i++)
                it++;
            std::cout << "erase middle | trying to erase : " << (*it)<< " | ret : " << (*(my_setcpy.erase(it)))<< std::endl;
            std::cout << "Set after : " << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
            // erase max
            it = my_setcpy.end();
            it--;
            std::cout << "erase max | trying to erase : " << (*it)<< " | ret : " << (*(my_setcpy.erase(it)))<< std::endl;
            std::cout << "Set after : " << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
        }
        std::cout << BMAGENTA "2. range iterator" RESET << std::endl;
        {
            set_type my_setcpy(my_set);
            ftSetPrint<set_type>(&my_setcpy);
            typename set_type::iterator it = my_setcpy.begin();
            for (size_t i = 0; i <= my_setcpy.size() / 3 ; i++)
                it++;
            std::cout << "trying to erase from : " << (*it)<< " to end" << std::endl;
            typename set_type::iterator ret  = my_setcpy.erase(it, my_setcpy.end());
            std::cout << "ret == end ? " << (ret == my_setcpy.end()) << std::endl; 
            ftSetPrint<set_type>(&my_setcpy);
        }
        {
            std::cout << std::endl;
            set_type my_setcpy(my_set);
            std::cout << "Set before : " << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
            typename set_type::iterator it = my_setcpy.begin();
            for (size_t i = 0; i <= my_setcpy.size() / 4 ; i++)
                it++;
            typename set_type::iterator start = it;
            for (size_t i = 0; i <= my_setcpy.size() / 4 ; i++)
                it++;
            std::cout << "trying to erase from : " << (*start)<< " to " << (*it)<< std::endl;
            typename set_type::iterator ret  = my_setcpy.erase(start, it);
            std::cout << "ret : " << (*ret)<< std::endl;
            std::cout << "Set after : " << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
        }
        std::cout << BMAGENTA "3. single key" RESET << std::endl;
        {
            set_type my_setcpy(my_set);
            ftSetPrint<set_type>(&my_setcpy);
            typename set_type::iterator it = my_setcpy.begin();
            for (size_t i = 0; i <= my_setcpy.size() / 2 ; i++)
                it++;
            std::cout << my_setcpy.erase((*it)) << std::endl;
            ftSetPrint<set_type>(&my_setcpy);
        }
// swap | swaps the contents
        printTitle("Testing swap()", "General", LVL2, START);
        {
            set_type my_setcpy;
            ftSetPrint<set_type>(&my_set);
            ftSetPrint<set_type>(&my_setcpy);
            my_setcpy.swap(my_set);
            ftSetPrint<set_type>(&my_set);
            ftSetPrint<set_type>(&my_setcpy);
// Non member function
// std::swap(std::set) | specializes the std::swap algorithm (function template)
        printTitle("Testing ft::swap()", "General", LVL2, START);
            ftSetPrint<set_type>(&my_set);
            ftSetPrint<set_type>(&my_setcpy);
            ft::swap(my_set, my_setcpy);
            ftSetPrint<set_type>(&my_set);
            ftSetPrint<set_type>(&my_setcpy);
        }
    printTitle("testing Modifiers", "General", LVL1, END);
}

template <class set_type, class key_type>
void ftSetLookup(set_type & my_set, const ft::vector< key_type> & ){
    printTitle("TESTING LOOKUP", "General", LVL1, START);
//* Lookup
// count | returns the number of elements matching specific key
        printTitle("Testing count()", "General", LVL2, START);
        {
            std::cout << "count key : " << my_set.count(value1) << std::endl;;
            std::cout << "count key : " << my_set.count(value2) << std::endl;;
        }
// find | finds element with specific key
        printTitle("Testing find()", "General", LVL2, START);
        {
            typename set_type::iterator it = my_set.find(value1);
            typename set_type::iterator it2 = my_set.find(value2);
            std::cout << (*it)<< std::endl;
            std::cout << (it == my_set.end()) << std::endl;
            std::cout << (it2 == my_set.end()) << std::endl;
        }
// equal_range |  returns range of elements matching a specific key
// lower_bound | returns an iterator to the first element not less than the given key
        printTitle("Testing lower_bound()", "General", LVL2, START);
        {
            set_type set2;
            
            int i = 0;
            int n_loops = 10;
            int range_max = 20;
            std::cout << YELLOW "Filling set with " << n_loops << " random values from 0/null to " << range_max << RESET << std::endl;
            while (i < n_loops) {
                int rand = std::rand() % range_max;
                key_type key = val1 * rand;
                rand = std::rand() % range_max;
                set2.insert(key);
                i++;
            }    
            ftSetPrint<set_type>(&set2);

            for (int j = 0; j < 20; j++)
                std::cout << "Testing " << j << ": " << (*(set2.lower_bound(j)))<< std::endl;
            
            std::cout << "Testing " << -2 << ": " << (*(set2.lower_bound(-2)))<< std::endl;
            std::cout << "Testing " << 21 << ": " << (*(set2.lower_bound(21)))<< std::endl;


        }
// upper_bound | returns an iterator to the first element greater than the given key
        printTitle("Testing upper_bound()", "General", LVL2, START);
        {
            set_type set2;
            
            int i = 0;
            int n_loops = 10;
            int range_max = 20;
            std::cout << YELLOW "Filling set with " << n_loops << " random values from 0/null to " << range_max << RESET << std::endl;
            while (i < n_loops) {
                int rand = std::rand() % range_max;
                key_type key = val1 * rand;
                rand = std::rand() % range_max;
                set2.insert(key);
                i++;
            }    
            ftSetPrint<set_type>(&set2);

            for (int j = 0; j < 20; j++)
                std::cout << "Testing " << j << ": " << (*(set2.upper_bound(j)))<< std::endl;

            std::cout << "Testing " << -2 << ": " << (*(set2.upper_bound(-2)))<< std::endl;
            std::cout << "Testing " << 21 << ": " << (*(set2.upper_bound(21)))<< std::endl;
        }
    printTitle("testing Lookup", "General", LVL1, END);
}

template <class set_type, class key_type>
void ftSetOperators(set_type & my_set, const ft::vector< key_type> & ){
    printTitle("TESTING OPERATORS", "General", LVL1, START);
    // Comparison operators ==, !=, <, <=, >, >=
    {
        set_type LHS(my_set);
        set_type RHS(LHS);

        std::cout << std::boolalpha;

        std::cout << CYAN  << "Compare equal containers" RESET << std::endl;
        ftSetPrint<set_type>(&LHS);
        ftSetPrint<set_type>(&RHS);

        std::cout << "LHS == RHS should return true  | " ; setStreamColor((LHS == RHS), true);  std::cout <<  (LHS == RHS) << RESET << std::endl;
        std::cout << "LHS != RHS should return false | " ; setStreamColor((LHS != RHS), false); std::cout <<  (LHS != RHS) << RESET << std::endl;
        std::cout << "LHS <  RHS should return false | " ; setStreamColor((LHS <  RHS), false); std::cout <<  (LHS <  RHS) << RESET << std::endl;
        std::cout << "LHS <= RHS should return true  | " ; setStreamColor((LHS <= RHS), true);  std::cout <<  (LHS <= RHS) << RESET << std::endl;
        std::cout << "LHS >  RHS should return false | " ; setStreamColor((LHS >  RHS), false); std::cout <<  (LHS >  RHS) << RESET << std::endl;
        std::cout << "LHS >= RHS should return true  | " ; setStreamColor((LHS >= RHS), true);  std::cout <<  (LHS >= RHS) << RESET << std::endl;

        if (std::is_arithmetic<key_type>::value == true)
        {
            std::cout << std::endl;
            std::cout << CYAN  << "Compare non equal containers (VALUE)" RESET << std::endl;
            RHS = LHS;
            LHS.insert(100);
            RHS.insert(100);
            ftSetPrint<set_type>(&LHS);
            ftSetPrint<set_type>(&RHS);
            std::cout << "LHS == RHS should return false | " ; setStreamColor((LHS == RHS), false); std::cout <<  (LHS == RHS) << RESET << std::endl;
            std::cout << "LHS != RHS should return true  | " ; setStreamColor((LHS != RHS), true); std::cout <<  (LHS != RHS) << RESET << std::endl;
            std::cout << std::endl;
            std::cout << "LHS <  RHS should return false | " ; setStreamColor((LHS <  RHS), false); std::cout <<  (LHS <  RHS) << RESET << std::endl;
            std::cout << "LHS <= RHS should return false | " ; setStreamColor((LHS <= RHS), false); std::cout <<  (LHS <= RHS) << RESET << std::endl;
            std::cout << "LHS >  RHS should return true  | " ; setStreamColor((LHS >  RHS), true); std::cout <<  (LHS >  RHS) << RESET << std::endl;
            std::cout << "LHS >= RHS should return true  | " ; setStreamColor((LHS >= RHS), true); std::cout <<  (LHS >= RHS) << RESET << std::endl;
            std::cout << std::endl;
            std::cout << "RHS <  LHS should return true  | " ; setStreamColor((RHS <  LHS), true); std::cout <<  (RHS <  LHS) << RESET << std::endl;
            std::cout << "RHS <= LHS should return true  | " ; setStreamColor((RHS <= LHS), true); std::cout <<  (RHS <= LHS) << RESET << std::endl;
            std::cout << "RHS >  LHS should return false | " ; setStreamColor((RHS >  LHS), false); std::cout <<  (RHS >  LHS) << RESET << std::endl;
            std::cout << "RHS >= LHS should return false | " ; setStreamColor((RHS >= LHS), false); std::cout <<  (RHS >= LHS) << RESET << std::endl;
        }

        std::cout << std::endl;
        std::cout << CYAN  << "Compare non equal containers (SIZE)" RESET << std::endl;
        RHS = LHS;
        RHS.erase((*(RHS.begin())));
        ftSetPrint<set_type>(&LHS);
        ftSetPrint<set_type>(&RHS);
        std::cout << "LHS == RHS should return false | " ; setStreamColor((LHS == RHS), false); std::cout <<  (LHS == RHS) << RESET << std::endl;
        std::cout << "LHS != RHS should return true  | " ; setStreamColor((LHS != RHS), true); std::cout <<  (LHS != RHS) << RESET << std::endl;
        std::cout << std::endl;
        std::cout << "LHS <  RHS should return false | " ; setStreamColor((LHS <  RHS), false); std::cout <<  (LHS <  RHS) << RESET << std::endl;
        std::cout << "LHS <= RHS should return false | " ; setStreamColor((LHS <= RHS), false); std::cout <<  (LHS <= RHS) << RESET << std::endl;
        std::cout << "LHS >  RHS should return true  | " ; setStreamColor((LHS >  RHS), true); std::cout <<  (LHS >  RHS) << RESET << std::endl;
        std::cout << "LHS >= RHS should return true  | " ; setStreamColor((LHS >= RHS), true); std::cout <<  (LHS >= RHS) << RESET << std::endl;
        std::cout << std::endl;
        std::cout << "RHS <  LHS should return true  | " ; setStreamColor((RHS <  LHS), true); std::cout <<  (RHS <  LHS) << RESET << std::endl;
        std::cout << "RHS <= LHS should return true  | " ; setStreamColor((RHS <= LHS), true); std::cout <<  (RHS <= LHS) << RESET << std::endl;
        std::cout << "RHS >  LHS should return false | " ; setStreamColor((RHS >  LHS), false); std::cout <<  (RHS >  LHS) << RESET << std::endl;
        std::cout << "RHS >= LHS should return false | " ; setStreamColor((RHS >= LHS), false); std::cout <<  (RHS >= LHS) << RESET << std::endl;

        printTitle("operator ==,!=, <,<=,>,>= ", "", LVL3, END);

        printTitle("testing operators", "", LVL2, END);
    }
    printTitle("testing Operators", "General", LVL1, END);
}


template <class set_type, class key_type>
void ftTestSet(const ft::vector< key_type> & data_key){
///* Set
    printTitle("START TEST SET", "General", LVL0, START);

    set_type    my_set;
    ftFillSet<set_type, key_type>(&my_set, data_key);
    std::srand(0);

    ///* Member functions
    printTitle("TESTING MEMBER FUNCTIONS", "", LVL1, START);
        ftSetBasics<set_type, key_type>(data_key);
        ftSetIterators<set_type, key_type>(my_set, data_key);
        ftSetCapacity<set_type, key_type>(my_set, data_key);
        ftSetModifiers<set_type, key_type>(my_set, data_key);
        ftSetLookup<set_type, key_type>(my_set, data_key);
    ///* Non-member functions
    printTitle("TESTING NON MEMBER FUNCTIONS", "", LVL1, START);
        ftSetOperators<set_type, key_type>(my_set, data_key);

    printTitle("END TEST SET", "General", LVL0, END);
    return ;
}

#endif
// ============================================================================<<test_vector.hpp============================================================================
