/* <vector.h> -*- C -*- */
/**
 ** @copyright
 ** This file is part of the "eclibc" project.
 ** Copyright (C) 2022 ExoticCandy
 ** @email  admin@ecandy.ir
 **
 ** Project's home page:
 ** https://github.com/ExoticCandyC/eclibc
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

/**
 *****************************************************************************
 **                                                                         **
 **                          How to use this API                            **
 **                                                                         **
 *****************************************************************************
 *****************************************************************************
 **                                                                         **
 ** To create a new vector, use:                                            **
 **      ec_api_vector_create($VECTOR_NAME$);                               **
 **                                                                         **
 ** This function will register the vector into the allocated vectors, so   **
 ** you dont have to worry about memory leaks, because the built-in garbage **
 ** collector will delete the vector and all it's allocated memory ON       **
 ** PROGRAM EXIT.                                                           **
 ** That directly means if a vector is going out of scope, you HAVE TO      **
 ** delete it manually to avoid memory leaks DURING program execution.      **
 **                                                                         **
 ** To delete a vector, use:                                                **
 **      ec_api_vector_delete($VECTOR_NAME$);                               **
 **                                                                         **
 ** You need to expand the vector each time you want to add a new variable. **
 **      ec_api_vector_expand($VECTOR_NAME$, $VARIABLE_TYPE$);              **
 **                                                                         **
 ** To access a variable at a specific index you can use:                   **
 **      ec_api_vector_element_at($VARIABLE_TYPE$, $VECTOR_NAME$, $INDEX$)  **
 **                                                                         **
 ** Please note that "ec_api_vector_element_at" will return the value and   **
 ** NOT the pointer.                                                        **
 **                                                                         **
 ** To access the pointer to a variable at a specific index you can use:    **
 **      ec_api_vector_iterator_at($VARIABLE_TYPE$, $VECTOR_NAME$, $INDEX$) **
 **                                                                         **
 ** To iterate through a vector you have access to the following functions: **
 **     1) ec_api_vector_iterate_begin($VECTOR_NAME$)                       **
 **             returns the iterator pointing to the first value of the     **
 **             vector.                                                     **
 **     2) ec_api_vector_iterate_last($VECTOR_NAME$)                        **
 **             returns the iterator pointing to the last value of the      **
 **             vector.                                                     **
 **     3) ec_api_vector_iterate_next($ITERATOR_NAME$)                      **
 **             returns the iterator pointing to the next value after the   **
 **             given iterator.                                             **
 **     4) ec_api_vector_iterate_previous($ITERATOR_NAME$)                  **
 **             returns the iterator pointing to the previous value before  **
 **             the given iterator.                                         **
 **     5) ec_api_vector_iterator_value($VARIABLE_TYPE$, $ITERATOR_NAME$)   **
 **             returns the value held by the iterator.                     **
 **     6) ec_api_vector_iteration_end()                                    **
 **             return an instance of a null pointer, which is the last     **
 **             iterator generated at the end of each iteration.            **
 **     7) ec_api_vector_for_each($ITERATOR_NAME$, $VECTOR_NAME$)           **
 **             loops through all the values stored in the vector. the      **
 **             given iterator will always hold the value of the current    **
 **             element.                                                    **
 **     7) ec_api_vector_for_each_reverse($ITERATOR_NAME$, $VECTOR_NAME$)   **
 **             the same as "ec_api_vector_for_each" but starts from the    **
 **             last element and ends after the first element.              **
 **                                                                         **
 ** To add a variable at the end of the vector, you can use the following:  **
 **     ec_api_vector_push_back($VECTOR_NAME$, $VARIABLE_TYPE$, $DATA$)     **
 **                                                                         **
 ** To get the size of a given vector, use the following function:          **
 **      ec_api_vector_size(VECTOR_NAME$)                                   **
 **                                                                         **
 **                                                                         **
 **                                                                         **
 **                                                                         **
 ** Please note that this API was written with "the programmer knows what   **
 ** they are doing" mindset. So, the API is not memory safe, you CAN        **
 ** corrupt the memory, for example by giving the wrong data type, or cause **
 ** segmentation faults or stack smashing if you dont watch what you are    **
 ** doing.                                                                  **
 ** This API is by no means aimed at making C programming "easy" and it is  **
 ** simply just a wrapper around 5 compiler features:                       **
 **         1) Macros                                                       **
 **         2) malloc                                                       **
 **         3) free                                                         **
 **         4) destructor                                                   **
 **         5) pointers                                                     **
 **                                                                         **
 **                                                                         **
 ** free and malloc dont work on 8bit compilers like Microchip(R) XC8       **
 ** compiler. So, the only compilers unable to compile this API are 8bit    **
 ** compilers.                                                              **
 ** Generally speaking to use this API for MCU projects, you                **
 ** should make sure you have enough heap memory allocated, as this API     **
 ** relies on the heap memory manipulation.                                 **
 ** (For example "xc16-gcc --heap=4000" in case of Microchip(R) XC16)       **
 **                                                                         **
 *****************************************************************************
 *****************************************************************************
 **/

#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
      defined(__TI_COMPILER_VERSION__)) && defined(__STRICT_ANSI__) &&        \
      (defined(_WIN32) || defined(__linux__))
#pragma GCC diagnostic ignored "-Wvla"
#endif

#ifndef ECLIBC_VECTOR_H
#define ECLIBC_VECTOR_H 1

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Since different compilers and different platforms implement NULL in a
 * different manner, EC_NULL is a helping macro to unify the NULL pointer over
 * all platforms.
 * E.g. some platforms have __builtin_null (like XC16) and some define it the
 *      same exact way.
 */
#ifndef EC_NULL
#define EC_NULL ((void *)0)
#endif

/* All CPP compilers on the other hand, use the same exact NULL pointer on all
 * platforms. So, there is no need to change the course of standard C++ library.
 */
#ifdef __cplusplus
#undef EC_NULL
#define EC_NULL NULL
#endif

typedef struct
{
    void *_parent;  /**< The pointer to the node before this node */
    void *_this;    /**< The pointer to the contents of the node */
    void *_child;   /**< The pointer to the node after this node */
} ec_api_vector; /**< The structure used to make vectors. */

/**
 * @def ec_api_extern_vector(name)
 * @brief           makes an extern definition of the given vector.
 * @param [in]name  name of the vector.
 */
#define ec_api_extern_vector(name)                                             \
        extern ec_api_vector *name

/**
 * @def ec_api_vector_create(name)
 * @brief           creates an empty vector with the given name.
 * @param [in]name  name of the vector to be created.
 */
#define ec_api_vector_create(name)                                             \
        ec_api_vector *name = EC_NULL

/**
 * @def ec_api_vector_delete(name)
 * @brief           deletes a whole vector and all its sub-nodes and frees the
 *                  memory assigned to it.
 * @param [in]name  name of the vector to be deleted.
 */
#define ec_api_vector_delete(name)                                             \
    {                                                                          \
        if(name != EC_NULL)                                                    \
            __ec_api_vector_delete(name);                                      \
        name = EC_NULL;                                                        \
    }

/**
 * @def ec_api_vector_iteration_end()
 * @brief           makes a dummy vector (null pointer) which can be used while
 *                  iterating through vector items to determine the end of the
 *                  iteration.
 * @return          A NULL pointer, denoting the end of the iteration.
 */
#define ec_api_vector_iteration_end() EC_NULL

/**
 * @def ec_api_vector_iterate_next(obj)
 * @brief               Gets the iterator object pointing to the next item
 *                      after the given object inside the vector.
 * @param [in]obj       The iterator object to be used as a reference to the
 *                      vector.
 * @return              The iterator pointing to the next item inside the
 *                      vector.
 */
#define ec_api_vector_iterate_next(obj)                                        \
    ((ec_api_vector *)(obj->_child))

/**
 * @def ec_api_vector_iterate_begin(obj)
 * @brief               Gets the iterator object pointing to the first item of
 *                      the vector.
 * @param [in]obj       The iterator object to be used as a reference to the
 *                      vector.
 * @return              The iterator pointing to the last item of the vector.
 */
#define ec_api_vector_iterate_begin(obj)                                       \
    (ec_api_vector_begin(obj))

/**
 * @def ec_api_vector_iterate_last(obj)
 * @brief               Gets the iterator object pointing to the last item of
 *                      the vector.
 * @param [in]obj       The iterator object to be used as a reference to the
 *                      vector.
 * @return              The iterator pointing to the last item of the vector.
 */
#define ec_api_vector_iterate_last(obj)                                        \
    (ec_api_vector_last(obj))

/**
 * @def ec_api_vector_iterate_previous(obj)
 * @brief               Gets the iterator object pointing to the previous item
 *                      before the given object inside the vector.
 * @param [in]obj       The iterator object to be used as a reference to the
 *                      vector.
 * @return              The iterator pointing to the previous item inside the
 *                      vector.
 */
#define ec_api_vector_iterate_previous(obj)                                    \
    ((ec_api_vector *)(obj->_parent))

/**
 * @def ec_api_vector_iterator_value(type, itr)
 * @brief               This simply acts as an alias for the contents of the
 *                      given iterator having the given type.
 * @param [in]type      The type of the value stored in the chosen item.
 *                      E.g. int, float, double, etc.
 * @param [in]itr       The iterator you wish to work with its value.
 * @example:
 *      // make two temporary iterators
 *      ec_api_vector_iterator itr1;
 *      ec_api_vector_iterator itr2;
 *
 *      // make a new vector named "vector1"
 *      ec_api_vector_create(vector1);
 *
 *      // add three integers to the vector:
 *      ec_api_vector_expand(vector1, int);
 *      ec_api_vector_expand(vector1, int);
 *      ec_api_vector_expand(vector1, int);
 *
 *      // get the iterator pointing to the begining of the vector1
 *      itr1 = ec_api_vector_iterate_begin(vector1);
 *      itr2 = itr1;
 *
 *      // set the first item of the vector to Integer:1
 *      ec_api_vector_iterator_value(int, itr1) = 1;
 *
 *      // move the itr2 to the 2nd item inside the vector
 *      itr2 = ec_api_vector_iterate_next(itr2);
 *
 *      // set the value of the 2nd item to be equal to the 1st item plus one.
 *      // note that itr2 is now pointing to the 2nd item while itr1 is pointing
 *      // to the first item.
 *      ec_api_vector_iterator_value(int, itr2) =
 *                                  ec_api_vector_iterator_value(int, itr1) + 1;
 *
 *      // move the itr3 to the 3rd item inside the vector
 *      itr2 = ec_api_vector_iterate_next(itr2);
 *
 *      // set the third item of the vector to Integer:3
 *      ec_api_vector_iterator_value(int, itr2) = 3;
 *
 *      // the code above will effectively make a vector of integers with 3
 *      // variables, and the values of [1, 2, 3]
 *
 *      // to print the values, one can simply do the following:
 *      ec_api_vector_for_each(itr1, vector1)
 *          printf("Item = %d\r\n", ec_api_vector_iterator_value(int, itr1));
 */
#define ec_api_vector_iterator_value(type, itr)                                \
    (*(((type *)((ec_api_vector *)itr)->_this)))

/**
 * @def ec_api_vector_iterator_pointer(type, itr)
 * @brief               This simply acts as an alias for the pointer to the
 *                      contents of the given iterator, having the given type.
 * @param [in]type      The type of the value stored in the chosen item.
 *                      E.g. int, float, double, etc.
 * @param [in]itr       The iterator you wish to work with its value.
 */
#define ec_api_vector_iterator_pointer(type, itr)                              \
     (((type *)((ec_api_vector *)itr)->_this))

/**
 * @def ec_api_vector_for_each(iterator, tree)
 * @brief               Just an alias for a for loop that will iterate through
 *                      all the items inside the vector.
 * @param [out]iterator The iterator pointing to the value of each item inside
 *                      the vector on each iteration.
 * @param [in]_vector   the vector to be iterated through.
 */
#define ec_api_vector_for_each(iterator, _vector)                              \
    for(iterator  = ec_api_vector_iterate_begin(_vector);                      \
        iterator != ec_api_vector_iteration_end();                             \
        iterator  = ec_api_vector_iterate_next(iterator))

/**
 * @def ec_api_vector_for_each(iterator, tree)
 * @brief               Just an alias for a for loop that will iterate through
 *                      all the items inside the vector. This macro will iterate
 *                      from the last item of the vector to the first one.
 * @param [out]iterator The iterator pointing to the value of each item inside
 *                      the vector on each iteration.
 * @param [in]_vector   the vector to be iterated through.
 */
#define ec_api_vector_for_each_reverse(iterator, _vector)                      \
    for(iterator  = ec_api_vector_iterate_last(_vector);                       \
        iterator != ec_api_vector_iteration_end();                             \
        iterator  = ec_api_vector_iterate_previous(iterator))

/**
 * @warning NOT SAFE
 * @warning NOT MEANT TO BE USED BY THE END USER
 * @def ec_api_vector_new_node(node_type)
 * @brief               Allocates enough memory for the given data type and
 *                      makes a dummy node. This node is supposed to be added
 *                      to an already existing vector. If not assigned properly,
 *                      this function WILL LEAD TO MEMORY LEAKS.
 * @param [in]node_type Type of the item to be used to make a new node. The size
 *                      of this item is used to determine the memory size.
 */
#define ec_api_vector_new_node(node_type)                                      \
      __ec_api_vector_new_node(sizeof(node_type))

/**
 * @def ec_api_vector_expand(_vector, node_type)
 * @brief               Expands an already existing vector, or initiate an
 *                      uninitialized vector. The node will be able to contain
 *                      a variable of the given type, and any other types with
 *                      equal or less size.
 * @param [in]_vector   The vector to be initialized and/or expanded.
 * @param [in]node_type The type of the item to be added to the vector.
 */
#define ec_api_vector_expand(_vector, node_type)                               \
        {                                                                      \
            if(ec_api_vector_size(_vector) == 0)                               \
            {                                                                  \
                _vector = ec_api_vector_new_node(node_type);                   \
                ____ec_api_register_new_vector(_vector);                       \
            }                                                                  \
            else                                                               \
                __ec_api_vector_expand(_vector, sizeof(node_type));            \
        }

/**
 * @def ec_api_vector_push_back(__vector, __type, __data)
 * @brief               Expands a vector and puts the given data at the end of
 *                      the vector.
 * @param [in]__vector  The vector to be initialized and/or expanded.
 * @param [in]__type    The type of the item to be added to the vector.
 * @param [in]__data    The data to be added to the new object inside the
 *                      vector.
 * @param [in]__size    The size of the data given to be added.
 */
#define ec_api_vector_push_back(__vector, __type, __data, __size)              \
    {                                                                          \
        ec_api_vector_expand(__vector, __type);                                \
        memcpy((((ec_api_vector *)ec_api_vector_last(__vector))->_this),       \
        (void *)(__data), __size);                                             \
    }

/**
 * @warning INVALID INDEX NUMBER CAN AND WILL LEAD TO SEGMENTATION FAULT OR
 *          STACK SMASHING. THE USER IS TO BE TRUSTED WITH THE USAGE OF THIS
 *          FUNCTION, JUST LIKE ANY OTHER THING IN STANDARD C LIBRARY.
 * @def ec_api_vector_iterator_at(type, _vector, index)
 * @brief               Gets an iterator, pointing to the desired item inside
 *                      the given vector, having the given data type.
 * @param [in]type      The type of the item stored at the given index.
 * @param [in]_vector   The vector the user wants to get/set a value of.
 * @param [in]index     The index of the item, inside the vector.
 * @return              The iterator pointing to the desired item inside the
 *                      given vector.
 */
#define ec_api_vector_iterator_at(type, _vector, index)                        \
          ((((type *)((ec_api_vector *)                                        \
                __ec_api_vector_element_at(_vector, index))->_this)))

/**
 * @warning INVALID INDEX NUMBER CAN AND WILL LEAD TO SEGMENTATION FAULT OR
 *          STACK SMASHING. THE USER IS TO BE TRUSTED WITH THE USAGE OF THIS
 *          FUNCTION, JUST LIKE ANY OTHER THING IN STANDARD C LIBRARY.
 * @def ec_api_vector_element_at(type, _vector, index)
 * @brief               An alias for the Nth item inside the vector.
 *                      The same exact syntax as "ec_api_vector_iterator_at"
 *                      but this one is an alias to the item value, not an
 *                      iterator.
 */
#define ec_api_vector_element_at(type, _vector, index)                         \
          (*(((type *)((ec_api_vector *)                                       \
                __ec_api_vector_element_at(_vector, index))->_this)))

/**
 * @brief ec_api_vector_iterator    The data type for the vector iterators
 */
typedef ec_api_vector *ec_api_vector_iterator;

/**
 * @brief ec_api_vector_begin   Gets the iterator pointing to the beggining of
 *                              the vector.
 * @param tree_node             Target vector
 * @return                      An iterator to the begining of the vector.
 */
ec_api_vector *ec_api_vector_begin(ec_api_vector *tree_node);

/**
 * @brief ec_api_vector_last    Gets the iterator pointing to the last item of
 *                              the vector.
 * @param tree_node             Target vector
 * @return                      An iterator to the last item of the vector.
 */
ec_api_vector *ec_api_vector_last(ec_api_vector *tree_node);

/**
 * @brief ec_api_vector_size    Calculates the current number of items stored
 *                              inside the vector.
 * @param tree_node             Target vector.
 * @return                      The number of the items stored inside the vector
 */
size_t ec_api_vector_size(ec_api_vector *tree_node);

/******************************************************************************/
/* API private functions. Not meant to be used outside the scope of this API. */
/* They are contained within the appropriate macros and they will invoke      */
/* these functions. So, their definition is required inside the header file.  */
/******************************************************************************/
void ____ec_api_register_new_vector(ec_api_vector_iterator itr);
ec_api_vector *__ec_api_vector_new_node(size_t node_size);
void __ec_api_vector_expand(ec_api_vector *tree_node, size_t node_size);
void __ec_api_vector_delete(ec_api_vector *tree_node);
ec_api_vector *__ec_api_vector_element_at(ec_api_vector *tree_node,
                                                                 size_t index);

#ifdef __cplusplus
}
#endif

#endif
