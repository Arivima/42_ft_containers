/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:44:22 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 14:54:48 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>test_iterator.hpp============================================================================
#ifndef TEST_ITERATOR_HPP
#define TEST_ITERATOR_HPP

/// INCLUDES
    #include "header.hpp"
    #include "test_vector.hpp"

/// TYPEDEF

/// DEFINES

/// UTILS

/// NON TEMPLATED FUNCTIONS
void testAllIterators();

/// TEMPLATED FUNCTIONS
//TODO testing only on vectors as random access is used only for vector, reverse is also tested in test_map
// REVERSE
template <class vector_type>
void    ftTestReverseIterator(const vector_type & data){
    printTitle("START TEST REVERSE ITERATORS", "General", LVL0, START);

    printTitle("START TEST RBEGIN REND", "General", LVL2, START);
    {
        vector_type digits;
        digits.push_back(data[val1]);
        digits.push_back(data[val2]);
        digits.push_back(data[val3]);
        digits.push_back(data[val4]);
        digits.push_back(data[val5]);
        digits.push_back(data[val6]);

        // std::cout << "1º| "<< *digits.begin() << std::endl;          //TODO kept here in case need to test iterator and reverse iterator begin/end functions side by side
        // std::cout << "2º| "<< *(digits.end() - 1) << std::endl;      //TODO here
        std::cout << "3º| "<< *digits.rbegin() << std::endl;
        std::cout << "4º| "<< *(digits.rend() - 1) << std::endl;


        // Iterator it = digits.begin();                                //TODO here
        // Iterator ite = digits.end();                                 //TODO here

        typename vector_type::reverse_iterator rit = digits.rbegin();
        typename vector_type::reverse_iterator rite = digits.rend();

        // std::cout << "Base begin | it |\t"<< *it.base() << std::endl; //TODO here
        // std::cout << "Base end | ite |\t"<< *ite.base() << std::endl; //TODO here //? segfault = normal
        // std::cout << "Base rbegin | rit |\t"<< *rit.base() << std::endl; //? segfault = normal
        std::cout << "Base rend | rite |\t"<< *rite.base() << std::endl;

        // std::cout << "begin - end : " << (it - ite) << std::endl;    //TODO here
        // std::cout << "end - begin : " << (ite - it) << std::endl;    //TODO here
        std::cout << "rbegin - rend : " << (rit - rite) << std::endl;
        std::cout << "rend - rbegin : " << (rite - rit) << std::endl;
    }
    printTitle("End test Rbegin Rend", "General", LVL2, END);


    printTitle("START TEST ALL REVERSE ITERATOR FUNCTIONS", "General", LVL2, START);
        std::cout << ITALICS BLUE "-------------------Creating vector" RESET << std::endl;
        vector_type  myVector;
        size_t  sizeOfVector = 4;
        myVector.push_back(data[val1]); //? starts at one specifically to help debug 
        myVector.push_back(data[val2]);
        myVector.push_back(data[val3]);
        myVector.push_back(data[val4]);
        std::cout << CYAN; printVector<vector_type>("myVector", myVector);

        printTitle("Testing REVERSE Constructors", "General", LVL3, START);
        /*Default*/         std::cout << CYAN "/*Default*/" RESET;      typename vector_type::reverse_iterator it;                             std::cout << std::endl << CYAN "================" RESET << std::endl;
        /*Fill*/            std::cout << CYAN "/*Fill*/" RESET;         typename vector_type::reverse_iterator begin(myVector.rbegin());       std::cout << std::endl << CYAN "================" RESET << std::endl;
        /*Fill assign*/     std::cout << CYAN "/*Fill assign*/";        typename vector_type::reverse_iterator end = myVector.rend();          std::cout << std::endl << CYAN "================" RESET << std::endl;
        /*Copy*/            std::cout << CYAN "/*Copy*/";               typename vector_type::reverse_iterator itcpy(begin);                   std::cout << std::endl << CYAN "================" RESET << std::endl;
        printTitle("End Reverse Constructors", "General", LVL3, END);

    printTitle("Testing REVERSE Member functions", "General", LVL3, START);
    {
                            std::cout << CYAN; printVector<vector_type>("myVector", myVector);                                   std::cout << CYAN "================" RESET << std::endl;
        /*Copy Assignment*/ 
                            std::cout << CYAN "/*Copy Assignment*/" RESET << std::endl;
                            std::cout << CYAN "it = begin | *it: default initialized | begin(myVector.rbegin())" RESET << std::endl;
                            it = begin;
                            std::cout << "(it == begin) = " << (it == begin) << " | true (1) false (0)";            std::cout << std::endl << CYAN "================" RESET << std::endl;
        /*Access Operators*/
                            std::cout << CYAN "/*Access Operators*/" RESET << std::endl;
        /* * */             std::cout << CYAN "operator*\t" RESET << "| *it: " << *it;                              std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* -> */            std::cout << CYAN "operator->\t" RESET << "| *it.operator->(): " << *it.operator->();   std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* [] */            std::cout << CYAN "operator[]\t" RESET;
                            for (long i = 0; i < static_cast<long>(sizeOfVector); i++)
                                std::cout << "| it["<< i << "]:" << it[i] << " ";                                   std::cout << std::endl << CYAN "================" RESET << std::endl;

        /*Arithmetic Operators*/
                            std::cout << CYAN "/*Arithmetic Operators*/" RESET << std::endl;
        /* ()++ */          std::cout << CYAN "++it\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(++it);      std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* ()-- */          std::cout << CYAN "--it\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(--it);      std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* ++() */          std::cout << CYAN "it++\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it++) << "| *it: " << *it;  std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* --() */          std::cout << CYAN "it--\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it--) << "| *it: " << *it;  std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* it+n */          std::cout << CYAN "it+2\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it+2);      std::cout << std::endl << CYAN "================" RESET << std::endl;
        it = end - 1;std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* it-n */          std::cout << CYAN "it-2\t\t" RESET << "|  *it: " << *it << "\t=> *it " << *(it-2);   std::cout << std::endl << CYAN "================" RESET << std::endl;
        it = begin;std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* += */            std::cout << CYAN "it+=2\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it+=2);    std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* -= */            std::cout << CYAN "it-=2\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it-=2);    std::cout << std::endl << CYAN "================" RESET << std::endl;

        printTitle("End Reverse member functions", "General", LVL3, END);

        printTitle("Testing REVERSE Non Member functions", "General", LVL3, START);
                            std::cout << CYAN "| *it: " << *it << "| *itcpy: " << *itcpy << "| *begin: " << *begin << " | true (1) false (0)" RESET << std::endl;
        /* == */            std::cout << CYAN "==\t\t" RESET << "| (it==itcpy): " << (it==itcpy);
                            std::cout << "| (begin==end): " << (begin==end);                                        std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* != */            std::cout << CYAN "!=\t\t" RESET << "| (it!=itcpy): "<< (it!=itcpy);
                            std::cout << "| (begin!=end): "<< (begin!=end);                                          std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* <  */            std::cout << CYAN "<\t\t" RESET << "| (it< itcpy): "<< (it<itcpy); 
                            std::cout << "| (begin< end): "<< (begin<end);                                           std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* <= */            std::cout << CYAN "<=\t\t" RESET << "| (it<=itcpy): "<< (it<=itcpy);
                            std::cout << "| (begin<=end): "<< (begin<=end);                                          std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* >  */            std::cout << CYAN ">\t\t" RESET << "| (it> itcpy): "<< (it>itcpy); 
                            std::cout << "| (begin> end): "<< (begin>end);                                           std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* >= */            std::cout << CYAN ">=\t\t" RESET << "| (it>=itcpy): "<< (it>=itcpy);
                            std::cout << "| (begin>=end): "<< (begin>=end);                                          std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* n+it*/           std::cout << CYAN "n+it\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(2 + it);std::cout << std::endl << CYAN "================" RESET << std::endl;
        /* it-it */         std::cout << CYAN "it-it\t\t" RESET << "| (end-begin): "<< end-begin;                   std::cout << std::endl << CYAN "================" RESET << std::endl;
    }
    printTitle("End Reverse non member functions", "General", LVL3, END);
    printTitle("End test all reverse iterator functions", "General", LVL2, END);

    printTitle("START TEST CONST REVERSE ITERATORS", "General", LVL2, START);
    {
        const vector_type ctest(10, data[value1]); 
        typename vector_type::const_reverse_iterator    cit = ctest.rbegin();
        typename vector_type::const_reverse_iterator    cend = ctest.rend();
        std::cout << CYAN "const Vector ctest(10, 5)" RESET << std::endl;
        for (;cit != cend; cit++) std::cout << *cit << "|"; std::cout << std::endl << CYAN "================" RESET << std::endl;
    }
    printTitle("End test const reverse iterators", "General", LVL2, END);

    printTitle("LOOPING ON REVERSE ITERATORS", "General", LVL2, START);
        end = myVector.rend();
        
        std::cout << YELLOW "Default + assign" RESET; 
        int i = 0;
        for (it = myVector.rbegin(); it != end; it++)
            std::cout  << std::endl << "[" << i++ << "]: " << *it; 
        std::cout << std::endl << CYAN "================" RESET << std::endl;
        
        std::cout << YELLOW "Fill" RESET; 
        i = 0;
        for (it = begin; it != end; it++)
            std::cout  << std::endl << "[" << i++ << "]: " << *it; 
        std::cout << std::endl << CYAN "================" RESET << std::endl;
        
        std::cout << YELLOW "Copy" RESET; 
        i = 0;
        for (it = itcpy; it != end; it++)
            std::cout  << std::endl << "[" << i++ << "]: " << *it; 
        std::cout << std::endl << CYAN "================" RESET << std::endl;
    printTitle("Looping on reverse iterators", "General", LVL2, END);

    printTitle("End test reverse iterators", "General", LVL0, END);
}







// RANDOM ACCESS ITERATOR
template <class vector_type>
void    ftTestRandomAccessIterator(const vector_type & data){
    printTitle("START TEST RANDOM ACCESS ITERATORS", "General", LVL0, START);

    printTitle("START TEST BEGIN END", "General", LVL2, START);
    {
        vector_type digits;
        digits.push_back(data[val1]);
        digits.push_back(data[val2]);
        digits.push_back(data[val3]);
        digits.push_back(data[val4]);
        digits.push_back(data[val5]);
        digits.push_back(data[val6]);

        std::cout << "1º| "<< *digits.begin() << std::endl;
        std::cout << "2º| "<< *(digits.end() - 1) << std::endl;

        typename vector_type::iterator it = digits.begin();
        typename vector_type::iterator ite = digits.end();

        std::cout << "Base begin | it |\t"<< *it.base() << std::endl;
        // std::cout << "Base end | ite |\t"<< *ite.base() << std::endl; //? segfault = normal

        std::cout << "begin - end : " << (it - ite) << std::endl;
        std::cout << "end - begin : " << (ite - it) << std::endl;
    }
    printTitle("End test Rbegin Rend", "General", LVL2, END);



    printTitle("START TEST ALL RANDOM ACCESS ITERATOR FUNCTIONS", "General", LVL2, START);
        std::cout << ITALICS BLUE "-------------------Creating vector" RESET << std::endl;
        vector_type  myVector;
        size_t  sizeOfVector = 4;
        myVector.push_back(data[val1]); //? starts at one specifically to help debug 
        myVector.push_back(data[val2]);
        myVector.push_back(data[val3]);
        myVector.push_back(data[val4]);
        std::cout << BLUE; printVector<vector_type>("myVector", myVector);


        printTitle("Testing RANDOM ACCESS Constructors", "General", LVL3, START);
        /*Default*/         std::cout << BLUE "/*Default*/" RESET;      typename vector_type::iterator it;                                std::cout << std::endl << BLUE "================" RESET << std::endl;
        /*Fill*/            std::cout << BLUE "/*Fill*/" RESET;         typename vector_type::iterator begin(myVector.begin());           std::cout << std::endl << BLUE "================" RESET << std::endl;
        /*Fill assign*/     std::cout << BLUE "/*Fill assign*/";        typename vector_type::iterator end = myVector.end();              std::cout << std::endl << BLUE "================" RESET << std::endl;
        /*Copy*/            std::cout << BLUE "/*Copy*/";               typename vector_type::iterator itcpy(begin);                      std::cout << std::endl << BLUE "================" RESET << std::endl;
        printTitle("End Random access Constructors", "General", LVL3, END);
        
    printTitle("Testing RANDOM ACCESS member functions", "General", LVL3, START);
    {
                            std::cout << BLUE; printVector<vector_type>("myVector", myVector);                                   std::cout << BLUE "================" RESET << std::endl;
        /*Copy Assignment*/ 
                            std::cout << BLUE "/*Copy Assignment*/" RESET << std::endl;
                            std::cout << BLUE "it = begin | *it: default initialized | begin(myVector.begin())" RESET << std::endl;
                            it = begin;
                            std::cout << "(it == begin) = " << (it == begin) << " | true (1) false (0)";            std::cout << std::endl << BLUE "================" RESET << std::endl;
        /*Access Operators*/
                            std::cout << BLUE "/*Access Operators*/" RESET << std::endl;
        /* * */             std::cout << BLUE "operator*\t" RESET << "| *it: " << *it;                              std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* -> */            std::cout << BLUE "operator->\t" RESET << "| *it.operator->(): " << *it.operator->();   std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* [] */            std::cout << BLUE "operator[]\t" RESET;
                            for (long i = 0; i < static_cast<long>(sizeOfVector); i++)
                                std::cout << "| it["<< i << "]:" << it[i] << " ";                                   std::cout << std::endl << BLUE "================" RESET << std::endl;

        /*Arithmetic Operators*/
                            std::cout << BLUE "/*Arithmetic Operators*/" RESET << std::endl;
        /* ()++ */          std::cout << BLUE "++it\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(++it);      std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* ()-- */          std::cout << BLUE "--it\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(--it);      std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* ++() */          std::cout << BLUE "it++\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it++) << "| *it: " << *it;  std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* --() */          std::cout << BLUE "it--\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it--) << "| *it: " << *it;  std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* it+n */          std::cout << BLUE "it+2\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it+2);      std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* it-n */          std::cout << BLUE "it-2\t\t" RESET << "| *(end-1): "<< *(end-1) << "\t=> *(end-1)-2: " << *(end-1-2);   std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* += */            std::cout << BLUE "it+=2\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it+=2);    std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* -= */            std::cout << BLUE "it-=2\t\t" RESET << "| *it: " << *it << "\t=> *it: " << *(it-=2);    std::cout << std::endl << BLUE "================" RESET << std::endl;

    printTitle("End Random access member functions", "General", LVL3, END);

    printTitle("Testing RANDOM ACCESS non member functions", "General", LVL3, START);
                            std::cout << BLUE "| *it: " << *it << "| *itcpy: " << *itcpy << "| *begin: " << *begin << " | true (1) false (0)" RESET << std::endl;
        /* == */            std::cout << BLUE "==\t\t" RESET << "| (it==itcpy): " << (it==itcpy);
                            std::cout << "| (begin==end): " << (begin==end);                                        std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* != */            std::cout << BLUE "!=\t\t" RESET << "| (it!=itcpy): "<< (it!=itcpy);
                            std::cout << "| (begin!=end): "<< (begin!=end);                                          std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* <  */            std::cout << BLUE "<\t\t" RESET << "| (it< itcpy): "<< (it<itcpy); 
                            std::cout << "| (begin< end): "<< (begin<end);                                           std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* <= */            std::cout << BLUE "<=\t\t" RESET << "| (it<=itcpy): "<< (it<=itcpy);
                            std::cout << "| (begin<=end): "<< (begin<=end);                                          std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* >  */            std::cout << BLUE ">\t\t" RESET << "| (it> itcpy): "<< (it>itcpy); 
                            std::cout << "| (begin> end): "<< (begin>end);                                           std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* >= */            std::cout << BLUE ">=\t\t" RESET << "| (it>=itcpy): "<< (it>=itcpy);
                            std::cout << "| (begin>=end): "<< (begin>=end);                                          std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* n+it*/           std::cout << BLUE "n+it\t\t" RESET << "| begin: " << *begin << " | 2 + begin: " << *(2 + begin);std::cout << std::endl << BLUE "================" RESET << std::endl;
        /* it-it */         std::cout << BLUE "it-it\t\t" RESET << "| (end-begin): "<< end-begin;                   std::cout << std::endl << BLUE "================" RESET << std::endl;
    }
    printTitle("End Random access non member functions", "General", LVL3, END);
    printTitle("End test all random access iterator functions", "General", LVL2, END);

    printTitle("START TEST CONST RANDOM ACCESS ITERATORS", "General", LVL2, START);
    {
        const vector_type ctest(10, data[value1]); 
        typename vector_type::const_iterator cit = ctest.begin();
        typename vector_type::const_iterator cend = ctest.end();
        std::cout << BLUE "const Vector ctest(10, 5)" RESET << std::endl;
        for (;cit != cend; cit++) std::cout << *cit << "|"; std::cout << std::endl << BLUE "================" RESET << std::endl;
    }
    printTitle("End test const random access iterators", "General", LVL2, END);

    printTitle("LOOPING ON REVERSE ITERATORS", "General", LVL2, START);
        std::cout << BLUE; printVector<vector_type>("myVector", myVector);
        end = myVector.end();
        
        std::cout << YELLOW "Default + assign" RESET; 
        int i = 0;
        for (it = myVector.begin(); it != end; it++)
            std::cout  << std::endl << "[" << i++ << "]: " << *it; 
        std::cout << std::endl << BLUE "================" RESET << std::endl;
        
        std::cout << YELLOW "Fill" RESET; 
        i = 0;
        for (it = begin; it != end; it++)
            std::cout  << std::endl << "[" << i++ << "]: " << *it; 
        std::cout << std::endl << BLUE "================" RESET << std::endl;
        
        std::cout << YELLOW "Copy" RESET; 
        i = 0;
        for (it = itcpy; it != end; it++)
            std::cout  << std::endl << "[" << i++ << "]: " << *it; 
        std::cout << std::endl << BLUE "================" RESET << std::endl;
    printTitle("Looping on random access iterators", "General", LVL2, END);

    printTitle("End test random access iterators", "General", LVL0, END);
}

#endif
// ============================================================================<<test_iterator.hpp============================================================================
