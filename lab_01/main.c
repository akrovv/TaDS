#include "func_stdio.h"

int main(void)
{
	int error;
	big_float_t num_float_1, num_int_2;
	big_float_t num_float_result;

	big_float_default(&num_float_1);
	big_float_default(&num_int_2);
	big_float_default(&num_float_result);

	print_task();

	printf("Введите вещественное число:");
	print_field();
	error = big_float_read(&num_float_1);
	if (error == EXIT_SUCCESS)
	{
		printf("Введите целое число       :");
		print_field();
		error = big_int_read(&num_int_2);
		if (error == EXIT_SUCCESS)
		{
			if (num_float_1.sign == '-' || num_int_2.sign == '-')
				num_float_result.sign = '-';
			if (num_float_1.sign == '-' && num_int_2.sign == '-')
				num_float_result.sign = '+';
			
			if (num_float_1.size > num_int_2.size)
				mult_big_float(&num_float_1, &num_int_2, &num_float_result);
			else
				mult_big_float(&num_int_2, &num_float_1, &num_float_result);

			if (!num_float_1.order || num_float_1.order == (int)num_float_1.size)
				num_float_result.order += num_float_result.size;
			else if (num_float_1.order && (num_float_1.order > 0 || num_float_result.size < num_int_2.size + num_float_1.size))
				num_float_result.order += num_int_2.size + num_float_1.order - 1;
			else if (num_float_1.order && num_float_1.order < 0)
				num_float_result.order += num_int_2.size + num_float_1.order;
			delete_zero(&num_float_result);
			if (!num_float_result.mantissa[0])
				num_float_result.sign = '+';

			if (num_float_result.order > MAX_ORDER)
				error = ORDER_OVERFLOW;
			else
				print_big_float(&num_float_result);
		}
	}
	print_error(error);

	return error;
}
