#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>



struct Node {
    char data[1000];
    struct Node* next;
};

struct Stack {
    Node* top;
};

void init(Stack* s) {
    s->top = NULL;
}

bool isEmpty(Stack s) {
    return s.top == NULL;
}

Node* createNode(char* str) {
    Node* n = new Node;
    strcpy(n->data, str);
    n->next = NULL;
    return n;
}

void push(Stack* s, char* str) {
    Node* n = createNode(str);
    n->next = s->top;
    s->top = n;
}

char* pop(Stack* s) {
    if (isEmpty(*s)) return NULL;
    Node* temp = s->top;
    s->top = temp->next;
    return temp->data;
}

void clear(Stack* s) {
    while (!isEmpty(*s)) {
        pop(s);
    }
}
typedef struct QNode {
    char action[50];
    char content[500];
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

QNode* createQNode(const char* action, const char* content) {
    QNode* n = new QNode;
    strcpy(n->action, action);
    strcpy(n->content, content);
    n->next = NULL;
    return n;
}

void enqueue(Queue* q, const char* action, const char* content) {
    QNode* n = createQNode(action, content);
    strcpy(n->action, action);
    strcpy(n->content, content);
    n->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = n;
        return;
    }

    q->rear->next = n;
    q->rear = n;
}
char* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;

    QNode* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    return temp->action;
}

int main() {
    Stack undo, redo;
    init(&undo);
    init(&redo);
    Queue history;
    initQueue(&history);

    char current[1000] = "";
    int choice;
    char input[1000];
    system("color E");

    while (1) {

        system("cls");

        printf("+-----------------------------------------------------------------------+\n");
        printf("|                         TEXT EDITOR APP                               |\n");
        printf("+-----------------------------------------------------------------------+\n");
        printf("| 1. Nhap van ban                                                       |\n");
        printf("| 2. Undo                                                               |\n");
        printf("| 3. Redo                                                               |\n");
        printf("| 4. Hien thi                                                           |\n");
        printf("| 5. Lich su thao tac                                                   |\n");
        printf("| 0. Thoat                                                              |\n");
        printf("+-----------------------------------------------------------------------+\n");
        printf("| Noi dung:                                                             |\n");
        printf("| > %-67s |\n", current);
        printf("+-----------------------------------------------------------------------+\n");
        printf("Chon: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {


        case 1: {
            printf("Nhap van ban: ");
            fgets(input, 1000, stdin);
            input[strcspn(input, "\n")] = 0;

            push(&undo, current);
            clear(&redo);

            strcat(current, input); //Nối chuỗi Input mới vào cái current cũ
            enqueue(&history, "Nhap van ban", input);
            break;
        }

        case 2: {
            if (!isEmpty(undo)) {
                push(&redo, current); //đưa cái hiện tại vào trong redo vì nó là undo
                strcpy(current, pop(&undo)); //sau đó copy cái cái undo vào lại chỗ cũ trong current
                enqueue(&history, "Undo", "");
            }
            break;
        }

        case 3: {
            if (!isEmpty(redo)) {
                push(&undo, current);
                strcpy(current, pop(&redo));
                enqueue(&history, "Redo", "");
            }
            break;
        }

        case 4: {
            printf("\nVan ban: %s\n", current);
            getchar();
            break;
        }//
        case 5: {
            printf("\n=========================== Lich su thao tac ============================\n");

            QNode* temp = history.front;
            int i = 1;

            while (temp != NULL) {
                if (strlen(temp->content) > 0)
                    printf("%d. %s: %s\n", i++, temp->action, temp->content);
                else
                    printf("%d. %s\n", i++, temp->action);

                temp = temp->next;
            }

            printf("\nNhan phim bat ky...");
            _getch();
            break;
        }//

        case 0:
            return 0;

        default:
            printf("Lua chon khong hop le!\n");
            getchar();
        }
    }
}