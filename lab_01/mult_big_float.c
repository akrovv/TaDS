#include "func_stdio.h"

void delete_zero(big_float_t *num)
{
    for (int i = num->size - 1; i >= 0 && !num->mantissa[i]; i--)
        num->size--;
}

void swap_right(short arr[], int n)
{
    for (int i = n - 1; i >= 0; i--)
        arr[i + 1] = arr[i];
    arr[0] = 0;
}

void round_mantissa(big_float_t *num, int n)
{
    int remainder = 0;
    int k = n - 1;
    num->mantissa[k]++;
    while ((num->mantissa[k] += remainder) > 9)
    {
        if (k == 0 && num->mantissa[k] > 9)
        {
            k = n - 1;
            swap_right(num->mantissa, n);
            num->mantissa[0] = num->mantissa[1] / 10;
            num->mantissa[1] %= 10;
            num->order++;
        }

        remainder = num->mantissa[k] / 10;
        num->mantissa[k] %= 10;
        k--;
    }
    num->order++;
}

void mult_big_float(big_float_t *num1, big_float_t *num2, big_float_t *res)
{
    int remainder = 0;
    int shift_left = 0;

    for (int i = num2->size - 1; i >= 0; i--)
    {
        bool flag = false;
        remainder = 0;

        for (int j = num1->size - 1; j >= 0; j--)
        {
            int multiply = num2->mantissa[i] * num1->mantissa[j] + remainder;

            if (j == 0 && multiply > 9)
            {
                multiply += res->mantissa[j];
            
                shift_left++;
                swap_right(res->mantissa, num1->size + shift_left);
                res->mantissa[0] = multiply / 10;
                res->mantissa[1] = multiply % 10;
                if (num1->size + shift_left > 30 && res->mantissa[num1->size + shift_left - 1] >= 5)
                {
                    round_mantissa(res, num1->size + shift_left - 1);
                    shift_left--;
                }
                else if (num1->size + shift_left > 30 && res->mantissa[num1->size + shift_left - 1] < 5)
                {
                    res->mantissa[num1->size + shift_left - 1] = 0;
                    shift_left--;
                    res->order++;
                }

                flag = true;
                break;
            }
            remainder = (res->mantissa[j] + multiply) / 10;
            res->mantissa[j] = (res->mantissa[j] + multiply) % 10;
        }

        if (!flag && i && !remainder)
        {
            shift_left++;
            swap_right(res->mantissa, num1->size + shift_left);
            if (num1->size + shift_left > 30 && res->mantissa[num1->size + shift_left - 1] >= 5)
            {
                round_mantissa(res, num1->size + shift_left - 1);
                shift_left--;
            }
            else if (num1->size + shift_left > 30 && res->mantissa[num1->size + shift_left - 1] < 5)
            {
                res->mantissa[num1->size + shift_left - 1] = 0;
                shift_left--;
                res->order++;
            }
        }
        else if (!flag && remainder)
        {
            shift_left++;
            swap_right(res->mantissa, num1->size + shift_left);
            res->mantissa[0] += remainder % 10;
            if (num1->size + shift_left > 30 && res->mantissa[num1->size + shift_left - 1] >= 5)
            {
                round_mantissa(res, num1->size + shift_left - 1);
                shift_left--;
            }
            else if (num1->size + shift_left > 30 && res->mantissa[num1->size + shift_left - 1] < 5)
            {
                res->mantissa[num1->size + shift_left - 1] = 0;
                shift_left--;
                res->order++;
            }
        }
    }
    res->size = num1->size + shift_left;
}
