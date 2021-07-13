#include "watchpoint.h"
#include "expr.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

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
    /*
    WP *temp_free = free_;

    for(i = 1; i < NR_WP; ++i){
        temp_free->next = &wp_pool[i];
        temp_free = free_->next;
    }
    temp_free = NULL;
    */
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

    WP *removedFree_ = free_;
    removedFree_->next = NULL;

    free_ = free_->next;
    return removedFree_;
}

