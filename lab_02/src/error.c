#include "errors.h"

void print_add_err(int rc)
{
    switch (rc)
    {
        case EXIT_FAILURE:
            printf("\nОшибка: Введенно неправильное значение.");
            break;
        case COUNTRY_DIGIT_ERR:
            printf("\nОшибка: В названии страны есть цифры.");
            break;
        case CAPITAL_DIGIT_ERR:
            printf("\nОшибка: В названии столицы есть цифры.");
            break;
        case MATERIC_DIGIT_ERR:
            printf("\nОшибка: В названии материка есть цифры.");
            break;
        case COUNTRY_OVERFLOW:
            printf("\nОшибка: Строка для ввода страны переполнена.");
            break;
        case CAPITAL_OVERFLOW:
            printf("\nОшибка: Строка для ввода столицы переполнена.");
            break;
        case MATERIC_OVERFLOW:
            printf("\nОшибка: Строка для ввода материка переполнена.");
            break;
        case NOT_IS_MATERIC:
            printf("\nОшибка: Это не материк.");
            break;
        case POPULATION_ZERO_ERROR:
            printf("\nОшибка: Популяция население не может быть отрицательным или нулевым.");
            break;
        case INCORRECT_COUNTRY_SYMB:
            printf("\nОшибка: В стране содержится пробел.");
            break;
        case INCORRECT_CAPITAL_SYMB:
            printf("\nОшибка: В столице содержится пробел.");
            break;
        case NOT_DIGIT_POPULATION:
            printf("\nОшибка: В численности содержится не числовой символ.");
            break;
        case TESTS_VALUE_ERR:
            printf("\nОшибка: В пцр содержится символ отличный от \"+-\" .");
            break;
        case DATA_EMPTY_ERR:
            printf("\nОшибка: Основой вид туризма отсутствует или является некорректным.");
            break;
        case INCORRECT_STR:
            printf("\nОшибка: Строка не содержит необходимый формат.");
            break;
        case BASE_PARAMS_ERROR:
            printf("\nОшибка: Превышено количество допустимых параметров для страны.");
            break;
        case NOT_DIGIT_NUMBER_OBJECTS:
            printf("\nОшибка: В количестве объектов содержится не числовой символ.");
            break;
        case NUMBER_OBJECTS_IS_NEGATIVE:
            printf("\nОшибка: Количество объектов меньше или равно нулю.");
            break;
        case NAME_OBJECT_OVERFLOW:
            printf("\nОшибка: Длина строки превышена.");
            break;
        case SIGHT_PARAM_ERROR:
            printf("\nОшибка: Превышено количество допустимых параметров для экскурсионного вида отдыха.");
            break;
        case NOT_DIGIT_MAIN_SEASON:
            printf("\nОшибка: В основном сезоне содержится не числовой символ.");
            break;
        case MAIN_SEASON_IS_NEGATIVE:
            printf("\nОшибка: Основной сезон меньше или равен нулю.");
            break;
        case NOT_DIGIT_AIR_TEMP:
            printf("\nОшибка: В температуре воздуха содержится не числовой символ.");
            break;
        case NOT_DIGIT_WATER_TEMP:
            printf("\nОшибка: В температуре воды содержится не числовой символ.");
            break;
        case WATER_TEMP_IS_NEG:
            printf("\nОшибка: Температура воды меньше или равна нулю.");
            break;
        case NOT_DIGIT_TIME_FLYING:
            printf("\nОшибка: Во времени полета содержится не числовой символ.");
            break;
        case TIME_FLYING_IS_NEG:
            printf("\nОшибка: Время полета меньше или равна нулю.");
            break;
        case BEACH_PARAM_ERROR:
            printf("\nОшибка: Превышено количество допустимых параметров для пляжного вида отдыха.");
            break;
        case STRING_SPORT_OVERFLOW:
            printf("\nОшибка: Строка для ввода вида спорта переполнена.");
            break;
        case NOT_DIGIT_MIN_COUNT_PRICE:
            printf("\nОшибка: В минимальной стоимости отдыха содержится не числовой символ.");
            break;
        case MIN_COUNT_PRICE_IS_NEG:
            printf("\nОшибка: Ошибка: Минимальная стоимость отдыха меньше или равна нулю.");
            break;
        case SPORT_PARAM_ERROR:
            printf("\nОшибка: Превышено количество допустимых параметров для спортивного вида отдыха.");
            break;
        case SCAN_ERROR:
            printf("\nОшибка: Ошибка чтения строки.");
            break;
        case STRING_OVERFLOW:
            printf("\nОшибка: Строка для таблицы больше 1K символов.");
            break;
        case MAIN_PARAM_ERROR:
            printf("\nОшибка: Количество аргументов командной строки больше 2-х.");
            break;
        case FILE_NOT_FOUND:
            printf("\nОшибка: Не удается найти файл.");
            break;
        case ERROR_NAME_OBJECT:
            printf("\nОшибка: Строка с основным видом не содержит (история, искусство, ирирода).");
            break;
        case ERROR_TYPE_SPORT:
            printf("\nОшибка: Строка с видом спорта не содержит (горные лыжи, серфинг, восхождения).");
            break;
    }
}

