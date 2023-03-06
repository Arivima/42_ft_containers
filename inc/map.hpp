/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:07 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 14:54:19 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>map.hpp============================================================================
// Map class is referenced from: 
    // https://en.cppreference.com/w/cpp/container/map
    // https://cplusplus.com/reference/map/map/
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Map structure:
    /// Member types
        //  key_type;   mapped_type;    value_type;  key_compare;    allocator_type; size_type; difference_type;
        //  reference;  const_reference;    pointer;    const_pointer;  
        //  iterator;   const_iterator;     reverse_iterator;   const_reverse_iterator;
    /// Member functions
            // Basics           // Constructors | Destructor | operator= | get_allocator
            // ElementAccess    // at | operator[]
            // Iterators        // begin | end | rbegin | rend
            // Capacity         // empty | size | max_size
            // Modifiers        // clear | insert | erase | swap
            // Lookup           // count | find | equal_range | lower_bound | upper_bound
            // Observers        // key_comp | value_comp
    /// Non Member functions
            // ft::swap
// --------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef     MAP_HPP
# define    MAP_HPP

#include "header.hpp"
#include "iterator_reverse.hpp" // ft::reverse_iterator<iterator>
#include "map_RB_Tree.hpp"      // ft::_s_RB_Node<> | ft::RB_Tree<> | ft::tree_iterator<>
#include "utils.hpp"            // ft::pair< Key, T> |  ft::enable_if | ft::is_iterator_tagged | ft::make_pair | ft::swap
#include <functional>           // std::binary_function //TODO ideally, to recode

namespace ft
{
    template <
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair< const Key, T> >
    > class map {
// ============================================================================>>MapClassDeclaration====================================================
//* Member Classes (value_compare added to member types)====================================================================================================
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// std::map<Key,T,Compare,Allocator>::value_compare
// Function object that compares objects of type std::map::value_type (key-value pairs) by comparing of the first components of the pairs.
// Mmember types are obtained via publicly inheriting std::binary_function<value_type, value_type, bool>.
// https://en.cppreference.com/w/cpp/container/map/value_compare
    // std::binary_function
    // template< class Arg1, class Arg2, class Result > struct binary_function;
    // binary_function is a base class for creating function objects with two arguments.                                              
    // binary_function does not define operator(); it is expected that derived classes will define this. 
    // binary_function provides only three types - first_argument_type, second_argument_type and result_type - defined by the template parameters.
    // Some standard library function object adaptors, such as std::not2, require the function objects they adapt to have certain types defined; 
    // std::not2 requires the function object being adapted to have two types named first_argument_type and second_argument_type. 
    // Deriving function objects that take two arguments from binary_function is an easy way to make them compatible with those adaptors.
    // https://en.cppreference.com/w/cpp/utility/functional/binary_function
// --------------------------------------------------------------------------------------------------------------------------------------------------------
//* Member types============================================================================================================================================
        public:                 // Definition                                       // Member type      // recap
            typedef             const Key                                           key_type;     // Key
            typedef             T                                                   mapped_type;        // T
        private:
            typedef             Allocator                                           pair_alloc_type;     // Alloc of pair<const Key, T>
        public:
            typedef typename    pair_alloc_type::value_type                         value_type;         // ft::pair<const Key, T>
            typedef             std::size_t                                         size_type;          // unsigned long
            typedef             std::ptrdiff_t                                      difference_type;    // long
            typedef             Compare                                             key_compare;        // Compare

            class value_compare : public std::binary_function<value_type, value_type, bool> 
            {                                           
                    friend class         map;
                // Member objects
                protected:
                    key_compare             _comp;
                // Member types             // as inherited from parent class std::binary_function<value_type, value_type, bool>
                public:
                    // typedef bool         result_type;                    
                    // typedef value_type	first_argument_type;
                    // typedef value_type	second_argument_type;
                // Member functions
                    value_compare(key_compare c) : _comp(c){};
                    bool operator() (const value_type& lhs, const value_type& rhs) const {return _comp(lhs.first, rhs.first);};
            };

        // tree typedef         // Definition                                       // Member type      // recap
        private: 
            typedef             userdefined::_s_RB_Node<value_type>                 node_type;          // node<pair<const Key, T>>
            typedef             userdefined::_s_RB_Node<value_type>*                node_ptr;           // node<pair<const Key, T>> *
            typedef typename    pair_alloc_type::template rebind<node_type>::other  alloc_node_type;    // Alloc of node<pair<const Key, T>> 		        // std::allocator.rebind<Type> 
            typedef             userdefined::RB_Tree<pair_alloc_type, key_compare>  tree_type;          // Tree of Allocator of node<pair<const Key, T>>    // will rebind in RB_Tree

        public:                 // Definition                                       // Member type      // recap
            typedef             alloc_node_type                                     allocator_type;     // Alloc of             node<pair<const Key, T>>
            typedef             value_type&                                         reference;          // reference to a       pair<const Key, T>
            typedef const       value_type&                                         const_reference;    // const reference to a pair<const Key, T>
            typedef             node_ptr                                            pointer;            // Pointer to a         node<pair<const Key, T>>
            typedef const       pointer                                             const_pointer;      // const Pointer to a   node<pair<const Key, T>>
            typedef             userdefined::tree_iterator<node_type>               iterator;           // iterator to a        node<pair<const Key, T>>
            typedef             userdefined::tree_const_iterator<node_type>         const_iterator;     // const iterator to a  node<pair<const Key, T>>
            typedef typename    ft::reverse_iterator<iterator>                      reverse_iterator;   // reverse it to a      node<pair<const Key, T>>
            typedef typename    ft::reverse_iterator<const_iterator>                const_reverse_iterator;// const rev it to a node<pair<const Key, T>>

        private:
			allocator_type      _allocator;
			key_compare         _compare;
			tree_type     	    _tree;
			size_type           _size;

//* Member Functions========================================================================================================================================
        public:
            // Basics           // Constructors | Destructor | operator= | get_allocator
            // ElementAccess    // at | operator[]
            // Iterators        // begin | end | rbegin | rend
            // Capacity         // empty | size | max_size
            // Modifiers        // clear | insert | erase | swap
            // Lookup           // count | find | equal_range | lower_bound | upper_bound
            // Observers        // key_comp | value_comp
// ============================================================================>>ftMapBasics===================================================================
///* Constructors | Destructor | operator= | get_allocator
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Constructors | Constructs new container from a variety of data sources and optionally using user supplied allocator alloc or comparison function object comp.
// 1-2) Constructs an empty container.
// 4)   Constructs the container with the contents of the range [first, last). 
//      If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted (pending LWG2844).
// 6)   Copy constructor. Constructs the container with the copy of the contents of other.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1*/ /*2*/ // Default
            explicit map( 
                const key_compare&      comp = key_compare(), 
                const allocator_type&   alloc = allocator_type() 
                )
            : _allocator(alloc), _compare(comp), _tree(), _size() {}
            /*4*/       // Range
            template< class InputIt >
            map(
                typename ft::enable_if < ft::is_iterator_tagged< typename InputIt::iterator_category >::value, InputIt > ::type first,
                InputIt last,
                const key_compare& comp = key_compare(),
                const Allocator& alloc = Allocator()
                )
            : _allocator(alloc), _compare(comp), _tree(), _size() {
                this->insert(first, last);
            }
            /*6*/       // Copy
            map(const map& other)
            : _allocator(other._allocator), _compare(other._compare), _tree(), _size() {
                *this = other;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Destructor | Destructs the map. The destructors of the elements are called and the used storage is deallocated. Note, that if the elements are pointers, 
// the pointed-to objects are not destroyed.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            ~map(){}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator=    | 1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            map& operator=(const map& other){
				this->clear();
				this->_allocator = other._allocator;
				this->_compare = other._compare;
                this->_tree = other._tree;
				return (*this);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// get_allocator    | Returns the allocator associated with the container.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            // allocator_type get_allocator() const{return (this->_allocator);} 
            allocator_type get_allocator() const{return (this->_allocator);} //TODO currently returning wrong allocator (pair instead of node) to fit with std tester
// ============================================================================<<ftMapBasics==================================================================

// ============================================================================>>ftMapElementAccess===================================================================
//* ElementAccess    // at | operator[]
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// at   | Returns a reference to the mapped value of the element with key equivalent to key. If no such element exists, an exception of type std::out_of_range is thrown.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
     		mapped_type&        at (const key_type& key) {
				pointer node = _tree.search(key);
				if (userdefined::_is_nil<value_type>(node))
					throw std::out_of_range("key not found");
				return node->content.second;
			}
     		const mapped_type&  at (const key_type& key) const {
				pointer node = _tree.search(key);
				if (userdefined::_is_nil<value_type>(node))
					throw std::out_of_range("key not found");
				return node->content.second;
			}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator[]   | Returns a reference to the value that is mapped to a key equivalent to key, performing an insertion if such key does not already exist.
//              1) Inserts value_type(key, T()) if the key does not exist.
//                  -key_type must meet the requirements of CopyConstructible.
//                  -mapped_type must meet the requirements of CopyConstructible and DefaultConstructible.
//              If an insertion is performed, the mapped value is value-initialized (default-constructed for class types, zero-initialized otherwise) and a reference to it is returned.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			mapped_type& operator[] (const key_type& key){
				pointer node = _tree.search(key);
				if (userdefined::_is_nil<value_type>(node))
                    node = _tree.insert(value_type(key, T()));
                return node->content.second;
			}
// ============================================================================<<ftMapElementAccess==================================================================

// ============================================================================>>ftMapIterators===================================================================
//* Iterators        // begin | end | rbegin | rend
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// begin    | returns an iterator to the beginning.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            iterator begin()				        {pointer ptr; if (this->empty()) ptr = userdefined::get_end_node<value_type>(); else ptr = this->_tree.min(); return iterator(ptr, this->_tree.max());}
            const_iterator begin()          const   {pointer ptr; if (this->empty()) ptr = userdefined::get_end_node<value_type>(); else ptr = this->_tree.min(); return const_iterator(ptr, this->_tree.max());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// end      | returns an iterator to the end.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            iterator end()					        {return iterator(userdefined::get_end_node<value_type>(), this->_tree.max());}
            const_iterator end()            const   {return const_iterator(userdefined::get_end_node<value_type>(), this->_tree.max());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// rbegin    | Returns a reverse iterator to the first element of the reversed map. It corresponds to the last element of the non-reversed map. 
//              If the map is empty, the returned iterator is equal to rend().
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            reverse_iterator rbegin()               {return reverse_iterator(end());}
            const_reverse_iterator rbegin() const   {return const_reverse_iterator(end());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// rend      | Returns a reverse iterator to the element following the last element of the reversed map. It corresponds to the element preceding the first
//              element of the non-reversed map. This element acts as a placeholder, attempting to access it results in undefined behavior.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            reverse_iterator rend()                 {return reverse_iterator(begin());}
            const_reverse_iterator rend()   const   {return const_reverse_iterator(begin());}
// ============================================================================<<ftMapIterators==================================================================

// ============================================================================>>ftMapCapacity===================================================================
//* Capacity         // empty | size | max_size
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// empty    | Checks if the container has no elements, i.e. whether begin() == end(). Returns true if the container is empty, false otherwise
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            bool empty() const                      {return (this->_tree.empty());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// size    | Returns the number of elements in the container, i.e. std::distance(begin(), end()). Returns The number of elements in the container.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            size_type size() const                  {return (this->_tree.size());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// max_size | Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
//              i.e. std::distance(begin(), end()) for the largest container.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            size_type max_size() const              {return (this->_tree.max_size());}
// ============================================================================<<ftMapCapacity==================================================================

// ============================================================================>>ftMapModifiers===================================================================
//* Modifiers        // clear | insert | erase | swap
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// clear    | Erases all elements from the container. After this call, size() returns zero. 
//              Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterator remains valid.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            void clear()                            {this->_tree.clear(); return;}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// insert   | Inserts element(s) into the container, if the container doesn't already contain an element with an equivalent key. No iterators or references are invalidated.
//          1-3) Inserts value. | Returns a pair consisting of an iterator to the inserted element (or to the element that prevented the insertion) and a 
//              bool value set to true if and only if the insertion took place.
//          4-6) Inserts value in the position as close as possible to the position just prior to pos. 
//              | Returns an iterator to the inserted element, or to the element that prevented the insertion.
//          7) Inserts elements from range [first, last). If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted (pending LWG2844).
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1*/       // Default Value
            ft::pair<iterator, bool>   insert(const value_type& value){
                pointer node = this->_tree.search(value.first);
                if (userdefined::_is_nil<value_type>(node)) {
                    node = this->_tree.insert(value);
                    return (ft::make_pair(iterator(node, this->_tree.max()), true));
                }
                return (ft::make_pair(iterator(node, this->_tree.max()), false));
            }
            
            /*4*/       // Hint Value
            iterator    insert(iterator, const value_type& value){
				return ((this->insert(value)).first);				
			}
            //TODO impossible to have an hinted insert with current tree, need to redo the tree functions if we need to do with hint, see draft code below for insert with hint
            // pointer successor;
            // if (_compare((*position).first, value.first)){                                                           // if position < value
            //     successor = _tree.get_successor(position.base());
            // 	if (userdefined::_is_end<value_type>(successor) || _compare(value.first, successor->content.first)){                 // insert if successor is end node or position < value < successor
            // 		std::cout << "ici" << std::endl;
            //         node = _tree.insert(position.base(), value);
            // 		return iterator(node);	
            // 	}
            // }

            /*7*/       // Range
            //TODO functions are not protected aginst invalid range or inverted range => for endless loop
            template< class InputIt >
            void    insert(
                            typename ft::enable_if < ft::is_iterator_tagged< typename InputIt::iterator_category >::value, InputIt > ::type first,
                            InputIt last
                            ){
                if (false == ft::is_iterator_tagged<typename ft::iterator_traits<InputIt>::iterator_category >::value)
                    return ;
                if ((ft::distance(first, last)) > static_cast<difference_type>(this->max_size()))
                    throw std::length_error("map");
                for (; first != last; first++)
                    this->insert(*first);
            }

// --------------------------------------------------------------------------------------------------------------------------------------------------------
// erase    | Removes specified elements from the container.
//          1,2) Removes the element at pos. | returns Iterator following the last removed element.
//          3) Removes the elements in the range [first, last), which must be a valid range in *this. | returns Iterator following the last removed element.
//          4) Removes the element (if one exists) with the key equivalent to key. References and iterators to the erased elements are invalidated. 
//              Other references and iterators are not affected. | returns Number of elements removed (0 or 1). | throws  Any exceptions thrown by the Compare object.
//          The iterator pos must be valid and dereferenceable. Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            //TODO functions are not protected aginst invalid range or inverted range => for endless loop
            /*1*/       // single iterator
            iterator erase(iterator position){
                key_type                    key= (*position).first;
                ft::pair<pointer, bool>     ret= this->_tree.remove(key);

                if (ret.second == true)
                    return iterator(ret.first, this->_tree.max());
                return position;
			}
            /*3*/       // range iterator
            iterator erase(iterator first, iterator last){
				ft::pair<pointer, bool>     ret;
                iterator                    ret_it = first;     // to prevent segfault

                while (first != last){
					key_type key = (*first).first;
					++first;
                    ret = this->_tree.remove(key);              // return (successor, true) or (nil, false)
                    if (ret.second == true)
                        ret_it = iterator(ret.first, this->_tree.max());
				}
                if (this->_tree.empty())
                    return iterator(userdefined::get_end_node<value_type>(), this->_tree.max());
                return ret_it;
			}     
            /*4*/       // single key
            size_type erase(const key_type& key){
				return (this->_tree.remove(key)).second;
			}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// swap    | Exchanges the contents of the container with those of other. Does not invoke any move, copy, or swap operations on individual elements.
//              All iterators and references remain valid. The past-the-end iterator is invalidated.
//              The Compare objects must be Swappable, and they are exchanged using unqualified call to non-member swap.
//          std::swap => template< class T > void swap( T& a, T& b ){T c = a; a = b; b = c;}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			void swap (map& other){
				ft::swap(this->_allocator, other._allocator);
				ft::swap(this->_compare, other._compare);
				ft::swap(this->_size, other._size);
				tree_type::swap_tree(this->_tree, other._tree);
			}
// ============================================================================<<ftMapModifiers==================================================================

// ============================================================================>>ftMapLookup===================================================================
//* Lookup           // count | find | equal_range | lower_bound | upper_bound
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// count    | Returns the number of elements with key that compares equivalent to the specified argument.
//          1) Returns the number of elements with key key. This is either 1 or 0 since this container does not allow duplicates.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            size_type       count( const key_type& key ) const      {return this->_tree.count(key);}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// find    | 1,2) Returns Iterator to an element with key equivalent to key. If no such element is found, past-the-end (see end()) iterator is returned.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            iterator        find( const key_type& key )             {return iterator(this->_tree.find(key), this->_tree.max());}
            const_iterator  find( const key_type& key ) const       {return const_iterator(this->_tree.find(key), this->_tree.max());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// lower_bound    | 1,2) Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
//                  ret : Iterator pointing to the first element that is not less than key. If no such element is found, a past-the-end iterator (see end()) is returned.
//                  If no such element is found, a past-the-end iterator (see end()) is returned.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			iterator lower_bound(const key_type& key){
                node_ptr node = userdefined::get_end_node<value_type>();
                // std::cout << "hello" << std::endl;
                if (this->empty())
                    return iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<value_type>(node) && userdefined::_is_not_end_node<value_type>(node) && _compare(node->content.first, key))
                    node = userdefined::get_successor<value_type>(node);
                return iterator(node, this->_tree.max());

			}
			const_iterator lower_bound(const key_type& key) const{
                node_ptr node = userdefined::get_end_node<value_type>();
                if (this->empty())
                    return const_iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<value_type>(node) && userdefined::_is_not_end_node<value_type>(node) && _compare(node->content.first, key))
                    node = userdefined::get_successor<value_type>(node);
                return const_iterator(node, this->_tree.max());
			}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// upper_bound    | 1,2) Returns an iterator pointing to the first element that is greater than key.
//                  ret : Iterator pointing to the first element that is greater than key. If no such element is found, past-the-end (see end()) iterator is returned.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			iterator upper_bound(const key_type& key){
                node_ptr node = userdefined::get_end_node<value_type>();
                if (this->empty())
                    return iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<value_type>(node) && userdefined::_is_not_end_node<value_type>(node) && !_compare(key, node->content.first))
                    node = userdefined::get_successor<value_type>(node);
                return iterator(node, this->_tree.max());
			}

			const_iterator upper_bound(const key_type& key) const{
                node_ptr node = userdefined::get_end_node<value_type>();
                if (this->empty())
                    return const_iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<value_type>(node) && userdefined::_is_not_end_node<value_type>(node) && !_compare(key, node->content.first))
                    node = userdefined::get_successor<value_type>(node);
                return const_iterator(node, this->_tree.max());
			}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// equal_range    | Returns a range containing all elements with the given key in the container. The range is defined by two iterators, one pointing to the 
//                  first element that is not less than key and another pointing to the first element greater than key. Alternatively, the first iterator may 
//                  be obtained with lower_bound(), and the second with upper_bound().
//                  1,2) Compares the keys to key.
//                  Returns ft::pair containing a pair of iterators defining the wanted range: 
//                  the first pointing to the first element that is not less than key and the second pointing to the first element greater than key.
//                  If there are no elements not less than key, past-the-end (see end()) iterator is returned as the first element. 
//                  Similarly if there are no elements greater than key, past-the-end iterator is returned as the second element.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			ft::pair<iterator,iterator>	equal_range (const key_type& k){
				iterator lower = lower_bound(k);
				iterator upper = upper_bound(k);
				return ft::make_pair<iterator, iterator>(lower,upper);
			}
			ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const{
				const_iterator lower = lower_bound(k);
				const_iterator upper = upper_bound(k);
				return ft::make_pair<const_iterator, const_iterator>(lower,upper);
			}
// ============================================================================<<ftMapLookup==================================================================

// ============================================================================>>ftMapObservers===================================================================
//* Observers        // key_comp | value_comp
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// key_comp     | Returns the function object that compares the keys, which is a copy of this container's constructor argument comp. returns The key comparison function object.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			key_compare     key_comp()      const   {return key_compare();}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// value_comp   | Returns a function object that compares objects of type std::map::value_type (key-value pairs) by using key_comp to compare the first components of the pairs.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            value_compare   value_comp()    const   {return value_compare(key_comp());}
// ============================================================================<<ftMapObservers==================================================================
            template <class K1, class T1, class C1, class A1>
            friend bool operator==(const map<K1,T1,C1,A1>& lhs, const map<K1,T1,C1,A1>& rhs);
            template <class K1, class T1, class C1, class A1>
            friend bool operator< (const map<K1,T1,C1,A1>& lhs, const map<K1,T1,C1,A1>& rhs);

}; //* end of map class -----------------------------------------------------------------------------------------------------------------------------------

//* Non Member Functions====================================================================================================================================
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Comparison Operators   | ==, !=, <, <=, >, >=
// Compares the contents of two maps.
// 1-2) Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
// 3-6) Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent to std::lexicographical_compare. This comparison ignores the map's ordering Compare.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1-2*/
            template <class Key, class T, class Compare, class Alloc>
            bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());}
            template <class Key, class T, class Compare, class Alloc>
            bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return !(lhs == rhs);}
            /*3-6*/
            template <class Key, class T, class Compare, class Alloc>
            bool operator< (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}
            template <class Key, class T, class Compare, class Alloc>
            bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return !(rhs < lhs);}
            template <class Key, class T, class Compare, class Alloc>
            bool operator> (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return (rhs < lhs);}
            template <class Key, class T, class Compare, class Alloc>
            bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) {return !(lhs < rhs);}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// ft::swap   | Specializes the std::swap algorithm for std::map. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            template< class Key, class T, class Compare, class Alloc >
            void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs){
                lhs.swap(rhs);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
} //* end of namespace ft -----------------------------------------------------------------------------------------------------------------------------------
#endif // ============================================================================<<map.hpp============================================================
