#include "watchpoint.h"
#include "expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static int cnt = 0;

void init_wp_pool() {
    int i;
    for (i = 0; i < NR_WP; i ++) {
        wp_pool[i].NO = i;
        wp_pool[i].next = &wp_pool[i + 1];
        wp_pool[i].info = -1;
    }
    wp_pool[NR_WP - 1].next = NULL;

    head = NULL;
    free_ = wp_pool;

}

/* TODO: Implement the functionality of watchpoint */
void free_wp(WP *wp, WP *head)
{
    /* delete wp from head */
    if(wp == head){
        head = head->next;
    }else{
        WP * tempHead = head;
        while(tempHead->next != wp){tempHead = tempHead->next;}
        tempHead->next = tempHead->next->next;
    }

    /* insert wp to free_ */
    WP * tempFree = free_;
    while(tempFree)
    {
        if(tempFree->next == NULL) // last one
        {
            tempFree->next = wp;
            break;
        }
        if(wp->NO > tempFree->NO  && wp->NO < tempFree->next->NO)
        {
            wp->next = tempFree->next;
            tempFree->next = wp;
            break;
        }
        tempFree = tempFree->next;
    }
}

WP* new_wp()
{
    assert(free_ != NULL);
    int temp_cnt = cnt - 1;
    WP *removed_head = head;

    if(cnt == 0) {removed_head = &wp_pool[0]; removed_head->next = NULL;}
    else{
        while(temp_cnt --){removed_head = removed_head->next;}
        printf("123");
        removed_head->next = &wp_pool[cnt];
        removed_head->next->next = NULL;
    }

    if(cnt == NR_WP) {
        free_ = NULL;
    }else{
     free_ = &wp_pool[cnt+1];
    }

    ++cnt;
    return removed_head;
}

