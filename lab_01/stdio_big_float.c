#include "func_stdio.h"

void big_float_default(big_float_t *num)
{
	num->sign = '+';
	num->size = 0;
	num->order = 0;

	for (size_t i = 0; i < M_N; i++)
		num->mantissa[i] = 0;
}

int big_float_read(big_float_t *num)
{
	char str[STRING_FLOAT];
	short n = 0, m = 0;
	int order = 0, order_p = 0;
	bool point = false, sign = false, eps = false, flag = false;
	size_t i = 0;

	if (fgets(str, STRING_FLOAT + 2, stdin) == NULL)
		return EMPTY_STRING;
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	if (strlen(str) > STRING_FLOAT)
		return STRING_OVERFLOW;
	if (strlen(str) == 0)
		return EMPTY_STRING;
	if (str[i] == 'e' || str[i] == 'E')
		return EPS_ERROR;
	if (str[i] == '-' || str[i] == '+')
	{
		num->sign = str[i];
		i++;
	}

	while (i < (size_t)(M_N + point + sign + 1) && str[i] != '\0' && !eps)
	{
		if (!point && (str[i] == '.' || str[i] == ','))
			point = true;
		else if (str[i] == 'e' || str[i] == 'E')
			eps = true;
		else if (isdigit(str[i]))
		{
			if (str[i] == '0' && !flag)
			{
				if (point)
                    order_p--;
				i++;
				continue;
			}
			if (str[i] != '0')
			{
				if (!flag)
					flag = true;
			}
			num->mantissa[m + n] = (short)(str[i] - '0');
			if (point)
                n++;
            else
                m++;
		}
		else
		{
			if (str[i] == '-' || str[i] == '+')
				return MANTISS_SIGN_ERROR;
			if (str[i] == '.' || str[i] == ',')
                return MANTISS_POINT_ERROR;
            else
                return INCORRECT_FLOAT;
		}
		i++;
	}

	if ((i - point - eps - sign) > M_N)
		return MANTISSA_OVERFLOW;

	num->size = m + n;

	if (eps)
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = true;
			i++;
		}
		for (; str[i] != '\0'; i++)
		{
			if (isdigit(str[i]))
				order = order * 10 + (int)(str[i] - '0');
			else
				if (str[i] == '+' || str[i] == '-')
					return ORDER_SIGN_ERROR;
				else if (str[i] == 'E' || str[i] == 'e')
					return ORDER_EPS_ERROR;
				else
					return INCORRECT_FLOAT;
		}
		if (sign)
			order *= -1;
	}

	if (num->size)
		num->order = order_p + order + m;
	else
		num->size = 1;
	
	if (num->order >= MAX_ORDER || num->order <= MIN_ORDER)
		return ORDER_OVERFLOW;

	return EXIT_SUCCESS;
}

int big_int_read(big_float_t *num)
{
	bool sign = false;
	char str[STRING_FLOAT];
	size_t i = 0;
	short m = 0;

	if (fgets(str, STRING_FLOAT + 2, stdin) == NULL)
		return EMPTY_STRING;
	if (str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = '\0';
	if (strlen(str) > STRING_FLOAT)
		return STRING_OVERFLOW;
	if (strlen(str) == 0)
		return EMPTY_STRING;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = true;
		num->sign = str[i];
		i++;
	}

	for (; str[i] != '\0'; i++)
	{
		if (isdigit(str[i]))
			num->mantissa[m++] = (short)(str[i] - '0');
		else
			return INCORRECT_INT;
		if ((i - sign) >= M_N)
			return MANTISSA_OVERFLOW;
	}

	num->size = m;
	
	return EXIT_SUCCESS;
}


