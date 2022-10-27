#include "errors.h"

void show_error(int error)
{
    switch (error)
    {
        case STRING_CREATE_ERROR:
            printf("Ошибка! Невозможно инициализировать строку.\n");
            break;
        case INPUT_STACK_ERROR:
            printf("Ошибка! При инициализации стека было введенно недопустимое значение.\n");
            break;
        case INCORRECT_SYMB:
            printf("Ошибка! При добавлении значения в стек было введенно недопустимое значение.\n");
            break;
        case SIZE_TOO_LONG:
            printf("Ошибка! При добавлении значения в стек было введенно значение длина которого больше 1.\n");
            break;
        case STACK_OVERFLOW:
            printf("Ошибка! Стек переполнен.\n");
            break;
        case INCORRECT_EXPRESSION:
            printf("Ошибка! При вычислении значения стека произошла ошибка.\n");
            break;
        case PRINT_ERROR:
            printf("Ошибка! Стек невозможно распечатать.\n");
            break;
        case SCANF_ERROR:
            printf("Ошибка! В меню можно ввести только 0-11.\n");
            break;
    }
}
