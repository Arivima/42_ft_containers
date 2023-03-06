/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:45:26 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 12:50:36 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>test_stack.hpp============================================================================
#ifndef TEST_STACK_HPP
#define TEST_STACK_HPP

/// INCLUDES
    #include "header.hpp"
    #include "compilation.hpp"
    #include "test_vector.hpp"
    #include <vector>
    #include <deque>
    #include <list>

    #include <memory>
    #include <locale>

/// Template
    template< class T, class Container >
    void ftStackTemplatedTest(const ft::vector<T> & data){
        
        /*Default*/
        ft::stack<T, Container >     my_stack;  
        my_stack.push(data[value1]);
        std::cout << "my_stack | top () : " << my_stack.top() << std::endl;
        
        /*Copy*/
        ft::stack<T, Container >     my_stackCpy(my_stack); 
        std::cout << "my_stackCpy(my_stack) | top () : " << my_stackCpy.top() << std::endl;
        my_stackCpy.push(data[value1]);
        my_stackCpy.push(data[value2]);

        std::cout << "my_stackCpy.empty(): " << my_stackCpy.empty() << std::endl;
        std::cout << "my_stackCpy.size(): " << my_stackCpy.size() << std::endl;
        
        ft::stack<T, Container >     my_stackEmpty; 

        /*Functions*/
        std::cout << std::boolalpha;
        std::cout << "Initially, my_stackEmpty.empty(): " << my_stackEmpty.empty() << std::endl;
        std::cout << "Initially, my_stackEmpty.size(): " << my_stackEmpty.size() << std::endl;
        std::cout << "Before : is == ? " << (my_stackEmpty == my_stack) << std::endl;
        my_stackEmpty = my_stack;
        std::cout << "After copy : is == ? " << (my_stackEmpty == my_stack) << std::endl;
        std::cout << "After copy, my_stackEmpty.empty(): " << my_stackEmpty.empty() << std::endl;
        std::cout << "After copy, my_stackEmpty.size(): " << my_stackEmpty.size() << std::endl;

        my_stackEmpty.push(data[val1]);
        my_stackEmpty.push(data[val2]);
        my_stackEmpty.push(data[val3]);
        my_stackEmpty.push(data[val4]);
        std::cout << "After adding elements, my_stackEmpty.size() should be 5 : " << my_stackEmpty.size() << std::endl;
        std::cout << "Poping " << my_stackEmpty.top() << std::endl; my_stackEmpty.pop();
        std::cout << "Poping " << my_stackEmpty.top() << std::endl; my_stackEmpty.pop();
        std::cout << "Poping " << my_stackEmpty.top() << std::endl; my_stackEmpty.pop();
        std::cout << "Poping " << my_stackEmpty.top() << std::endl; my_stackEmpty.pop();
        std::cout << "After removing elements, my_stackEmpty.size() should be 1 : " << my_stackEmpty.size() << std::endl;

    {
        std::cout << "Tester" << std::endl;
        Container	ctnr;

        ctnr.push_back(data[val1]);
        ctnr.push_back(data[val1]);
        ctnr.push_back(data[val1]);
        ctnr.push_back(data[val1]);
        ctnr.push_back(data[val1]);
        ctnr.push_back(data[val1]);

        ft::stack<T, Container >    stck(ctnr);

        std::cout << "empty: " << stck.empty() << std::endl;
        std::cout << "size: " << stck.size() << std::endl;

        stck.push(data[val1]);
        stck.push(data[val1]);
        stck.push(data[val1]);
        stck.push(data[val1]);
        stck.push(data[val1]);
        stck.push(data[val1]);

        std::cout << "Added some elements" << std::endl;

        std::cout << "empty: " << stck.empty() << std::endl;
        std::cout << "size: " << stck.size() << std::endl;
    }
}

template<class value_type>
void ftTestStack(const ft::vector<value_type> & data){

    printTitle("START TEST STACK", "General", LVL0, START);

    printTitle("Testing stack< typeTest, ft::vector<value_type> >", "General", LVL1, START);
    ftStackTemplatedTest<value_type, ft::vector<value_type> >(data);
    printTitle("Testing stack< typeTest, std::vector<value_type> >", "General", LVL1, START);
    ftStackTemplatedTest<value_type, std::vector<value_type> >(data);
    printTitle("Testing stack< typeTest, std::deque<value_type> >", "General", LVL1, START);
    ftStackTemplatedTest<value_type, std::deque<value_type> >(data);
    printTitle("Testing stack< typeTest, std::list<value_type> >", "General", LVL1, START);
    ftStackTemplatedTest<value_type, std::list<value_type> >(data);

    printTitle("END TEST STACK", "General", LVL0, END);
    return ;
}

/// FUNCTIONS
    void testAllStack();

#endif
// ============================================================================<<test_stack.hpp============================================================================
