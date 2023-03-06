/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_RB_Tree.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:02 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 14:53:28 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>map_RB_Tree.hpp============================================================================
#ifndef RB_TREE_HPP
#define RB_TREE_HPP

///* Properties of red-black trees--------------------------------------------------------------------------------------------------------------------------------------
	// 1. Every node is either red or black.
	// 2. The root is black.
	// 3. Every leaf (NIL) is black.
	// 4. If a node is red, then both its children are black.
	// 5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.
// See at the end of this file Pseudo code from "Introduction_to_Algorithms_Third_Edition_(2009)"

///* INDEX -------------------------------------------------------------------------------------------------------------------------------------------------------------

///* INCLUDES ----------------------------------------------------------------------------------------------------------------------------------------------------------
#include "utils.hpp"
///* DEFINES -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Colors
#define RB_BLACK 	0
#define RB_RED		1
// Rotation direction and left/right child identification // _rbt_rotate() // _get_tmp_end_node()
#define LEFT 		0
#define RIGHT		1

// DEBUG
# define DEBUG_MAP 0

namespace userdefined {
//* NODE CLASS DEFINITION-----------------------------------------------------------------------------------------------------------------------------------------------
//* Base Node ----------------------------------------------------------------------------------------------------------------------------------------------------------
	template < typename Pair >
	struct _s_RB_Node {
		/*	Node type definition */	
			typedef	Pair		value_type;	 
		/*	Node Member attributes */		 
			value_type			content;
			bool				color;
			struct _s_RB_Node	*parent, *right, *left;
		/*	Default Constructor */	
			_s_RB_Node()						: content(value_type()), 	color(RB_BLACK), parent(nullptr), right(nullptr), left(nullptr) {}
		/*	Fill Constructor */		
			_s_RB_Node(const value_type& pair) 	: content(pair), 			color(RB_BLACK), parent(nullptr), right(nullptr), left(nullptr) {}
		/*	Destructor */			
			~_s_RB_Node() {}
		/*	Copy Assignment Operator */
			_s_RB_Node& operator=(const _s_RB_Node& other) {
				this->content.second 	= other.content.second;
				this->color 	= other.color;
				this->parent 	= other.parent;
				this->right 	= other.right;
				this->left 		= other.left;
				return (*this);
			}
		/* color flipping */		
			void	color_flip() {this->color = this->color == RB_RED ? RB_BLACK : RB_RED;}
		/*	Comparison Operators */
			bool	operator==(const _s_RB_Node *other) {
				return (
					this->content == other->content
					&& this->color == other->color
					&& this->parent == other->parent
					&& this->left == other->left
					&& this->right == other->right
					);
			}
			bool	operator!=(const _s_RB_Node *other) {return (!(*this == other));}
	};
//* Inside Node --------------------------------------------------------------------------------------------------------------------------------------------------------
	template < typename value_type >
	struct _s_RB_Inside_Node	:	public _s_RB_Node<value_type> {};
//* Nil Node -----------------------------------------------------------------------------------------------------------------------------------------------------------
	template < typename value_type >
	class _s_RB_NIL			:	public _s_RB_Node<value_type> {
		private :
			_s_RB_NIL() : _s_RB_Node<value_type>() {
				this->parent = this;
				this->left = this;
				this->right = this;
			}
		public : 
			static _s_RB_NIL*	get_nil_node(){
				static _s_RB_NIL nil_node;
				return &nil_node;
			}
	};
//* End Node -----------------------------------------------------------------------------------------------------------------------------------------------------------
	template < typename value_type >
	class _s_RB_END			:	public _s_RB_Node<value_type> {
		private :
			_s_RB_END() : _s_RB_Node<value_type>() {
				this->parent = this;
				this->left = this;
				this->right = this;
			}
		public : 
			static _s_RB_END*	get_end_node(){
				static _s_RB_END end_node;
				return &end_node;
			}
	};

//* End of Node classes ------------------------------------------------------------------------------------------------------------------------------------------------

///* Node Toolbox ------------------------------------------------------------------------------------------------------------------------------------------------
	template < typename value_type >
	static _s_RB_NIL<value_type>*	get_nil_node() {
		return (_s_RB_NIL<value_type>::get_nil_node());
	}
	template < typename value_type >
	static _s_RB_END<value_type>*	get_end_node() {
		return (_s_RB_END<value_type>::get_end_node());
	}

	template < typename value_type >
	static bool	_is_nil(const _s_RB_Node<value_type>* node)				{return (node == userdefined::get_nil_node<value_type>());}
	template < typename value_type >
	static bool	_is_not_nil(const _s_RB_Node<value_type>* node)			{return (node != userdefined::get_nil_node<value_type>());}
		
	template < typename value_type >
	static bool	_is_end_node(const _s_RB_Node<value_type>* node)		{return (node == userdefined::get_end_node<value_type>());}
	template < typename value_type >
	static bool	_is_not_end_node(const _s_RB_Node<value_type>* node)	{return (node != userdefined::get_end_node<value_type>());}

	template < typename value_type >
	static bool	_is_root(const _s_RB_Node<value_type>* node)			{return (node->parent == userdefined::get_nil_node<value_type>());}
	template < typename value_type >
	static bool	_has_parent(const _s_RB_Node<value_type>* node)			{return (node->parent != userdefined::get_nil_node<value_type>());}

	template < typename value_type >
	static bool	_has_left_child(const _s_RB_Node<value_type>* node)		{return (node->left != userdefined::get_nil_node<value_type>());}
	template < typename value_type >
	static bool	_has_right_child(const _s_RB_Node<value_type>* node)	{return (node->right != userdefined::get_nil_node<value_type>());}
	template < typename value_type >
	static bool	_has_children(const _s_RB_Node<value_type>* node)		{return (userdefined::_has_left_child<value_type>(node) || userdefined::_has_right_child<value_type>(node));}

	template < typename value_type >
	static bool	_has_no_left_child(const _s_RB_Node<value_type>* node)	{return (node->left == userdefined::get_nil_node<value_type>());}
	template < typename value_type >
	static bool	_has_no_right_child(const _s_RB_Node<value_type>* node)	{return (node->right == userdefined::get_nil_node<value_type>());}
	template < typename value_type >
	static bool	_has_no_children(const _s_RB_Node<value_type>* node)	{return (userdefined::_has_no_left_child<value_type>(node) && userdefined::_has_no_right_child<value_type>(node));}

	template < typename value_type >
	static bool	_is_left_child(const _s_RB_Node<value_type>* node)		{if (userdefined::_has_parent<value_type>(node)) return (node == node->parent->left); else return false;}
	template < typename value_type >
	static bool	_is_right_child(const _s_RB_Node<value_type>* node)		{if (userdefined::_has_parent<value_type>(node)) return (node == node->parent->right); else return false;}

	//*	Tree get_max_node
	template < typename value_type >
	static _s_RB_Node<value_type>*	get_max_node(const _s_RB_Node<value_type>* node) {
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);

		if (userdefined::_is_nil<value_type>(current))
			return (current);
		while (userdefined::_has_parent<value_type>(current)) {
			current = current->parent;
		}
		while (userdefined::_has_right_child<value_type>(current)) {
			current = current->right;
		}
		return (current);
	}
	template < typename value_type >
	static bool	_is_max_node(const _s_RB_Node<value_type>* node) {
		return (node == userdefined::get_max_node<value_type>(node));
	}


	///* Lookup
	// 	//*	Tree Find Min/Max in subtree
	template < typename value_type >
	static _s_RB_Node<value_type>*	min(const _s_RB_Node<value_type>*  node) {
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);

		if (userdefined::_is_nil<value_type>(current))
			return (current);
		while (userdefined::_has_left_child<value_type>(current)) {
			current = current->left;
		}
		return (current);
	}

	template < typename value_type >
	static _s_RB_Node<value_type>*	max(const _s_RB_Node<value_type>*  node) {
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);

		if (userdefined::_is_nil<value_type>(current))
			return (current);
		while (userdefined::_has_right_child<value_type>(current)) {
			current = current->right;
		}
		return (current);
	}

	//*	Tree get_uncle
	template < typename value_type >
	static _s_RB_Node<value_type>*	get_uncle(const _s_RB_Node<value_type>* node){
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);

		if (userdefined::_is_nil<value_type>(current) || userdefined::_is_root<value_type>(current) || userdefined::_is_root<value_type>(current->parent))
			return (userdefined::get_nil_node<value_type>());
		else {
			if (userdefined::_is_left_child<value_type>(current->parent))
				return (current->parent->parent->right);
			else
				return (current->parent->parent->left);
		}
	}

	template < typename value_type >
	static bool	_has_uncle(const _s_RB_Node<value_type>* node) {
		return (userdefined::get_uncle(node) != userdefined::get_nil_node<value_type>());
	}

	//*	Tree get sibling
	template < typename value_type >
	static _s_RB_Node<value_type>*	_get_sibling(const _s_RB_Node<value_type>* node){
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);	

		if ((userdefined::_is_nil<value_type>(current)) || (userdefined::_is_root<value_type>(current)))
			return (userdefined::get_nil_node<value_type>());
		if (userdefined::_is_left_child<value_type>(current))
			return (current->parent->right);
		return (current->parent->left);
	}
			
	// *	Tree get successor
	template < typename value_type >
	static _s_RB_Node<value_type>*	get_successor(const _s_RB_Node<value_type>* node) {
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);
		_s_RB_Node<value_type>* successor;					// if (DEBUG_MAP) std::cout << "get_successor | node: " << node->content.first << std::endl;
		
		if (userdefined::_has_right_child<value_type>(current))
			return (userdefined::min<value_type>(current->right));
		else {
			while (userdefined::_has_parent<value_type>(current) && userdefined::_is_right_child<value_type>(current))
				current = current->parent;
		}
		successor = current->parent;
		if (userdefined::_is_nil<value_type>(successor) || userdefined::_is_end_node<value_type>(successor)) {
			successor = userdefined::get_end_node<value_type>();
		}
		return (successor);
	}

	//*	Tree get predecessor
	template < typename value_type >
	static _s_RB_Node<value_type>* 	get_predecessor(const _s_RB_Node<value_type>*  node) {
		_s_RB_Node<value_type>* current = const_cast< _s_RB_Node<value_type> * >(node);
		_s_RB_Node<value_type>*  predecessor;

		if (userdefined::_is_end_node<value_type>(current)) {
			predecessor = userdefined::get_max_node<value_type>(current);
		}
		else {
			if (userdefined::_has_left_child<value_type>(current))
				return (userdefined::max<value_type>(current->left));
			else
			{
				while (userdefined::_has_parent<value_type>(current) && userdefined::_is_left_child<value_type>(current))
					current = current->parent;
			}
			predecessor = current->parent;
		}
		return (predecessor);
	}
///* End Node Toolbox ------------------------------------------------------------------------------------------------------------------------------------------------

//* TREE CLASS DEFINITION-----------------------------------------------------------------------------------------------------------------------------------------------
	template <	class Allocator,
				class Compare = std::less< typename Allocator::value_type::first_type >
				>
	class RB_Tree
	{
	////*	Types definition -------------------------------------------------------------------------------------------------------------------------------------------
		// -------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Ressources
		// std::allocator.rebind<Type> 
		// => used when there is the need inside of a container to allocate an object of different size than templated type parameter
		// Rebind is a member class of std::allocator | Its member type "other" is the equivalent allocator type to allocate elements of type "Type"
		// 	template <class Type> 
		//	struct rebind {
		//   	typedef allocator<Type> other;
		// 	};
		// https://stackoverflow.com/questions/14148756/what-does-template-rebind-do
		// https://cplusplus.com/reference/memory/allocator/
		// https://en.cppreference.com/w/cpp/memory/allocator
		// -------------------------------------------------------------------------------------------------------------------------------------------------------------
		public:                 // Definition									// Member type      // Recap

			typedef				Allocator										allocator_type;		// std::allocator<ft::pair< Key, T> >
			typedef typename 	Allocator::value_type							value_type;			// Element type : ft::pair< Key, T>
			typedef typename 	Allocator::value_type::first_type				key_type;			// pair.first
			typedef typename 	Allocator::value_type::second_type				content_type;		// pair.second
		// Nodes
			typedef				_s_RB_Node<value_type>							node_type;			// _s_RB_Node<pair<Key, T>>
			typedef				_s_RB_Inside_Node<value_type>					inside_node_type;
			typedef				_s_RB_NIL<value_type>							nil_node_type;
			typedef				_s_RB_END<value_type>							end_node_type;
		// new allocator type for node - see reference below
			typedef typename 	Allocator::template rebind<node_type>::other	node_allocator_type;//std::allocator<_s_RB_Node<pair<Key, T>>
			typedef typename 	node_allocator_type::pointer					pointer;			// Pointer to element Node*
			typedef typename 	node_allocator_type::const_pointer				const_pointer;		// const _s_RB_Node<pair<Key, T>>*
			typedef typename 	node_allocator_type::reference					reference;			// Reference to element Node&
			typedef typename 	node_allocator_type::const_reference			const_reference;	// const Node&
			typedef typename 	node_allocator_type::size_type					size_type;			// size of an element Node
			typedef typename 	node_allocator_type::difference_type			difference_type;	// Difference between two pointers Node

			typedef 		 	Compare											key_compare;

	////*	Private Member attributes ----------------------------------------------------------------------------------------------------------------------------------
		protected:
			pointer				_root;
			size_t				_size;
			node_allocator_type	_allocator;
			key_compare			_compare;
			
	////*	Private Member functions -----------------------------------------------------------------------------------------------------------------------------------
		protected:
			///*	Tree Print
				void	_print_rec(const_pointer node, int tabs, char c) const {
					if (userdefined::_is_nil<value_type>(node))
						std::cout << std::endl;
					else {
						this->_print_rec(node->right, tabs + 1, '/');
						
						if (userdefined::_is_root<value_type>(node))
							std::cout <<  BWHITE BLACK "x" RESET;
						else 
							std::cout <<  "." ;
						const char * color = node->color == RB_RED ? BRED : BWHITE BLACK;
						const std::string val = std::to_string(node->content.first);
						std::cout << std::setfill('.') << std::setw(4 * tabs) << std::right << c << color << val << RESET;
						if (this->_has_no_children(node))
							std::cout <<  " " BWHITE BLACK "x" RESET;
						
						_print_rec(node->left, tabs + 1, '\\');
					}
				}
				void		_print(std::string subtree_name, pointer subtree) const {
					std::cout << MAGENTA 	"-----------------------"  << std::endl;
					std::cout <<			"Printing tree: " << subtree_name;
					std::cout << 			" | Root: #" << subtree->content.first;
					std::cout << 			" | Size: " << this->size();
					std::cout << 			" | Min: #" << (userdefined::min<value_type>(subtree))->content.first;
					std::cout << 			" | Max: #" << (userdefined::max<value_type>(subtree))->content.first << RESET << std::endl;
					this->_print_rec(subtree, 0, '.');
					std::cout << MAGENTA 	"Checking order : " RESET ; this->_order_check();
					std::cout << MAGENTA 	"Checking violation : " RESET ; this->_violation_check();
					std::cout << MAGENTA 	"-----------------------" RESET << std::endl;
					return ;
				}

			///*	Whole Tree Deletion => recursive bottom up approach on Key
				void	_deletion_end_node(pointer node) {
						if (userdefined::_is_left_child<value_type>(node))						// deleting node's presence in parent
							node->parent->left = userdefined::get_nil_node<value_type>();
						else if (userdefined::_is_right_child<value_type>(node))	
							node->parent->right = userdefined::get_nil_node<value_type>();
						else											// if has no parent (== root) => reset root to t.nil
							this->_root = userdefined::get_nil_node<value_type>();
						node->parent = NULL;							// resetting node to default to make it cleaner and avoid segfault during checks
						node->color = RB_BLACK;
						node->left = NULL;
						node->right = NULL;
						this->_allocator.destroy(node);
						this->_allocator.deallocate(node, 1);
						this->_size--;									// decrementing size
				}

				void	_recursive_deletion_bottom_up(pointer node) {
					if (userdefined::_is_not_nil<value_type>(node)){
																						//std::cout << "calling deletion node "<< node->content.first <<" | left " << node->left->content.first << std::endl; 
						this->_recursive_deletion_bottom_up(node->left);
																						//std::cout << "calling deletion node "<< node->content.first <<" | right " << node->right->content.first << std::endl; 
						this->_recursive_deletion_bottom_up(node->right);
																						//std::cout << "deleting node " << node->content.first << std::endl;
						this->_deletion_end_node(node);
					}
					return;				
				}

			///*	Whole Tree Copy => recursive Top Down approach on hierarchy
				void	_recursive_copy_top_down(const_pointer other, const RB_Tree& other_tree){
					if (userdefined::_is_not_nil<value_type>(other)){
						// insertion
						if (userdefined::_is_not_nil<value_type>(other->left))
							this->_rbt_insert(other->left->content.first, other->left->content.second);
						if (userdefined::_is_not_nil<value_type>(other->right))
							this->_rbt_insert(other->right->content.first, other->right->content.second);
						
						// recursivity
						if (userdefined::_is_not_nil<value_type>(other->left))
							this->_recursive_copy_top_down(other->left, other_tree);
						if (userdefined::_is_not_nil<value_type>(other->right))
							this->_recursive_copy_top_down(other->right, other_tree);
					}
					return;	
				}

				void	_recursive_copy_top_down(const RB_Tree& other_tree){
					const_pointer other_root = other_tree.get_root();

					this->_allocator = other_tree._allocator;
					this->_rbt_insert(other_root->content.first, other_root->content.second);
					this->_recursive_copy_top_down(other_root, other_tree);
					return;
				}

			///* Tree Properties Violation Check
				/// Checks that all nodes respect the properties of Red Black Trees
				/// Properties of red-black trees
					// 1. Every node is either red or black.
					// 2. The root is black.
					// 3. Every leaf (NIL) is black.
					// 4. If a node is red, then both its children are black.
					// 5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

				//*	recursive function checking subtrees
				int		_violation_check_subtrees(const_pointer node) const {
					int i = 0;
					if (node->color == RB_BLACK)
						i++;
					if (userdefined::_is_not_nil(node)){
						// 1. Every node is either red or black.
						if ((node->color != RB_RED) && (node->color != RB_BLACK)){
							std::cout << RED "!Violation" << std::endl << "1. Every node is either red or black. => FALSE" RESET << std::endl;
							std::cout << " | node: " << node->content.first << std::endl;
							return -1;
						}
						// 4. If a node is red, then both its children are black.
						if ((node->color == RB_RED) 
							&& (
								(userdefined::_has_left_child(node) && (node->left->color != RB_BLACK)) 
								|| (userdefined::_has_right_child(node) && (node->right->color != RB_BLACK))
							)){
							std::cout << RED "!Violation" << std::endl << "4. If a node is red, then both its children are black. => FALSE" RESET << std::endl;
							std::cout << " | node: " << node->content.first << std::endl;
							return -1;
						}
						// 5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.
						int j = this->_violation_check_subtrees(node->left);
						int k = this->_violation_check_subtrees(node->right);
						if (j == -1 || k == -1)
							return -1;
						if (j != k){
							std::cout << RED "!Violation" << std::endl << "5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes. => FALSE" RESET << std::endl;
							std::cout << " | node: " << node->content.first << " | left: " << j << " | right : " << k << std::endl;
							return -1;
						}
						else
							i += j;
					}
					// 3. Every leaf (NIL) is black.
					else if (userdefined::_is_nil<value_type>(node) && (node->color != RB_BLACK)){
						std::cout << RED "!Violation" << std::endl << "3. Every leaf (NIL) is black. => FALSE" RESET << std::endl;
						std::cout << " | node: " << node->parent->content.first << std::endl;
						return -1;
					}
					return i;				
				}

			//*	checking whole tree
				bool	_violation_check(void) const {
					pointer node = this->_root;

					// 2. The root is black.
					if (userdefined::_is_not_nil<value_type>(node) && (node->color != RB_BLACK)){
						std::cout << RED "!Violation" << std::endl << "2. The root is black. => FALSE" RESET << std::endl;
						return false;
					}
					else {
						if (this->_violation_check_subtrees(node) == -1)
							return false;
					}
					std::cout << GREEN "No Violation <3 "<< std::endl;
					return true;
				}

			///* Tree Node Order Check
				///checks that nodes have the right order with parents
				//* checking subtree
				bool	_order_check(const_pointer node) const {
					if (userdefined::_is_nil<value_type>(node)){																			/*0*/ // CASE tree empty
						return true;
					}
					if	(																													/*1*/ // CASE order check is ok OR has no parents
							(userdefined::_is_root<value_type>(node)) 																		// if has no parent
							|| (userdefined::_is_left_child<value_type>(node) && this->_compare(node->content, node->parent->content))		// if order check ok as a left child
							|| (userdefined::_is_right_child<value_type>(node) && this->_compare(node->content > node->parent->content))	// if order check ok as a right child
						){
						if (userdefined::_has_left_child<value_type>(node)){																// continue check on left node
							if (this->_order_check(node->left) == false)
								return false;
						}
						if (userdefined::_has_right_child<value_type>(node)){																// continue check on right node
							if (this->_order_check(node->right) == false)
								return false;
						}
					}
					else {																													/*2*/ // CASE hasn't passed order check = STOP
						std::cout << RED "Order check wrong " << " | node" << node->content.first << " | parent " << node->parent->content.first << RESET << std::endl;
						return false; 
					}
					return true; 																											/*3*/ // CASE  passed all check throughout branch and reached an end leaf OR // only node on tree
				}

				//* checking whole tree
				bool	_order_check(void) const  {if (this->_order_check(this->_root) == true){std::cout << GREEN "Order check ok <3" RESET << std::endl; return true;} else return false;}

			
			///*	Tree Count
				// archive : recursive count
				size_t	recursive_count(const_pointer node) const {
					if (userdefined::_is_nil<value_type>(node))
						return (userdefined::_is_not_nil<value_type>(node));
					else
						return (this->count(node->left) + this->count(node->right) + 1);
				}
				size_t	recursive_count() const {
					return (this->count(this->_root));
				}

		
		///* Binary Search Tree dedicated functions
				//* BST Insert														
				void	_insert_on_filled_tree(pointer node) {
					pointer		current;
					pointer		cur_prev;

					current = this->_root;
					while (userdefined::_is_not_nil<value_type>(current) && current->content.first != node->content.first){
						cur_prev = current;
						if (this->_compare(node->content.first, current->content.first)) 
							current = current->left;
						else
							current = current->right;
					}
					if (this->_compare(node->content.first, cur_prev->content.first)) 
						cur_prev->left = node;
					else
						cur_prev->right = node;
					node->parent = cur_prev;
				}
				
				void	_insert_on_empty_tree(pointer node) {
					this->_root = node;
					node->parent = userdefined::get_nil_node<value_type>();
				}
			
				pointer	_bst_insert(const key_type key, const content_type value) {
					pointer		node;

					node = this->_allocator.allocate(1);
					this->_allocator.construct(node, value_type(key, value));

					if (_is_nil(this->_root))
						this->_insert_on_empty_tree(node);
					else
						this->_insert_on_filled_tree(node);
					node->left = userdefined::get_nil_node<value_type>();
					node->right = userdefined::get_nil_node<value_type>();
					this->_size++;
					return (node);
				}

				//*	BST Transplant
				void	_bst_transplant(pointer destination, pointer source) {

					if (userdefined::_is_nil<value_type>(destination))										// added to prevent seg fault
						return;

					if (userdefined::_is_root<value_type>(destination))										// adding source on tree if destination is the root
						this->_root = source;
					else if (userdefined::_is_left_child<value_type>(destination))							// adding source on tree if destination is on the left
						destination->parent->left = source;
					else																					// adding source on tree if destination is on the right
						destination->parent->right = source;

					if (userdefined::_is_not_nil<value_type>(source)) {
						if (userdefined::_is_left_child<value_type>(source))								// clearing source existence on its previous parent 
							source->parent->left = userdefined::get_nil_node<value_type>();
						else
							source->parent->right = userdefined::get_nil_node<value_type>();
						source->parent = destination->parent;												// setting new parent for source
					}

					destination->parent = userdefined::get_nil_node<value_type>(); 							// clearing destination parent
				}

				//*	BST Delete
				void	_bst_delete(key_type key) {
					pointer		node;
					pointer		successor;

					node = this->search(key);
					if (userdefined::_is_not_nil<value_type>(node)){										// std::cout << CYAN "deleting node: " RESET << node->content.first << std::endl;
						if (userdefined::_has_no_left_child<value_type>(node))								// CASE a: node has no children or one right child	=> right child takes node's position & subtrees
							this->_bst_transplant(node, node->right);
						else if (userdefined::_has_no_right_child<value_type>(node))						// CASE b: node has no children or one left child 	=> left child takes node's position & subtrees
							this->_bst_transplant(node, node->left);
						else{																				// CASE c: node has two children 					=> successor will take node's position and new subtrees
							successor = userdefined::min<value_type>(node->right);
							if (node == successor->parent) {												// CASE c1: successor is node's direct right child 	=> transplant successor to node
								this->_bst_transplant(node, successor);
								successor->left = node->left;												// linking successor with node's left child
								node->left->parent = successor;
							}
							else {																			// CASE c2: successor isn't node direct right child	=> successor's right child takes successor's position to enable successor's to take node's position
								this->_bst_transplant(successor, successor->right);							// transplant successor right child to successor's position
								successor->right = node->right;												// successor accepts node's children
								successor->left = node->left;
								node->right->parent = successor;											// node's children accept successor as a parent
								node->left->parent = successor;
								this->_bst_transplant(node, successor);										// transplant successor to node's position
							}
						}
						this->_allocator.destroy(node);
						this->_allocator.deallocate(node, 1);
						this->_size--;
					}
					return ;
				}


		///* Red Black Tree dedicated functions
			///* RBT_INSERT
				//* Rotation
				void	_rbt_rotate(pointer node, bool direction){
					if (direction == LEFT)
						this->_rbt_left_rotate(node);
					else if (direction == RIGHT)
						this->_rbt_right_rotate(node);
					else
						return;
				}

				void	_rbt_left_rotate(pointer v){
					// std::cout << "_rbt_left_rotate(" << v->content.first << ")"<< std::endl;
					if (userdefined::_is_nil<value_type>(v) || userdefined::_is_nil<value_type>(v->right))
						return ;

					pointer		x = v;
					pointer		y = x->right;
					pointer		z = y->left;

					this->_bst_transplant(y, z);
					// std::cout << "_bst_transplant(" << y->content.first << ", " << z->content.first << ")" << std::endl;

					this->_bst_transplant(x, y);
					// std::cout << "_bst_transplant(" << x->content.first << ", " << z->content.first << ")" << std::endl;

					y->left = x;
					x->parent = y;
				}

				void	_rbt_right_rotate(pointer v){
					// std::cout << "_rbt_right_rotate(" << v->content.first << ")" << std::endl;
					if (userdefined::_is_nil<value_type>(v) || userdefined::_is_nil<value_type>(v->left))
						return ;
					
					pointer		x = v;
					pointer		y = x->left;
					pointer		z = y->right;

					this->_bst_transplant(y, z);
					// std::cout << "_bst_transplant(" << y->content.first << ", " << z->content.first << ")" << std::endl;
					this->_bst_transplant(x, y);
					// std::cout << "_bst_transplant(" << x->content.first << ", " << z->content.first << ")" << std::endl;
					y->right = x;
					x->parent = y;
				}

				//* Fixup
				void	_rbt_insert_fixup(pointer node)
				{
					// std::cout << YELLOW "------------------------------------------------------------------------" RESET << std::endl;
					// std::cout << "_rbt_insert_fixup node: " << node->content.first << std::endl;
					// this->print();
					
					// if (node->parent->color == RB_RED) 
					// {
						// Violation : node is red and has red parent
						while (node->parent->color == RB_RED){					
																													// std::cout << "Violation: node (" << node->content.first << ") is " << node->color << " and his parent (" << node->parent->content.first << ") is " << node->parent->color << " ."<< std::endl;
							// node has grandparent
							if (userdefined::_has_parent<value_type>(node->parent)){ 								// std::cout << "Node has grandparent (" << node->parent->content.first << ")."<< std::endl;
								pointer		uncle = userdefined::get_uncle<value_type>(node);
								
								// CASE 1 Node has red uncle
								if (uncle->color == RB_RED){														// std::cout << "Case 1 : Node has red uncle (" << uncle->content.first << ")." << std::endl;					
									node->parent->color = RB_BLACK;
									uncle->color = RB_BLACK;
									node->parent->parent->color = RB_RED;
									node = node->parent->parent;													// this->print();
								}
								// CASE 2 triangle situation
								else if (userdefined::_is_left_child<value_type>(node->parent) && userdefined::_is_right_child<value_type>(node)){
									node = node->parent;
									this->_rbt_rotate(node, LEFT);													// std::cout << "Case 2.A : Triangle situation: Node is right child and parent is left child" << std::endl; this->print();
								}
								else if (userdefined::_is_right_child<value_type>(node->parent) && userdefined::_is_left_child<value_type>(node)){
									node = node->parent;
									this->_rbt_rotate(node, RIGHT);													// std::cout << "Case 2.B : Triangle situation : Node is left child and parent is right child" << std::endl; this->print();
								}																				
								// CASE 3 recolor parent and granparent and rotate
								else {																				// std::cout << "case 3 : no uncle or black uncle AND node is left child" << std::endl;	
									node->parent->color = RB_BLACK;
									node->parent->parent->color = RB_RED;
									if (userdefined::_is_left_child<value_type>(node->parent))
										this->_rbt_rotate(node->parent->parent, RIGHT);
									else
										this->_rbt_rotate(node->parent->parent, LEFT);								// this->print();
								}
							}
						}
					// }
					// else std::cout << "case 0 : no parent or black parent => no fix" << std::endl;
					if (this->_root->color == RB_RED) {
						this->_root->color_flip();
						// std::cout << "case 4 : root is red => flip color" << std::endl;
					}
					// this->print();
					// this->_violation_check();
				}

				//*	RBT Insert
				pointer		_rbt_insert(const key_type key, const content_type value) {

					pointer		node = this->search(key);
					if (userdefined::_is_not_nil<value_type>(node))
						node->content.second = value;
					else {
						node = this->_bst_insert(key, value);
						node->color = RB_RED;
						this->_rbt_insert_fixup(node);
					}
					return (node);
				}
		///* Red Black Tree dedicated functions
			///* RBT_DELETE
				//*	RBT Transplant
				void	_rbt_transplant(pointer destination, pointer source) {
					if (userdefined::_is_nil<value_type>(destination))								// added to prevent seg fault
						return;
					else if (userdefined::_is_root<value_type>(destination))						// adding source on tree if destination is the root
						this->_root = source;
					else if (userdefined::_is_left_child<value_type>(destination))					// adding source on tree if destination is on the left
						destination->parent->left = source;
					else																			// adding source on tree if destination is on the right
						destination->parent->right = source;
					
					if (userdefined::_is_not_nil<value_type>(source)) {
						if (userdefined::_is_left_child<value_type>(source))						// clearing source existence on its previous parent 
							source->parent->left = userdefined::get_nil_node<value_type>();
						else
							source->parent->right = userdefined::get_nil_node<value_type>();
					}
					source->parent = destination->parent;											// NEW vs _bst_transplant : setting new parent for source WITHOUT CONDITION
					destination->parent = userdefined::get_nil_node<value_type>(); 					// clearing destination parent
				}

				//*	RBT Delete Fixup
				void	_rbt_delete_fixup(pointer node){
					pointer sibling;

					if (userdefined::_is_nil<value_type>(node))
						return;
																									// std::cout << "Fixing up : " << node->content.first << std::endl; 
					while (!(userdefined::_is_root<value_type>(node)) && (node->color == RB_BLACK)){
						if(userdefined::_is_left_child<value_type>(node)){
							sibling = node->parent->right;
							// Case 1: node’s sibling is red
							if (sibling->color == RB_RED){
								sibling->color = RB_BLACK;
								node->parent->color = RB_RED;
								this->_rbt_rotate(node->parent, LEFT);
								sibling = node->parent->right;
							}
							// Case 2: node’s sibling is black, and both of sibling’s children are black
							if ((sibling->left->color == RB_BLACK) && sibling->right->color == RB_BLACK){
								sibling->color = RB_RED;
								node = node->parent;
							}
							// Case 3: node’s sibling is black, sibling’s left child is red, and sibling’s right child is black
							else if (sibling->right->color == RB_BLACK){
								sibling->left->color = RB_BLACK;
								sibling->color = RB_RED;
								this->_rbt_rotate(sibling, RIGHT);
								sibling = node->parent->right;
							}
							// Case 4: node’s sibling is black, and sibling’s right child is red
							sibling->color = node->parent->color;
							node->parent->color = RB_BLACK;
							sibling->right->color = RB_BLACK;
							this->_rbt_rotate(node->parent, LEFT);
							node = this->_root;
						}
						else {
							sibling = node->parent->left;
							// Case 1: node’s sibling is red
							if (sibling->color == RB_RED){
								sibling->color = RB_BLACK;
								node->parent->color = RB_RED;
								this->_rbt_rotate(node->parent, RIGHT);
								sibling = node->parent->left;
							}
							// Case 2: node’s sibling is black, and both of sibling’s children are black
							if ((sibling->right->color == RB_BLACK) && sibling->left->color == RB_BLACK){
								sibling->color = RB_RED;
								node = node->parent;
							}
							// Case 3: node’s sibling is black, sibling’s left child is red, and sibling’s right child is black
							else if (sibling->left->color == RB_BLACK){
								sibling->right->color = RB_BLACK;
								sibling->color = RB_RED;
								this->_rbt_rotate(sibling, LEFT);
								sibling = node->parent->left;
							}
							// Case 4: node’s sibling is black, and sibling’s right child is red
							sibling->color = node->parent->color;
							node->parent->color = RB_BLACK;
							sibling->left->color = RB_BLACK;
							this->_rbt_rotate(node->parent, RIGHT);
							node = this->_root;
						}
					}
					node->color = RB_BLACK;
				}

			//*	RBT Delete
				pointer	_get_tmp_end_node(pointer parent, bool child, bool* flag){
					pointer tmp_node; 											// std::cout << "creating a temp node for fixup | setting flag | initial value : " << *flag << std::endl;
					
					*flag = 1;
					tmp_node = this->_allocator.allocate(1);
					this->_allocator.construct(tmp_node, value_type());
					tmp_node->parent = parent;
					tmp_node->right = userdefined::get_nil_node<value_type>();
					tmp_node->left = userdefined::get_nil_node<value_type>();
					this->_size++;

					if (child == LEFT)
						parent->left = tmp_node;
					else
						parent->right = tmp_node;

					return tmp_node;
				}

				ft::pair<pointer, bool>	_rbt_delete(key_type key) {
					pointer		node;
					pointer		ret;
					pointer		successor;
					bool		successor_original_color;
					pointer		successor_of_successor;
					bool 		flag = 0; 													// using flag to manage memory with temp creation of end node for fixup

					node = this->search(key);
					if (userdefined::_is_nil<value_type>(node))
						return (ft::make_pair<pointer, bool>(node, false));
					ret = userdefined::get_successor<value_type>(node);

					successor = node;
					successor_original_color = successor->color;
																								// std::cout << CYAN "deleting node: " RESET << node->content.first << std::endl;
					if (userdefined::_has_no_left_child<value_type>(node)){						// std::cout << "CASE A1 : node has no children or one right child => right child takes node's position & subtrees" << std::endl;
						successor_of_successor = userdefined::_is_nil<value_type>(node->right) ? _get_tmp_end_node(node, RIGHT, &flag) : node->right;
						this->_rbt_transplant(node, node->right);
					}
					else if (userdefined::_has_no_right_child<value_type>(node)){				// std::cout << "CASE A2 : node has one left child => left child takes node's position & subtrees" << std::endl;
						successor_of_successor = userdefined::_is_nil<value_type>(node->left) ? _get_tmp_end_node(node, LEFT, &flag) : node->left;
						this->_rbt_transplant(node, node->left);
					}
					else {																		// std::cout << "CASE B : node has two children  | successor : " << successor->content.first << "| => successor will take node's position and new subtrees "<< std::endl;
						successor = userdefined::min<value_type>(node->right); 					
						successor_original_color = successor->color;
						successor_of_successor = userdefined::_is_nil<value_type>(successor->right) ? _get_tmp_end_node(successor, RIGHT, &flag) : successor->right;

						if (node == successor->parent)											// std::cout << "CASE B1: successor is node's direct right child 	=> transplant successor to node" << std::endl;
							successor_of_successor->parent = successor;
						else {																	// std::cout << "CASE B2: successor isn't node direct right child	=> successor's right child takes successor's position to enable successor's to take node's position" << std::endl;
							this->_rbt_transplant(successor, successor->right);	
							successor->right = node->right;						
							successor->right->parent = successor;	
						}
							
						this->_rbt_transplant(node, successor);					
						successor->left = node->left;							
						successor->left->parent = successor;
						successor->color = node->color;
					}
																								// std::cout << "Destroying node " << node->content.first << std::endl;
					this->_allocator.destroy(node);
					this->_allocator.deallocate(node, 1);
					this->_size--;

					if (successor_original_color == RB_BLACK)
						this->_rbt_delete_fixup(successor_of_successor);

					if (flag == 1){																// if temp end_node has been created for fixup, delete the node
						this->_deletion_end_node(successor_of_successor);
						flag = 0;
					}
																								// std::cout << "flag : " << flag << std::endl;
					return (ft::make_pair<pointer, bool>(ret, true));
				}

	////*	Public Member functions -------------------------------------------------------------------------------
		public:
		///* Constructors, Destructors, Operators
			//*	Tree Default Constructor 
				explicit RB_Tree(const allocator_type& allocator = allocator_type(), const key_compare& compare = key_compare())
				: _size(), _allocator(allocator), _compare(compare) {
					// print(DEBUG_FT,  GREEN, "Calling Tree Default2 Constructor");
					this->_root = userdefined::get_nil_node<value_type>();
					return;
				}

			//*	Tree Copy Constructor 
				RB_Tree(const RB_Tree& other)  
				: _size(), _allocator(other._allocator), _compare(other._compare) {
					// print(DEBUG_FT,  GREEN, "Calling Tree Copy Constructor");
					this->_root = userdefined::get_nil_node<value_type>();
					*this = other;
				}

			//*	Tree Copy Assignment operator = 
				RB_Tree&	operator=(const RB_Tree& other_tree) {

					// if existing tree, delete all nodes in the current tree - from lower key to higher key
					if (userdefined::_is_not_nil<value_type>(this->_root))
						this->_recursive_deletion_bottom_up(this->_root);

					this->_allocator = other_tree._allocator;
					this->_compare = other_tree._compare;

					// if existing copy, add all nodes from the source tree - from higher hierarchy to lower hierarchy
					if (userdefined::_is_not_nil<value_type>(other_tree.get_root()))
						this->_recursive_copy_top_down(other_tree);
					return (*this);
				}

			//*	Tree Destructor
				~RB_Tree() {
					this->clear();
				}
				
	
		///* Utils
				void					print(void) 			const {this->_print("Root", this->_root);}
		///* Getters
				allocator_type&   		get_allocator(void) 	const {return this->_allocator;}
				pointer					get_root() 				const {return (this->_root);}
				RB_Tree*				get_tree() 				const {return (this);}


			//*	Tree Find Min/Max in root tree
				pointer		min(void) const	{return (userdefined::min<value_type>(this->_root));}
				pointer		max(void) const	{return (userdefined::max<value_type>(this->_root));}

			//*	Iterative Tree Search Key
			// returns node with Key "key", or nil_node
				pointer		search(const key_type key) const {
					pointer		current;																// if (DEBUG_MAP) std::cout << "search| key: " << key << std::endl;

					current = this->_root;
					while (userdefined::_is_not_nil<value_type>(current) && current->content.first != key){
						if (this->_compare(key, current->content.first))
							current = current->left;
						else
							current = current->right;
					}
																										// if (DEBUG_MAP) std::cout << " search | found : " << current->content.first << std::endl;
					return (current);
				}


///* MAP/SET FUNCTIONS
            //* ElementAccess	// at | operator[]
            //* Iterators		// begin | end | rbegin | rend	
			//*	Capacity		// empty | size | max_size
					bool 		empty() const      	{return (this->_size == 0 ? true : false);}
					size_t		size() const 		{return (this->_size);}
					size_t		max_size() const 	{return (this->_allocator.max_size());}
			//* Modifiers		// clear | insert | erase | swap
				// clear | clears the contents
					void 		clear(){
						if (userdefined::_is_not_nil<value_type>(this->_root))
							this->_recursive_deletion_bottom_up(this->_root);
					}
				// insert | inserts elements
					pointer		insert(const value_type content) {
						return (this->_rbt_insert(content.first, content.second));
					}
				// erase | erases elements
					ft::pair<pointer, bool>	remove(key_type key) {
						return this->_rbt_delete(key);
					}
				// swap
					static	void swap_tree(RB_Tree& A, RB_Tree& B){
						pointer				rootA = A._root;
						size_t				sizeA = A._size;
						node_allocator_type	allocatorA = A._allocator;
						key_compare			compareA = A._compare;

						A._root = B._root;
						A._size = B._size;
						A._allocator = B._allocator;
						A._compare = B._compare;

						B._root = rootA;
						B._size = sizeA;
						B._allocator = allocatorA;
						B._compare = compareA;
					}
 
			//* Lookup			// count | find | equal_range | lower_bound | upper_bound
				// count | returns the number of elements matching specific key
					size_type 	count( const key_type& key ) const{
						if(userdefined::_is_nil<value_type>(this->search(key)))
							return false;
						return true;
					}
				// find | finds element with specific key // altered tree.search to return end_node instead of nil_node
					pointer		find( const key_type& key ) const {
						pointer node = this->search(key); 
						if (userdefined::_is_nil<value_type>(node)) 
							return userdefined::get_end_node<value_type>(); 
						return node;
					}
            //* Observers		// key_comp | value_comp
};	// end of class RB_Tree

//* ITERATOR CLASS DEFINITION ------------------------------------------------------------------------------------------------------------------------------------------

template <typename> class tree_const_iterator;

	template <typename Node>
	class tree_iterator {
	// Member types
		public:                 // Definition										// Member type      // Recap
			typedef 			Node												node_type;			// 					_s_RB_Node<pair<Key, T>> 
			typedef	typename	std::allocator<node_type>::pointer					node_pointer;		// Node ptr			_s_RB_Node<pair<Key, T>> *

			typedef typename 	std::allocator<node_type>::value_type::value_type	pair_type;			// Element type  	ft::pair< Key, T>
			typedef typename 	std::allocator<pair_type>::pointer					pair_pointer;		// Pair ptr			ft::pair< Key, T> *
			typedef typename 	std::allocator<pair_type>::reference				pair_reference;		// Pair ref			ft::pair< Key, T> &

			// definition for convention
			typedef				ft::bidirectional_iterator_tag						iterator_category;	// tag
			typedef 			pair_type								        	value_type;         
			typedef typename 	std::allocator<node_type>::difference_type			difference_type;    // distance between 2 nodes std::ptrdiff_t
			typedef				pair_pointer						           		pointer;            
			typedef 			pair_reference         								reference;          
			typedef          	node_pointer                                    	iterator_type;		
	// Member attributes
		private:
			node_type			_empty; // added to prevent segfault when access to default built iterator
			iterator_type		_max;
			iterator_type		_ptr;
			template <typename> friend class tree_const_iterator;
	// Member functions
		public:
		// Canonical
								tree_iterator() 									: _empty(), _max(&_empty), _ptr(&_empty)	{}
								tree_iterator(iterator_type cpy, iterator_type max)	: _empty(), _max(max), _ptr(cpy)		{}
								tree_iterator(const tree_iterator & cpy)			: _empty(), _max(cpy._max), _ptr(cpy._ptr)	{}

								~tree_iterator() {}
			tree_iterator&		operator=(const tree_iterator &cpy)				{this->_ptr = cpy._ptr; this->_max = cpy._max; return (*this);}
		// Access
			iterator_type		base()									const 	{return this->_ptr;}
			reference			operator*()								const	{return this->_ptr->content;}
			pointer				operator->()							const	{return &(this->_ptr->content);}
		// Manipulation
			tree_iterator& 		operator++() 		/*++i*/						{this->_ptr = userdefined::get_successor<value_type>(this->_ptr); return *this;} 
			tree_iterator 		operator++(int) 	/*i++*/						{tree_iterator tmp = *this;this->_ptr = userdefined::get_successor<value_type>(this->_ptr);return tmp;}
			tree_iterator& 		operator--() 		/*--i*/						{if (userdefined::_is_end_node<value_type>(this->_ptr)) this->_ptr = _max; else this->_ptr = userdefined::get_predecessor<value_type>(this->_ptr); return *this;}
			tree_iterator 		operator--(int) 	/*i--*/						{tree_iterator tmp = *this; if (userdefined::_is_end_node<value_type>(this->_ptr)) this->_ptr = _max; else this->_ptr = userdefined::get_predecessor<value_type>(this->_ptr); return tmp;}
		// Comparison
			bool 				operator==(const tree_iterator &that)	const	{return (this->_ptr == that._ptr);}
			bool 				operator!=(const tree_iterator &that)	const	{return (this->_ptr != that._ptr);}
	}; //* end of class tree_iterator ----------------------------------------------------------------------------------------------------------------------------------

//* CONST ITERATOR CLASS DEFINITION ------------------------------------------------------------------------------------------------------------------------------------
	// iterator handling const pair
	template <typename Node>
	class tree_const_iterator {
	// Member types
		public:                 // Definition										// Member type      // Recap
			typedef 			Node												node_type;			// 					_s_RB_Node<pair<Key, T>> 
			typedef	typename	std::allocator<node_type>::pointer					node_pointer;		// Node ptr			_s_RB_Node<pair<Key, T>> *

			typedef typename 	std::allocator<node_type>::value_type::value_type	pair_type;			// Element type  	ft::pair< Key, T>
			typedef typename 	std::allocator<pair_type>::const_pointer			pair_pointer;		// const Pair ptr			ft::pair< Key, T> *
			typedef typename 	std::allocator<pair_type>::const_reference			pair_reference;		// const Pair ref			ft::pair< Key, T> &

			// definition for convention
			typedef				ft::bidirectional_iterator_tag						iterator_category;	// tag
			typedef 			pair_type								        	value_type;         
			typedef typename 	std::allocator<node_type>::difference_type			difference_type;    // distance between 2 nodes std::ptrdiff_t
			typedef				pair_pointer						           		pointer;            
			typedef 			pair_reference         								reference;          
			typedef          	node_pointer                                    	iterator_type;		
	// Member attributes
		private:
			node_type			_empty; // added to prevent segfault when access to default built iterator
			iterator_type		_max;
			iterator_type		_ptr;
			template <typename> friend class tree_iterator;

	// Member functions
		public:
		// Canonical
								tree_const_iterator() 										: _empty(), _max(&_empty), _ptr(&_empty)	{}
								tree_const_iterator(const iterator_type cpy)				: _empty(), _max(&_empty), _ptr(cpy)		{}
								tree_const_iterator(const iterator_type cpy, const iterator_type max)	: _empty(), _max(max), _ptr(cpy)		{}
								tree_const_iterator(const tree_iterator<node_type> & cpy)	: _empty(), _max(cpy._max), _ptr(cpy._ptr)	{}
								tree_const_iterator(const tree_const_iterator & cpy)		: _empty(), _max(cpy._max), _ptr(cpy._ptr)	{}

								~tree_const_iterator() {}
			tree_const_iterator&		operator=(const tree_const_iterator &cpy) 			{this->_ptr = cpy._ptr; this->_max = cpy._max; return (*this);}
			tree_const_iterator&		operator=(const tree_iterator<node_type> &cpy)		{this->_ptr = cpy._ptr; this->_max = cpy._max; return (*this);}
		// Access
			iterator_type		base()										const 	{return this->_ptr;}
			reference			operator*()									const	{return this->_ptr->content;}
			pointer				operator->()								const	{return &(this->_ptr->content);}
		// Manipulation
			tree_const_iterator&	operator++() 		/*++i*/						{this->_ptr = userdefined::get_successor<value_type>(this->_ptr); return *this;} 
			tree_const_iterator		operator++(int) 	/*i++*/						{tree_const_iterator tmp = *this;this->_ptr = userdefined::get_successor<value_type>(this->_ptr);return tmp;}
			tree_const_iterator&	operator--() 		/*--i*/						{if (userdefined::_is_end_node<value_type>(this->_ptr)) this->_ptr = _max; else this->_ptr = userdefined::get_predecessor<value_type>(this->_ptr); return *this;}
			tree_const_iterator		operator--(int) 	/*i--*/						{tree_const_iterator tmp = *this; if (userdefined::_is_end_node<value_type>(this->_ptr)) this->_ptr = _max; else this->_ptr = userdefined::get_predecessor<value_type>(this->_ptr); return tmp;}
		// Comparison
			bool 				operator==(const tree_const_iterator &that)	const	{return (this->_ptr == that._ptr);}
			bool 				operator!=(const tree_const_iterator &that)	const	{return (this->_ptr != that._ptr);}
	}; //* end of class tree_iterator ----------------------------------------------------------------------------------------------------------------------------------

	template <typename Node>
	class set_tree_iterator {
	// Member types
		public:                 // Definition										// Member type      // Recap
			typedef 			Node												node_type;			// 					_s_RB_Node<pair<Key, T>> 
			typedef	typename	std::allocator<node_type>::pointer					node_pointer;		// Node ptr			_s_RB_Node<pair<Key, T>> *

			typedef typename 	std::allocator<node_type>::value_type::value_type	pair_type;			// Element type  	ft::pair< Key, T>
			typedef typename 	std::allocator<pair_type>::const_pointer			pair_pointer;		// Pair ptr			ft::pair< Key, T> *
			typedef typename 	std::allocator<pair_type>::const_reference			pair_reference;		// Pair ref			ft::pair< Key, T> &

			// definition for convention
			typedef				ft::bidirectional_iterator_tag						iterator_category;	// tag
			typedef 			pair_type								        	value_type;         
			typedef typename 	std::allocator<node_type>::difference_type			difference_type;    // distance between 2 nodes std::ptrdiff_t
			typedef typename 	std::allocator<pair_type>::value_type::first_type	key_type;            
			typedef 		 	const key_type *									pointer;            
			typedef 		 	const key_type &									reference;          
			typedef          	node_pointer                                    	iterator_type;		
	// Member attributes
		private:
			node_type			_empty; // added to prevent segfault when access to default built iterator
			iterator_type		_max;
			iterator_type		_ptr;
			// template <typename> friend class tree_const_iterator;
	// Member functions
		public:
		// Canonical
								set_tree_iterator() 								: _empty(), _max(&_empty), _ptr(&_empty)	{}
								set_tree_iterator(iterator_type cpy, iterator_type max)	: _empty(), _max(max), _ptr(cpy)		{}
								set_tree_iterator(const set_tree_iterator & cpy)	: _empty(), _max(cpy._max), _ptr(cpy._ptr)	{}

								~set_tree_iterator() {}
			set_tree_iterator&		operator=(const set_tree_iterator &cpy)			{this->_ptr = cpy._ptr; this->_max = cpy._max; return (*this);}
		// Access
			iterator_type		base()										const 	{return this->_ptr;}
			reference			operator*()									const	{return this->_ptr->content.first;}
			pointer				operator->()								const	{return &(this->_ptr->content.first);}
		// Manipulation
			set_tree_iterator& 		operator++() 		/*++i*/						{this->_ptr = userdefined::get_successor<value_type>(this->_ptr); return *this;} 
			set_tree_iterator 		operator++(int) 	/*i++*/						{set_tree_iterator tmp = *this;this->_ptr = userdefined::get_successor<value_type>(this->_ptr);return tmp;}
			set_tree_iterator& 		operator--() 		/*--i*/						{if (userdefined::_is_end_node<value_type>(this->_ptr)) this->_ptr = _max; else this->_ptr = userdefined::get_predecessor<value_type>(this->_ptr); return *this;}
			set_tree_iterator 		operator--(int) 	/*i--*/						{set_tree_iterator tmp = *this; if (userdefined::_is_end_node<value_type>(this->_ptr)) this->_ptr = _max; else this->_ptr = userdefined::get_predecessor<value_type>(this->_ptr); return tmp;}
		// Comparison
			bool 				operator==(const set_tree_iterator &that)	const	{return (this->_ptr == that._ptr);}
			bool 				operator!=(const set_tree_iterator &that)	const	{return (this->_ptr != that._ptr);}
	}; //* end of class set_tree_iterator ----------------------------------------------------------------------------------------------------------------------------------

} //* end of namespace ft

#endif // ============================================================================<<map_RB_Tree.hpp============================================================================

	///* Pseudo code from 
	// https://sd.blackball.lv/library/Introduction_to_Algorithms_Third_Edition_(2009).pdf

	// TRANSPLANT(T, dst, src)
	// 1 if dst.p == NIL
	// 2 	T.root = src
	// 3 elseif dst == dst.p.left
	// 4 	dst.p.left = src
	// 5 else dst.p.right = src
	// 6 if src != NIL
	// 7 	src.p = dst.p

	// RB-TRANSPLANT(T, dst, src)
	// 1 if dst.p == T.nil
	// 2 	T.root = src
	// 3 elseif dst == dst.p.left
	// 4 	dst.p.left = src
	// 5 else dst.p.right = src
	// 6 src.p = dst.p

	// RB-DELETE(T, z)
	// 1 y = z
	// 2 y-original-color = y.color
	// 3 if z.left == T.nil
	// 4 	x = z.right
	// 5 	RB-TRANSPLANT(T, z, z.right)
	// 6 elseif z.right == T.nil
	// 7 	x = z.left
	// 8 	RB-TRANSPLANT(T, z, z.left)
	// 9 else y = TREE-MINIMUM(z.right)
	// 10 	y-original-color = y.color
	// 11 	x = y.right
	// 12 	if y.p == z
	// 13 		x.p = y
	// 14 	else RB-TRANSPLANT(T, y, y.right)
	// 15 		y.right = z.right
	// 16 		y.right.p = y
	// 17 	RB-TRANSPLANT(T, z, y)
	// 18 	y.left = z.left
	// 19 	y.left.p = y
	// 20 	y.color = z.color
	// 21 if y-original-color == BLACK
	// 22	RB-DELETE-FIXUP(T, x)

	// RB-DELETE-FIXUP(T, x)
	// 1 while x != T.root and x.color == BLACK
	// 2 	if x == x.p.left
	// 3 		w = x.p.right
	// 4 		if w.color == RED
	// 5 			w.color = BLACK // case 1
	// 6 			x.p.color = RED // case 1
	// 7 			LEFT-ROTATE(T, x.p) // case 1
	// 8 			w = x.p.right // case 1
	// 9 		if w.left.color == BLACK and w.right.color == BLACK
	// 10 			w.color = RED // case 2
	// 11 			x = x.p // case 2
	// 12 		else if w.right.color == BLACK
	// 13 				w.left.color = BLACK // case 3
	// 14 				w.color = RED // case 3
	// 15 				RIGHT-ROTATE(T, w/ // case 3
	// 16 				w = x.p.right // case 3
	// 17 			w.color = x.p.color // case 4
	// 18 			x.p.color = BLACK // case 4
	// 19 			w.right.color = BLACK // case 4
	// 20 			LEFT-ROTATE(T, x.p/ // case 4
	// 21 			x = T.root // case 4
	// 22 	else 
	// 		(same as then clause with “right” and “left” exchanged)
	// 23 x.color = BLACK
