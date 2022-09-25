/*
* func_stdio.h
* Модуль с функциями
*/

#ifndef __FUNC_STDIO_H__

#define __FUNC_STDIO_H__

// Стандартные библиотеки

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// Постоянные значения

#define M_N 30
#define MAX_FLOAT 100
#define STRING_FLOAT 100
#define MAX_ORDER 100000
#define MIN_ORDER -100000

// Коды ошибок
#define EMPTY_STRING 1
#define STRING_OVERFLOW 2
#define EPS_ERROR 3
#define MANTISS_SIGN_ERROR 4
#define MANTISS_POINT_ERROR 5
#define INCORRECT_FLOAT 6
#define MANTISSA_OVERFLOW 7
#define ORDER_SIGN_ERROR 8
#define ORDER_EPS_ERROR 9
#define ORDER_OVERFLOW 10
#define INCORRECT_INT 11

// Структура числа big_float_t

typedef struct 
{
	char sign;
	short mantissa[MAX_FLOAT];
	size_t size;
	int order;
} big_float_t;

void delete_zero(big_float_t *num);

void print_task(void);

/*
 * void big_float_default(big_float *num)
 * Функция заполняет значение стурктуры big_float по умолчанию
*/

void big_float_default(big_float_t *num);

/*
 * int read_big_float(big_float *number)
 * Функция считывания данных(специальных вещественных чисел)
 * Возвращает код ошибки 0 или не нулевой
*/

int big_float_read(big_float_t *num);

/*
 * int big_int_read(big_float_t *num)
 * Функция считывания данных(специальных целочисленных чисел)
 * Возвращает код ошибки 0 или не нулевой
*/

int big_int_read(big_float_t *num);

/*
 * void mult_big_float(big_float_t *num1, big_float_t *num2, big_float_t *res);
 * Функция использует алгоритм умножения в «столбик».
*/

void mult_big_float(big_float_t *num1, big_float_t *num2, big_float_t *res);

/*
 * void round_mantissa(big_float_t *num, int n);
 * Функция округляет мантиссу, если она имеет длину больше 30 и 31 элемент больше или равен 5
*/

void round_mantissa(big_float_t *num, int n);

/*
 * void swap_right(short arr[], int n);
 * Функция сдвигает элементы массива вправо
*/

void swap_right(short arr[], int n);

/*
 * void print_field();
 * Функция формуриет текст перед вводом
*/

void print_field(void);

/*
 * void print_big_float(big_float_t *num);
 * Функция печатает вычисленное значение в формате: +-0.m1Е+-K1
*/

void print_big_float(big_float_t *num);

/*
 * void print_error(int error);
 * Функция печатает ошибки
*/

void print_error(int error);

#endif
