#include <stdio.h>
#include "linked_list.h"

int test_linked_list() {
    LinkedList* list = create_list();
    
    append(list, 1); // list: 1
    append(list, 2); // list: 1 -> 2
    append(list, 3); // list: 1 -> 2 -> 3
    print_list(list);
    printf("Size: %d\n", get_size(list)); // size = 3

    prepend(list, 0); // list: 0 -> 1 -> 2 -> 3
    print_list(list);
    printf("Size: %d\n", get_size(list)); // size = 4

    insert_at(list, 10, 2); // list: 0 -> 1 -> 10 -> 2 -> 3
    print_list(list);
    printf("Size: %d\n", get_size(list)); // size = 5

    if (find(list, 10) == -1)
        printf("10 not found in the list.\n");
    else    
        printf("Index of 10 is : %d\n", find(list, 10)); 

    if (find(list, 99) == -1) 
        printf("99 not found in the list.\n");
    else
        printf("Index of 99 is : %d\n", find(list, 99)); 

    int removed = remove_at(list, 2);
    printf("Removed: %d\n", removed);
    print_list(list);
    printf("Size: %d\n", get_size(list));

    destroy_list(list);


    return 0;
}