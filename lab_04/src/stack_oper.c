#include "stack.h"

int push_array(stack_array_t *stack, char symb)
{
    if (stack->size_stack + 1 >= SIZE_STACK)
        return EXIT_FAILURE;
    stack->size_stack++;
    stack->string[stack->size_stack - 1] = symb; 

    return EXIT_SUCCESS;
}

char pop_array(stack_array_t *stack)
{
    stack->size_stack--;
    return stack->string[stack->size_stack];
}
// 2 - 3 - 2
// 2 + + 3
/*
2+3
// 2+3-3-3+2-5+9
// - - - + - +
2-3-3-3+2-5+9
9 5 2 3 3 3 2
+ - + - - - +

3
+
2

*/

int calc_expr(stack_array_t *stack, int *error, size_t count_num, size_t count_sign)
{
    int sum = 0;
    if (count_num != count_sign + 1)
    {
        *error = EXIT_FAILURE;
        return sum;
    }

    stack_array_t number;
    stack_array_t sign;

    char symb;
    
    number.string = malloc(count_num * sizeof(char));
    sign.string = malloc(count_sign * sizeof(char));

    number.size_stack = 0;
    sign.size_stack = 0;

    while (stack->size_stack)
    {
        symb = pop_array(stack);
        if (isdigit(symb))
            push_array(&number, symb);
        else
            push_array(&sign, symb);
    }

    sum = pop_array(&number) - '0';
    
    if (number.size_stack)
    {
        char symb_sign;
        while (number.size_stack)
        {
            symb_sign = pop_array(&sign);
            if (symb_sign == '-')
                sum -= pop_array(&number) - '0';
            else
                sum +=  pop_array(&number) - '0';;
        }
    }

    free(number.string);
    free(sign.string);

    return sum;
}

stack_list_t *new_list_create(char symb)
{
    stack_list_t *node = malloc(sizeof(stack_list_t));

    if (node)
    {
        node->symb = symb;
        node->size_stack = 1;
        node->next = NULL;
    }

    return node;
}

void defaul_stack_list_t(stack_list_t *stack)
{
    stack->size_stack = 0;
    stack->next = NULL;
}

int push_list(stack_list_t **head, char symb)
{
    if ((*head)->size_stack + 1 >= SIZE_STACK)
        return EXIT_FAILURE;
    
    stack_list_t *node = new_list_create(symb);
    
    if (node)
    {
        node->next = *head;
        node->size_stack += (*head)->size_stack;
        *head = node;
    }
    
    return EXIT_SUCCESS;
}

char pop_list(stack_list_t **head)
{
    char symb = (*head)->symb;
    stack_list_t *tmp = *head;

    if ((*head)->next)
        *head = (*head)->next;
    
    free(tmp);

    return symb;
}

int calc_expr_list(stack_list_t **stack, int *error, size_t count_num, size_t count_sign)
{
    int sum = 0;
    if (count_num != count_sign + 1)
    {
        *error = EXIT_FAILURE;
        return sum;
    }

    stack_list_t num;
    num.size_stack = 0;
    num.next = NULL;
    stack_list_t si;
    si.size_stack = 0;
    si.next = NULL;

    stack_list_t *number = &num;
    stack_list_t *sign = &si;

    char symb;

    while ((*stack)->next)
    {
        symb = pop_list(stack);
        if (isdigit(symb))
            push_list(&number, symb);
        else
            push_list(&sign, symb);
    }

    sum = pop_list(&number) - '0';
    
    if (number->next)
    {
        char symb_sign;
        while (number->next)
        {
            symb_sign = pop_list(&sign);
            if (symb_sign == '-')
                sum -= pop_list(&number) - '0';
            else
                sum +=  pop_list(&number) - '0';;
        }
    }

    return sum;
}
