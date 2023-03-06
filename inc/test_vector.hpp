/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:39 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 14:55:03 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>test_vector.hpp============================================================================
#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

/// INCLUDES
    #include "header.hpp"
    #include "compilation.hpp"

    // #include <vector>
    #include <memory>
    #include <locale>

/// Non templated functions
    void    testAllVector();

/// Templated functions
// ============================================================================>>UTILS============================================================================
template <class value_type>
void printval(value_type val)   {std::cout << val << " | ";};

template <class value_type>
void doubleval(value_type &val) {val *= 2;};

template <class vector_type> // FOR DEBUG
void printVector(std::string name, const vector_type &arr, bool)
{
    std::cout << "(print)\t" << std::left << std::setfill(' ') << std::setw(10) << name << "| ";
    std::cout << "s(" << arr.size() << "/" << arr.capacity()<< ") : " << std::endl;

    vector_type                 temp = arr;
    typename vector_type::iterator       it = temp.begin();

    int i = 0;
    while (it < temp.end())
    {
        std::cout << i++ << " | ";
        printval<typename vector_type::value_type>(*it);
        std::cout << std::endl;
        it++;
    }
    
    if (arr.begin() == arr.end())
        std::cout << "(empty)\t";
    std::cout << std::endl;
}

template <class vector_type>
void printVector(std::string name, const vector_type &arr)
{
    std::cout << "(print)\t" << std::left << std::setfill(' ') << std::setw(10) << name << "| ";
    std::cout << "s(" << arr.size() << "/" << arr.capacity()<< ") : " << std::endl;

    std::for_each(arr.begin(), arr.end(), printval<typename vector_type::value_type>);

    if (arr.begin() == arr.end())
        std::cout << "(empty)\t";
    std::cout << std::endl;
}

template <class vector_type>
void printVector(std::string name, ft::vector<vector_type> &arr)
{
    int i = 0;
    for (typename ft::vector<vector_type>::iterator it = arr.begin(); it != arr.end(); it++)
    {
        char c = 'A' + i;
        printVector<vector_type>(name + "_" + c, *it);
        i++;
    }
    if (arr.begin() == arr.end())
        std::cout << "(print)\t" << name << "(empty)\n";
}
// ============================================================================<<UTILS============================================================================


// ============================================================================>>ftVectorBasics============================================================================
template <class vector_type>
void ftVectorBasics(ft::vector<vector_type> *arr, const vector_type & data)
{
    printTitle("TESTING BASICS", "General", LVL1, START);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // Constructors
    // 1) Default constructor. Constructs an empty container with a default-constructed allocator.
    //      vector();
    // 2) Constructs an empty container with the given allocator alloc.
    //     explicit vector( const Allocator& alloc );
    // 3) Constructs the container with count copies of elements with value value.
    //     explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
    // 5) Constructs the container with the contents of the range [first, last).
    //    This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a) if InputIt is an integral type.
    //     template< class InputIt >
    //     vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
    // 6) Copy constructor. Constructs the container with the copy of the contents of other.
    //     vector( const vector& other );
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    																											printTitle("Testing Constructor", "General", LVL2, START);

																												printTitle("VectorofVector", "General", LVL3, START);
	ft::vector<vector_type>				    Vectorholder = *arr;
	typename ft::vector<vector_type>::iterator		VectorholderIterator;
																												printTitle("VectorofVector", "General", LVL3, END);
	std::allocator<typename vector_type::value_type>	alloc;
	size_t 						            VectorSize = 5;

																												printTitle("Vector constructors", "General", LVL3, START);
	std::cout << "/*1_Default*/" << std::endl;      vector_type A;                                  printVector<vector_type>("A", A);
	std::cout << "/*2_Alloc*/" << std::endl;        vector_type B(alloc);                           printVector<vector_type>("B", B);
	std::cout << "/*3_Fill*/" << std::endl;         vector_type C(VectorSize, data[value1]);        printVector<vector_type>("C", C);

	std::cout << "/*5_Range*/" << std::endl;        vector_type D(C.begin(), C.end(), alloc);       printVector<vector_type>("D", D);
	std::cout << "/*6_Copy*/" << std::endl;         vector_type E(C);                               printVector<vector_type>("E", E);
	std::cout << "/*Const*/" << std::endl;    const vector_type F(4, data[value2]);                 printVector<vector_type>("F", F);

    
    																											std::cout << "Pushing all vectors back to Vector of Vector" << std::endl;
	B.push_back(data[val1]);
	B.push_back(data[val2]);
	B.push_back(data[val3]);
	B.push_back(data[val4]); 

    Vectorholder.push_back(A);
	Vectorholder.push_back(B);
	Vectorholder.push_back(C);
    Vectorholder.push_back(D);
	Vectorholder.push_back(E);
	Vectorholder.push_back(F);
																												printTitle("Vector constructors", "General", LVL3, END);

																												printTitle("Testing Constructor", "General", LVL2, END);
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator=
// 1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
// vector& operator=( const vector& other );
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("Testing Copy assignment operator", "General", LVL2, START);
    printVector<vector_type>("A", A);
    printVector<vector_type>("C", C);
    A = C;
    std::cout << "Copy assignment operator : A = C" << std::endl;
    printVector<vector_type>("A", A);
    printVector<vector_type>("C", C);
    if (A == C)
        std::cout << BGREEN ">> OK" RESET << std::endl;
    else
        std::cout << BRED ">> NOK" RESET << std::endl;
    printTitle("Testing Copy assignment operator", "General", LVL2, END);
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// assign
// Replaces the contents of the container.
// 1) Replaces the contents with count copies of value value
//     void assign( size_type count, const T& value );
// 2) Replaces the contents with copies of those in the range [first, last). The behavior is undefined if either argument is an iterator into *this.
// This overload has the same effect as overload (1) if InputIt is an integral type.
//     template< class InputIt >
//     void assign( InputIt first, InputIt last );
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("Testing assign", "General", LVL2, START);
    std::cout << CYAN "On empty containers\n" RESET;
    {
        vector_type empty1;
        std::cout << CYAN "empty1.assign(10, data[value1])\n" RESET;
        printVector<vector_type>("empty1", empty1);
        empty1.assign(10, data[value1]);
        printVector<vector_type>("empty1", empty1);

        std::cout << std::endl;
        vector_type empty2;
        std::cout << CYAN "empty2.assign(empty1.begin() + 5, empty1.end())\n" RESET;
        printVector<vector_type>("empty2", empty2);
        empty2.assign(empty1.begin() + 5, empty1.end());
        printVector<vector_type>("empty2", empty2);
    }

    std::cout << CYAN "\nOn filled containers\n" RESET;
    std::cout << CYAN "C.assign(3, data[value2])\n" RESET;
    printVector<vector_type>("C", C);
    C.assign(3, data[value2]);
    printVector<vector_type>("C", C);

    std::cout << std::endl;
    std::cout << CYAN "D.assign(C.begin() + 1, C.end())\n" RESET;
    printVector<vector_type>("D", D);
    D.assign(C.begin() + 1, C.end());
    printVector<vector_type>("D", D);

    printTitle("Testing assign", "General", LVL2, END);
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// get_allocator
// Returns the allocator associated with the container.
//    allocator_type get_allocator() const;
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("Testing get_allocator", "General", LVL2, START);
    std::cout << "max size of allocator " << A.get_allocator().max_size() << std::endl;
    std::cout << std::boolalpha;
    std::cout << "comparing allocators >> " << (A.get_allocator() == B.get_allocator()) << std::endl;
    // std::cout << "max size of allocator " << A.get_allocator().destroy(A.at(0)) << std::endl;
    printTitle("Testing get_allocator", "General", LVL2, END);
// ========================================================================================================================================================

    *arr = Vectorholder;
  
    printTitle("testing basics", "General", LVL1, END);
    return;
}
// ============================================================================<<ftVectorBasics============================================================================

// ============================================================================>>ftVectorElementAccess============================================================================
// at | operator[] | front | back | data ????
template <class vector_type>
void ftVectorElementAccess(std::string name, const vector_type &arr, const vector_type &)
{
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // at
    // Returns a reference to the element at specified location pos, with bounds checking.
    // std::out_of_range if !(pos < size()).
    //     reference at( size_type pos );
    //     const_reference at( size_type pos ) const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("TESTING ELEMENT ACCESS", name, LVL2, START);
    printVector<vector_type>(name, arr);
        printTitle("at()", name, LVL3, START);
        {
            try {
                std::cout << "Testing out of bounds at start - Should throw now\n";
                std::cout << arr.at(static_cast<unsigned long>(-1)); // access out of bond at the start
                std::cout << RED ">Did not throw" << RESET << std::endl;
            }
            catch(const std::out_of_range& e) {
                std::cout << GREEN ">OK Catching Error std::out_of_range: " << e.what() << RESET << std::endl;
            }
            try {
                unsigned long it = 0;
                std::cout << "Testing access to in bounds values\n" << GREEN;
                for(; it != arr.size(); it++)
                    std::cout << it << ": " << arr.at(it) << "| ";
                if (it == 0)
                    std::cout << "(no values)\n" RESET;
                else
                    std::cout << "\n" RESET;
                std::cout << "Testing out of bounds at end - Should throw now\n";
                std::cout << arr.at(it); // access out of bond at the end
                std::cout << RED ">Did not throw" << RESET << std::endl;
            }
            catch(const std::out_of_range& e) {
                std::cout << GREEN ">OK Catching Error std::out_of_range: " << e.what() << RESET << std::endl;
            }
            catch(const std::exception& e) {
                std::cout << RED ">NOK Catching Error std::exception: " << e.what() << RESET << std::endl;
            }
        }
        printTitle("at()", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // operator[]
    // Returns a reference to the element at specified location pos. No bounds checking is performed.
    // reference operator[]( size_type pos );
    // const_reference operator[]( size_type pos ) const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("operator[]", name, LVL3, START);
        {
            unsigned long it = 0;
            std::cout << "Testing access to in bounds values\n" << GREEN;
            for(; it != arr.size(); it++)
                std::cout << it << ": " << arr[it] << "| ";
            if (it == 0)
                std::cout << "(no values)\n" RESET;
            else
                std::cout << "\n" RESET;
        }
        printTitle("operator[]", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // front
    // Returns a reference to the first element in the container.
    // Calling front on an empty container is undefined. For a container c, the expression c.front() is equivalent to *c.begin().
    //     reference front();
    //     const_reference front() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("front", name, LVL3, START);
        {
            try{
                std::cout << "Testing values of front and *arr.begin()\n";
                if (arr.empty() == false && arr.front() == *arr.begin())
                    std::cout << GREEN "front: " << arr.front() << "| *arr.begin(): " << *arr.begin() << "\n" RESET;
                else if (arr.empty() == false && arr.front() != *arr.begin())
                    std::cout << RED "front: " << arr.front() << "| *arr.begin(): " << *arr.begin() << "\n" RESET;
                else
                    std::cout << "front: (empty)\n";
            }
            catch(const std::exception& e){
                std::cout << RED ">Catching Error std::exception: " << e.what() << RESET << std::endl;
            }
        }
        printTitle("front", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // back
    // Returns a reference to the last element in the container.
    // Calling back on an empty container causes undefined behavior. For a non-empty container c, the expression c.back() is equivalent to *std::prev(c.end())
    //     reference back();
    //     const_reference back() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("back", name, LVL3, START);
        {
            try{
                std::cout << "Testing values of back and *(arr.end() - 1)\n";
                if (arr.empty() == false && arr.back() == *(arr.end() - 1))
                    std::cout << GREEN "back: " << arr.back() << "| *(c.end() - 1): " << *(arr.end() - 1) << "| arr.at(arr.size() - 1): " << arr.at(arr.size() - 1) << "\n" RESET;
                else if (arr.empty() == false && arr.back() != *(arr.end()))
                    std::cout << RED "back: " << arr.back() << "| *(c.end() - 1): " << *(arr.end() - 1) <<  "| arr.at(arr.size() - 1): " << arr.at(arr.size() - 1) << "\n" RESET;
                else
                    std::cout << "back: (empty)\n";
            }
            catch(const std::exception& e){
                std::cout << RED ">Catching Error std::exception: " << e.what() << RESET << std::endl;
            }
        }
        printTitle("back", name, LVL3, END);

    printTitle("element access", name, LVL2, END);
}
// ============================================================================<<ftVectorElementAccess============================================================================

// ============================================================================>>ftVectorIterators============================================================================
// begin | end | rbegin | rend
template <class vector_type>
void ftVectorIterators(std::string name, const vector_type &arr, const vector_type & data)
{
    printTitle("TESTING ITERATORS", name, LVL2, START);
    printVector<vector_type>(name, arr);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // begin
    // Returns an iterator to the first element of the vector.
    // If the vector is empty, the returned iterator will be equal to end().
    //    iterator begin();
    //    const_iterator begin() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // end
    // Returns an iterator to the element following the last element of the vector.
    // This element acts as a placeholder; attempting to access it results in undefined behavior.
    //    iterator end();
    //    const_iterator end() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING BEGIN AND END", name, LVL3, START);
        {
        std::cout <<  "Testing iteration ConstIterator" RESET << std::endl;
        int i = 0;
        for (typename vector_type::const_iterator it = arr.begin(); it != arr.end(); it++)
            std::cout << i++ << "|" << *it << std::endl;

        vector_type    test(arr);
        std::cout <<  "APrinting container test" RESET << std::endl;
        printVector<vector_type>(name, test);

        std::cout <<  "Testing iteration Iterator" RESET << std::endl;
        i = 0;
        for (typename vector_type::iterator it = test.begin(); it != test.end(); it++)
            std::cout << i++ << "|" << *it << std::endl;
        
        std::cout <<  "Clearing container test" RESET << std::endl;
        test.clear();
        if (test.begin() == test.end())
            std::cout << GREEN ">> OK, is empty" RESET << std::endl;

        std::cout <<  "Filling container test" RESET << std::endl;
        test.push_back(data[value1]);
        test.push_back(data[value2]);

        std::cout <<  "BPrinting container test" RESET << std::endl;
        printVector<vector_type>(name, test);
        std::cout <<  "*test.begin(): " RESET << *test.begin();
        if (*test.begin() == data[value1])
            std::cout << GREEN " >> OK" RESET << std::endl;
        else
            std::cout << RED " >> NOK" RESET << std::endl;

        std::cout <<  "*test.end() - 1: " RESET << *(test.end() - 1);
        if (*(test.end() - 1) == data[value2])
            std::cout << GREEN " >> OK" RESET << std::endl;
        else
            std::cout << RED " >> NOK" RESET << std::endl;

        }
        printTitle("testing begin and end", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // rbegin
    // Returns a reverse iterator to the first element of the reversed vector. It corresponds to the last element of the non-reversed vector.
    // If the vector is empty, the returned iterator is equal to rend().
    //    reverse_iterator rbegin();
    //    const_reverse_iterator rbegin() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // end
    // Returns a reverse iterator to the element following the last element of the reversed vector.
    // It corresponds to the element preceding the first element of the non-reversed vector.
    // This element acts as a placeholder, attempting to access it results in undefined behavior.
    //     reverse_iterator rend();
    //     const_reverse_iterator rend() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING RBEGIN AND REND", name, LVL3, START);
        {

        std::cout <<  "Testing reverse iteration RevConstIterator" RESET << std::endl;
        printVector<vector_type>(name, arr);

        int i = 0;
        for (typename vector_type::const_reverse_iterator it = arr.rbegin(); it != arr.rend(); it++)
            std::cout << i++ << "|" << *it << std::endl;

        vector_type    test(arr);
        std::cout <<  "CPrinting container test" RESET << std::endl;
        test.push_back(data[value2]);
        printVector<vector_type>(name, test);

        std::cout <<  "Testing reverse iteration RevIterator" RESET << std::endl;
        i = 0;
        for (typename vector_type::reverse_iterator it = test.rbegin(); it != test.rend(); it++)
            std::cout << i++ << "|" << *it << std::endl;
        
        std::cout << CYAN "Clearing container test" RESET << std::endl;
        test.clear();
        
        if (test.rbegin() == test.rend())
            std::cout << GREEN ">> OK, is empty" RESET << std::endl;
        else 
            std::cout << RED ">> NOK, is NOT empty" RESET << std::endl;

        std::cout << CYAN "Filling container test" RESET << std::endl;
        test.push_back(data[value1]);
        test.push_back(data[value2]);

        printVector<vector_type>(name, test);
        std::cout << "(reverse print)\t" << name << " | ";
        vector_type              temp = test;
        typename vector_type::iterator    it = temp.begin();

        while (it < temp.end())
        {
            printval<typename vector_type::value_type>(*it);
            it++;
        }
    
        if (test.rbegin() == test.rend())
            std::cout << "(empty)\t";
        std::cout<< std::endl;

        std::cout << CYAN "*test.rbegin(): " RESET << *test.rbegin();
        if (*test.rbegin() == data[value2])
            std::cout << GREEN " >> OK" RESET << std::endl;
        else
            std::cout << RED " >> NOK" RESET << std::endl;

        std::cout << CYAN "*test.rend()- 1: " RESET << *(test.rend() - 1);
        if (*(test.rend() - 1) == data[value1])
            std::cout << GREEN " >> OK" RESET << std::endl;
        else
            std::cout << RED " >> NOK" RESET << std::endl;
        }
        printTitle("testing rbegin and rend", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("testing iterators", name, LVL2, END);
}
// ============================================================================<<ftVectorIterators============================================================================

#include <locale>

// ============================================================================>>ftVectorCapacity============================================================================
// empty | size | max_size | reserve | capacity
template <class vector_type>
void ftVectorCapacity(std::string name, const vector_type &arr, const vector_type & data)
{
    printTitle("TESTING CAPACITY", name, LVL2, START);
    printVector<vector_type>(name, arr);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // empty
    // Checks if the container has no elements, i.e. whether begin() == end(). true if the container is empty, false otherwise
    //     bool empty() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING EMPTY", name, LVL3, START);
        printVector<vector_type>(name, arr);
        std::cout << "Is container empty ? "; setStreamColor(arr.empty(), true); std::cout << arr.empty();
        std::cout << RESET " | double check begin() == end() : " ; setStreamColor((arr.begin() == arr.end()), true); std::cout <<  (arr.begin() == arr.end()) << std::endl;

        if (arr.empty() == false)
        {
            vector_type    test(arr);
            std::cout << CYAN "Clearing container test" RESET << std::endl;
            test.clear();
            std::cout << "Is container empty ? "; setStreamColor(test.empty(), true); std::cout << test.empty() ;
            std::cout << RESET " | double check begin() == end() : " ; setStreamColor((test.begin() == test.end()), true); std::cout <<  (test.begin() == test.end()) << std::endl;

            if (test.empty() == true)
                std::cout << GREEN ">> OK, is empty" RESET << std::endl;
            else
                std::cout << RED ">> NOK, is not empty" RESET << std::endl;
        }
        printTitle("testing empty", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // size
    // Returns the number of elements in the container, i.e. std::distance(begin(), end()).
    //    size_type size() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING SIZE", name, LVL3, START);
        std::cout << CYAN "Size of current container: " RESET << arr.size() << "| double check std::distance(begin(), end()) : " << arr.end() - arr.begin() << std::endl;
        {
            vector_type    test;
            std::cout << CYAN "Size of empty container: " RESET << test.size() << "| double check std::distance(begin(), end()) : " <<  test.end() - test.begin() << std::endl;
        }
        printTitle("testing size", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // max_size
    // Returns the maximum number of elements the container is able to hold due to system or library implementation limitations,
    // i.e. std::distance(begin(), end()) for the largest container.
    // This value typically reflects the theoretical limit on the size of the container, at most std::numeric_limits<difference_type>::max().
    // At runtime, the size of the container may be limited to a value smaller than max_size() by the amount of RAM available.
    //    size_type max_size() const;
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING MAX_SIZE", name, LVL3, START);
        std::cout.imbue(std::locale("en_US.UTF-8"));
        std::cout << "Maximum size of this container is\t" << arr.max_size() << '\n';
        {
            vector_type test;
            std::cout << "Maximum size of same std container is\t" << test.max_size() << '\n';
            std::cout << "Is same size ? "; setStreamColor((arr.max_size() == test.max_size()), true); std::cout << (arr.max_size() == test.max_size()) << std::endl;
        }
        printTitle("testing max_size", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // capacity
    // Returns the number of elements that the container has currently allocated space for.
    // size_type capacity() const;
    // https://en.cppreference.com/w/cpp/container/vector/capacity//
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING CAPACITY", name, LVL3, START);
        std::cout << CYAN "Capacity of currently allocated storage for this container is:\n" RESET << arr.capacity() << '\n';
        {
            int size = 100;
            vector_type test;

            size_t capacity = test.capacity();
            std::cout << CYAN "Test capacity's growth policy.\n" RESET;
            std::cout << "Initial size: " << test.size() << ", capacity: " << capacity << '\n';
            std::cout << "Size:  Capacity:  Ratio:\n" << std::left;
            while (size-- > 0) {
                test.push_back(data[value1]);
                if (capacity != test.capacity()) {
                    std::cout << std::setw( 7) << test.size()
                            << std::setw(11) << test.capacity()
                            << std::setw(10) << test.capacity() / static_cast<float>(capacity) << '\n';
                    capacity = test.capacity();
                }
            }
            std::cout << "Final size: " << test.size() << ", capacity: " << test.capacity() << '\n';
        }
        printTitle("testing capacity", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // reserve
    // Requests that the vector capacity be at least enough to contain n elements.
    // If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
    // In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
    // This function has no effect on the vector size and cannot alter its elements.
    // If the size requested is greater than the maximum size (vector::max_size), a length_error exception is thrown.
    //    void reserve( size_type new_cap );
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING RESERVE", name, LVL3, START);
        unsigned int	n = 100;
        {
            std::cout << CYAN"1. n > current capacity" RESET<< std::endl;;
            vector_type		test(arr);
            std::cout << CYAN"Capacity of currently allocated storage for this container is:\n" RESET << "test.capacity(): " << test.capacity() << '\n';
            std::cout << CYAN "Using reserve() to set it to "<< n << ":\n" RESET; test.reserve(n); std::cout << "test.capacity(): " << test.capacity() << '\n';
        }
        {
            std::cout << CYAN"2. n < current capacity" RESET<< std::endl;;
            vector_type		test(arr);
            for (int i=0; static_cast<unsigned int>(i)<(n * 2); ++i) {
                test.push_back(data[value1]);
                }
            std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';
            std::cout << CYAN"Using reserve("<< n <<") here shouldn't do anything as vector is already larger than "<< n << RESET << std::endl;
            test.reserve(n);
            std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';
        }
        {
            std::cout << CYAN"3." RESET<< std::endl;;
            typename vector_type::size_type sz;

            vector_type		randomVectorA;
            sz = randomVectorA.capacity();
            std::cout << CYAN "making randomVectorB grow:(NOT using reserve()) [In Magenta when capacity is changed]\n" RESET;
            for (int i=0; static_cast<unsigned int>(i)<n; ++i) {
                randomVectorA.push_back(data[value1]);
                if (sz!=randomVectorA.capacity()) {
                sz = randomVectorA.capacity();
                std::cout << BOLD MAGENTA << sz << '!' << RESET "|";
                }
                else
                std::cout <<  sz << "|";
            }
            std::cout << '\n';

            vector_type randomVectorB;
            sz = randomVectorB.capacity();
            randomVectorB.reserve(n);   // this is the only difference with randomVectorA above
            std::cout << CYAN "making randomVectorB grow:(using reserve()) [In Magenta when capacity is changed]\n" RESET;
            for (int i=0; static_cast<unsigned int>(i)<n; ++i) {
                randomVectorB.push_back(data[value1]);
                if (sz!=randomVectorB.capacity()) {
                sz = randomVectorB.capacity();
                std::cout << BOLD MAGENTA << sz << '!' << RESET "|";
                }
                else
                std::cout <<  sz << "|";
            }
            std::cout << '\n';
        }
        {
            std::cout << CYAN"4. Exceptions control" RESET<< std::endl;;
            vector_type test;
            std::cout << "Vector size: " << test.size() << ", capacity: " << test.capacity() << '\n';
            std::cout << CYAN "Max_size\t\t: " <<  test.max_size() << std::endl;
            try
            {
                size_t  new_size = test.max_size() / 1000000;
                std::cout	<< CYAN "Reserving to\t\t: " << new_size << "\t=> Should not throw max_size exception" RESET << std::endl;
                // test.reserve(new_size);
                std::cout	<< GREEN "Didn't throw\n" RESET;

                new_size = test.max_size() + 1;
                std::cout	<< CYAN "Reserving to max_size+1\t: " << new_size << "\t=> Should throw max_size exception" RESET << std::endl;
                test.reserve(new_size);
                std::cout	<< RED "Didn't throw\n" RESET;
            }
            catch (const std::length_error& le) {
                std::cout << GREEN "OK Caught error\n" RESET RED "=> Error: " << le.what() << '\n' << RESET;
            }
            catch(const std::exception& e)
            {
                std::cout << RED << "! Unhandled error: " << e.what() << RESET << std::endl;
            }
            std::cout << "Vector size: " << test.size() << ", capacity: " << test.capacity() << '\n';

        }
        printTitle("testing reserve", name, LVL3, END);

    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("testing capacity section", name, LVL2, END);
}
// ============================================================================<<ftVectorCapacity============================================================================

// ============================================================================>>ftVectorModifiers============================================================================
// clear | insert | erase | push_back | pop_back | resize | swap
template <class vector_type>
void ftVectorModifiers(std::string name, const vector_type &arr, const vector_type & data)
{
    printTitle("TESTING MODIFIERS", name, LVL2, START);
    printVector<vector_type>(name, arr);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // clear
    // Erases all elements from the container. After this call, size() returns zero.
    // Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterators are also invalidated.
    // Leaves the capacity() of the vector unchanged (note: the standard's restriction on the changes to capacity is in the specification of vector::reserve, see [1])
    //    void clear();
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING CLEAR", name, LVL3, START);
        {
            vector_type		        test(arr);
            typename vector_type::size_type  capacity = test.capacity();

            printVector<vector_type>("test", test);
            std::cout << "Is container empty ? "; setStreamColor(test.empty(), true); std::cout << test.empty() ;
            std::cout << RESET " | double check begin() == end() : " ; setStreamColor((test.begin() == test.end()), true); std::cout <<  (test.begin() == test.end());
            std::cout << RESET " | size() : " << test.size();
            std::cout << RESET " | capacity() : " << test.capacity() << std::endl;

            std::cout << CYAN "Clearing container test" RESET << std::endl;
            test.clear();
            printVector<vector_type>("test", test);
            std::cout << "Is container empty ? "; setStreamColor(test.empty(), true); std::cout << test.empty() ;
            std::cout << RESET " | double check begin() == end() : " ; setStreamColor((test.begin() == test.end()), true); std::cout <<  (test.begin() == test.end());
            std::cout << RESET " | size() : " << test.size();
            std::cout << RESET " | capacity() : " << test.capacity() << std::endl;

            if (test.empty() == true)
                std::cout << GREEN ">> OK, is empty" RESET << std::endl;
            else
                std::cout << RED ">> NOK, is not empty" RESET << std::endl;
            if (test.capacity() == capacity)
                std::cout << GREEN ">> OK, capacity is unchanged" RESET << std::endl;
            else
                std::cout << RED ">> NOK, is not the same capacity" RESET << std::endl;
        }
        printTitle("testing clear", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // insert
    // /*1*/   iterator insert( const_iterator pos, const T& value );
    // /*3*/   iterator insert( const_iterator pos, size_type count, const T& value );
    // /*4*/   template< class InputIt >
    //         iterator insert( const_iterator pos, InputIt first, InputIt last );
    // Inserts elements at the specified location in the container.
    // 1-2) inserts value before pos.
    // 3) inserts count copies of the value before pos.
    // 4) inserts elements from range [first, last) before pos.
    // This overload has the same effect as overload (3) if InputIt is an integral type.
    // The behavior is undefined if first and last are iterators into *this.
    // ---
    // Causes reallocation if the new size() is greater than the old capacity(). If the new size() is greater than capacity(), all iterators and references are invalidated.
    // Otherwise, only the iterators and references before the insertion point remain valid. The past-the-end iterator is also invalidated.
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
		printTitle("TESTING INSERT", name, LVL3, START);
        {
            std::cout << CYAN"1. iterator insert( const_iterator pos, const T& value )" RESET<< std::endl;;
            
            vector_type   test(arr);
            printVector<vector_type>("test_1_before", test);

            typename vector_type::iterator   pos         = test.begin();
            typename vector_type::iterator   ret;
            int                     position    = 0;
            typename vector_type::size_type  capacity    = test.capacity();

            if (test.size() > 1) {
                pos += (test.size() / 2);
                position += (test.size() / 2);
                std::cout << YELLOW "test.insert(" << (pos - test.begin()) << " , " << data[val6] << ");" RESET<< std::endl;
                ret = test.insert(pos, data[val6]);
                printVector<vector_type>("test_1_after", test);
            }
            else
            {
                std::cout << YELLOW "test.insert(" << (pos - test.begin()) << " , " << data[val6] << ");" RESET<< std::endl;;
                ret = test.insert(pos, data[val6]);
                printVector<vector_type>("test_1_after", test);
            }

            typename vector_type::size_type  cap;
            vector_type             loop_capacity;
            std::cout << "(" << loop_capacity.size() << "/" << loop_capacity.capacity() << ")" << std::endl;
            for (int i = 0; i < 100; i++)
            {
                cap = loop_capacity.capacity();
                loop_capacity.insert(loop_capacity.begin(), i);
                if (cap != loop_capacity.capacity())
                    std::cout << "(" << loop_capacity.size() << "/" BMAGENTA << loop_capacity.capacity() << ")" RESET << std::endl;
                std::cout << "(" << loop_capacity.size() << "/" << loop_capacity.capacity() << ")" << std::endl;
            }
            
            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;
        }
        {
            std::cout << CYAN"2. iterator insert( const_iterator pos, size_type count, const T& value )" RESET<< std::endl;

            vector_type   test(arr);
            printVector<vector_type>("test_2_before", test);

            typename vector_type::iterator    pos         = test.begin();
            typename vector_type::iterator    ret;
            int         position    = 0;
            size_t      capacity    = test.capacity();
            size_t      count       = 20;

            if (test.size() > 1) {
                pos += (test.size() / 2);
                position += (test.size() / 2);
                std::cout << MAGENTA "ret = test.insert(" << (pos - test.begin()) << " , " << count << ", " << data[val6] << ");" RESET<< std::endl;;
                ret = test.insert(pos, count, data[val6]);
            }
            else
            {
                std::cout << MAGENTA "ret = test.insert(" << (pos - test.begin()) << " , " << count << ", " << data[val6] << ");" RESET<< std::endl;;
                ret = test.insert(pos, count, data[val6]);
            }
            printVector<vector_type>("test_2_after", test);

            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;

            std::cout << CYAN"Testing adding nothing " << std::endl;
            printVector<vector_type>("test_2_empty_before", test);
            ret = test.insert(test.begin(), 0, data[val6]);
            printVector<vector_type>("test_2_empty_after", test);

        }
        {
            std::cout << CYAN"3. template< class InputIt >\niterator insert( const_iterator pos, InputIt first, InputIt last )" RESET<< std::endl;

            vector_type   test(arr);
            std::for_each(test.begin(), test.end(), doubleval<typename vector_type::value_type>);

            typename vector_type::iterator    pos         = test.begin();
            typename vector_type::iterator    ret;
            int         position    = 0;
            size_t      capacity    = test.capacity();
            size_t      size        = test.size();

            printVector<vector_type>("test_3_before_destination\t: test", test); 
            printVector<vector_type>("test_3_before_source\t: arr", arr); 

            if (size > 1) {
                pos += (size / 2);
                position += (size / 2);
                std::cout << BLUE "ret = test.insert(" << (pos - test.begin()) << ", " << (arr.begin() - arr.begin()) << ", " << (arr.end() - arr.begin()) << ");" RESET<< std::endl;;
                ret = test.insert(pos, arr.begin(), arr.end());
            }
            else
            {
                std::cout << BLUE "ret = test.insert(" << (pos - test.begin()) << ", " << (arr.begin() - arr.begin()) << ", " << (arr.end() - arr.begin()) << ");" RESET<< std::endl;;
                ret = test.insert(pos, arr.begin(), arr.end());
            }
            printVector<vector_type>("test_3_after_destination\t: test", test); 
            printVector<vector_type>("test_3_after_source\t: arr", arr); 

            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;

            std::cout << CYAN "Testing adding on empty array" << RESET << std::endl;
            test.clear();
            printVector<vector_type>("test_3_emptyArr_before\t: test", test); 
            std::cout << CYAN"test.insert(test.begin(), " << (arr.begin() - arr.begin()) << ", " << (arr.end() - arr.begin()) << ");" RESET<< std::endl;;
            test.insert(test.begin(), arr.begin(), arr.end());
            printVector<vector_type>("test_3_emptyArr_after\t: test", test); 
        }
        printTitle("testing insert", name, LVL3, END);

    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // erase
    // Erases the specified elements from the container.
    // 1) Removes the element at pos.
    // 2) Removes the elements in the range [first, last).
    // Invalidates iterators and references at or after the point of the erase, including the end() iterator.
    // The iterator pos must be valid and dereferenceable. Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
    // The iterator first does not need to be dereferenceable if first == last: erasing an empty range is a no-op.
    // /*1*/ iterator erase( iterator pos );
    // /*2*/ iterator erase( iterator first, iterator last );
    // Return value
    //     Iterator following the last removed element.
    //     If pos refers to the last element, then the end() iterator is returned.
    //     If last == end() prior to removal, then the updated end() iterator is returned.
    //     If [first, last) is an empty range, then last is returned.
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING ERASE", name, LVL3, START);
        {
            std::cout << CYAN"1. iterator erase( iterator pos )" RESET<< std::endl;;
            vector_type   test(arr);
            std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << std::endl; printVector<vector_type>("test", test); 
            
            typename vector_type::iterator    pos = test.begin(), ret;
            int         position = 0;
            size_t      capacity = test.capacity();

            if (!test.empty())
            {
                if (test.size() > 1) {
                    pos += (test.size() / 2);
                    position += (test.size() / 2);
                    ret = test.erase(pos);
                    std::cout << CYAN "ret = test.erase("<< (pos - test.begin()) << ") | return value 'ret': " << *ret << RESET << std::endl;
                }
                else {
                    test.erase(test.begin());
                    std::cout << CYAN "ret = test.erase(test.begin()) | return value 'ret': " << (ret == test.end() ? "past the end it" : std::to_string(*ret)) << RESET << std::endl;
                }

                std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << std::endl; printVector<vector_type>("test", test); 

                if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
                else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;
            }
            else
                std::cout << RED "Vector is empty, no erase() operation performed" << RESET << std::endl;
        }
        {
            std::cout << CYAN"2. iterator erase( iterator first, iterator last )" RESET<< std::endl;;
            
            vector_type   test(arr);
            std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << std::endl; printVector<vector_type>("test", test); 
            
            typename vector_type::iterator    ret;
            size_t      capacity = test.capacity();

            if (!test.empty())
            {
                if (test.size() < 5)
                {
                    ret = test.erase(test.begin(), test.end() - 1);
                    std::cout << CYAN "Partial erasement\nret = test.erase(" << (test.begin() - test.begin()) << ", " << ((test.end() - 1) - test.begin()) << " | return value 'ret': " << *ret << RESET << std::endl;
                }
                else
                {
                    ret = test.erase(test.begin(), test.end());
                    std::cout << CYAN "Total erasement\nret = test.erase(" << (test.begin() - test.begin()) << ", " << ((test.end()) - test.begin()) << " | return value 'ret': " << *ret << RESET << std::endl;
                }
                std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << std::endl; printVector<vector_type>("test", test); 

                if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
                else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;
            }
            else
                std::cout << RED "Vector is empty, no erase() operation performed" << RESET << std::endl;

        }
        printTitle("testing erase", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // push_back
    // Appends the given element value to the end of the container.
    // 1) The new element is initialized as a copy of value.
    // If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated.
    // Otherwise only the past-the-end iterator is invalidated.
    //     void push_back( const T& value );
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING PUSH_BACK", name, LVL3, START);
        {
            std::cout << CYAN"1. void push_back( const T& value )" RESET<< std::endl;;
            vector_type  test(arr);
            size_t  capacity = test.capacity();
            printVector<vector_type>("test", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

            int i = 0;
            for(; i < 6; i++)
            {
                if (i % 2)
                    test.push_back(data[value1]);
                else
                    test.push_back(data[value2]);
            }
            std::cout << CYAN "test.push_back(data[value1] or value 2) " << i << " times" << RESET << std::endl;

            printVector<vector_type>("test", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;

        printTitle("testing push_back", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // pop_back
    // Removes the last element of the container.
    // Calling pop_back on an empty container results in undefined behavior.
    // Iterators and references to the last element, as well as the end() iterator, are invalidated.
    //     void pop_back();
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING POP_BACK", name, LVL3, START);

            std::cout << CYAN"1. void pop_back()" RESET<< std::endl;;
            capacity = test.capacity();
            printVector<vector_type>("test", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

            i = 0;
            for(; i < 3; i++)
                test.pop_back();

            std::cout << CYAN "test.pop_back() " << i << " times" << RESET << std::endl;

            printVector<vector_type>("test", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;
        }
        printTitle("testing pop_back", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // resize
    // Resizes the container to contain count elements.
    // If the current size is greater than count, the container is reduced to its first count elements.
    // If the current size is less than count,
    // 1) additional default-inserted elements are appended
    // 2) additional copies of value are appended.
    // /*2*/ void resize( size_type count, T value = T() );
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING RESIZE", name, LVL3, START);
        {
            std::cout << CYAN"1. void resize( size_type count, T value = T() )" RESET<< std::endl;;
            vector_type   test(arr);
            size_t                  capacity = test.capacity();
            printVector<vector_type>("RESIZEtest", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';

            test.resize(15, data[value1]);
            std::cout << CYAN "test.resize(15, data[value1])" RESET << std::endl;
            printVector<vector_type>("RESIZEtest", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';
            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;

            test.resize(10, data[value1]);
            std::cout << CYAN "test.resize(3, data[value2])" RESET << std::endl;
            printVector<vector_type>("RESIZEtest", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';
            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;

            test.resize(13, data[value2]);
            std::cout << CYAN "test.resize(10, data[value1])" RESET << std::endl;
            printVector<vector_type>("RESIZEtest", test); std::cout << "size: " << test.size() << ", capacity: " << test.capacity() << '\n';
            if (capacity != test.capacity()) std::cout << GREEN "capacity was updated" << RESET << std::endl;
            else std::cout << GREEN "capacity is unchanged" << RESET << std::endl;
        }
        printTitle("testing resize", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // swap
    // Exchanges the contents of the container with those of other.
    // Does not invoke any move, copy, or swap operations on individual elements.
    // All iterators and references remain valid. The past-the-end iterator is invalidated.
    // void swap( vector& other );
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING SWAP", name, LVL3, START);
        {
            vector_type A(arr), B;

            printVector<vector_type>("A", A); printVector<vector_type>("B", B);
            A.swap(B);
            std::cout << CYAN "A.swap(B)" RESET << std::endl;
            printVector<vector_type>("A", A); printVector<vector_type>("B", B);

            std::cout << CYAN "\nPushing back in A (data[val1] to data[val6])" RESET << std::endl;
            A.push_back(data[val1]);
            A.push_back(data[val2]);
            A.push_back(data[val3]);
            A.push_back(data[val4]);
            A.push_back(data[val5]);
            A.push_back(data[val6]);

            typename vector_type::iterator it = A.begin();
            typename vector_type::iterator end = A.end();
            typename vector_type::const_iterator cit = A.begin();

            std::cout << BRED "Checking comparable iterators :" RESET << (it - cit) << std::endl;
            
            printVector<vector_type>("A", A); printVector<vector_type>("B", B);
            A.swap(B);
            std::cout << CYAN "A.swap(B)" RESET << std::endl;
            printVector<vector_type>("A", A); printVector<vector_type>("B", B);

            std::cout << BRED "Checking iterators validity" RESET << std::endl;
            for (; it != end; it++)
                std::cout << *it << std::endl;

            std::cout << CYAN "Test supertest" RESET << std::endl;

            vector_type Humpty, Dumpty;
            Humpty.push_back(data[val1]);
            Humpty.push_back(data[val2]);

            Dumpty.reserve(50);
            Dumpty.push_back(data[val1]);
            Dumpty.push_back(data[val2]);

            printVector<vector_type>("Humpty_before", Humpty); 
            printVector<vector_type>("Dumpty_before", Dumpty); 
            Humpty.swap(Dumpty);
            std::cout << CYAN "Humpty and Dumpty now SWAPPIN'" RESET << std::endl;
            printVector<vector_type>("Humpty_after", Humpty); 
            printVector<vector_type>("Dumpty_after", Dumpty); 

        }
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    // ft::swap
    // Exchanges the contents of the container with those of other.
    // Does not invoke any move, copy, or swap operations on individual elements.
    // All iterators and references remain valid. The past-the-end iterator is invalidated.
    // void swap( vector& other );
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
        printTitle("TESTING FT_SWAP", name, LVL3, START);
        {
            vector_type A(arr), B;

            printVector<vector_type>("A", A); printVector<vector_type>("B", B);
            ft::swap(A, B);
            std::cout << CYAN "ft::swap(A, B)" RESET << std::endl;
            printVector<vector_type>("A", A); printVector<vector_type>("B", B);

            std::cout << CYAN "\nPushing back in A (data[val1] to data[val6])" RESET << std::endl;
            A.push_back(data[val1]);
            A.push_back(data[val2]);
            A.push_back(data[val3]);
            A.push_back(data[val4]);
            A.push_back(data[val5]);
            A.push_back(data[val6]);
            printVector<vector_type>("A", A); printVector<vector_type>("B", B);
            ft::swap(A, B);
            std::cout << CYAN "ft::swap(A, B)" RESET << std::endl;
            printVector<vector_type>("A", A); printVector<vector_type>("B", B);

            std::cout << CYAN "Test supertest" RESET << std::endl;

            vector_type Humpty, Dumpty;
            Humpty.push_back(data[val1]);
            Humpty.push_back(data[val2]);

            Dumpty.reserve(50);
            Dumpty.push_back(data[val1]);
            Dumpty.push_back(data[val2]);

            printVector<vector_type>("Humpty_before", Humpty); 
            printVector<vector_type>("Dumpty_before", Dumpty); 
            ft::swap(Humpty, Dumpty);
            std::cout << CYAN "Humpty and Dumpty now SWAPPIN'" RESET << std::endl;
            printVector<vector_type>("Humpty_after", Humpty); 
            printVector<vector_type>("Dumpty_after", Dumpty); 

        }
        printTitle("testing swap", name, LVL3, END);
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("testing modifiers", name, LVL2, END);
}
// ============================================================================<<ftVectorModifiers============================================================================

// ============================================================================>>ftVectorOperators============================================================================
template <class vector_type>
void ftVectorOperators(std::string name, const vector_type &arr, const vector_type & data)
{
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator (1, 2): ==,!= ; and (3 - 6): <,<=,>,>=
// Compares the contents of two vectors.
// 1-2) Checks if the contents of lhs and rhs are equal, that is,
// they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
// 3-6) Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent to std::lexicographical_compare.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    printTitle("TESTING OPERATORS", name, LVL2, START);
    printVector<vector_type>(name, arr);
    printTitle("operator ==,!=, <,<=,>,>= ", name, LVL3, START);
    vector_type LHS(arr);
    vector_type RHS(LHS);

    std::cout << std::boolalpha;

    std::cout << CYAN  << "Compare equal containers" RESET << std::endl;
    printVector<vector_type>("LHS", LHS);
    printVector<vector_type>("RHS", RHS);

    std::cout << "LHS == RHS should return true  | " ; setStreamColor((LHS == RHS), true);  std::cout <<  (LHS == RHS) << RESET << std::endl;
    std::cout << "LHS != RHS should return false | " ; setStreamColor((LHS != RHS), false); std::cout <<  (LHS != RHS) << RESET << std::endl;
    std::cout << "LHS <  RHS should return false | " ; setStreamColor((LHS <  RHS), false); std::cout <<  (LHS <  RHS) << RESET << std::endl;
    std::cout << "LHS <= RHS should return true  | " ; setStreamColor((LHS <= RHS), true);  std::cout <<  (LHS <= RHS) << RESET << std::endl;
    std::cout << "LHS >  RHS should return false | " ; setStreamColor((LHS >  RHS), false); std::cout <<  (LHS >  RHS) << RESET << std::endl;
    std::cout << "LHS >= RHS should return true  | " ; setStreamColor((LHS >= RHS), true);  std::cout <<  (LHS >= RHS) << RESET << std::endl;

    if (std::is_arithmetic<typename vector_type::value_type>::value == true)
    {
        std::cout << std::endl;
        std::cout << CYAN  << "Compare non equal containers (VALUE)" RESET << std::endl;
        RHS = LHS;
        LHS.push_back(data[val2]);
        RHS.push_back(data[val1]);
        printVector<vector_type>("LHS", LHS);
        printVector<vector_type>("RHS", RHS);
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
    RHS.pop_back();
    printVector<vector_type>("LHS", LHS);
    printVector<vector_type>("RHS", RHS);
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

    printTitle("operator ==,!=, <,<=,>,>= ", name, LVL3, END);

    printTitle("testing operators", name, LVL2, END);
}
// ============================================================================<<ftVectorOperators============================================================================


// ============================================================================>>ftTestVector============================================================================
template <class vector_type>
void ftTestVector(const vector_type & data)
{
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    /// Member functions
        // Basics           // constructors, operator=, assign, get_allocator
        // ElementAccess    // at, operator[], front, back, data ????
        // Iterators        // begin, cbegin, end, cend, rbegin, crbegin, rend, crend
        // Capacity         // empty, size, max_size, reserve, capacity
        // Modifiers        // clear, insert, erase, push_back, pop_back, resize, swap
    /// Non Member functions
        // Operators        // ==,!=, <,<=,>,>=
        // std::swap(std::vector)
    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    try
    {
        printTitle("START TEST VECTOR", "General", LVL0, START);

        ft::vector<vector_type> Vectorholder;
        std::cout << std::boolalpha;

        ftVectorBasics<vector_type>(&Vectorholder, data); printVector<vector_type>("Vectorholder", Vectorholder);
        

        int i = 0;
        for (typename ft::vector<vector_type>::iterator it = Vectorholder.begin(); it != Vectorholder.end(); it++) {
            char c = 'A' + i;
            std::string name("LoopVectorFunctions");

            printTitle("TESTING MEMBER FUNCTIONS", name + "_" + c, LVL1, START);
            printVector<vector_type>(name + "_" + c, *it);
            
            ftVectorElementAccess<vector_type>(name + "_" + c, *it, data);
            ftVectorIterators<vector_type>(name + "_" + c, *it, data);
            ftVectorCapacity<vector_type>(name + "_" + c, *it, data);
            ftVectorModifiers<vector_type>(name + "_" + c, *it, data);
            printTitle("testing member functions", name + "_" + c, LVL1, END);

            printTitle("TESTING NON MEMBER FUNCTIONS", name, LVL1, START);
            ftVectorOperators<vector_type>(name + "_" + c, *it, data);
            printTitle("testing non member functions", name, LVL1, END);

            i++;
        }
        printTitle("END TEST VECTOR", "General", LVL0, END);
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << '\n';
    }
}
// ============================================================================<<ftTestVector============================================================================


#endif
// ============================================================================<<test_vector.hpp============================================================================
