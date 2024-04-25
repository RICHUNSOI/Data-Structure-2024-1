// 202111296 이준수
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

#define WORD_SIZE 101 // 추가됨
typedef char* element; // 추가됨
typedef struct { // 큐 타입
    element data[MAX_QUEUE_SIZE];
    int  front, rear;
} QueueType;

// 오류 함수
void error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
    return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front % MAX_QUEUE_SIZE);
}

// 원형큐 출력 함수
void queue_print(QueueType* q) {
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q)) {
        int i = q->front;
        do {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        } while (i != q->front);
    }
    printf("\n");
}

// 삽입 함수
void enqueue(QueueType* q, element item) {
    if (is_full(q))
        error("큐가 포화상태입니다.");
    q->data[(q->rear + 1) % MAX_QUEUE_SIZE] = (char*)malloc(WORD_SIZE * sizeof(char));  // 추가됨
    strcpy(q->data[(q->rear + 1) % MAX_QUEUE_SIZE], item);  // 추가됨
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

// 삭제 함수
element dequeue(QueueType* q) {
    if (is_empty(q))
        error("큐가 공백상태입니다.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    element item = q->data[q->front];
    return item;
}

element get_front(QueueType* q) {
    if (is_empty(q))
        error("큐이 공백상태입니다.");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

element get_rear(QueueType* q) {
    if (is_empty(q))
        error("큐이 공백상태입니다.");
    return q->data[q->rear];
}


int main() {
    int problem_num, student_num, word_num = 0;
    scanf("%d", &problem_num);

    for (int problem = 0; problem < problem_num; problem++) {
        scanf("%d %d", &student_num, &word_num);

        //string(문자열)을 여러개 담는 배열
        //문자열 자체가 char의 배열이라
        //이중 포인터가 되었음
        char** sentence = (char**)malloc(word_num * sizeof(char*));
        for (int word = 0; word < word_num; word++) {
            sentence[word] = (char*)malloc(WORD_SIZE * sizeof(char));
            scanf("%s", sentence[word]);
        }

        QueueType* queue_array = (QueueType*)malloc(student_num * sizeof(QueueType));
        for (int student = 0; student < student_num; student++) {
            init_queue(&queue_array[student]);  // Initialize each queue
            int input_num;
            scanf("%d", &input_num);
            for (int input = 0; input < input_num; input++) {
                char word[WORD_SIZE];
                scanf("%s", word);
                enqueue(&queue_array[student], word);
            }
        }

        int is_existed = 0;
        for (int word = 0; word < word_num; word++) {
            is_existed = 0;
            for (int student = 0; student < student_num; student++) {
                if (!strcmp(sentence[word], get_front(&queue_array[student]))) {
                    char* temp = dequeue(&queue_array[student]);
                    free(temp);  // Free the dequeued element
                    is_existed = 1;
                }
            }
            if (!is_existed) {
                break;
            }
        }
        printf("%d\n", is_existed);

        // Cleanup
        for (int word = 0; word < word_num; word++) {
            free(sentence[word]); // Free each word
        }
        free(sentence); // Free the array of words

        for (int student = 0; student < student_num; student++) {
            while (!is_empty(&queue_array[student])) {
                char* temp = dequeue(&queue_array[student]);
                free(temp); // Free remaining words in the queue
            }
        }
        free(queue_array); // Free the array of queues
    }
    return 0;
}