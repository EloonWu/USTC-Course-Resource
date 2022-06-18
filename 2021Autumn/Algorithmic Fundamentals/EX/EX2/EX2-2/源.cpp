#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点

typedef int Type;

// 红黑树的节点
typedef struct RBTreeNode {
    unsigned char color;        // 颜色(RED 或 BLACK)
    Type   key;                    // 关键字(键值)
    char name[9];
    struct RBTreeNode* left;    // 左孩子
    struct RBTreeNode* right;    // 右孩子
    struct RBTreeNode* parent;    // 父结点
}Node, * RBTree;

// 红黑树的根
typedef struct rb_root {
    Node* node;
}RBRoot;

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)


RBRoot* create_rbtree()
{
    RBRoot* root = (RBRoot*)malloc(sizeof(RBRoot));
    root->node = NULL;

    return root;
}

Node* search(RBTree x, Type key)
{
    if (x == NULL || x->key == key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}
int rbtree_search(RBRoot* root, Type key)
{
    if (root)
        return search(root->node, key) ? 0 : -1;
}

int find_predecessor(RBTree x, Type key)
{
    if (x == NULL)
        return -1;
    if (key < x->key)
    {
        return find_predecessor(x->left, key);
    }
    else
    {
        int rightval = find_predecessor(x->right, key);
        if (x->key > rightval || rightval == -1)
            return x->key;
        else
            return rightval;
    }
}


static void rbtree_left_rotate(RBRoot* root, Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        root->node = y;
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

static void rbtree_right_rotate(RBRoot* root, Node* y)
{
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == NULL)
    {
        root->node = x;
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

static void rbtree_insert_fixup(RBRoot* root, Node* node)
{
    Node* parent, * gparent;
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                Node* uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                Node* tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        }
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                Node* uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                Node* tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }
    rb_set_black(root->node);
}

static void rbtree_insert(RBRoot* root, Node* node)
{
    Node* y = NULL;
    Node* x = root->node;
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    rb_parent(node) = y;

    if (y != NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root->node = node;
    node->color = RED;
    rbtree_insert_fixup(root, node);
}

static Node* create_rbtree_node(Type key, char* name, Node* parent, Node* left, Node* right)
{
    Node* p;

    if ((p = (Node*)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    strcpy(p->name, name);
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK;

    return p;
}

int insert_rbtree(RBRoot* root, Type key, char* name)
{
    Node* node;
    if ((node = create_rbtree_node(key, name, NULL, NULL, NULL)) == NULL)
        return -1;

    rbtree_insert(root, node);

    return 0;
}

static void rbtree_destroy(RBTree tree)
{
    if (tree == NULL)
        return;

    if (tree->left != NULL)
        rbtree_destroy(tree->left);
    if (tree->right != NULL)
        rbtree_destroy(tree->right);

    free(tree);
}

void destroy_rbtree(RBRoot* root)
{
    if (root != NULL)
        rbtree_destroy(root->node);

    free(root);
}

int main()
{
    Type key;
    char cmd[7];
    RBRoot* root = NULL;
    root = create_rbtree();
    scanf("%s", cmd);
    while (cmd[0] != 'E')
    {
        scanf("%d", &key);
        if (cmd[0] == 'I')
        {
            insert_rbtree(root, key);
        }
        else
        {
            if (rbtree_search(root, key) == 0)
            {
                printf("%d\n", key);
            }
            else
            {
                printf("%d\n", find_predecessor(root->node, key));
            }
        }
        scanf("%s", cmd);
    }
    destroy_rbtree(root);
    return 0;
}