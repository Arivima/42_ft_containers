/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:45:53 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 15:20:20 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>header.hpp============================================================================
#ifndef HEADER_HPP
# define HEADER_HPP

/// GENERAL and TOOLS
    // header
        #include <iostream>
        #include <stdexcept>
        #include <iomanip>          //* setw
        #include <cstddef>          //* size_type
    // Debug
        # define DEBUG_V    0
        # define DEBUG_VALL 0
        # define DEBUG_IT   0
        # define DEBUG_RIT  0
        # define DEBUG_FT      (DEBUG_V | DEBUG_IT | DEBUG_RIT)

        # define SHOW(...)      std::cout << std::setw(5) << #__VA_ARGS__ << " = " << __VA_ARGS__ << '\n' // SHOW( std::is_integral<int>::value );
    // format.cpp
        # define START          0
        # define END            1
        enum    TITLE_LEVELS    { LVL, LVL0, LVL1, LVL2, LVL3 };
        void    setStreamColor  (bool a, bool b);
        void    printTitle      (std::string title, std::string name, int level, bool startEnd);
        void    print(int flag, std::string color, std::string string);
    
    // colors
        # define RESET          "\033[0m"
        # define BOLD           "\033[1m"
        # define FAINT          "\033[2m"
        # define ITALICS        "\033[3m"
        # define UNDERLINED     "\033[4m"
        // Foreground
        # define BLACK          "\033[30m"
        # define RED            "\033[31m"
        # define GREEN          "\033[32m"
        # define YELLOW         "\033[33m"
        # define BLUE           "\033[34m"
        # define MAGENTA        "\033[35m"
        # define CYAN           "\033[36m"
        # define LIGHTGRAY      "\033[37m"
        # define GRAY           "\033[90m"
        # define WHITE          "\033[97m"
        // Background
        # define BBLACK          "\033[40m"
        # define BRED            "\033[41m"
        # define BGREEN          "\033[42m"
        # define BYELLOW         "\033[43m"
        # define BBLUE           "\033[44m"
        # define BMAGENTA        "\033[45m"
        # define BCYAN           "\033[46m"
        # define BWHITE          "\033[47m"
#endif
// ============================================================================>>header.hpp============================================================================
