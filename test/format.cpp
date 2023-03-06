/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:47 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/03 17:39:39 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"
#include "compilation.hpp"

void    print(int flag, std::string color, std::string string){
    if (flag)
        std::cout << color << string << RESET << std::endl;
    return;
}

void    printTitle(std::string title, std::string name, int level, bool startEnd){
    std::string color;
    switch (level){
    case LVL:   if (startEnd == START)  color = BBLACK;     else color = BLACK;    break;
    case LVL0:  if (startEnd == START)  color = BYELLOW;    else color = YELLOW;    break;
    case LVL1:  if (startEnd == START)  color = BMAGENTA;   else color = MAGENTA;   break;
    case LVL2:  if (startEnd == START)  color = BCYAN;      else color = CYAN;      break;
    case LVL3:  if (startEnd == START)  color = BWHITE;     else color = WHITE;     break;
    default:    if (startEnd == START)  color = BWHITE;     else color = WHITE;     break;
    }

    std::string line;
    if (level == LVL0)
        std::cout   << std::setfill('=');
    else
        std::cout   << std::setfill('-');

    std::string chevron;
    if (startEnd == START)
        chevron  = ">>";
    else
        chevron  = "<<";

        std::cout   << color << std::setw(45) << std::right << " " + name 
                    << " " + chevron + " " 
                    << std::left << std::setw(60)  << title + " " << BWHITE;
        if (DEBUG_FT)
            std::cout << " "  COMPILE_MODE_TXT  " ";
        std::cout << RESET << std::endl;
    return;
}

void    setStreamColor(bool a, bool b){
    if (a == b)
        std::cout << GREEN;
    else
        std::cout << RED;

    return;
}