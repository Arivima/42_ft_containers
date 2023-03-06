/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:47:05 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/03 11:47:06 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.hpp"

void    ftTestUtils()
{
    ftTestUtilsPair();
    return ;
}

void    ftTestUtilsPair()
{
    printTitle("START TEST UTILS", "General", LVL0, START);
        std::cout<< "Testing Pair "  << std::endl;
        typedef int T1; typedef int T2;
        T1  A_first = 2; T2  A_second = 2;
        T1  B_first = 2; T2  B_second = 3;
        // typedef float T1; typedef int T2;
        // T1  A_first = 56.35; T2  A_second = 2;
        // T1  B_first = 89.52; T2  B_second = 3;
        {
            ft::pair<T1, T2> A; std::cout << "| Testing Pair "<< "| pair<T1, T2> A\t\t" <<"| A ("<< A.first <<", "<< A.second << ")" << std::endl;
        }
        {
            ft::pair<T1, T2> A(A_first, A_second); std::cout << "| Testing Pair "<< "| pair<T1, T2> A(x, y)\t" <<"| A ("<< A.first <<", "<< A.second << ")" << std::endl;
            ft::pair<T1, T2> B(A); std::cout << "| Testing Pair "<< "| pair<T1, T2> B(A)\t" <<"| B ("<< B.first <<", "<< B.second << ")" << std::endl;
            ft::pair<T1, T2> C = ft::make_pair(A_first, A_second); std::cout << "| Testing Pair "<< "| C=make_pair(A_x, A_y)\t" <<"| C ("<< C.first <<", "<< C.second << ")" << std::endl;
        }

        {
            ft::pair<T1, T2> A (A_first, A_second);
            ft::pair<T1, T2> B = ft::pair<T1, T2>(B_first, B_second);
            std::cout << "------------" << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<") == B ("<< B.first <<", "<< B.second <<")\t" << (A == B) << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<") != B ("<< B.first <<", "<< B.second <<")\t" << (A != B) << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<") <  B ("<< B.first <<", "<< B.second <<")\t" << (A < B) << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<") <= B ("<< B.first <<", "<< B.second <<")\t" << (A <= B) << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<") >  B ("<< B.first <<", "<< B.second <<")\t" << (A > B) << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<") >= B ("<< B.first <<", "<< B.second <<")\t" << (A >= B) << std::endl;
            std::cout << "------------" << std::endl;
            std::cout << "| Testing Pair "<< "| B ("<< B.first <<", "<< B.second <<") == A ("<< A.first <<", "<< A.second <<")\t" << (B == A) << std::endl;
            std::cout << "| Testing Pair "<< "| B ("<< B.first <<", "<< B.second <<") != A ("<< A.first <<", "<< A.second <<")\t" << (B != A) << std::endl;
            std::cout << "| Testing Pair "<< "| B ("<< B.first <<", "<< B.second <<") <  A ("<< A.first <<", "<< A.second <<")\t" << (B < A) << std::endl;
            std::cout << "| Testing Pair "<< "| B ("<< B.first <<", "<< B.second <<") <= A ("<< A.first <<", "<< A.second <<")\t" << (B <= A) << std::endl;
            std::cout << "| Testing Pair "<< "| B ("<< B.first <<", "<< B.second <<") >  A ("<< A.first <<", "<< A.second <<")\t" << (B > A) << std::endl;
            std::cout << "| Testing Pair "<< "| B ("<< B.first <<", "<< B.second <<") >= A ("<< A.first <<", "<< A.second <<")\t" << (B >= A) << std::endl;
            std::cout << "------------" << std::endl;
            std::cout << "| Testing Pair "<< "| A ("<< A.first <<", "<< A.second <<")| B ("<< B.first <<", "<< B.second <<")"<< "| (A = B) "; A = B; std::cout << "| A ("<< A.first <<", "<< A.second <<")| B ("<< B.first <<", "<< B.second <<")" << std::endl;
        }
    printTitle("End test Utils", "General", LVL0, END);
    return ;
}