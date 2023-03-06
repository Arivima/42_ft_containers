# 42_ft_containers
passed with bonus 125%

## includes 
<b>Containers</b> | Vector, Map, Set, Stack
<b>Trees</b> | Red_black Tree working with nodes (internal / unique external nil node / end node), with commented debug lines to see step by step fixup manipulations, includes also binary search tree code
<b>Iterators</b> | RandomAccess iterators, reverse iterators, RBTree iterators
<b>Utils</b> | swap, remove_const, enable_if, integral_constant, bool_constant, false_type, true_type, is_same, is_integral, iterator_tags, is_iterator, iterator_traits, lexicographical_compare, equal, pair, make_pair


## Testers used

<b>Own exhaustive tester</b>
Testing int, float, double for all containers, testing all functions
This tester found a few mistakes that other testers didn't find

flags used during testing
-Wall -Wextra -Werror -std=c++98 -Wshadow -fsanitize=address

left all code for debug commented

<b>https://github.com/mli42/containers_test.git</b>
Passed 100%

<b>https://github.com/divinepet/ft_containers-unit-test</b>
Passed 100% Map, Stack, Set
Utilities 4/5 | Used own recoded iterator tags, passing 5/5 when std tags are used
Vector 34/36 | resize fails, added alternative resize commented version that passes this tester but fails my own test against std |  insert(range) fails, who knows why

<b>Main provided on subject page</b>
