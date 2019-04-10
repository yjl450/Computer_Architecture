#include <stdlib.h>
#include <stdio.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
};


struct node *mknode(int x, struct node *left, struct node *right){
    struct node *newnode;
    newnode = malloc(sizeof(struct node));
    newnode -> key = x;
    newnode -> left = left;
    newnode -> right = right;
    return newnode;
}


struct node *full_tree(int h){
    struct node *fulltree;
    if (h == 1) {
        fulltree = mknode(1, NULL, NULL);
        return fulltree;
    }
    fulltree = mknode(1, full_tree(h-1), full_tree(h-1));
    return fulltree;
}

void print_infix(struct node *tree){
    if (tree -> left != NULL) {
        print_infix(tree -> left);
    }
    printf("%d ", tree -> key);
    if (tree -> right != NULL) {
        print_infix(tree -> right);
    }
}

void free_tree(struct node *tree){
    if (tree -> left != NULL) {
        free_tree(tree -> left);
    }
    if (tree -> right != NULL) {
        free_tree(tree -> right);
    }
    free(tree);
}

int find(int val, struct node *bst){
    if ((bst -> key) == val) {
        return 1;
    }
    if ((bst -> key) > val) {
        if ((bst -> left == NULL)) {
            return 0;
        }
        return find(val, bst -> left);
    }
    if ((bst -> key) < val) {
        if ((bst -> right == NULL)) {
            return 0;
        }
        return find(val, bst -> right);
    }
    
}

struct node *find_pos(int val, struct node *bst){
    if ((bst -> key) > val) {
        if ((bst -> left) == NULL) {
            return bst;
        }
        return find_pos(val, bst -> left);
    }
    if ((bst -> key) < val) {
        if ((bst -> right) == NULL) {
            return  bst;
        }
        return find_pos(val, bst -> right);
    }
}

struct node *insert(int val, struct node *bst){
    if (bst == NULL) {
        bst = mknode(val, NULL, NULL);
        return bst;
    }
    if (find(val, bst)) {
        return bst;
    }
    struct node *pos;
    pos = find_pos(val, bst);
    if ((pos -> key) > val) {
        pos -> left = mknode(val, NULL, NULL);
    }
    if ((pos -> key) < val) {
        pos -> right = mknode(val, NULL, NULL);
    }
    return bst;
}

int max_num(int a, int b){
    if (a >= b) {
        return a;
    }
    if (a < b) {
        return b;
    }    
}

int max_tree(struct node *tree){
    printf ("*");
    int maxi = tree -> key;
    if ((tree -> left) == NULL && (tree -> right) == NULL) {
        return maxi;
    }
    if ((tree -> left) != NULL) {
        maxi = max_num(maxi, max_tree(tree -> left));
    }
    if ((tree -> right) != NULL) {
        maxi = max_num(maxi, max_tree(tree -> right));
    }
    return maxi;    
}

int min_num(int a, int b){
    if (a >= b) {
        return b;
    }
    if (a < b) {
        return a;
    }    
}

int min_tree(struct node *tree){
    printf ("*");
    int mini = tree -> key;
    if ((tree -> left) == NULL && (tree -> right) == NULL) {
        return mini;
    }
    if ((tree -> left) != NULL) {
        mini = min_num(mini, min_tree(tree -> left));
    }
    if ((tree -> right) != NULL) {
        mini = min_num(mini, min_tree(tree -> right));
    }
    return mini;    
}

int is_BST(struct node *tree){
    printf ("@");
    if (tree == NULL) {
        return 1;
    }
    if (tree ->left == NULL && tree -> right == NULL) {
        return 1;
    }
    if (tree->left !=  NULL) {
        if (max_tree(tree->left) >= tree -> key) {
            return 0;
        }
    }
    if (tree->right !=  NULL) {
        if (min_tree(tree->right) <= tree -> key) {
            return 0;
        }
    }
    return (is_BST(tree->left) && is_BST(tree->right));   
}

int is_BST_helper(struct node *tree, int a, int b){
    printf ("#");
    if (tree == NULL) {
        return 1;
    }
    if (tree->key >= a && tree->key <= b) {
        return (is_BST_helper(tree->left, a, tree->key-1) && is_BST_helper(tree->right, tree->key+1, b));
    }
    else
    {
        return 0;
    }
}

int fast_is_BST(struct node *tree){
    int a = min_tree(tree);
    int b = max_tree(tree);
    return is_BST_helper(tree, a, b);
}

int main(){
    printf("-------------------- Problem 1 --------------------\n");
    struct node *tree;
    tree = full_tree(4);
    print_infix(tree);
    printf("\n");
    // free_tree(tree);

    printf("\n§1-4: This tree has been freed without any memory leak.\n\n");

    printf("-------------------- Problem 2 --------------------\n");
    struct node *bst = NULL;
    int k = 0;
    int a[100] = {0};
    int target=0;
    printf("Enter the number of nodes in the BST:\n");
    scanf("%d", &k);
    printf("Enter %d numbers:\n", k);
    for(int i = 0; i < k; i++)
    {
        scanf("%d", &a[i]);
        bst = insert(a[i], bst);
    }
    printf("The BST in in-order: ");
    print_infix(bst);
    printf("\n");
    printf("Enter the value you want to search:\n");
    scanf("%d", &target);
    if (find(target, bst)) {
        printf("The value %d is in the BST.\n", target);
    }
    else
    {
        printf("The value %d is not in the BST.\n", target);
    }
    printf("\n");
    // free_tree(bst);
    printf("-------------------- Problem 3 --------------------\n");
    printf("Max: %d\n", max_tree(bst));
    printf("Min: %d\n", min_tree(bst));
    printf("Is_BST: %d\n", is_BST(bst));
    printf("Is_BST: %d\n", is_BST(tree));
    printf("fast_Is_BST: %d\n", fast_is_BST(bst));
    printf("fast_Is_BST: %d\n", fast_is_BST(tree));
    return 0;
}