/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:28 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 15:06:09 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>test_vector.hpp============================================================================
#ifndef TEST_MAP_HPP
#define TEST_MAP_HPP

/// INCLUDES
    #include "header.hpp"
    #include "compilation.hpp"

    #include <memory>
    #include <locale>

/// NON TEMPLATED FUNCTIONS
    void testAllMap();

/// TEMPLATED FUNCTIONS


template <class map_type>
void    ftMapPrint(map_type* my_map)
{
    std::cout << MAGENTA "Printing Map "<< "| size: " << my_map->size() << std::endl;
    typename map_type::iterator begin = my_map->begin();
    typename map_type::iterator end = my_map->end();

    if (begin == end)
        std::cout << "Empty Map" << std::endl;
    for (; begin != end; begin++)
        std::cout<< "|" << (*begin).first;
    std::cout<< "|" RESET << std::endl;;
}

template <class map_type, class key_type, class mapped_type >
void    ftFillMap(map_type * my_map, const ft::vector< key_type> & data_key, const mapped_type & )
{
    int i = 0;
    int n_loops = 100;
    int range_max = 10;
    std::cout << YELLOW "Filling map with " << n_loops << " random values from 0/null to " << range_max << RESET << std::endl;
    while (i < n_loops) {
        int rand = std::rand() % range_max;
        key_type     key = data_key[val1] * rand;
        rand = std::rand() % range_max;
        mapped_type  value = data_key[val1] * rand;
        my_map->insert(ft::make_pair<key_type, mapped_type>(key, value));
        i++;
    }    
    ftMapPrint<map_type>(my_map);
}



template <class map_type, class key_type, class mapped_type >
void ftMapBasics(const ft::vector< key_type> & data_key, const mapped_type & data_value){
    printTitle("TESTING BASICS", "General", LVL1, START);
    
    //* Basics
    // (constructor)    | constructs the map | Default, Range, Copy
    // (destructor)     | destructs the map
    printTitle("Testing Constructor", "General", LVL2, START);
        std::cout << "Default" << std::endl;    /*Default*/ map_type		my_map;                                     ftMapPrint<map_type>(&my_map);
        ftFillMap<map_type, key_type, mapped_type>(&my_map, data_key, data_value);
        std::cout << "Copy" << std::endl;       /*Copy*/    map_type		my_mapCpy(my_map);                          ftMapPrint<map_type>(&my_mapCpy);
        std::cout << "Range" << std::endl;      /*Range*/   map_type		my_mapRange(my_map.begin(), my_map.end());  ftMapPrint<map_type>(&my_mapRange);
    
    // operator=        | assigns values to the container
    printTitle("Testing operator=", "General", LVL2, START);
        /*Default*/ map_type    my_mapEmpty;
        std::cout << "Before" << std::endl; ftMapPrint<map_type>(&my_mapEmpty); ftMapPrint<map_type>(&my_mapRange);
        /* = */     my_mapEmpty = my_mapRange;
        std::cout << "After" << std::endl; ftMapPrint<map_type>(&my_mapEmpty); ftMapPrint<map_type>(&my_mapRange);
    
    printTitle("testing basics", "General", LVL1, END);
}

template <class map_type, class key_type, class mapped_type >
void ftMapElementAccess(map_type & my_map, const ft::vector< key_type> & , const mapped_type & ){
    printTitle("TESTING ELEMENT ACCESS", "General", LVL1, START);
    //* Element access
    // at | access specified element with bounds checking
    // operator[] | access or insert specified element
    {
        printTitle("Testing at()", "General", LVL2, START); 
        try {
            for (typename map_type::iterator it = my_map.begin(); it != my_map.end(); it++)
                std::cout << (*it).first << " : " << my_map.at((*it).first ) << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }             
    }
    {
        printTitle("Testing operator[]", "General", LVL2, START);
        try {
            for (typename map_type::iterator it = my_map.begin(); it != my_map.end(); it++)
                std::cout << (*it).first << " : " << my_map[(*it).first] << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
        }             
    }
    printTitle("testing element access", "General", LVL1, END);
}


template <class map_type, class key_type, class mapped_type >
void ftMapIterators(map_type & my_map, const ft::vector< key_type> & , const mapped_type & ){
//* Iterators
// begin | returns an iterator to the beginning
// end | returns an iterator to the end
// rbegin | returns a reverse iterator to the beginning
// rend | returns a reverse iterator to the end
    printTitle("TESTING ITERATORS", "General", LVL1, START);
    {
        printTitle("Testing begin()", "General", LVL2, START);
        ftMapPrint<map_type>(&my_map);
        typename map_type::iterator   it = my_map.begin();
        typename map_type::iterator   itcpy(it);
        typename map_type::iterator   itcpy2;
        for (int i = 0; i < 10; i++) {
            std::cout << "++it | " << i << " | " << (*it).first << std::endl;
            ++it;
        }
        for (int i = 9; i >= 0; i--) {
            --it;
            std::cout << "--it | " << i << " | " << (*it).first << std::endl;
        }
        std::cout << "it is " << (*it).first;
        std::cout << " | itcpy2 is empty " << std::endl;
        itcpy2 = it;
        std::cout << "itcpy2 = it; " << std::endl;
        std::cout << "it is " << (*it).first;
        std::cout << " | itcpy2 is " << (*itcpy2).first << std::endl;
        std::cout << "itcpy2 == it: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != it: " << (itcpy2 != it) << std::endl;
        std::cout << "itcpy2 == itcpy: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != itcpy: " << (itcpy2 != it) << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << "it++ | " << i << " | " << (*itcpy).first << std::endl;
            itcpy++;
        }
        for (int i = 9; i >= 0; i--) {
            itcpy--;
            std::cout << "it-- | " << i << " | " << (*itcpy).first << std::endl;
        }
    }
    {
        printTitle("Testing end()", "General", LVL2, START);
        typename map_type::iterator   end = my_map.end();
        typename map_type::iterator   it;
        end--;

        std::cout << "end -- : " << (*end).first << std::endl;
        int i = 0;
        for (it = my_map.begin(); it != end ; it++) {
            std::cout << "| " << i++ << " : " << (*it).first;
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
        typename map_type::reverse_iterator   it = my_map.rbegin();
        typename map_type::reverse_iterator   itcpy(it);
        typename map_type::reverse_iterator   itcpy2;
        for (int i = 0; i < 10; i++) {
            std::cout << "++it | " << i << " | " << (*it).first << std::endl;
            ++it;
        }
        for (int i = 9; i >= 0; i--) {
            --it;
            std::cout << "--it | " << i << " | " << (*it).first << std::endl;
        }
        std::cout << "it is " << (*it).first;
        std::cout << " | itcpy2 is empty" << std::endl;
        itcpy2 = it;
        std::cout << "itcpy2 = it; " << std::endl;
        std::cout << "it is " << (*it).first;
        std::cout << " | itcpy2 is " << (*itcpy2).first << std::endl;
        std::cout << "itcpy2 == it: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != it: " << (itcpy2 != it) << std::endl;
        std::cout << "itcpy2 == itcpy: " << (itcpy2 == it) << std::endl;
        std::cout << "itcpy2 != itcpy: " << (itcpy2 != it) << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << "it++ | " << i << " | " << (*itcpy).first << std::endl;
            itcpy++;
        }
        for (int i = 9; i >= 0; i--) {
            itcpy--;
            std::cout << "it-- | " << i << " | " << (*itcpy).first << std::endl;
        }
    }
    {
        printTitle("Testing rend()", "General", LVL2, START);
        typename map_type::reverse_iterator   end = my_map.rend();
        typename map_type::reverse_iterator   it;

        end--;
        std::cout << "end -- : " << (*end).first << std::endl;

        int i = 0;
        for (it = my_map.rbegin(); it != end ; it++) {
            std::cout << "| " << i++ << " | " << (*it).first;
        }
        if (it == end)
            std::cout << GREEN "\nit is end" RESET << std::endl;
        else
            std::cout << RED "\nit is not end" RESET << std::endl;
    }
    printTitle("testing Reverse Iterators", "General", LVL1, END);
    {
        ftMapPrint<map_type>(&my_map);
        
        std::cout << BRED "Testing iterator invalidation" RESET << std::endl;
        typename map_type::iterator   it = my_map.begin();
        typename map_type::iterator   itcpy(it);
        
        for (size_t i = 0; i <= my_map.size()/2; i++)
            it++;

        std::cout << "Erasing" <<  (*it).first << std::endl;

        my_map.erase((*it).first);

        for (;itcpy!= my_map.end(); itcpy++)
            std::cout << (*itcpy).first << std::endl;
    }
}

template <class map_type, class key_type, class mapped_type >
void ftMapCapacity(map_type & my_map, const ft::vector< key_type> & data_key, const mapped_type & data_value){
//* Capacity
// empty | checks whether the container is empty
// size | returns the number of elements
// max_size | returns the maximum possible number of elements
    printTitle("TESTING CAPACITY", "General", LVL1, START);
    {
        printTitle("Testing Capacity functions : Empty, Size, Max_size", "General", LVL2, START);
        try {
            map_type numbers;
            std::cout << std::boolalpha;
            std::cout << "Max_size: " << numbers.max_size() << std::endl;
            std::cout << "Initially, numbers.empty(): " << numbers.empty() << std::endl;
            std::cout << "Initially, numbers.size(): " << numbers.size() << std::endl;
            numbers.insert(ft::make_pair<key_type, mapped_type>(data_key[value1], data_value));
            std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << std::endl;
            std::cout << "After adding elements, numbers.size(): " << numbers.size() << std::endl;
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }             
        std::cout << "Printing TREE"<< std::endl; ftMapPrint<map_type>(&my_map);
    }     
    printTitle("testing Capacity", "General", LVL1, END);
}

template <class map_type, class key_type, class mapped_type >
void ftMapModifiers(map_type & my_map, const ft::vector< key_type> & data_key, const mapped_type & data_value){
    printTitle("TESTING CAPACITY", "General", LVL1, START);
//* Modifiers
// clear | clears the contents
        printTitle("Testing clear()", "General", LVL2, START);
        my_map.clear();
        std::cout << my_map.size() << std::endl;
// insert | inserts elements or nodes (since C++17)
        printTitle("Testing insert()", "General", LVL2, START);
        std::cout << BMAGENTA "1. Value" RESET << std::endl;
        {
            typename map_type::iterator it;
            ft::pair<typename map_type::iterator, bool> ret;
            ftMapPrint<map_type>(&my_map);
            std::cout << "Non existent" << std::endl;        
            ret = my_map.insert(ft::make_pair<key_type, mapped_type>(data_key[value1], data_value));
            it = ret.first;
            ftMapPrint<map_type>(&my_map);
            std::cout << "it: " << (*it).first;        
            std::cout << " | ret: " << ret.second << std::endl;
            std::cout << "already existing" << std::endl;        
            ret = my_map.insert(ft::make_pair<key_type, mapped_type>(data_key[value1], data_value));
            it = ret.first;
            ftMapPrint<map_type>(&my_map);
            std::cout << "it: " << (*it).first;        
            std::cout << " | ret: " << ret.second << std::endl;        
        }
        std::cout << BMAGENTA "2. Hint" RESET << std::endl;
        {
            ftMapPrint<map_type>(&my_map);
            typename map_type::iterator hint = my_map.end(); hint--;
            typename map_type::iterator ret;
            ret = my_map.insert(hint, ft::make_pair<key_type, mapped_type>(data_key[value1], data_value));
            std::cout << "it: " << (*ret).first << std::endl;        
            ftMapPrint<map_type>(&my_map);
        }
        std::cout << BMAGENTA "3. Range" RESET << std::endl;
        {
            std::cout << "map 1" << std::endl;        
            ftMapPrint<map_type>(&my_map);
            std::cout << "map 2" << std::endl;        
            map_type    my_mapcpy;
            ftFillMap<map_type, key_type, mapped_type>(&my_mapcpy, data_key, data_value);
            typename map_type::iterator begin = my_mapcpy.begin();
            typename map_type::iterator end = my_mapcpy.end();
            std::cout << "map 1 + 2" << std::endl;        
            my_map.insert(begin, end);
            ftMapPrint<map_type>(&my_map);
        }
        //TODO functions are not protected aginst invalid range or inverted range => for endless loop
        // std::cout << BMAGENTA "3. Range" RESET << std::endl;
        // try {
        //     std::cout << "map 1" << std::endl;        
        //     ftMapPrint<map_type>(&my_map);
        //     std::cout << "map 2" << std::endl;        
        //     Map		my_mapcpy;
        //     ftFillMap<map_type, key_type, mapped_type>(&my_mapcpy, data_key, data_value);
        //     typename map_type::iterator end = my_mapcpy.begin();
        //     typename map_type::iterator begin = my_mapcpy.end();
        //     std::cout << "map 1 + 2" << std::endl;        
        //     my_map.insert(begin, end);
        //     ftMapPrint<map_type>(&my_map);
        // }
        // catch (const std::exception &e) {
        //     std::cerr << e.what() << '\n';
        // }  
        // erase | erases elements
        printTitle("Testing erase()", "General", LVL2, START);
        std::cout << BMAGENTA "1. single iterator" RESET << std::endl;
        {
            map_type my_mapcpy(my_map);
            std::cout << "Map before : " << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
            // erase min
            typename map_type::iterator it = my_mapcpy.begin();
            std::cout << "erase min | trying to erase : " << (*it).first << " | ret : " << (*(my_mapcpy.erase(it))).first << std::endl;
            std::cout << "Map after : " << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
            // erase middle
            it = my_mapcpy.begin();
            for (size_t i = 0; i <= my_mapcpy.size() / 2 ; i++)
                it++;
            std::cout << "erase middle | trying to erase : " << (*it).first << " | ret : " << (*(my_mapcpy.erase(it))).first << std::endl;
            std::cout << "Map after : " << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
            // erase max
            it = my_mapcpy.end();
            it--;
            std::cout << "erase max | trying to erase : " << (*it).first << " | ret : " << (*(my_mapcpy.erase(it))).first << std::endl;
            std::cout << "Map after : " << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
        }
        std::cout << BMAGENTA "2. range iterator" RESET << std::endl;
        {
            map_type my_mapcpy(my_map);
            ftMapPrint<map_type>(&my_mapcpy);
            typename map_type::iterator it = my_mapcpy.begin();
            for (size_t i = 0; i <= my_mapcpy.size() / 3 ; i++)
                it++;
            std::cout << "trying to erase from : " << (*it).first << " to end" << std::endl;
            typename map_type::iterator ret  = my_mapcpy.erase(it, my_mapcpy.end());
            std::cout << "ret == end ? " << (ret == my_mapcpy.end()) << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
        }
        {
            std::cout << std::endl;
            map_type my_mapcpy(my_map);
            std::cout << "Map before : " << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
            typename map_type::iterator it = my_mapcpy.begin();
            for (size_t i = 0; i <= my_mapcpy.size() / 4 ; i++)
                it++;
            typename map_type::iterator start = it;
            for (size_t i = 0; i <= my_mapcpy.size() / 4 ; i++)
                it++;
            std::cout << "trying to erase from : " << (*start).first << " to " << (*it).first << std::endl;
            typename map_type::iterator ret  = my_mapcpy.erase(start, it);
            std::cout << "ret : " << (*ret).first << std::endl;
            std::cout << "Map after : " << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
        }
        std::cout << BMAGENTA "3. single key" RESET << std::endl;
        {
            map_type my_mapcpy(my_map);
            ftMapPrint<map_type>(&my_mapcpy);
            typename map_type::iterator it = my_mapcpy.begin();
            for (size_t i = 0; i <= my_mapcpy.size() / 2 ; i++)
                it++;
            std::cout << my_mapcpy.erase(my_mapcpy.at((*it).first)) << std::endl;
            ftMapPrint<map_type>(&my_mapcpy);
        }
// swap | swaps the contents
        printTitle("Testing swap()", "General", LVL2, START);
        {
            map_type my_mapcpy;
            ftMapPrint<map_type>(&my_map);
            ftMapPrint<map_type>(&my_mapcpy);
            my_mapcpy.swap(my_map);
            ftMapPrint<map_type>(&my_map);
            ftMapPrint<map_type>(&my_mapcpy);
// Non member function
// std::swap(std::map) | specializes the std::swap algorithm (function template)
        printTitle("Testing ft::swap()", "General", LVL2, START);
            ftMapPrint<map_type>(&my_map);
            ftMapPrint<map_type>(&my_mapcpy);
            ft::swap(my_map, my_mapcpy);
            ftMapPrint<map_type>(&my_map);
            ftMapPrint<map_type>(&my_mapcpy);
        }
    printTitle("testing Modifiers", "General", LVL1, END);
}

template <class map_type, class key_type, class mapped_type >
void ftMapLookup(map_type& my_map, const ft::vector< key_type> & data_key, const mapped_type & ){
    printTitle("TESTING LOOKUP", "General", LVL1, START);
//* Lookup
// count | returns the number of elements matching specific key
        printTitle("Testing count()", "General", LVL2, START);
        {
            std::cout << "count key : " << my_map.count(data_key[value1]) << std::endl;;
            std::cout << "count key : " << my_map.count(data_key[value2]) << std::endl;;
        }
// find | finds element with specific key
        printTitle("Testing find()", "General", LVL2, START);
        {
            typename map_type::iterator it = my_map.find(data_key[value1]);
            typename map_type::iterator it2 = my_map.find(data_key[value2]);
            std::cout << (*it).first << std::endl;
            std::cout << (it == my_map.end()) << std::endl;
            std::cout << (it2 == my_map.end()) << std::endl;
        }
// equal_range |  returns range of elements matching a specific key
// lower_bound | returns an iterator to the first element not less than the given key
        printTitle("Testing lower_bound()", "General", LVL2, START);
        {
            map_type map2;
            
            int i = 0;
            int n_loops = 10;
            int range_max = 20;
            std::cout << YELLOW "Filling map with " << n_loops << " random values from 0/null to " << range_max << RESET << std::endl;
            while (i < n_loops) {
                int rand = std::rand() % range_max;
                key_type key = data_key[val1] * rand;
                rand = std::rand() % range_max;
                mapped_type value = data_key[val1] * rand;
                map2.insert(ft::make_pair<key_type, mapped_type>(key, value));
                i++;
            }    
            ftMapPrint<map_type>(&map2);

            for (int j = 0; j < 20; j++)
                std::cout << "Testing " << j << ": " << (*(map2.lower_bound(j))).first << std::endl;
            
            std::cout << "Testing " << -2 << ": " << (*(map2.lower_bound(-2))).first << std::endl;
            std::cout << "Testing " << 21 << ": " << (*(map2.lower_bound(21))).first << std::endl;


        }
// upper_bound | returns an iterator to the first element greater than the given key
        printTitle("Testing upper_bound()", "General", LVL2, START);
        {
            map_type map2;
            
            int i = 0;
            int n_loops = 10;
            int range_max = 20;
            std::cout << YELLOW "Filling map with " << n_loops << " random values from 0/null to " << range_max << RESET << std::endl;
            while (i < n_loops) {
                int rand = std::rand() % range_max;
                key_type key = data_key[val1] * rand;
                rand = std::rand() % range_max;
                mapped_type value = data_key[val1] * rand;
                map2.insert(ft::make_pair<key_type, mapped_type>(key, value));
                i++;
            }    
            ftMapPrint<map_type>(&map2);

            for (int j = 0; j < 20; j++)
                std::cout << "Testing " << j << ": " << (*(map2.upper_bound(j))).first << std::endl;

            std::cout << "Testing " << -2 << ": " << (*(map2.upper_bound(-2))).first << std::endl;
            std::cout << "Testing " << 21 << ": " << (*(map2.upper_bound(21))).first << std::endl;
        }
    printTitle("testing Lookup", "General", LVL1, END);
}
template <class map_type, class key_type, class mapped_type >
void ftMapOperators(map_type& my_map, const ft::vector< key_type> & data_key, const mapped_type & data_value){
    printTitle("TESTING OPERATORS", "General", LVL1, START);
    // Comparison operators ==, !=, <, <=, >, >=
    {
        map_type LHS(my_map);
        map_type RHS(LHS);

        std::cout << std::boolalpha;

        std::cout << CYAN  << "Compare equal containers" RESET << std::endl;
        ftMapPrint<map_type>(&LHS);
        ftMapPrint<map_type>(&RHS);

        std::cout << "LHS == RHS should return true  | " ; setStreamColor((LHS == RHS), true);  std::cout <<  (LHS == RHS) << RESET << std::endl;
        std::cout << "LHS != RHS should return false | " ; setStreamColor((LHS != RHS), false); std::cout <<  (LHS != RHS) << RESET << std::endl;
        std::cout << "LHS <  RHS should return false | " ; setStreamColor((LHS <  RHS), false); std::cout <<  (LHS <  RHS) << RESET << std::endl;
        std::cout << "LHS <= RHS should return true  | " ; setStreamColor((LHS <= RHS), true);  std::cout <<  (LHS <= RHS) << RESET << std::endl;
        std::cout << "LHS >  RHS should return false | " ; setStreamColor((LHS >  RHS), false); std::cout <<  (LHS >  RHS) << RESET << std::endl;
        std::cout << "LHS >= RHS should return true  | " ; setStreamColor((LHS >= RHS), true);  std::cout <<  (LHS >= RHS) << RESET << std::endl;

        if (std::is_arithmetic<key_type>::value == true && std::is_arithmetic<mapped_type>::value == true )
        {
            std::cout << std::endl;
            std::cout << CYAN  << "Compare non equal containers (VALUE)" RESET << std::endl;
            RHS = LHS;
            LHS.insert(ft::make_pair<key_type, mapped_type>(data_key[value1], data_value));
            RHS.insert(ft::make_pair<key_type, mapped_type>(data_key[value1], data_key[value1]));
            ftMapPrint<map_type>(&LHS);
            ftMapPrint<map_type>(&RHS);
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
        RHS.erase((*(RHS.begin())).first);
        ftMapPrint<map_type>(&LHS);
        ftMapPrint<map_type>(&RHS);
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


template <class map_type, class key_type, class mapped_type >
void ftTestMap(ft::vector<key_type> & data_key, const mapped_type & data_value)
{
///* Map
    printTitle("START TEST MAP", "General", LVL0, START);

    map_type    my_map;
    ftFillMap<map_type, key_type, mapped_type>(&my_map, data_key, data_value);
    std::srand(0);

    ///* Member functions
    printTitle("TESTING MEMBER FUNCTIONS", "", LVL1, START);
        ftMapBasics<map_type, key_type, mapped_type>(data_key, data_value);
        ftMapElementAccess<map_type, key_type, mapped_type>(my_map, data_key, data_value);
        ftMapIterators<map_type, key_type, mapped_type>(my_map, data_key, data_value);
        ftMapCapacity<map_type, key_type, mapped_type>(my_map, data_key, data_value);
        ftMapModifiers<map_type, key_type, mapped_type>(my_map, data_key, data_value);
        ftMapLookup<map_type, key_type, mapped_type>(my_map, data_key, data_value);
    ///* Non-member functions
    printTitle("TESTING NON MEMBER FUNCTIONS", "", LVL1, START);
        ftMapOperators<map_type, key_type, mapped_type>(my_map, data_key, data_value);

    printTitle("END TEST MAP", "General", LVL0, END);
    return ;
}


#endif
// ============================================================================<<test_vector.hpp============================================================================
