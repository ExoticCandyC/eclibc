/**
 ** @copyright
 ** This file is part of the "eclibc" project.
 ** Copyright (C) 2022 ExoticCandy
 ** @email  ExoticCandyC.dev@gmail.com
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

#include <ec/vector.h>

/*
 * destructor is defined inside my own private API. So it is just a safeguard
 * to make sure it is not defined as my cutom macro. Feel free to delete these
 * three lines if you like.
 */
#ifdef destructor
#undef destructor
#endif

#ifdef __cplusplus
extern "C"
{
#endif
 
ec_api_vector_create(__ec_api_vectors_list);

__attribute__((destructor)) void ec_api_vector_garbage_collector(void)
{
    ec_api_vector_iterator itr;
    if(ec_api_vector_size(__ec_api_vectors_list) != 0)
    {
        ec_api_vector_for_each(itr, __ec_api_vectors_list)
        {
            ec_api_vector_iterator temp = ec_api_vector_iterator_value(ec_api_vector_iterator, itr);
            if(temp != EC_NULL)
                ec_api_vector_delete(temp);
        }
        ec_api_vector_delete(__ec_api_vectors_list);
    }
    ec_api_vector_delete(__ec_api_vectors_list);
}

void ____ec_api_register_new_vector(ec_api_vector_iterator itr)
{
    if(itr == __ec_api_vectors_list)
        return;
    ec_api_vector_expand(__ec_api_vectors_list, ec_api_vector_iterator);
    #ifdef __cplusplus
    ec_api_vector_element_at(ec_api_vector_iterator, __ec_api_vectors_list,
                             ec_api_vector_size(__ec_api_vectors_list) - 1)
                                = reinterpret_cast<ec_api_vector_iterator>(itr);
    #else
    ec_api_vector_element_at(ec_api_vector_iterator, __ec_api_vectors_list,
                             ec_api_vector_size(__ec_api_vectors_list) - 1)
                                            = (void *)itr;
    #endif
}

ec_api_vector *__ec_api_vector_new_node(size_t node_size)
{
    #ifdef __cplusplus
    ec_api_vector *node =
               reinterpret_cast<ec_api_vector *>(malloc(sizeof(ec_api_vector)));
    #else
    ec_api_vector *node = malloc(sizeof(ec_api_vector));
    #endif
    memset(node, 0, sizeof(ec_api_vector));
    node->_this = malloc(node_size);
    memset(node->_this, 0, node_size);
    return node;
}

ec_api_vector *ec_api_vector_begin(ec_api_vector *tree_node)
{
    if(tree_node != EC_NULL)
        while(tree_node->_parent != EC_NULL)
            tree_node = (ec_api_vector *)tree_node->_parent;
    return tree_node;
}

ec_api_vector *__ec_api_vector_element_at(ec_api_vector *tree_node, size_t index)
{
    size_t _index = 0;
    ec_api_vector *ptr = ec_api_vector_begin(tree_node);
    while(ptr->_child != EC_NULL)
    {
        if(_index++ == index)
            return ptr;
        ptr = (ec_api_vector *)ptr->_child;
    }
    if(_index == index)
        return ptr;
    return EC_NULL;
}

ec_api_vector *ec_api_vector_last(ec_api_vector *tree_node)
{
    while(tree_node->_child != EC_NULL)
        tree_node = (ec_api_vector *)tree_node->_child;
    return tree_node;
}

void __ec_api_vector_expand(ec_api_vector *tree_node, size_t node_size)
{
    ec_api_vector *ptr = ec_api_vector_last(tree_node);
    ec_api_vector *newNode = __ec_api_vector_new_node(node_size);

    #ifdef __cplusplus
    ptr->_child      = reinterpret_cast<void *>(newNode);
    newNode->_parent = reinterpret_cast<void *>(ptr);
    #else
    ptr->_child      = (void *)newNode;
    newNode->_parent = (void *)ptr;
    #endif
}

void __ec_api_vector_delete(ec_api_vector *tree_node)
{
    ec_api_vector_iterator itr;
    ec_api_vector *ptr = ec_api_vector_last(tree_node);
    if(tree_node == EC_NULL)
        return;
    ec_api_vector_for_each(itr, __ec_api_vectors_list)
    {
        if(ec_api_vector_iterator_value(ec_api_vector_iterator, itr)
                == tree_node)
        {
            ec_api_vector_iterator_value(ec_api_vector_iterator, itr) = EC_NULL;
            break;
        }
    }
    while(ptr->_parent != EC_NULL)
    {
        free(ptr->_this);
        ptr->_this = EC_NULL;
        ptr = (ec_api_vector *)ptr->_parent;
        free(ptr->_child);
        ptr->_child = EC_NULL;
    }
    if(ptr->_this != EC_NULL)
    {
        if(ptr->_child != EC_NULL)
            free(ptr->_child);
        free(ptr->_this);
        ptr->_this = EC_NULL;
    }
    if(ptr != EC_NULL)
    {
        free(ptr);
        ptr = EC_NULL;
    }
}

size_t ec_api_vector_size(ec_api_vector *tree_node)
{
    size_t tree_size = 0;
    ec_api_vector *ptr;
    if(tree_node == EC_NULL)
        return 0;
    ptr = ec_api_vector_begin(tree_node);
    if(ptr->_this != EC_NULL)
        tree_size++;
    while(ptr->_child != EC_NULL)
    {
        tree_size++;
        ptr = (ec_api_vector *)ptr->_child;
    }
    return tree_size;
}


#ifdef __cplusplus
}
#endif
