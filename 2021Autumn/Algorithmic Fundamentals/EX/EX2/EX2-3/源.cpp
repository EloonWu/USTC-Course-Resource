#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define RED        0  
#define BLACK    1   
#define MAXADD 2E30

typedef int Type;


typedef struct RBTreeNode {
    unsigned char color;        // 颜色(RED 或 BLACK)
    Type   low;
    Type   high;
    struct RBTreeNode* left;    // 左孩子
    struct RBTreeNode* right;    // 右孩子
    struct RBTreeNode* parent;    // 父结点
}Node, * RBTree;


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
            if (parent->right == node)
            {
                Node* tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        }
        else
        {
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
            if (parent->left == node)
            {
                Node* tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }
    rb_set_black(root->node);
}

int rbtree_insert(RBRoot* root, Node* node)
{
    Node* y = NULL;
    Node* x = root->node;
    while (x != NULL)
    {
        y = x;
        if (node->high < x->low && node->high <= MAXADD)
            x = x->left;
        else
        {
            if (node->low > x->high&& node->high <= MAXADD)
            {
                x = x->right;
            }
            else
                return -1;
        }
    }
    rb_parent(node) = y;

    if (y != NULL)
    {
        if (node->high < y->low)
            y->left = node;
        else
        {
            if (node->low > y->high&& node->high <= MAXADD)
                y->right = node;
            else
                return -1;
        }  
    }
    else
    {
        if (node->high <= MAXADD)
            root->node = node;
        else
            return -1;
    }
    node->color = RED;
    rbtree_insert_fixup(root, node);
    return 0;
}

static Node* create_rbtree_node(Type low, Type high, Node* parent, Node* left, Node* right)
{
    Node* p;

    if ((p = (Node*)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->low = low;
    p->high = high;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK;

    return p;
}

int insert_rbtree(RBRoot* root, Type low, Type high)
{
    Node* node;
    if ((node = create_rbtree_node(low, high, NULL, NULL, NULL)) == NULL)
        return -1;

    return rbtree_insert(root, node);
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
    int n, m;
    Type low, high;
    RBRoot* root = NULL;
    root = create_rbtree();
    scanf("%d", &n);
    for (m = 0; m < n; m++)
    {
        scanf("%d %d", &low, &high);
        printf("%d\n", insert_rbtree(root, low, high));
    }
    destroy_rbtree(root);
    return 0;
}