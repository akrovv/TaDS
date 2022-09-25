#include "func_stdio.h"

void print_error(int error)
{
    switch (error)
    {
    case EMPTY_STRING:
        printf("ОШИБКА! Введена пустая строка!\n");
        break;
    case STRING_OVERFLOW:
        printf("ОШИБКА! Переполнение возможно допустимых значений!\n");
        break;
    case EPS_ERROR:
        printf("ОШИБКА! В числе находятся несколько обозначений \"e\" либо одно \"e\"!\n");
        break;
    case MANTISS_SIGN_ERROR:
        printf("ОШИБКА! Введено несколько знаков перед мантиссой или в самой мантиссе!\n");
        break;
    case MANTISS_POINT_ERROR:
        printf("ОШИБКА! Введено несколько \".\" перед мантиссой или в самой мантиссе!\n");
        break;
    case INCORRECT_FLOAT:
        printf("ОШИБКА! Введена строка, не подходящая под формат \"+-m.nЕ+-K\"!\n");
        break;
    case MANTISSA_OVERFLOW:
        printf("ОШИБКА! Мантисса содержит больше 30 десятичных цифр!\n");
        break;
    case ORDER_EPS_ERROR:
        printf("ОШИБКА! В порядке находятся несколько обозначений \"e\"!\n");
        break;
    case ORDER_SIGN_ERROR:
        printf("ОШИБКА! Введено несколько знаков перед порядком или в самом порядке!\n");
        break;
    case ORDER_OVERFLOW:
        printf("ОШИБКА! В порядке больше 5 действительных цифр!\n");
        break;
    case INCORRECT_INT:
        printf("ОШИБКА! Введена строка, не подходящая под формат \"+-m\"!\n");
        break;
    }
}

void print_field(void)
{
    for (size_t i = 0; i < M_N; i++)
       printf(" ");
    printf("|");
    for (size_t i = 0; i < M_N + 1; i++)
       printf("\b");
}

void print_big_float(big_float_t *num)
{
    if (num->sign == '-')
        printf("%c", num->sign);
    printf("0.");
    if (num->size == 0)
        printf("0");
    else
        for (size_t i = 0; i < num->size; i++)
            printf("%hd", num->mantissa[i]);
    printf("e%d\n", num->order);
}

void print_task(void)
{
    printf("-----------------------------------------Умножение вещественного и целого числа----------------------------------------\n");
    printf("Формат ввода для вещественного числа: может содержать как целое, так и вещественное и экспонированном виде:\n+-M.Ne+-K\n");
    printf("Формат ввода для целого числа: может содержать только целое виде:\n+-M\n");
    printf("Вывод в виде +-0.N+Me+-K\n");
    printf("Пределы ввода, сумма N, M не превышает 30 значимых цифр, а порядок K - 5 цифр!\n");
    printf("-----------------------------------------------------------------------------------------------------------------------\n");
}
