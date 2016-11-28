- forward declares __list_node and __list_node_base
- uses list_node_pointer_traits and VoidPtr to replace the recursive use of NodePtr in place of VoidPtr
    - in __list_node_pointer_traits -> rebinds from VoidPtr to list_node pointer
    - in list_node_base uses the rebind to define node_pointer type, base_pointer type, and link_pointer type
    - link_pointer and non_link_pointer are swapped so link_pointer is a node_pointer for list_node and a base_pointer for base_node
    
- in list_imp, uses allocator_traits<allocator_type>::void_pointer to pass as VoidPtr


# iterators
- list_iterator
    - takes Tp and VoidPtr, stores node pointer traits and link pointer
    - stores a link pointer as `__ptr_`
    - operator * returns ptr's value (first gets ptr as a node using __as_node)
    - operator -> returns a pointer to ptrs value as above
    - operator ++ sets ptr to ptr->next (passing int is preincrement and postincrement, review)
    - operator == and != compares the __ptr_ of each iterator
    