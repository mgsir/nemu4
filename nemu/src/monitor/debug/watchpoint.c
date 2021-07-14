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
    free_ = &wp_pool[0];
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

    WP *oldfree_ = free_;
    if(cnt == NR_WP) {
        free_ = NULL;
    }else{
        free_ = free_->next;
    }

    WP *temp_head = head;

    if(head == NULL) {head = &wp_pool[0]; head->next = NULL;}
    else{
        if(temp_head->NO > oldfree_->NO){
            oldfree_->next = temp_head;
            head = oldfree_;
        }else{

            while(temp_head->next)
            {
                if(temp_head->next->NO >oldfree_->NO)  break;
                temp_head = temp_head->next;
            }

            oldfree_->next = temp_head->next;
            temp_head->next = oldfree_;
        }
    }
    ++cnt;
    printf("%d\n",cnt);
    return oldfree_;
}

