#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_counter_info 200

struct customer_info {
    int use_time;
    int cost;
};

struct counter_info {
    int end_time;
    int number;
};

typedef struct {
    counter_info heap[MAX_counter_info];
    int heap_size;
} HeapType;

// 생성 함수
HeapType* create() {
    return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h) {
    h->heap_size = 0;
}

// 현재 요소의 개수가 heap_size인 힙 h에 item을 삽입한다.
void push_min_heap(HeapType* h, counter_info item) {
    int i;
    i = ++(h->heap_size);

    // upheap
    //트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while ((i != 1) && (item.end_time < h->heap[i / 2].end_time)) {// 최소힙으로 바꿀 때 부등호 뒤집기 
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;   // 새로운 노드를 삽입
}

// 삭제 함수
counter_info pop_min_heap(HeapType* h) {
    int parent, child;
    counter_info item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    // downheap
    while (child <= h->heap_size) {
        // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if ((child < h->heap_size) &&
            (h->heap[child].end_time) > h->heap[child + 1].end_time)
            child++;
        if (temp.end_time <= h->heap[child].end_time) break;
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

int main() {
    int number_of_counter, number_of_customer;
    scanf("%d %d", &number_of_counter, &number_of_customer);

    counter_info* counter_list = (counter_info*)malloc((number_of_counter + 1) * sizeof(counter_info));
    for (int counter = 1; counter <= number_of_counter; counter++) {
        counter_list[counter].number = counter;
    }

    customer_info* customer_list = (customer_info*)malloc((number_of_customer + 1) * sizeof(customer_info));
    for (int customer = 1; customer <= number_of_customer; customer++) {
        scanf("%d %d", &customer_list[customer].use_time, &customer_list[customer].cost);
    }

    int total_time_answer = 0;

    int* counter_profit_answer = (int*)malloc((number_of_counter + 1) * sizeof(int));

    HeapType* pq = create();
    init(pq);

    for (int customer = 1; customer <= number_of_counter; customer++) {
        counter_list[customer].end_time = customer_list[customer].use_time;
        push_min_heap(pq, counter_list[customer]);

        counter_profit_answer[customer] = customer_list[customer].cost;
        total_time_answer = (total_time_answer > counter_list[customer].end_time) ? total_time_answer : counter_list[customer].end_time;
    }

    for (int customer = number_of_counter + 1; customer <= number_of_customer; customer++) {
        int counter = pop_min_heap(pq).number;
        counter_list[counter].end_time += customer_list[customer].use_time;
        push_min_heap(pq, counter_list[counter]);

        counter_profit_answer[counter] += customer_list[customer].cost;
        total_time_answer = (total_time_answer > counter_list[counter].end_time) ? total_time_answer : counter_list[counter].end_time;
    }

    printf("%d\n", total_time_answer);
    for (int counter = 1; counter <= number_of_counter; counter++) {
        printf("%d\n", counter_profit_answer[counter]);
    }

    return 0;
}
