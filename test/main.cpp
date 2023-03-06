/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:50 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 16:10:58 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"           // libraries, colors and debug settings
#include "test_vector.hpp"
#include "test_iterator.hpp"
#include "test_utils.hpp"
#include "test_map.hpp"
#include "test_stack.hpp"
#include "test_set.hpp"

int main ()
{
    // if (DEBUG)
      // std::cout << BRED COMPILE_MODE_TXT RESET << std::endl;

    printTitle("WELCOME TO FT_CONTAINERS", "", LVL, START);
    printTitle("TESTING FT_CONTAINERS", "", LVL, START);

      ftTestUtils(); 
      testAllIterators(); 
      testAllVector();
      testAllMap();
      testAllStack(); 
      testAllSet(); 

    printTitle("TESTING FT_CONTAINERS", "", LVL, END);
}
