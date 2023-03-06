/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <avilla-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:46:45 by avilla-m          #+#    #+#             */
/*   Updated: 2023/03/04 17:47:28 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ============================================================================>>vector.hpp============================================================================
// Vector class is referenced from: 
    // https://en.cppreference.com/w/cpp/container/vector
    // https://cplusplus.com/reference/vector/vector/
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Vector structure:
    /// Member types
        //  value_type; allocator_type; size_type;  difference_type;    reference;          const_reference;
        //  pointer;    const_pointer;  iterator;   const_iterator;     reverse_iterator;   const_reverse_iterator;
    /// Member functions
        // Basics           // Constructors, Destructor, operator=, assign, get_allocator
        // ElementAccess    // at, operator[], front, back, data ????
        // Iterators        // begin, cbegin, end, cend, rbegin, crbegin, rend, crend
        // Capacity         // empty, size, max_size, reserve, capacity
        // Modifiers        // clear, insert, erase, push_back, pop_back, resize, swap
    /// Non Member functions
        // Operators        // ==,!=, <,<=,>,>=
        // std::swap(std::vector)
// --------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef     VECTOR_HPP
# define    VECTOR_HPP

#include "header.hpp"
#include "iterator_RandomAccess.hpp"
#include "iterator_reverse.hpp"
#include "utils.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class vector {
// ============================================================================>>VectorClassDeclaration====================================================
// Member types============================================================================================================================================
        public:                 // Definition                                       // Member type      // recap
            typedef             T                                                   value_type;         // T
            typedef             Allocator                                           allocator_type;     // Alloc
            typedef             std::size_t                                         size_type;          // unsigned long
            typedef             std::ptrdiff_t                                      difference_type;    // long

            typedef             value_type&                                         reference;          // T&
            typedef const       value_type&                                         const_reference;    // const T&

            typedef typename    allocator_type::pointer                             pointer;            // T*
            typedef typename    allocator_type::const_pointer                       const_pointer;      // const T*

            typedef typename    userdefined::RandomAccessIterator<value_type>       iterator;       
            typedef typename    userdefined::RandomAccessIterator<const value_type> const_iterator; 

            typedef typename    ft::reverse_iterator<iterator>                      reverse_iterator;       
            typedef typename    ft::reverse_iterator<const_iterator>                const_reverse_iterator;

        private:
			allocator_type      _allocator;
			pointer     	    _head;
			size_type           _size;
			size_type           _capacity;

// Member Functions========================================================================================================================================
        public:
        // Basics           // Constructors, Destructor, operator=, assign, get_allocator
        // ElementAccess    // at, operator[], front, back
        // Iterators        // begin, cbegin, end, cend, rbegin, crbegin, rend, crend
        // Capacity         // empty, size, max_size, reserve, capacity
        // Modifiers        // clear, insert, erase, push_back, pop_back, resize, swap

// ============================================================================>>ftVectorBasics============================================================
/// Constructors, Destructor, operator=, assign, get_allocator
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Constructors
// 1) Default constructor. Constructs an empty container with a default-constructed allocator.
//      vector();
// 2) Constructs an empty container with the given allocator alloc.
//     explicit vector( const Allocator& alloc );
// 3) Constructs the container with count copies of elements with value value.
//     explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator());
// 5) Constructs the container with the contents of the range [first, last).
//    This constructor has the same effect as vector(static_cast<size_type>(first), static_cast<value_type>(last), a) if InputIt is an integral type.
//     template< class InputIt >
//     vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() );
// 6) Copy constructor. Constructs the container with the copy of the contents of other.
//     vector( const vector& other );
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1*/ /*2*/ // Default
            explicit vector(const allocator_type& alloc = allocator_type())
            : _allocator(alloc), _head(nullptr), _size(0), _capacity(0){
                // print(DEBUG_FT,  GREEN, "Calling Vector Default Constructor");
                return;
            }
            
            /*3*/       // Fill
            explicit vector(size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
            : _allocator(alloc), _head(nullptr), _size(0), _capacity(0){
                // print(DEBUG_FT,  GREEN, "Calling Vector Fill Constructor");
                if (count > this->max_size())
                    throw std::length_error("vector");
                this->assign(count, value);
                return;
            }
            
            /*5*/       // Range
            template< class It >
            vector(
                typename ft::enable_if < ft::is_iterator_tagged< typename It::iterator_category >::value, It > ::type first,
                It last, 
                const Allocator& alloc = Allocator()
                )
            : _allocator(alloc), _head(nullptr), _size(0), _capacity(0){
                // if (false == ft::is_iterator_tagged<typename ft::iterator_traits<It>::iterator_category >::value)

                // print(DEBUG_FT,  GREEN, "Calling Vector Range Constructor");
                this->assign(first, last);
                return;
            }

            /*6*/       // Copy
            vector( const vector& other )
            : _allocator(allocator_type()), _head(nullptr), _size(0), _capacity(0){
                // print(DEBUG_FT,  GREEN, "Calling Vector Copy Constructor");
                *this = other;
                return;
            }

// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Destructor
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			~vector() {
                // print(DEBUG_V,  RED, "Calling Vector Destructor");
				this->clear();
                if (this->_capacity)
                    _allocator.deallocate(this->_head, this->_capacity);
                this->_capacity = 0;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator=    | 1) Copy assignment operator. Replaces the contents with a copy of the contents of other.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            vector& operator= (const vector& other) {
                if (other == *this)
					return (*this);
                // clearing
				this->clear();
                if (this->_capacity)
                    this->_allocator.deallocate(this->_head, this->_capacity);
                this->_capacity = 0;
                // copying from other
				this->_size = other._size;
				this->_capacity = other._capacity;
				this->_allocator = other._allocator;
                this->_head = this->_allocator.allocate(this->_capacity);
                if (this->_size == 0)
                    return (*this);
                for (size_type i = 0; i < this->_size; i++)
                    this->_allocator.construct(this->_head + i, other._head[i]);
                return (*this);
            }

// --------------------------------------------------------------------------------------------------------------------------------------------------------
// assign    | Replaces the contents of the container.
// 1) Replaces the contents with count copies of value value
//     void assign( size_type count, const T& value );
// 2) Replaces the contents with copies of those in the range [first, last). 
// The behavior is undefined if either argument is an iterator into *this.
// This overload has the same effect as overload (1) if InputIt is an integral type.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1*/       // Fill
            void assign( size_type new_size, const T& value ){
                // print(DEBUG_V,  CYAN, "Calling Vector assign // Fill");
				this->clear();
                if (new_size == 0)
                    return;
                
                // for (int i = 0; i < new_size; i++)
                //     this->push_back(value);

                this->reserve(new_size); //? NOTE: capacity is not updated if new_size < old_size 
                for (size_type i = 0; i < new_size; i++)
                {
                    _allocator.construct(_head + i, value);
                }
                this->_size = new_size;
                return;
            }

            /*2*/       // Range
            template< class It >
            void assign(
                typename ft::enable_if < ft::is_iterator_tagged< typename It::iterator_category >::value, It > ::type first,
                It last
            ){
                if (false == ft::is_iterator_tagged<typename ft::iterator_traits<It>::iterator_category >::value)
                    return ;
                // print(DEBUG_V,  CYAN, "Calling Vector assign // Range");
                if ((ft::distance(first, last)) > static_cast<difference_type>(this->max_size()))
                    throw std::length_error("vector");
				this->clear();
                size_type new_size = static_cast<size_type>(ft::distance(first, last));
                if (new_size == 0)
                    return;

                this->reserve(new_size); //? NOTE: capacity is not updated if new_size < old_size
                
                difference_type dist = ft::distance(first, last);
                for (int i = 0; i < (dist); i++){
                    this->_allocator.construct(this->_head + i, *first);
                    ++first;
                }
                this->_size = new_size;
                return;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// get_allocator    | Returns the allocator associated with the container.
//    allocator_type get_allocator() const;
// ----------------------------------------------------------s----------------------------------------------------------------------------------------------
    const allocator_type&   get_allocator(void)const    {
        // print(DEBUG_VALL,  CYAN, "Calling Vector get_allocator");
        return this->_allocator;
        }
// ============================================================================<<ftVectorBasics============================================================










// ============================================================================>>ftVectorElementAccess=====================================================
/// at | operator[] | front | back 
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// at    | Returns a reference to the element at specified location pos, with bounds checking. std::out_of_range if !(pos < size()).
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    reference       at(size_type pos){
        if (!(pos < this->_size))
            throw std::out_of_range("vector");
        return (*(this->_head + pos));
    }
    const_reference at(size_type pos) const {
        if (!(pos < this->_size))
            throw std::out_of_range("vector");
        return (*(this->_head + pos));
    }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator[]    | Returns a reference to the element at specified location pos. No bounds checking is performed.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    reference       operator[](size_type pos)       {return (*(this->_head + pos));}
    const_reference operator[](size_type pos) const {return (*(this->_head + pos));}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// front    | Returns a reference to the first element in the container.
// Calling front on an empty container is undefined. For a container c, the expression c.front() is equivalent to *c.begin().
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    reference       front()         {return (*(this->_head));}
    const_reference front() const   {return (*(this->_head));}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// back    | Returns a reference to the last element in the container.
// Calling back on an empty container causes undefined behavior. For a non-empty container c, the expression c.back() is equivalent to *std::prev(c.end())
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    reference       back()          {return (*(this->_head + this->_size - 1));}
    const_reference back() const    {return (*(this->_head + this->_size - 1));}
// ============================================================================<<ftVectorElementAccess============================================================================










// ============================================================================>>ftVectorIterators============================================================================
/// begin | end | rbegin | rend
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// begin    | Returns an iterator to the first element of the vector.
// If the vector is empty, the returned iterator will be equal to end().
//    iterator begin();
//    const_iterator begin() const;
// --------------------------------------------------------------------------------------------------------------------------------------------------------
        iterator        begin()         {
            // print(DEBUG_V,  YELLOW, "Calling Vector begin");
            return (iterator        (this->_head)); 
        }
        
        const_iterator  begin() const   {
            // print(DEBUG_V,  YELLOW, "Calling Vector const_iterator begin");
            return (const_iterator  (this->_head)); 
        }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// end    | Returns an iterator to the element following the last element of the vector.
// This element acts as a placeholder; attempting to access it results in undefined behavior.
//    iterator end();
//    const_iterator end() const;
// --------------------------------------------------------------------------------------------------------------------------------------------------------
        iterator        end()           {
            // print(DEBUG_V,  YELLOW, "Calling Vector end");
            if (this->empty())
                return (this->_head);
            return (iterator        (this->_head + this->_size));
        }
        
        const_iterator  end() const     {
            // print(DEBUG_V,  YELLOW, "Calling Vector const_iterator end");
            if (this->empty())
                return (this->_head);
            return (const_iterator  (this->_head + this->_size));
        }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// rbegin    | Returns a reverse iterator to the first element of the reversed vector. It corresponds to the last element of the non-reversed vector. 
// If the vector is empty, the returned iterator is equal to rend().
// --------------------------------------------------------------------------------------------------------------------------------------------------------
        reverse_iterator        rbegin()        {
            // print(DEBUG_V,  YELLOW, "Calling Vector reverse begin");
            return (reverse_iterator        (this->end())); 
        }
        
        const_reverse_iterator  rbegin() const  {
            // print(DEBUG_V,  YELLOW, "Calling Vector reverse const_iterator begin");
            return (const_reverse_iterator  (this->end()));
        }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// end    | Returns a reverse iterator to the element following the last element of the reversed vector. 
// It corresponds to the element preceding the first element of the non-reversed vector. 
// This element acts as a placeholder, attempting to access it results in undefined behavior.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
        reverse_iterator        rend()          {
            // print(DEBUG_V,  YELLOW, "Calling Vector reverse end");
            return (reverse_iterator        (this->begin()));
        }
        
        const_reverse_iterator  rend() const    {
            // print(DEBUG_V,  YELLOW, "Calling Vector reverse const_iterator end");
            return (const_reverse_iterator  (this->begin()));
        }
// ============================================================================<<ftVectorIterators============================================================================







// ============================================================================>>ftVectorCapacity============================================================================
/// empty | size | max_size | capacity | reserve
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// empty    | Checks if the container has no elements, i.e. whether begin() == end(). true if the container is empty, false otherwise
// --------------------------------------------------------------------------------------------------------------------------------------------------------    
			bool empty (void) const {
                // print(DEBUG_VALL,  CYAN, "Calling Vector empty");
                return ((this->_size == 0) ? true : false);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// size    | Returns the number of elements in the container, i.e. std::distance(begin(), end()).
// --------------------------------------------------------------------------------------------------------------------------------------------------------    
            size_type size() const{
                // print(DEBUG_VALL,  CYAN, "Calling Vector size");
                return this->_size;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// max_size    | Returns the maximum number of elements the container is able to hold due to system or library implementation limitations, 
//              i.e. std::distance(begin(), end()) for the largest container.
//              This value typically reflects the theoretical limit on the size of the container, at most std::numeric_limits<difference_type>::max(). 
//              At runtime, the size of the container may be limited to a value smaller than max_size() by the amount of RAM available.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            size_type max_size() const{
                // print(DEBUG_VALL,  CYAN, "Calling Vector max_size");
                return _allocator.max_size();
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// capacity    | Returns the number of elements that the container has currently allocated space for.
//---------------------------------------------------------------------------------------------------------------------------------------------------------  
            size_type capacity() const{
                // print(DEBUG_VALL,  CYAN, "Calling Vector capacity");
                return this->_capacity;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// reserve    | Requests that the vector capacity be at least enough to contain n elements.
// If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n (or greater).
// In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
// This function has no effect on the vector size and cannot alter its elements.
// If the size requested is greater than the maximum size (vector::max_size), a length_error exception is thrown.
// --------------------------------------------------------------------------------------------------------------------------------------------------------  
            void reserve(size_type new_capacity){
                // print(DEBUG_V,  CYAN, "Calling Vector reserve");
                if (new_capacity > this->max_size())
					throw (std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
                else if (new_capacity > _capacity)
                {
                    pointer     new_head        = this->_allocator.allocate(new_capacity);
                    iterator    new_it          (new_head);

                    for (size_type i = 0; i < this->_size; i++)
                    {
                        this->_allocator.construct(new_head + i, *(this->_head + i));
                        this->_allocator.destroy(this->_head + i);
                    }
                    if (this->_capacity)
                        this->_allocator.deallocate(this->_head, this->_capacity);
                    this->_head = new_head;
                    this->_capacity = new_capacity;
                }
                return;
            }
// ============================================================================<<ftVectorCapacity============================================================================







// ============================================================================>>ftVectorModifiers============================================================================
/// clear | insert | erase | push_back | pop_back | resize | swap
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// clear    | Erases all elements from the container. After this call, size() returns zero.
// Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterators are also invalidated.  
// Leaves the capacity() of the vector unchanged (note: the standard's restriction on the changes to capacity is in the specification of vector::reserve, see [1])
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			void clear(){
				// print(DEBUG_V,  CYAN, "Calling Vector clear");
                if (this->_size == 0){
                    return;
                }
                size_type   i   = 0;
                pointer     ptr;
                for (i = 0; i < this->_size; i++){
                    ptr = this->_head + i;
                    _allocator.destroy(ptr);
                }
                this->_size = 0;
			}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// insert    | Inserts elements at the specified location in the container.
// 1-2) inserts value before pos.
// 3) inserts count copies of the value before pos.
// 4) inserts elements from range [first, last) before pos.
// This overload has the same effect as overload (3) if InputIt is an integral type.
// The behavior is undefined if first and last are iterators into *this.
// ---
// Causes reallocation if the new size() is greater than the old capacity(). If the new size() is greater than capacity(), all iterators and references are invalidated. 
// Otherwise, only the iterators and references before the insertion point remain valid. The past-the-end iterator is also invalidated.
// Return value
// 1-2) Iterator pointing to the inserted value.
// 3) Iterator pointing to the first element inserted, or pos if count == 0.
// 4) Iterator pointing to the first element inserted, or pos if first == last.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
/*1*/   iterator insert(
                userdefined::RandomAccessIterator< typename ft::remove_const<const T>::type > pos,
                const T& value
            ){
                size_type distance      = static_cast<size_type>(pos - this->begin());
                size_type new_capacity  = (
                    this->_size + 1 > this->_capacity ? 
                        (0 == this->_capacity ? 1 : this->_capacity * 2)
                        : this->_capacity
                );

                this->reserve(new_capacity);
                iterator it             = this->end();
                iterator position       = (this->begin() + distance);
                for (; it > position; it--){
                    _allocator.construct(it.base(), *(it - 1));
                    _allocator.destroy((it - 1).base());
                }
                this->_allocator.construct(it.base(), value);
                this->_size += 1;
                return  position;
            }

    /*3*/   iterator insert(
                userdefined::RandomAccessIterator< typename ft::remove_const<const T>::type > pos,
                size_type count,
                const T& value
                ){
                if (count == 0)
                    return  pos;

                size_type   distance = static_cast<size_type>(pos - this->begin());
                size_type   new_size = _size + count;
                iterator    it, position;

                this->reserve(new_size);
                position = (this->begin() + distance);
                for (it = (this->end() + count - 1); it > (position + count - 1); it--){
                    _allocator.construct(it.base(), *(it - count));
                    _allocator.destroy((it - count).base());
                }
                for (; it >= position; it--){
                    _allocator.construct(it.base(), value);
                }
                _size = new_size;
                return  position;
            }

    /*4*/   template< class It >
            iterator insert(
                userdefined::RandomAccessIterator< typename ft::remove_const<const T>::type > pos,
                typename ft::enable_if < ft::is_iterator_tagged< typename It::iterator_category >::value, It > ::type first,
                It last
            ){
                if (false == ft::is_iterator_tagged<typename ft::iterator_traits<It>::iterator_category >::value)
                    return pos;
                if (first == last)
                    return  pos;
                
                size_type   distanceToFirst   = static_cast<size_type>(pos - this->begin());
                size_type   rangeSize         = static_cast<size_type>(ft::distance(first, last));
                size_type   new_size          = _size + rangeSize;
                size_type   new_capacity;
                iterator    it, position;

                new_capacity = this->_capacity;
                for (size_type size_i = this->_size; size_i < new_size; size_i++)
                {
                    if (size_i == new_capacity)
                        new_capacity = (new_capacity == 0) ? 1 : (new_capacity * 2);                   
                }

                this->reserve(new_capacity);
                position = (this->begin() + distanceToFirst);
                for (it = (this->end() + rangeSize - 1); it > (position + rangeSize - 1); it--){
                    _allocator.construct(it.base(), *(it - rangeSize));
                    _allocator.destroy((it - rangeSize).base());
                }
                last--;
                for (; it >= (position ); it--){
                    _allocator.construct(it.base(), *last);
                    last--;
                }
                _size = new_size;
                return (position);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// erase    | Erases the specified elements from the container.
// 1) Removes the element at pos.
// 2) Removes the elements in the range [first, last).
// Invalidates iterators and references at or after the point of the erase, including the end() iterator.
// The iterator pos must be valid and dereferenceable. Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
// The iterator first does not need to be dereferenceable if first == last: erasing an empty range is a no-op.
// Return value
//     Iterator following the last removed element.
//     If pos refers to the last element, then the end() iterator is returned.
//     If last == end() prior to removal, then the updated end() iterator is returned.
//     If [first, last) is an empty range, then last is returned.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            /*1*/ iterator erase(iterator pos){
                size_type   distance = static_cast<size_type>(pos - this->begin());
                size_type   new_size = this->_size - 1;

                for (size_type i = distance; i < new_size; i++){
                    this->_allocator.destroy(this->_head + i);
                    this->_allocator.construct(this->_head + i, *(_head + i + 1));
                }
                this->_allocator.destroy(this->_head + new_size);
                this->_size = new_size;
                return iterator(this->_head + distance);
            }

            /*2*/ iterator erase( iterator first, iterator last ){
                size_type   distanceToFirst   = static_cast<size_type>(first - this->begin());
                size_type   rangeSize         = static_cast<size_type>(ft::distance(first, last));
                size_type   new_size          = (this->_size - rangeSize);
                size_type   i;

                for (i = distanceToFirst; i < new_size ; i++){
                    this->_allocator.destroy(this->_head + i);
                    if ((this->begin() + i + rangeSize) < this->end())
                        this->_allocator.construct(this->_head + i, *(this->_head + i + rangeSize));
                }
                for (; i < this->_size ; i++){
                    this->_allocator.destroy(this->_head + i);
                }
                this->_size = new_size;
                return iterator(this->_head + distanceToFirst);
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// push_back    | Appends the given element value to the end of the container.
// 1) The new element is initialized as a copy of value.
// If the new size() is greater than capacity() then all iterators and references (including the past-the-end iterator) are invalidated. 
// Otherwise only the past-the-end iterator is invalidated.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            void push_back(const T& value){
                if(this->_size == this->_capacity)
                    this->reserve(this->_capacity == 0 ? 1 : this->_capacity * 2);
                this->_allocator.construct(this->_head + this->_size, value);
                this->_size++;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// pop_back    | Removes the last element of the container.
// Calling pop_back on an empty container results in undefined behavior.
// Iterators and references to the last element, as well as the end() iterator, are invalidated.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
            void pop_back(){
                this->_allocator.destroy(this->_head + this->_size - 1);
                this->_size--;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// resize    | Resizes the container to contain count elements.
// If the current size is greater than count, the container is reduced to its first count elements.
// If the current size is less than count, (2) additional copies of value are appended.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
        // /*2*/ void resize (size_type count, value_type value = value_type())
		// 	{
		// 		if (count > this->max_size())
		// 			throw (std::length_error("vector"));
        //         while (count < this->size())
		// 			this->pop_back();
		// 		while (count > this->size())
		// 			this->push_back(value);
		// 	}
        /*2*/ void resize(size_type count, value_type value = value_type()){
				if (count > this->max_size())
					throw (std::length_error("vector"));
                if (this->_size > count){
                    this->erase(this->begin() + static_cast<difference_type>(count), this->end());
                }
                else if (this->_size < count){
                    this->reserve(count);
                    for (size_type i = 0; i < (count - this->_size); i++){
                        this->_allocator.construct(this->_head + this->_size + i, value);
                    }
                    this->_size += (count - this->_size);
                }
                return;
            }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// swap    | Exchanges the contents of the container with those of other. 
// Does not invoke any move, copy, or swap operations on individual elements.
// All iterators and references remain valid. The past-the-end iterator is invalidated.
//          std::swap => template< class T > void swap( T& a, T& b ){T c = a; a = b; b = c;}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
			void swap (vector& other){
				ft::swap(this->_size, other._size);
				ft::swap(this->_capacity, other._capacity);
                ft::swap(this->_allocator, other._allocator);
				
                ft::swap(this->_head, other._head);




			}

                // std::swap(this->_size, x._size);
				// std::swap(this->_capacity, x._capacity);
				// std::swap(this->_allocator, x._allocator);
				// std::swap(this->__vector, x.__vector);

            // void swap( vector& other ){
			// 	allocator_type	other_alloc = other._allocator;
			// 	size_type		other_size = other._size;
			// 	size_type		other_capacity = other._capacity;

                // pointer			other_head = other._head;
				// other._head = this->_head;
				// this->_head = other_head;
                
                // 	other._allocator = this->_allocator;
			// 	other._size = this->_size;
			// 	other._capacity = this->_capacity;

			// 	this->_allocator = other_alloc;
			// 	this->_size = other_size;
			// 	this->_capacity = other_capacity;
            // }
    }; // ============================================================================<<VectorClassDeclaration=============================================






// Non Member Functions====================================================================================================================================
        // Operators        // ==,!=, <,<=,>,>=
        // std::swap(std::vector)
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Operators
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// operator (1, 2): ==,!= ; and (3 - 6): <,<=,>,>=    | Compares the contents of two vectors.
// 1-2) Checks if the contents of lhs and rhs are equal, that is, 
// they have the same number of elements and each element in lhs compares equal with the element in rhs at the same position.
// 3-6) Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent to std::lexicographical_compare.
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    template< class T, class Alloc >
    bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < rhs.size(); i++){
            if (lhs[i] != rhs[i])
                return false;
        }
        return true;
    }

    template< class T, class Alloc >
    bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return (!(lhs == rhs));}

    template< class T, class Alloc >
    bool operator< (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

    template< class T, class Alloc >
    bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return (rhs < lhs);}

    template< class T, class Alloc >
    bool operator<=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return (!(lhs > rhs));}

    template< class T, class Alloc >
    bool operator>=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {return (!(lhs < rhs));}
// --------------------------------------------------------------------------------------------------------------------------------------------------------
// ft::swap
// Specializes the std::swap algorithm for std::vector. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
// --------------------------------------------------------------------------------------------------------------------------------------------------------
    template< class T, class Alloc >
    void swap(  ft::vector<T,Alloc>& lhs,
                ft::vector<T,Alloc>& rhs )
    {
        lhs.swap(rhs);
    }
// --------------------------------------------------------------------------------------------------------------------------------------------------------
}
#endif // ============================================================================<<vector.hpp==========================================================
