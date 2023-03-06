/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:17 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 14:54:40 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>set.hpp============================================================================
// Set class is referenced from: 
    // https://en.cppreference.com/w/cpp/container/set
    // https://cplusplus.com/reference/set/set/
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Set structure:
    /// Member types
        //  key_type;   value_type;  key_compare;   value_compare;    allocator_type; size_type; difference_type;
        //  reference;  const_reference;    pointer;    const_pointer;  
        //  iterator;   const_iterator;     reverse_iterator;   const_reverse_iterator;
    /// Member functions
            // Basics           // Constructors | Destructor | operator= | get_allocator
            // Iterators        // begin | end | rbegin | rend
            // Capacity         // empty | size | max_size
            // Modifiers        // clear | insert | erase | swap
            // Lookup           // count | find | equal_range | lower_bound | upper_bound
            // Observers        // key_comp | value_comp
    /// Non Member functions
            // comparison operators 
            // ft::swap
// --------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef     SET_HPP
# define    SET_HPP

#include "header.hpp"
#include "iterator_reverse.hpp" // ft::reverse_iterator<iterator>
#include "map_RB_Tree.hpp"      // ft::_s_RB_Node<> | ft::RB_Tree<> | ft::set_tree_iterator<>
#include "utils.hpp"            // ft::pair< Key, T> |  ft::enable_if | ft::is_iterator_tagged | ft::make_pair | ft::swap
#include <functional>           // std::binary_function //TODO ideally, to recode

namespace ft
{
    template <
        class Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator< Key >
    > class set {
// ============================================================================>>SetClassDeclaration====================================================
//* Member Classes (value_compare added to member types)====================================================================================================
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// std::set<Key,Compare,Allocator>::value_compare
// Function object that compares objects of type std::set::value_type (key-value pairs) by comparing of the first components of the pairs.
// Mmember types are obtained via publicly inheriting std::binary_function<value_type, value_type, bool>.
// https://en.cppreference.com/w/cpp/container/set/value_compare
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
            // typedef             Key                                                 key_type;           // Key
            typedef             Allocator                                           key_allocator_type;     // Alloc of Key
            typedef typename    key_allocator_type::value_type                      value_type;         // Key
            typedef             std::size_t                                         size_type;          // unsigned long
            typedef             std::ptrdiff_t                                      difference_type;    // long
            typedef             Compare                                             key_compare;        // Compare
            typedef             Compare                                             value_compare;        // Compare

        // tree typedef         // Definition                                       // Member type      // recap
        private: 
            typedef             value_type                                          key_type;         // Key
            typedef             ft::pair<value_type, value_type>                    pair_type;          // pair<Key, Key>
            typedef             userdefined::_s_RB_Node<pair_type>                  node_type;          // node<pair<Key, Key>>
            typedef             userdefined::_s_RB_Node<pair_type>*                 node_ptr;           // node<pair<Key, Key>> *
            typedef typename    key_allocator_type::template rebind<node_type>::other   alloc_node_type;    // Alloc of node<pair<Key, Key>> 		        // std::allocator.rebind<Type> 
            typedef typename    key_allocator_type::template rebind<pair_type>::other   alloc_pair_type;    // Alloc of node<pair<Key, Key>> 		        // std::allocator.rebind<Type> 
            typedef typename    key_allocator_type::template rebind<userdefined::_s_RB_Node<key_type> >::other   alloc_key_node_type;    // Alloc of node<pair<Key, Key>> 		        // std::allocator.rebind<Type> 
            typedef             userdefined::RB_Tree<alloc_pair_type, key_compare>   tree_type;          // Tree of Allocator of node<pair<Key, Key>>    // will rebind in RB_Tree

        public:                 // Definition                                       // Member type      // recap
            typedef             alloc_key_node_type                                  allocator_type;     // Alloc of Key
            typedef             value_type&                                         reference;          // reference to a       Key
            typedef const       value_type&                                         const_reference;    // const reference to a Key
            typedef             node_ptr                                            pointer;            // Pointer to a         node<pair<Key, Key>>
            typedef const       pointer                                             const_pointer;      // const Pointer to a   node<pair<Key, Key>>
            typedef             userdefined::set_tree_iterator<node_type>           iterator;           // iterator to a        node<pair<Key, Key>>
            typedef             userdefined::set_tree_iterator<node_type>           const_iterator;     // const iterator to a  node<pair<Key, Key>>
            typedef typename    ft::reverse_iterator<iterator>                      reverse_iterator;   // reverse it to a      node<pair<Key, Key>>
            typedef typename    ft::reverse_iterator<const_iterator>                const_reverse_iterator;// const rev it to a node<pair<Key, Key>>

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
// ============================================================================>>ftSetBasics===================================================================
///* Constructors | Destructor | operator= | get_allocator
            /*1*/ /*2*/ // Default
            explicit set( 
                const key_compare&      comp = key_compare(), 
                const allocator_type&   alloc = allocator_type() 
                )
            : _allocator(alloc), _compare(comp), _tree(), _size() {}
            /*4*/       // Range
            template< class InputIt >
            set(
                typename ft::enable_if < ft::is_iterator_tagged< typename InputIt::iterator_category >::value, InputIt > ::type first,
                InputIt last,
                const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()
                )
            : _allocator(alloc), _compare(comp), _tree(), _size() {
                this->insert(first, last);
            }
            /*6*/       // Copy
            set(const set& other)
            : _allocator(other._allocator), _compare(other._compare), _tree(), _size() {
                *this = other;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Destructor | 
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            ~set(){}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator=    | 
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            set& operator=(const set& other){
				this->clear();
				this->_allocator = other._allocator;
				this->_compare = other._compare;
                this->_tree = other._tree;
				return (*this);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// get_allocator    | 
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            // allocator_type get_allocator() const{return (this->_allocator);} 
            allocator_type get_allocator() const{return (this->_allocator);} //TODO currently returning wrong allocator (pair instead of node) to fit with std tester
// ============================================================================<<ftSetBasics==================================================================

// ============================================================================>>ftSetIterators===================================================================
//* Iterators        // begin | end | rbegin | rend
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// begin    | returns an iterator to the beginning.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            iterator begin()				        {pointer ptr; if (this->empty()) ptr = userdefined::get_end_node<pair_type>(); else ptr = this->_tree.min(); return iterator(ptr, this->_tree.max());}
            const_iterator begin()          const   {pointer ptr; if (this->empty()) ptr = userdefined::get_end_node<pair_type>(); else ptr = this->_tree.min(); return const_iterator(ptr, this->_tree.max());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// end      | returns an iterator to the end.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            iterator end()					        {return iterator(userdefined::get_end_node<pair_type>(), this->_tree.max());}
            const_iterator end()            const   {return const_iterator(userdefined::get_end_node<pair_type>(), this->_tree.max());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// rbegin    | Returns a reverse iterator to the first element of the reversed set. It corresponds to the last element of the non-reversed set. 
//              If the set is empty, the returned iterator is equal to rend().
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            reverse_iterator rbegin()               {return reverse_iterator(end());}
            const_reverse_iterator rbegin() const   {return const_reverse_iterator(end());}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// rend      | Returns a reverse iterator to the element following the last element of the reversed set. It corresponds to the element preceding the first
//              element of the non-reversed set. This element acts as a placeholder, attempting to access it results in undefined behavior.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            reverse_iterator rend()                 {return reverse_iterator(begin());}
            const_reverse_iterator rend()   const   {return const_reverse_iterator(begin());}
// ============================================================================<<ftSetIterators==================================================================

// ============================================================================>>ftSetCapacity===================================================================
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
            size_type max_size() const              {return (this->_allocator.max_size());}
// ============================================================================<<ftSetCapacity==================================================================

// ============================================================================>>ftSetModifiers===================================================================
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
                pointer node = this->_tree.search(value);
                if (userdefined::_is_nil<pair_type>(node)) {
                    node = this->_tree.insert(ft::make_pair<value_type, value_type>(value, value));
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
            // 	if (userdefined::_is_end<pair_type>(successor) || _compare(value.first, successor->content.first)){                 // insert if successor is end node or position < value < successor
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
                    throw std::length_error("set");
                for (; first != last; first++)
                    this->insert((*first));
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
                key_type                    key= (*position);
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
					key_type key = (*first);
					++first;
                    ret = this->_tree.remove(key);              // return (successor, true) or (nil, false)
                    if (ret.second == true)
                        ret_it = iterator(ret.first, this->_tree.max());
				}
                if (this->_tree.empty())
                    return iterator(userdefined::get_end_node<pair_type>(), this->_tree.max());
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
			void swap (set& other){
				ft::swap(this->_allocator, other._allocator);
				ft::swap(this->_compare, other._compare);
				ft::swap(this->_size, other._size);
				tree_type::swap_tree(this->_tree, other._tree);
			}
// ============================================================================<<ftSetModifiers==================================================================

// ============================================================================>>ftSetLookup===================================================================
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
                node_ptr node = userdefined::get_end_node<pair_type>();
                // std::cout << "hello" << std::endl;
                if (this->empty())
                    return iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<pair_type>(node) && userdefined::_is_not_end_node<pair_type>(node) && _compare(node->content.first, key))
                    node = userdefined::get_successor<pair_type>(node);
                return iterator(node, this->_tree.max());

			}
			const_iterator lower_bound(const key_type& key) const{
                node_ptr node = userdefined::get_end_node<pair_type>();
                if (this->empty())
                    return const_iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<pair_type>(node) && userdefined::_is_not_end_node<pair_type>(node) && _compare(node->content.first, key))
                    node = userdefined::get_successor<pair_type>(node);
                return const_iterator(node, this->_tree.max());
			}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// upper_bound    | 1,2) Returns an iterator pointing to the first element that is greater than key.
//                  ret : Iterator pointing to the first element that is greater than key. If no such element is found, past-the-end (see end()) iterator is returned.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			iterator upper_bound(const key_type& key){
                node_ptr node = userdefined::get_end_node<pair_type>();
                if (this->empty())
                    return iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<pair_type>(node) && userdefined::_is_not_end_node<pair_type>(node) && !_compare(key, node->content.first))
                    node = userdefined::get_successor<pair_type>(node);
                return iterator(node, this->_tree.max());
			}

			const_iterator upper_bound(const key_type& key) const{
                node_ptr node = userdefined::get_end_node<pair_type>();
                if (this->empty())
                    return const_iterator(node, this->_tree.max());
                node = this->_tree.min();
                while(userdefined::_is_not_nil<pair_type>(node) && userdefined::_is_not_end_node<pair_type>(node) && !_compare(key, node->content.first))
                    node = userdefined::get_successor<pair_type>(node);
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
// ============================================================================<<ftSetLookup==================================================================

// ============================================================================>>ftSetObservers===================================================================
//* Observers        // key_comp | value_comp
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// key_comp     | Returns the function object that compares the keys, which is a copy of this container's constructor argument comp. returns The key comparison function object.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			key_compare     key_comp()      const   {return key_compare();}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// value_comp   | Returns a function object that compares objects of type std::set::value_type (key-value pairs) by using key_comp to compare the first components of the pairs.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            value_compare   value_comp()    const   {return value_compare(key_comp());}
// ============================================================================<<ftSetObservers==================================================================
            template <class K1, class C1, class A1>
            friend bool operator==(const set<K1,C1,A1>& lhs, const set<K1,C1,A1>& rhs);
            template <class K1, class C1, class A1>
            friend bool operator< (const set<K1,C1,A1>& lhs, const set<K1,C1,A1>& rhs);

}; //* end of set class -----------------------------------------------------------------------------------------------------------------------------------

//* Non Member Functions====================================================================================================================================
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Comparison Operators   | ==, !=, <, <=, >, >=
// Compares the contents of two sets.
// 1-2) Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
// 3-6) Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent to std::lexicographical_compare. This comparison ignores the set's ordering Compare.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1-2*/
            template <class Key, class Compare, class Alloc>
            bool operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());}
            template <class Key, class Compare, class Alloc>
            bool operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return !(lhs == rhs);}
            /*3-6*/
            template <class Key, class Compare, class Alloc>
            bool operator< (const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}
            template <class Key, class Compare, class Alloc>
            bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return !(rhs < lhs);}
            template <class Key, class Compare, class Alloc>
            bool operator> (const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return (rhs < lhs);}
            template <class Key, class Compare, class Alloc>
            bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs) {return !(lhs < rhs);}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// ft::swap   | Specializes the std::swap algorithm for std::set. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            template< class Key, class Compare, class Alloc >
            void swap(ft::set<Key, Compare, Alloc>& lhs, ft::set<Key, Compare, Alloc>& rhs){
                lhs.swap(rhs);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
} //* end of namespace ft -----------------------------------------------------------------------------------------------------------------------------------
#endif // ============================================================================<<set.hpp============================================================
