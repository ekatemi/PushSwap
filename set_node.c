/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:30:50 by emikhayl          #+#    #+#             */
/*   Updated: 2024/01/15 19:30:54 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    set_index_and_above_med(t_stack_node *stack)
{
    t_stack_node *current;
    size_t i;
    long int median;

    i = 0;
    median = list_len(stack) / 2;
    current = stack;
    while (current != NULL)
    {
        current->index = i;
        if (current->index <= median) //check this, maybe < median
            current->above_median = 1;
        else
            current->above_median = 0;
        current = current->next;
        i++; //maybe ++i
    }
}
//push cost to push up each stack
void    set_push_cost(t_stack_node *stack)
{
    t_stack_node *current = stack;

    while (current != NULL)
    {
        if (current->above_median == 1)
            current->push_cost = current->index;
        else
            current->push_cost = list_len(stack) - current->index;
        current = current->next;
    }
}

//push cost optimisation when we do rr or rrr or ss

void set_target_node_a(t_stack_node *a, t_stack_node *b)
{
    t_stack_node *current_a = a;
    t_stack_node *current_b = b;
    int diff;
    
    while (current_a != NULL)
    {
        if (current_a->num == find_smallest(a) && current_a->num < find_smallest(b))
            current_a->target_node = find_biggest(b);
        else 
        {
            diff = INT_MAX;
            t_stack_node *closest_smaller = NULL;
            
            while (current_b != NULL)
            {
                if (current_a->num < current_b->num)
                {
                    current_b = current_b->next;
                    continue;
                }
                if (current_a->num - current_b->num < diff)
                {
                    closest_smaller = current_b;
                    diff = current_a->num - current_b->num;
                }
                current_b = current_b->next;
            }
            current_a->target_node = closest_smaller;
        }
        current_a = current_a->next;
    }
    //closest smaller value
    //if no closest smaller, bigger
}

void set_target_node_b(t_stack_node *a, t_stack_node *b)
{
    t_stack_node *current_a = a;
    t_stack_node *current_b = b;
    int diff;
    
    while (current_b != NULL)
    {
        if (current_b->num == find_biggest(b) && current_b->num < find_biggest(a))
            current_b->target_node = find_smallest(a);
        else 
        {
            diff = INT_MAX;
            t_stack_node *closest_bigger = NULL;
            
            while (current_a != NULL)
            {
                if (current_a->num < current_b->num)
                {
                    current_a = current_a->next;
                    continue;
                }
                
                if (current_a->num - current_b->num < diff)
                {
                    closest_bigger = current_a;
                    diff = current_a->num - current_b->num;
                }
                current_a = current_a->next;
            }
            current_b->target_node = closest_bigger;
        }
        current_b = current_b->next;
    }
    //closest bigger value
    //if no 
    //closest bigger, smaller
}




void set_cheapest(t_stack_node *stack) {
    int curr_price = INT_MAX;
    t_stack_node *current = stack;
    t_stack_node *cheapest_node = NULL;

    // Find the cheapest node
    while (current != NULL) {
        if (current->above_median == current->target_node->above_median) 
        {
            int cost_to_compare;
            if (current->target_node->push_cost >= current->push_cost) {
                cost_to_compare = current->target_node->push_cost;
            } else {
                cost_to_compare = current->push_cost;
            }

            if (cost_to_compare < curr_price) 
            {
                curr_price = cost_to_compare;
                cheapest_node = current;
            }
        } 
        else 
        {
            int cost_to_compare = current->push_cost + current->target_node->push_cost;
            if (cost_to_compare < curr_price) 
            {
                curr_price = cost_to_compare;
                cheapest_node = current;
            }
        }
        current = current->next;
    }

    // Set cheapest to 1 for the cheapest node and 0 for others
    current = stack;
    while (current != NULL) {
        if (current == cheapest_node) {
            current->cheapest = 1;
        } else {
            current->cheapest = 0;
        }
        current = current->next;
    }
}