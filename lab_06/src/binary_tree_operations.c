#include "operations.h"

static int comparator(char *word1, char *word2)
{
    return strcmp(word1, word2);
}

static branch_t *allocate_node(char *value, branch_t *branch)
{
    branch_t *tmp = malloc(sizeof(branch_t));
    if (!tmp)
        return NULL;

    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = branch;
    tmp->word = value;

    return tmp;
}

void insert(branch_t **head, char *value)
{
    if (!(*head))
    {
        *head = allocate_node(value, NULL);
        return;
    }

    branch_t *tmp = *head;

    while (tmp)
        if (comparator(value, tmp->word) > 0)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else 
            {
                tmp->right = allocate_node(value, tmp);
                return;
            }
        }
        else if (comparator(value, tmp->word) < 0)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = allocate_node(value, tmp);
                return;
            }
        }
        else
            return;
}

branch_t *getNodeByValue(branch_t *root, char *value) 
{
    while (root) {
        if (comparator(root->word, value) > 0) {

            root = root->left;
            continue;
        } else if (comparator(root->word, value) < 0) {

            root = root->right;
            continue;
        } else {
            return root;
        }
    }
    return NULL;
}

static branch_t* getMaxNode(branch_t *root) 
{
    while (root->right) {
        root = root->right;
    }
    return root;
}

static void delete(branch_t *target)
{
    if (target->left && target->right)
    {
        branch_t *tmp = getMaxNode(target->left);
        target->word = tmp->word;
        delete(tmp);
        return;
    }
    else if (target->left)
    {
        if (target == target->parent->left)
            target->parent->left = target->left;
        else
            target->parent->right = target->right;
    }
    else if (target->right)
    {
        if (target == target->parent->right)
            target->parent->right = target->right;
        else
            target->parent->left = target->right;
    }
    else
    {
        if (target == target->parent->left)
            target->parent->left = NULL;
        else
            target->parent->right = NULL;
    }

    free(target);
}


int deleteValue(branch_t *root, char *value) 
{
    branch_t *target = getNodeByValue(root, value);

    if (!target)
        return EXIT_FAILURE;

    delete(target);

    return EXIT_SUCCESS;
}

size_t get_quantity_by_letter(branch_t *root, char value) 
{
    static size_t quantity = 0;

    if (root->word[0] == value)
        quantity++;

    if (root->left)
        get_quantity_by_letter(root->left, value);

    if (root->right)
        get_quantity_by_letter(root->right, value);
        
    return quantity;
}

void print_tree(branch_t *head)
{
    printf("%s\n", head->word);
    if (head->left)
        print_tree(head->left);
    if (head->right)
        print_tree(head->right);
}

void sort(branch_t *head)
{
    if (head->left)
        sort(head->left);
    printf("%s\n", head->word);
    if (head->right)
        sort(head->right);
}
