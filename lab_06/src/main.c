#include "utils.h"
#include "operations.h"
#include "menu.h"
#include "read.h"
#include "paint.h"

int main(void)
{
    binary_tree_t binary_tree;
    int menu;
    
    binary_tree.head = NULL;
  
    print_main_menu();
    printf("Выбор: ");

    while (scanf("%d", &menu) == 1 && menu > 0 && menu < 9)
    {
        if (menu == 1)
        {
            file_read(&binary_tree);
        }
        else if (menu == 2)
        {
            char str[MAX_LEN];
            size_t byle_len = 0;
            printf("Введите слово, которое нужно добавить: ");
            scanf("%s", str);
    
            if (str[strlen(str) - 1] == '\n')
                str[strlen(str) - 1] = '\0';
            printf("%s\n", str);
            insert(&binary_tree.head, str);
        }
        else if (menu == 3)
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
        else if (menu == 4)
        {
            char letter = 'd'; 
            printf("Введите одну букву: ");

            printf("Найдено: \"%zu\"\n", get_quantity_by_letter(binary_tree.head, letter));

            FILE *f = fopen("./data/graph.gv", "w");
            treeExportToDot(f, "graph_bin", binary_tree.head, HIGHLIGHT, letter);
            fclose(f);
            system("./make_graph.sh");
            printf("Дерево визуализировано!\n");
        }
        else if (menu == 5)
        {
            int option;
            printf("Визуализировать дерево? (0 - Нет, 1 - Да): ");
            if (scanf("%d", &option) != 1 || option < 0 || option > 1)
                return EXIT_FAILURE;
            
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
        else if (menu == 6)
        {
            char s[100] = "doy";
            printf("%s\n", getNodeByValue(binary_tree.head, s)->word);
        }
        else if (menu == 7)
        {


        }
        else if (menu == 8)
        {
            
        }
        else
            break;

        print_main_menu();
        printf("Выбор: ");
    }
    
    return EXIT_SUCCESS;
}
