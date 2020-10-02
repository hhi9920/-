//<program 9.4 ���� ����>-�ִ�����
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200	//�迭 ũ�� 200

//���� �⺻ �ڵ� ����

//��������
typedef struct {	//������ �� ��ҵ� ����ü element�� ����
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;	//���� ���� �ȿ� ����� ����� ����
}HeapType;

//�����Լ�-����
HeapType * create() {
	return (HeapType *)malloc(sizeof(HeapType));
}

//�ʱ�ȭ�Լ�
void init(HeapType *h) {
	h->heap_size = 0;
}

//�����Լ�: ���� ����� ������ heap_size�� ���� h�� item ����
void insert_max_heap(HeapType *h, element item) {
	int i;
	i = ++(h->heap_size);	//������ ���� ����h�� ũ�� 1 ���� 

	//Ʈ�� �Ž��� �ö󰡸鼭 �θ���� ��
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		//i�� ��Ʈ�� �ƴϰ� �Է¹��� item���� i�� �θ����� Ű������ ũ��
		//�θ���� ���� ���Ե� ���� ��ȯ
		h->heap[i] = h->heap[i / 2];	//���� ��带 �θ���� ����
		i /= 2;	//i �ε����� �θ����� �ε����� ����
	}
	//while�� Ż�������Ƿ� ���̻� �Ž��� �ö� �� ���ٴ� �ǹ�
	//���� ���� �ε����� ��ġ(i)�� �Է� ���� item �� ����
	h->heap[i] = item;	//���ο� ��� �� item ����
}

//�����Լ�
element delete_max_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];	//��ȯ�� ��Ʈ ����� ���� item�� ����
	temp = h->heap[(h->heap_size)--];	//�� ������ ����� ���� temp�� ���� ��
										//��Ʈ ����� ���� ������ �����Ƿ� heap_size 1 ����

	//�� ������ ��尪(temp)�� �̿��� �� ���� 
	parent = 1;	//�� ù ������ �θ��带 ��Ʈ�� ��
	child = 2;	//��Ʈ�� ���� �ڽĺ��� ��

	while (child <= h->heap_size) {//child�� ��������� ũ�� ���� ��� ���̹Ƿ� �۰ų� ���� ��� ��

		//���� ����� �ڽĳ�� �� ���� �� ū �ڽĳ�� ã��
		if ((child < h->heap_size) && (h->heap[child].key) < (h->heap[child + 1].key))	//������ �ڽ��� ū ���
			child++;	//���ο� ������ ����� ����
		if (temp.key >= h->heap[child].key)	//�񱳴��(child)�� ��Ʈ ��忡 ��ġ ���� temp�� ��
			break;	//temp ���� �� ū ��� ���� ���� �����ϹǷ� �ݺ��� Ż��

		//temp�� �ڸ� ��ȯ �ʿ�(�Ʒ��� �����;���)
		//temp�� ���� ���� ã�� ����  �񱳴��(child)�� �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];	//�ڳ��� ���� ���ο� �� ��������
		child *= 2;	//child ���� 2�� ���Ͽ� ���� �ڳ�� �����

	}
	//�ݺ��� Ż��
	//parent�� temp�� ��ġ�� ���� �Ǿ� ����
	h->heap[parent] = temp;
	return item;	//��Ʈ ��� ��(�ִ�) ����

}

//������ �̿��� ����
void heap_sort(element a[], int n)// �迭, �迭 ��� ����
{
	int i;
	HeapType *h;

	h = create();	//���� ����
	init(h);	//���� �ʱ�ȭ

	//�迭-> ��
	for (i = 0; i < n; i++) {//�ε��� 0���� ���
		insert_max_heap(h, a[i]);	//�迭 a ��ҵ��� ���� ����

	}

	//��->�迭�� ���ʺ��� ����
	for (i = (n - 1); i >= 0; i--) {// �迭�� ���ʺ��� �����ϱ� ���� (n-1)����
		a[i] = delete_max_heap(h);	//�����ϴ� ������ ���� ���ĵ� �迭

	}
	free(h);	//���� ���� �޸� ��ȯ
}

//�����Լ�
#define SIZE 8
int main(void)
{
	element list[SIZE] = { 23,56,11,9,56,99,27,34 };
	heap_sort(list, SIZE);	//���� ����
	for (int i = 0; i < SIZE; i++) {
		//������ �Ϸ�� �迭�� ���
		printf("%d ", list[i].key);
	}
	printf("\n");
	return 0;
}

//result= 9 11 23 27 34 56 56 99