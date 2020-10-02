//우선순위큐-<program 9.3- 히프트리 테스트 프로그램>
//최소 히프
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

//히프정의
typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//생성함수
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}
//초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

//삽입함수-min
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && item.key < h->heap[i / 2].key) {
		//부모노드보다 item의 값이 작은 경우에 해당
		h->heap[i] = h->heap[i / 2];// 부모노드로 거슬러 올라가기
		i /= 2;
	}
	h->heap[i] = item;
}

//삭제함수-min
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];//말단 노드 temp에 저장

	parent = 1;
	child = 2;

	while (child <= h->heap_size) {
		if ((child < h->heap_size) && h->heap[child].key > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	//반복문 탈출, parent가 temp가 위치할 곳이 되어있음
	h->heap[parent] = temp;
	return item;
}

int main(void)
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;
	HeapType* heap;

	heap = create(); //히프 생성
	init(heap); //초기화

	//삽입
	insert_min_heap(heap, e1);
	insert_min_heap(heap, e2);
	insert_min_heap(heap, e3);

	//삭제
	e4 = delete_min_heap(heap);
	printf("< %d >", e4.key);
	e5 = delete_min_heap(heap);
	printf("< %d >", e5.key);
	e6 = delete_min_heap(heap);
	printf("< %d > \n", e6.key);

	free(heap);
	return 0;
}