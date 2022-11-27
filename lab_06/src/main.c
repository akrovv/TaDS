#include "utils.h"
#include "operations.h"
#include "menu.h"
#include "read.h"

int main(void)
{
    binary_tree_t binary_tree;
    int menu;
    
    binary_tree.head = NULL;
    // char *hey = "hello_world";
    // char *boy = "boy";
    // char *zopa = "zopa";
    // char *big_zopa = "big_zopa";
    // char *big_zopa1 = "doy";

    // insert(&binary_tree.head, hey);
    // insert(&binary_tree.head, boy);
    // insert(&binary_tree.head, zopa);
    // insert(&binary_tree.head, big_zopa);
    // insert(&binary_tree.head, big_zopa1);

    //printf("FIND: %zu\n", get_quantity_by_letter(binary_tree.head, 'a'));

    //deleteValue(binary_tree.head, boy);
  //  print_tree(binary_tree.head);

    print_main_menu();
    printf("Выбор: ");

    while (scanf("%d", &menu) == 1 && menu > 0 && menu < 7)
    {
        if (menu == 1)
        {
            file_read(&binary_tree);
        }
        else if (menu == 2)
        {
            char str[MAX_LEN];
            size_t byle_len = 0;
            printf("Введите слово, которое нужно удалить: ");
            scanf("%s", str);
    
            if (str[strlen(str) - 1] == '\n')
                str[strlen(str) - 1] = '\0';
            printf("%s\n", str);
            deleteValue(binary_tree.head, str);
        }
        else if (menu == 3)
        {
            char letter = 'b'; 
            printf("Введите одну букву: ");

            printf("Найдено: \"%zu\"\n", get_quantity_by_letter(binary_tree.head, letter));
            
        }
        else if (menu == 4)
        {
            print_tree(binary_tree.head);
        }
        else if (menu == 5)
        {
            sort(binary_tree.head);
        }
        else if (menu == 6)
        {}
        else
            break;

        print_main_menu();
        printf("Выбор: ");
    }
    
    return EXIT_SUCCESS;
}
