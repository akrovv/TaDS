#include "utils.h"
#include "operations.h"
#include "menu.h"
#include "read.h"
#include "paint.h"
#include "measure.h"

static void print_error(int rc)
{
    switch (rc)
    {
        case SCANF_ERROR:
            printf("Ошибка! При чтении пункта меню произошла ошибка.\n");
            break;
        case OUT_OF_RANGE:
            printf("Ошибка! Выход за допустимые значения меню (0 - 7)\n");
            break;
        case EXTRA_LETTERS:
            printf("Ошибка! Была введена не буква.\n");
            break;
        case FIND_MENU:
            printf("Ошибка! Выход за допустимые значения меню поиска (0 - 1)\n");
            break;
        case PRINT_MENU:
            printf("Ошибка! Выход за допустимые значения меню вывода (0 - 1)\n");
            break;
    }
}

int main(void)
{
    binary_tree_t binary_tree;
    int menu = 1;
    
    binary_tree.head = NULL;
  
    print_main_menu();
    printf("Выбор: ");

    while (scanf("%d", &menu) == 1 && menu > 0 && menu < 8)
    {
        if (menu == 1)
        {
            if (!binary_tree.head)
            {
                FILE *f = fopen("test.txt", "r");
                file_read(&binary_tree, f);
            }
            else
                printf("Бинарное дерево уже считано!\n");
        }
        else if (menu == 2)
        {
            if (binary_tree.head)
            {
                char str[MAX_LEN];
                char buffer[BUFF_SIZE];
                size_t byle_len = 0;
                printf("Введите слово, которое нужно добавить: ");
                fgets(buffer, BUFF_SIZE, stdin);
                if (fgets(str, MAX_LEN, stdin) == NULL)
                    return EXIT_FAILURE;
        
                if (str[strlen(str) - 1] == '\n')
                    str[strlen(str) - 1] = '\0';
                    
                printf("\"%s\" Успешно добавлен!\n", str);
                insert(&binary_tree.head, str);
            }
            else
                printf("Для того, чтобы добавить узел, сначала нужно считать данные из файла!\n");
        }
        else if (menu == 3)
        {
            if (binary_tree.head)
            {
                char str[MAX_LEN];
                size_t byle_len = 0;
                printf("Введите слово, которое нужно удалить: ");
                scanf("%s", str);
        
                if (str[strlen(str) - 1] == '\n')
                    str[strlen(str) - 1] = '\0';

                if (deleteValue(binary_tree.head, str))
                    printf("Слово \"%s\" не найдено!\n", str);
                else
                    printf("Успешно удалено!\n");
            }
            else
                printf("Дерево еще не считано, поэтому нельзя удалить данные!\n");
        }
        else if (menu == 4)
        {
            if (binary_tree.head)
            {
                char letters[SIZE];
                char letter; 
                char buffer[BUFF_SIZE];
                int menu;
                printf("Введите одну букву: ");
                fgets(buffer, BUFF_SIZE, stdin);

                if (fgets(letters, SIZE, stdin) == NULL)
                    return EXIT_FAILURE;

                if (letters[strlen(letters) - 1] == '\n')
                    letters[strlen(letters) - 1] = '\0';

                if (strlen(letters) > 1)
                {
                    print_error(EXTRA_LETTERS);
                    return EXTRA_LETTERS;
                }

                letter = letters[0];

                printf("Найдено: \"%zu\"\n", get_quantity_by_letter(binary_tree.head, letter));

                printf("Покрасить узлы, в которах найдена буква? (0 - Нет, 1 - Да): ");
                if (scanf("%d", &menu) != 1)
                {
                    print_error(SCANF_ERROR);
                    return SCANF_ERROR;
                }
                
                if (menu < 0 || menu > 1)
                {
                    print_error(FIND_MENU);
                    return FIND_MENU;
                }
                
                if (menu == 1)
                {
                    FILE *f = fopen("./data/graph.gv", "w");
                    treeExportToDot(f, "graph_bin", binary_tree.head, HIGHLIGHT, letter);
                    fclose(f);
                    system("./make_graph.sh");
                    printf("Дерево визуализировано!\n");
                }
            }
            else
                printf("Дерево еще не считано!\n");
        }
        else if (menu == 5)
        {
            int option;
            if (binary_tree.head)
            {
                printf("Визуализировать дерево? (0 - Нет, 1 - Да): ");
                if (scanf("%d", &option) != 1 || option < 0 || option > 1)
                {
                    print_error(SCANF_ERROR);
                    return SCANF_ERROR;
                }

                if (option < 0 || option > 1)
                {
                    print_error(PRINT_MENU);
                    return PRINT_MENU;
                }
                
                if (option)
                {
                    FILE *f = fopen("./data/graph.gv", "w");
                    treeExportToDot(f, "graph_bin", binary_tree.head, BST, 0);
                    fclose(f);
                    system("./make_graph.sh");
                    printf("Дерево визуализировано!\n");
                }
                else
                    print_tree(binary_tree.head);
            }
            else
                printf("Дерево еще не считано!\n");
        }
        else if (menu == 6)
        {
            if (binary_tree.head)
            {
                char buffer[BUFF_SIZE];
                char word[SIZE];

                printf("Введите слово: ");
                fgets(buffer, BUFF_SIZE, stdin);

                if (fgets(word, SIZE, stdin) == NULL)
                    return EXIT_FAILURE;

                if (word[strlen(word) - 1] == '\n')
                    word[strlen(word) - 1] = '\0';

                branch_t *result = getNodeByValue(binary_tree.head, word);

                if (result)
                    printf("%s\n", result->word);
                else
                    printf("Слово не найдено!\n");
            }
            else
                printf("Дерево еще не считано!\n");
        }
        else if (menu == 7)
            measure_find();

        print_main_menu();
        printf("Выбор: ");
    }

    if (menu)
    {
        print_error(SCANF_ERROR);
        return SCANF_ERROR;
    }
    else if (menu > 7 || menu < 0)
    {
        print_error(OUT_OF_RANGE);
        return OUT_OF_RANGE;
    }
    
    return EXIT_SUCCESS;
}
