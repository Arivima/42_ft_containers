/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:47:02 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 16:11:22 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"           // libraries, colors and debug settings
#include "test_stack.hpp"

void testAllStack()
{
    printTitle("START TEST STACK", "General", LVL0, START);
    std::cout << BRED "TESTING INT" RESET << std::endl;
    ft::vector<int> data_int;
    FillVectorDataType<ft::vector<int>, int>(&data_int, 5, 10, 1, 2, 3, 4, 5, 6);
    printVector<ft::vector<int> >("data_int", data_int);
    ftTestStack<int>(data_int);

    std::cout << BRED "TESTING DOUBLE" RESET << std::endl;
    ft::vector<double> data_double;
    FillVectorDataType<ft::vector<double>, double>(&data_double, 5.5, 10.10, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6);
    printVector<ft::vector<double> >("data_double", data_double);
    ftTestStack<double>(data_double);

    std::cout << BRED "TESTING FLOAT" RESET << std::endl;
    ft::vector<float> data_float;
    FillVectorDataType<ft::vector<float>, float>(&data_float, 5.5f, 10.10f, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f);
    printVector<ft::vector<float> >("data_float", data_float);
   ftTestStack<float>(data_float);

    printTitle("END TEST STACK", "General", LVL0, END);
    return ;
}