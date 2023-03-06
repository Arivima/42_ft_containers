# 42_ft_containers
passed with bonus 125%

## Includes 
<b>Containers</b>  
Vector, Map, Set, Stack

<b>Trees</b>  
Red_black Tree working with nodes (internal / unique external nil node / end node), with commented debug lines to see step by step fixup manipulations, includes also binary search tree code

<b>Iterators</b>  
RandomAccess iterators, reverse iterators, RBTree iterators

<b>Utils</b>  
swap, remove_const, enable_if, integral_constant, bool_constant, false_type, true_type, is_same, is_integral, iterator_tags, is_iterator, iterator_traits, lexicographical_compare, equal, pair, make_pair

## Ressources & Research
<b>C++ ressources</b>  
Amazing exhaustive step by step lessons and tuto [learncpp.com](https://www.learncpp.com/)  
My own personal notes from [CPP_piscine](https://docs.google.com/document/d/1sJmcwJ2TpBea9qtBLYcQk0gQs0x8nNDgrh1IbuxkQEY/edit#heading=h.unwxh1f29wir)  
[C++ language reference](https://en.cppreference.com/w/cpp/language)  
[C++ types](https://en.cppreference.com/w/cpp/language/type)  
[Named Requirements](https://en.cppreference.com/w/cpp/named_req)  

<b>Containers</b>  
Containers library from [cppreference.com](https://en.cppreference.com/w/cpp/container)  
Containers library from [cplusplus.com](https://cplusplus.com/reference/stl/)  
My own personal notes while researching for [ft_containers](https://docs.google.com/spreadsheets/d/1L9F9KSd2TZ2Avx2H7hctTRYRkVgJUvJ0G8yin7XbfPo/edit#gid=595240115)  

<b>Important stuff you also need to learn with ft_containers</b>  
[Metaprogramming library](https://en.cppreference.com/w/cpp/meta)  
[SFINAE](https://www.fluentcpp.com/2018/05/15/make-sfinae-pretty-1-what-value-sfinae-brings-to-code/)  
[rebind stackoverflow](https://stackoverflow.com/questions/14148756/what-does-template-rebind-do)  
[rebind cplusplus](https://cplusplus.com/reference/memory/allocator/rebind/)  

<b>Red_Black_trees</b>  
[Introduction to Algorithms, Third Edition](https://sd.blackball.lv/library/Introduction_to_Algorithms_Third_Edition_(2009).pdf)  
My own personal notes while researching for [RB_tree](https://docs.google.com/document/d/1EsAQB54D8K_JvL7gNO97rQZ7c1GBS_PtVPdsmDUdosQ/edit#heading=h.dunhhts3lz17)  
[RB_trees Youtube playlist](https://www.youtube.com/playlist?list=PL9xmBV_5YoZNqDI8qfOZgzbqahCUmUEin)  

<b>Iterators</b>  
[Iterator library](https://en.cppreference.com/w/cpp/iterator)  
[reverse iterators](https://en.cppreference.com/w/cpp/iterator/reverse_iterator)  


[one-click full list](https://www.one-tab.com/page/0eNlBgltTUCASSjdpRQ6-Q)  


## Testers perf

<b>~ Own tester</b> | 100%  
</t>Exhaustive tester, testing int, float, double for all containers, testing all functions.  
</t>This tester found a few mistakes that other testers didn't find. 
</t>Flags used during testing : -Wall -Wextra -Werror -std=c++98 -Wshadow -fsanitize=address  
</t>Left all code for debug commented.  

<b>~ [containers_test](https://github.com/mli42/containers_test.git) </b >by mli42 | 100%

<b>~ [ft_containers-unit-test](https://github.com/divinepet/ft_containers-unit-test) </b>  by divinepet | 97%    
100% | Map, Stack, Set  
4/5 | Utilities | iterator_traits failed (fake fail) bc used own recoded iterator tags, tester only checks against std tags, passing 5/5 with std tags  
34/36 | Vector  | rezise failed (weird fail), not sure why, added alternative resize commented version that passes this tester but fails my own test against std |  insert(range) fails (true fail), who knows why

<b>~ Main provided on subject page</b> | 100%

~ Other ft_containers testers non tested on this project
 | [ft_containers_monkey_tester](https://github.com/jgiron42/ft_containers_monkey_tester)
 | [ft_containers-terminator](https://github.com/Mikastiv/ft_containers-terminator)
 | [ft_containers_tests](https://github.com/mamoussa405/ft_containers_tests)

<b>~ This repo includes both correction sheet and subject at the time of evaluation</b>
