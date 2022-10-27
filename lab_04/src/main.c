#include "utils.h"
#include "stack.h"
#include "errors.h"

void print_menu(void)
{
    printf("%s",
           "=====================================СТЕК МАССИВ==========================================\n"
           "|| Выберите номер пункта меню для работы со стеком, реализованным при помощи МАССИВА: ||\n"
           "|| 1. Ввести стек                                                                     ||\n"
           "|| 2. Добавить элемент в стек(push)                                                   ||\n"
           "|| 3. Удалить элемент из стека(pop)                                                   ||\n"
           "|| 4. Вычислить выражение                                                             ||\n"
           "|| 5. Вывести стек                                                                    ||\n"
           "=====================================СТЕК СПИСОК========================================\n");
    printf("%s",
           "|| Выберите номер пункта меню для работы со стеком, реализованным при помощи СПИСКА:  ||\n"
           "|| 6. Ввести стек                                                                     ||\n"
           "|| 7. Добавить элемент в стек(push)                                                   ||\n"
           "|| 8. Удалить элемент из стека(pop)                                                   ||\n"
           "|| 9. Вычислить выражение                                                             ||\n"
           "|| 10. Вывести стек                                                                   ||\n"
           "======================================Разное============================================\n"
           "|| 11. Анализ эффективности                                                           ||\n"
           "|| 0. Выход                                                                           ||\n"
           "========================================================================================\n");
}

int copy_stack_array(stack_array_t *copy, stack_array_t *den)
{
    copy->string = malloc(den->size_stack * sizeof(char));
    if (!copy->string)
        return EXIT_FAILURE;
    else
    {
        copy->size_stack = den->size_stack;
        strcpy(copy->string, den->string);
        copy->string[copy->size_stack] = '\0';
    }

    return EXIT_SUCCESS;
}

stack_list_t *copy_stack_list_t(stack_list_t *den)
{
    stack_list_t *tail = NULL, *head = NULL, *current = den;
    while (current != NULL)
    {
        if (head == NULL)
        {
            head = (stack_list_t *) malloc(sizeof(stack_list_t));
            head->size_stack = current->size_stack;
            head->symb = current->symb;
            head->next = NULL;
            tail = head;
        } else
        {
            tail->next = (stack_list_t *) malloc(sizeof(stack_list_t));
            tail = tail->next;
            tail->size_stack = current->size_stack;
            tail->symb = current->symb;
            tail->next = NULL;
        }
        current = current->next;
    }
    return head;
}

int print_stack_list_t(stack_list_t *stack_head)
{
    int rc = EXIT_SUCCESS;
    if(stack_head == NULL)
        return EXIT_FAILURE;
    else
    {
        stack_list_t copy_stack, *copy_list = &copy_stack;
        stack_list_t *head;
        copy_list = copy_stack_list_t(stack_head);
        printf("\nТекущее состояние стека, реализованного при помощи списка:\n");
        for (; copy_list->next; copy_list = head)
        {
            head = copy_list->next;
            printf("Адресс элемента: %p\n", (void*)copy_list);
            printf("Значение элемента: %c\n", copy_list->symb);
            (void) pop_list(&copy_list);
        }
        printf("Адресс элемента: %p\n", (void*)copy_list);
        printf("Значение элемента: %c\n", copy_list->symb);
    }
    return rc;
}

int print_stack_array(stack_array_t *stack)
{
    stack_array_t copy_stack;
    if (stack->size_stack == 0)
        return EXIT_FAILURE;
    else
    {
        if (copy_stack_array(&copy_stack, stack) == EXIT_FAILURE)
            return EXIT_FAILURE;

        printf("\nТекущее состояние стека, реализованного при помощи массива:\n");

        while (copy_stack.size_stack)
        {
            printf("Адресс элемета: %p\n", (void*)&(copy_stack.string[copy_stack.size_stack - 1]));
            if (copy_stack.string[copy_stack.size_stack - 2] == -48)
                printf("Значение элемента: %c%c\n", pop_array(&copy_stack), pop_array(&copy_stack));
            else
                printf("Значение элемнета: %c\n", pop_array(&copy_stack));
        }

        free(copy_stack.string);
        copy_stack.size_stack = 0;
        copy_stack.string = NULL;
    }
    return EXIT_SUCCESS;
}

int allocate_string(size_t size, char **string)
{
    char *str = malloc(size * sizeof(*str));
    if (!str)
        return EXIT_FAILURE;
    
    *string = str;

    return EXIT_SUCCESS;
}

int input_stack(stack_array_t *stack, size_t *count_num, size_t *count_sign)
{  
    char buff[BUFF_SIZE];
    char symb;
    printf("Строка для арифметической операции.\n");
    printf("Введите последовательность символов, оканчивающихся переводом на следующую строку: ");
    
    fgets(buff, BUFF_SIZE, stdin);

    while ((symb = getchar()) != '\n')
    {
        if (!isdigit(symb) && symb != '+' && symb != '-')
            return EXIT_FAILURE;
        if (isdigit(symb))
            (*count_num)++;
        else
            (*count_sign)++;
        if (push_array(stack, symb) != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int input_list(stack_list_t **next, size_t *count_num, size_t *count_sign)
{

    char buff[BUFF_SIZE];
    char symb;
    printf("Строка для арифметической операции.\n");
    printf("Введите последовательность символов, оканчивающихся переводом на следующую строку: ");
    
    fgets(buff, BUFF_SIZE, stdin);

    while ((symb = getchar()) != '\n')
    {
        if (!isdigit(symb) && symb != '+' && symb != '-')
            return EXIT_FAILURE;
        if (isdigit(symb))
            (*count_num)++;
        else
            (*count_sign)++;
        
        if (push_list(next, symb) != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void free_all(stack_list_t *stack1, stack_array_t *stack2)
{
    stack_list_t *next;

    if (stack2->string)
        free(stack2->string);
    
    for (; stack1->next; stack1 = next)
    {
        next = stack1->next;
        free(stack1);
    }
}

int main(void)
{
    size_t option;

    stack_array_t stack_array;
    stack_list_t *stack_list, stack;

    stack.size_stack = 0;
    stack.next = NULL;

    size_t count_num = 0;
    size_t count_sign = 0;

    size_t count_num_list = 0;
    size_t count_sign_list = 0;

    stack_array.size_stack = 0;
    stack_array.string = NULL;

    bool is_stack_array_create = false;
    bool is_stack_list_create = false;

    stack_list = &stack;

    print_menu();

    printf("Выберите пункт из меню: ");

    if (!scanf("%zu", &option))
    {
        show_error(SCANF_ERROR);
        return SCANF_ERROR;
    }

    while (option)
    {
        if (option == 1)
        {
            if (stack_array.size_stack)
                printf("Стек уже создан!\n");
            else
            {
                if (allocate_string(SIZE_STACK, &stack_array.string) != EXIT_SUCCESS)
                {
                    free_all(stack_list, &stack_array);
                    show_error(STRING_CREATE_ERROR);
                    return STRING_CREATE_ERROR;
                }

                if (input_stack(&stack_array, &count_num, &count_sign) != EXIT_SUCCESS)
                {
                    free_all(stack_list, &stack_array);
                    show_error(INPUT_STACK_ERROR);
                    return INPUT_STACK_ERROR;
                }
                is_stack_array_create = true;
            }
        }
        else if (option == 2)
        {
            if (!is_stack_array_create)
                printf("Стек еще не создан!\n");
            else
            {
                printf("Введите один символ: ");
                char buff[BUFF_SIZE];
                char symb;

                fgets(buff, BUFF_SIZE, stdin);

                symb = getchar();
                if (getchar() != '\n')
                {
                    free_all(stack_list, &stack_array);
                    show_error(SIZE_TOO_LONG);
                    return SIZE_TOO_LONG;
                }

                if (!isdigit(symb) && symb != '+' && symb != '-')
                {
                    free_all(stack_list, &stack_array);
                    return INCORRECT_SYMB;
                }

                if (push_array(&stack_array, symb) != EXIT_SUCCESS)
                {
                    free_all(stack_list, &stack_array);
                    show_error(STACK_OVERFLOW);
                    return STACK_OVERFLOW;
                }

                printf("\"%c\" успешно добавлен в стек!\n", symb);
            }
        }
        else if (option == 3)
        {
            if (!is_stack_array_create)
                printf("Стек еще не создан!\n");
            else
            {
                if (!stack_array.size_stack)
                    printf("Стек пуст!\n");
                else
                    printf("Элемент \"%c\" успешно удален.\n", pop_array(&stack_array));
            }
        }
        else if (option == 4)
        {
            if (!is_stack_array_create)
                printf("Стек еще не создан!\n");
            else
            {
                int error = EXIT_SUCCESS;
                if (!stack_array.size_stack)
                    printf("Стек пуст!\n");
                else
                {
                    int result = calc_expr(&stack_array, &error, count_num, count_sign);
                    if (error == EXIT_FAILURE)
                    {
                        free_all(stack_list, &stack_array);
                        show_error(INCORRECT_EXPRESSION);
                        return INCORRECT_EXPRESSION;
                    }
                    
                    printf("Результат выражения: %d\n", result);
                }
            }   
        }
        else if (option == 5)
        {
            if (!is_stack_array_create)
                printf("Стек еще не создан!\n");
            else
                if (print_stack_array(&stack_array))
                {
                    free_all(stack_list, &stack_array);
                    show_error(PRINT_ERROR);
                    return PRINT_ERROR;
                }
        }
        else if (option == 6)
        {
            if (is_stack_list_create)
                printf("Стек уже создан! Вы можете его заполнить или удалить элементы, воспользуйтесь \"7\" или \"8\"\n");
            else
            {
                if (input_list(&stack_list, &count_num_list, &count_sign_list) == EXIT_FAILURE)
                {
                    free_all(stack_list, &stack_array);
                    show_error(INPUT_STACK_ERROR);
                    return INPUT_STACK_ERROR;
                }
                is_stack_list_create = true;
            }
        }
        else if (option == 7)
        {
            if (!is_stack_list_create)
                printf("Стек еще не создан!\n");
            else
            {
                printf("Введите один символ: ");
                char symb = getchar();
                
                symb = getchar();

                if (getchar() != '\n')
                {
                    free_all(stack_list, &stack_array);
                    show_error(SIZE_TOO_LONG);
                    return SIZE_TOO_LONG;
                }
                if (!isdigit(symb) && symb != '+' && symb != '-')
                {
                    free_all(stack_list, &stack_array);
                    show_error(INCORRECT_SYMB);
                    return INCORRECT_SYMB;
                }
                if (push_list(&stack_list, symb) != EXIT_SUCCESS)
                {
                    free_all(stack_list, &stack_array);
                    show_error(STACK_OVERFLOW);
                    return STACK_OVERFLOW;
                }
                printf("\"%c\" успешно добавлен в стек!\n", symb);
            }
        }
        else if (option == 8)
        {
            if (!is_stack_list_create)
                printf("Стек еще не создан!\n");
            else
            {
                if (!stack_list->next)
                    printf("Все элементы стека удалены!\n");
                else
                    printf("Элемент \"%c\" успешно удален.\n", pop_list(&stack_list));
            }
        }
        else if (option == 9)
        {
            if (!is_stack_list_create)
                printf("Стек еще не создан!\n");
            else
            {
                if (!stack_list->next)
                    printf("Стек пуст!\n");
                else
                {
                    int error = EXIT_SUCCESS;
                    int result = calc_expr_list(&stack_list, &error, count_num_list, count_sign_list);
                    if (error == EXIT_FAILURE)
                    {
                        free_all(stack_list, &stack_array);
                        show_error(INCORRECT_EXPRESSION);
                        return INCORRECT_EXPRESSION;
                    }
                    printf("Результат выражения: %d\n", result);
                }
            }
        }
        else if (option == 10)
        {
            if (!is_stack_list_create)
                printf("Стек еще не создан!\n");
            else
            {
                if (!stack_list->next)
                    printf("Стек пуст!\n");
                else
                    if (print_stack_list_t(stack_list) == EXIT_FAILURE)
                    {
                        free_all(stack_list, &stack_array);
                        show_error(PRINT_ERROR);
                        return PRINT_ERROR;
                    }
            }
        }

        print_menu();
        printf("Выберите пункт из меню: ");
        if (!scanf("%zu", &option))
        {
            free_all(stack_list, &stack_array);
            show_error(SCANF_ERROR);
            return SCANF_ERROR;
        }
    }

    free_all(stack_list, &stack_array);

    return EXIT_SUCCESS;
}
