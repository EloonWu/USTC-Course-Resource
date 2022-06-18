#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CHARNUM 26
int cnt = 0;

struct TreeNode
{
	int num;
	TreeNode* child[CHARNUM];
};

TreeNode* NewTree(void)
{
	TreeNode* newtree;
	int m;

	newtree = (TreeNode*)malloc(sizeof(TreeNode));
	newtree->num = 0;
	for (m = 0; m < CHARNUM; m++)
		newtree->child[m] = NULL;

	return newtree;
}

int Insert(char* string, TreeNode* root)
{
	int i;
	TreeNode* ptr = root;
	for (i = 0; string[i] != '\0'; i++)
	{
		if (ptr->child[string[i] - 'a'] == NULL)
			ptr->child[string[i] - 'a'] = NewTree();
		ptr = ptr->child[string[i] - 'a'];
	}
	ptr->num++;
	return ptr->num == 1;
}

int Delete(char* string, TreeNode* root)
{
	int i;
	TreeNode* ptr = root;
	for (i = 0; string[i] != '\0'; i++)
	{
		if (ptr->child[string[i] - 'a'] == NULL)
			return 0;
		ptr = ptr->child[string[i] - 'a'];
	}
	if (ptr->num <= 0)
		return 0;
	ptr->num--;
	return ptr->num == 0;
}

int task4(int num_of_name, int k, TreeNode* root, char** name_list)
{
	int num = 0;
	int result = 0;
	int left = 0;
	int right = 0;
	while (right < num_of_name)
	{
		if (Insert(name_list[right], root))
			num++;
		while (num > k)
		{
			if (Delete(name_list[left], root))
				num--;
			left++;
		}
		result += right - left + 1;
		right++;
	}
	return result;
}

int main()
{
	int num_of_name, k;
	int m, n;
	char** name_list;
	char* buffer;
	TreeNode* root1;
	TreeNode* root2;
	scanf("%d %d", &num_of_name, &k);
	
	buffer = (char*)malloc(6 * sizeof(char));
	name_list = (char**)malloc(num_of_name * sizeof(char*));

	for (m = 0; m < num_of_name; m++)
	{
		scanf("%s", buffer);
		name_list[m] = (char*)malloc(6 * sizeof(char));
		strcpy(name_list[m], buffer);
	}

	root1 = NewTree();
	root2 = NewTree();
	cnt = task4(num_of_name, k, root1, name_list) - task4(num_of_name, k - 1, root2, name_list);

	printf("%d\n", cnt);

	return 0;
}