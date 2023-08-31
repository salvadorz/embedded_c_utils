#include "llist.h"
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free*/

#define MAX_LLIST_LEN 10

typedef struct my_struct {
  uint8_t  dummy;
  uint32_t data;
} my_struct_t;

static void print_my_struct(void *s) {
  if (NULL == s) {
    printf("-{nil}\n");
  } else {
    printf("[%d]", (int)((my_struct_t *)(s))->data);
  }
}

static void print_ints(void *i) {
  if (NULL == i) {
    printf("-{nil}\n");
  } else {
    printf("[%d]", *(int *)(i));
  }
}

ll_handle_t mergeInBetween(ll_handle_t list1, ll_handle_t list2, int a, int b) {
    ll_handle_t ret_list = list1; //hold the head ref
    
    int cnt = 0;
    ll_handle_t prevA_node = NULL;
    ll_handle_t currB_node = list1;
    int nodeB_found = 0;
    
    if (a == 1){
        //prevA_node has null so only skipt the while
        ret_list = list2;
    } 
    else {
        prevA_node = list1;
        while(list1->next) {
            ++cnt;
            if (a == cnt)
                break;
            prevA_node = list1; // saving the prior
            list1 = list1->next;
        }
    //currB_node = prevA_node;
    }

    cnt = 0; // Need restart as a<=b constraint
    
    while(currB_node->next) {
        ++cnt;
        if (b == cnt) {
            nodeB_found = 1;
            currB_node  = currB_node->next;
            break;
        }
        currB_node = currB_node->next; 
    }
    if (0 == nodeB_found){
        currB_node = NULL;
    }

    
    if (NULL == prevA_node)
        prevA_node = list2;
    else
        prevA_node->next = list2;
    
    //Find the tail
    while(list2->next)
        list2 = list2->next;
    
    if (currB_node)
        list2->next = currB_node;
   
    return ret_list;
}

int main(int args, char** argv) {
    sl_list_t* my_list1 = malloc(sizeof(sl_list_t));
    sl_list_t* my_list2 = malloc(sizeof(sl_list_t));
    ll_handle_t new_list;
    my_list1->head = NULL;
    my_list1->tail = NULL;
    my_list2->head = NULL;
    my_list2->tail = NULL;
    (void)args;
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    fputc(a + '0', stderr);
    fputc('\n', stderr);
    fputc(b + '0', stderr);
    fputc('\n', stderr);

    int list_len_1    = atoi(argv[3]);
    int list_len_2    = 10;

    for (int i = 0; i < list_len_1; i++)
    {
        int tmp = i + 1;
        sl_list_insert(&my_list1, &tmp, sizeof(int));
    }
    for (int i = 6; i < list_len_2; i++)
    {
        int tmp = i;
        sl_list_insert(&my_list1, &tmp, sizeof(int));
    }
    llist_traverse(my_list1->head, print_ints);
    llist_traverse(my_list2->head, print_ints);
    new_list = mergeInBetween(my_list1->head, my_list2->head, a, b);
    llist_traverse(new_list, print_ints);
    //llist_delete_list(&my_list1->head);
    llist_delete_list(&my_list2->head);
    free(my_list1);
    free(my_list2);

    return 0;
}