//<program 9.6 허프만코드>-최소히프
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct TreeNode {
	int weight; // 트리의 weight 값= key 값 , 우선순위 결정
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef struct {
	TreeNode* ptree;
	char ch;
	int key;
}element;

//히프 정의
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//생성 함수
HeapType* create()
{
	return(HeapType*)malloc(sizeof(HeapType));
}

//초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}

//삽입함수-min : 기본 최대히프 삽입함수와 while문 조건만 다름
//현재 요소의 개수가 heap_size인 히프 h에 item을 삽입
void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size); //삽입을 하기 위하여 히프 h의 크기 증가 (인덱스 1만큼 증가)

	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {// i가 루트가 아니고(루트는 인덱스=1이므로) , 입력 받은 item 값이 i의 부모노드의 키 값보다 작으면
		//해당된다면 부모노드와 새로운 노드 교환
		h->heap[i] = h->heap[i / 2]; //과정1) 거슬러 올라가야 하므로 현재노드를 부모노드로 설정
		i /= 2;  // i 인덱스를 부모노드의 인덱스로 설정
	}
	//while문 탈출했으므로 더이상 거슬러 올라갈 곳 없다는 것 의미
	//따라서 현재 인덱스의 위치(i)에 입력 받은 item 값을 삽입
	h->heap[i] = item; //새로운 노드 삽입
}

//삭제함수-min
element delete_min_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; //반환할 루트 노드의 값을 item에 저장
	temp = h->heap[(h->heap_size)--]; // 맨 마지막에 있는 노드의 값을 temp에 저장 후
					 // 루트 노드의 정보를 위에서 빼냈으므로 힙사이즈 1 줄임

	//맨 마지막에 있던 노드값(temp)를 이용한 비교과정
	parent = 1; //맨 첫 실행의 부모노드를 루트로 둠
	child = 2; // 루트의 왼쪽 자식부터 비교

	while (child <= h->heap_size) {  //child가 힙 사이즈보다 크면 힙을 벗어난 비교이므로 child가 힙 사이즈보다 작거나 같을 때 비교

		//현재 노드의 자식노드 중 더 작은 자식노드를 찾기
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)  //왼쪽 자식[child]이 오른쪽 자식 보다 더 큰 경우 |최대히프와 다른 부분
			child++;
		if (temp.key < h->heap[child].key)  // 비교대상(child)와 루트 노드에 위치 중인 temp와 비교
			break;  // temp가 더 작으면 히프 조건 만족하므로 반복문 빠져나감-최소 히프

		//temp의 자리 교환 필요, temp가 있을 곳을 찾기 위해 비교대상(child)를 한 단계 아래로 이동
		h->heap[parent] = h->heap[child]; //자녀의 값이 새로운 비교 기준점
		parent = child;
		child *= 2;
	}
	//반복문 빠져나오면, parent가 temp가 위치할 곳이 되어 있음
	h->heap[parent] = temp;
	return item;
}

//이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) // 노드 생성
{
	//매개변수로 받은 포인터들을 왼쪽 자식과 오른쪽 자식으로 하는 루트 노드를 만들어서 반환
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	return node;
}

//이진 트리 제거 함수
void destroy_tree(TreeNode* root)
{
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

//단말 노드 판별 함수 is_leaf
int is_leaf(TreeNode* root)
{
	return !(root->left) && !(root->right);
}

//프린트 array 함수 print_array |코드 배열 함수? ex)110
void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

//프린트 codes 함수 print_codes | 코드값은 0 or 1
void print_codes(TreeNode* root, int codes[], int top)
{
	//1을 저장하고 순환호출
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	//0을 저장하고 순환호출
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	//단말노드이면 코드를 출력
	if (is_leaf(root)) {
		printf("%c: ", root->ch); //문자 출력
		print_array(codes, top); //코드 출력
				// ex) n: 110
	}

}//end print_codes

//허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n) // freq[]=빈도수 배열
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
		e.ch = node->ch = ch_list[i]; //문자는 ch_list배열에
		e.key = node->weight = freq[i]; //빈도수(key)는 freq배열에
		e.ptree = node;
		insert_min_heap(heap, e); //생성한 노드를 힙에 삽입
	}

	for (i = 1; i < n; i++) { //== for(i=0; i<n-1; i++) 
		//제일 작은 값 두 개를 꺼내어 합치는 for 루프는 n-1번만 수행!, 마지막 남은 노드=루트
		//최소값을 가지는 두개의 노드를 삭제( 힙에서 꺼내기)
		e1 = delete_min_heap(heap);
		/*printf("방금 힙에서 꺼낸 것: %d\n", e1.key);
			   for(int k=1; k<n; k++)
			printf("꺼내고 난 후에 힙 배열: %d\n", heap.heap[k].key);  h->heap[k].key아닌가?*/

		e2 = delete_min_heap(heap);
		/*printf("그 다음 힙에서 꺼낸 것: %d\n", e2.key);
		   for(k=1; k<n; k++)
			printf("꺼내고 난 후에 힙 배열: %d\n", heap.heap[k].key); */

			//두개의 노드 합치기
		x = make_tree(e1.ptree, e2.ptree); // 2개의 노드를 가지는 노드 생성 | x= 합쳐서 만든 새로운 노드
		e.key = x->weight = e1.key + e2.key;  //2개의 노드 값 합하기
						//printf("e.key=%d, x->weight=%d\n", e.key, x->weight);
		e.ptree = x;  // 위에서 만든 노드를 대입
		printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);  //트리로 구성된 노드를 힙에 삽입
						//printf("%d\n", heap.heap[4].key);
	}

	e = delete_min_heap(heap); // 최종 트리
	print_codes(e.ptree, codes, top); //허프만 코드 출력
	destroy_tree(e.ptree);  //메모리 반환
	free(heap);


}//end huffman_tree 함수

//메인 함수
int main(void)
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4,6,8,12,15 };  //빈도수
	huffman_tree(freq, ch_list, 5);
	return 0;
}