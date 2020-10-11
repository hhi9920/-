//<program 9.6 �������ڵ�>-�ּ�����
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight; // Ʈ���� weight ��= key �� , �켱���� ����
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef struct {
	TreeNode* ptree;
	char ch;
	int key;
}element;

//���� ����
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//���� �Լ�
HeapType* create()
{
	return(HeapType*)malloc(sizeof(HeapType));
}

//�ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}

//�����Լ�-min : �⺻ �ִ����� �����Լ��� while�� ���Ǹ� �ٸ�
//���� ����� ������ heap_size�� ���� h�� item�� ����
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size); //������ �ϱ� ���Ͽ� ���� h�� ũ�� ���� (�ε��� 1��ŭ ����)

	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {// i�� ��Ʈ�� �ƴϰ�(��Ʈ�� �ε���=1�̹Ƿ�) , �Է� ���� item ���� i�� �θ����� Ű ������ ������
		//�ش�ȴٸ� �θ���� ���ο� ��� ��ȯ
		h->heap[i] = h->heap[i / 2]; //����1) �Ž��� �ö󰡾� �ϹǷ� �����带 �θ���� ����
		i /= 2;  // i �ε����� �θ����� �ε����� ����
	}
	//while�� Ż�������Ƿ� ���̻� �Ž��� �ö� �� ���ٴ� �� �ǹ�
	//���� ���� �ε����� ��ġ(i)�� �Է� ���� item ���� ����
	h->heap[i] = item; //���ο� ��� ����
}

//�����Լ�-min
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; //��ȯ�� ��Ʈ ����� ���� item�� ����
	temp = h->heap[(h->heap_size)--]; // �� �������� �ִ� ����� ���� temp�� ���� ��
					 // ��Ʈ ����� ������ ������ �������Ƿ� �������� 1 ����

	//�� �������� �ִ� ��尪(temp)�� �̿��� �񱳰���
	parent = 1; //�� ù ������ �θ��带 ��Ʈ�� ��
	child = 2; // ��Ʈ�� ���� �ڽĺ��� ��

	while (child <= h->heap_size) {  //child�� �� ������� ũ�� ���� ��� ���̹Ƿ� child�� �� ������� �۰ų� ���� �� ��

		//���� ����� �ڽĳ�� �� �� ���� �ڽĳ�带 ã��
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)  //���� �ڽ�[child]�� ������ �ڽ� ���� �� ū ��� |�ִ������� �ٸ� �κ�
			child++;
		if (temp.key < h->heap[child].key)  // �񱳴��(child)�� ��Ʈ ��忡 ��ġ ���� temp�� ��
			break;  // temp�� �� ������ ���� ���� �����ϹǷ� �ݺ��� ��������-�ּ� ����

		//temp�� �ڸ� ��ȯ �ʿ�, temp�� ���� ���� ã�� ���� �񱳴��(child)�� �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child]; //�ڳ��� ���� ���ο� �� ������
		parent = child;
		child *= 2;
	}
	//�ݺ��� ����������, parent�� temp�� ��ġ�� ���� �Ǿ� ����
	h->heap[parent] = temp;
	return item;
}

//���� Ʈ�� ���� �Լ�
TreeNode* make_tree(TreeNode* left, TreeNode* right) // ��� ����
{
	//�Ű������� ���� �����͵��� ���� �ڽİ� ������ �ڽ����� �ϴ� ��Ʈ ��带 ���� ��ȯ
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

//���� Ʈ�� ���� �Լ�
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

//�ܸ� ��� �Ǻ� �Լ� is_leaf
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}

//����Ʈ array �Լ� print_array |�ڵ� �迭 �Լ�? ex)110
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

//����Ʈ codes �Լ� print_codes | �ڵ尪�� 0 or 1
void print_codes(TreeNode* root, int codes[], int top)
{
	//1�� �����ϰ� ��ȯȣ��
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	//0�� �����ϰ� ��ȯȣ��
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	//�ܸ�����̸� �ڵ带 ���
	if (is_leaf(root)) {
		printf("%c: ", root->ch); //���� ���
		print_array(codes, top); //�ڵ� ���
				// ex) n: 110
	}

}//end print_codes

//������ �ڵ� ���� �Լ�
void huffman_tree(int freq[], char ch_list[], int n) // freq[]=�󵵼� �迭
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);

	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i]; //���ڴ� ch_list�迭��
		e.key = node->weight = freq[i]; //�󵵼�(key)�� freq�迭��
		e.ptree = node;
		insert_min_heap(heap, e); //������ ��带 ���� ����
	}

	for (i = 1; i < n; i++) { //== for(i=0; i<n-1; i++) 
		//���� ���� �� �� ���� ������ ��ġ�� for ������ n-1���� ����!, ������ ���� ���=��Ʈ
		//�ּҰ��� ������ �ΰ��� ��带 ����( ������ ������)
		e1 = delete_min_heap(heap);
		/*printf("��� ������ ���� ��: %d\n", e1.key);
			   for(int k=1; k<n; k++)
			printf("������ �� �Ŀ� �� �迭: %d\n", heap.heap[k].key);  h->heap[k].key�ƴѰ�?*/

		e2 = delete_min_heap(heap);
		/*printf("�� ���� ������ ���� ��: %d\n", e2.key);
		   for(k=1; k<n; k++)
			printf("������ �� �Ŀ� �� �迭: %d\n", heap.heap[k].key); */

			//�ΰ��� ��� ��ġ��
		x = make_tree(e1.ptree, e2.ptree); // 2���� ��带 ������ ��� ���� | x= ���ļ� ���� ���ο� ���
		e.key = x->weight = e1.key + e2.key;  //2���� ��� �� ���ϱ�
						//printf("e.key=%d, x->weight=%d\n", e.key, x->weight);
		e.ptree = x;  // ������ ���� ��带 ����
		printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);  //Ʈ���� ������ ��带 ���� ����
						//printf("%d\n", heap.heap[4].key);
	}

	e = delete_min_heap(heap); // ���� Ʈ��
	print_codes(e.ptree, codes, top); //������ �ڵ� ���
	destroy_tree(e.ptree);  //�޸� ��ȯ
	free(heap);


}//end huffman_tree �Լ�

//���� �Լ�
int main(void)
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4,6,8,12,15 };  //�󵵼�
	huffman_tree(freq, ch_list, 5);
	return 0;
}