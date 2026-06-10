#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define TABLE_SIZE 10
#define STACK_SIZE 10
#define QUEUE_SIZE 10

struct Product {
    int id;
    char name[50];
    float price;
    float rating;
};

struct Product products[MAX];
int count = 0;

// LINKED LIST
struct Node {
    struct Product data;
    struct Node* next;
};
struct Node* head = NULL;

// HASH TABLE
struct Product hashTable[TABLE_SIZE];

// STACK
int stack[STACK_SIZE];
int top = -1;

// QUEUE
int queue[QUEUE_SIZE];
int front = -1, rear = -1;



void addProduct() {
    struct Product p;

    printf("Enter ID: ");
    scanf("%d", &p.id);

    getchar(); 

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);  

    printf("Enter Price: ");
    scanf("%f", &p.price);

    printf("Enter Rating: ");
    scanf("%f", &p.rating);

    products[count++] = p;

    //Linked List
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = p;
    newNode->next = head;
    head = newNode;

    // Hash Table
    int index = p.id % TABLE_SIZE;
    hashTable[index] = p;

    printf("Product Added Successfully!\n");
}


// DISPLAY PRODUCTS
void displayProducts() {
    if(count == 0) {
        printf("No products available\n");
        return;
    }

    printf("\n--- Product List ---\n");

    for(int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Price: %.2f | Rating: %.1f\n",
               products[i].id,
               products[i].name,
               products[i].price,
               products[i].rating);
    }
}


// LINEAR SEARCH
void linearSearch(int id) {
    for(int i = 0; i < count; i++) {
        if(products[i].id == id) {
            printf("Found: %s\n", products[i].name);
            return;
        }
    }
    printf("Product Not Found\n");
}


// HASH SEARCH
void hashSearch(int id) {
    int index = id % TABLE_SIZE;

    if(hashTable[index].id == id)
        printf("Found (Hash): %s\n", hashTable[index].name);
    else
        printf("Product Not Found\n");
}


// STACK (Recently Viewed)
void push(int id) {
    if(top == STACK_SIZE - 1)
        printf("Stack Full\n");
    else {
        stack[++top] = id;
        printf("Product %d added to recent\n", id);
    }
}

void pop() {
    if(top == -1)
        printf("Stack Empty\n");
    else {
        printf("Removed Product ID: %d\n", stack[top--]);
    }
}


// QUEUE (Orders)
void enqueue(int id) {
    if(rear == QUEUE_SIZE - 1)
        printf("Queue Full\n");
    else {
        if(front == -1) front = 0;
        queue[++rear] = id;
        printf("Order %d added\n", id);
    }
}

void dequeue() {
    if(front == -1 || front > rear)
        printf("Queue Empty\n");
    else {
        printf("Processing Order ID: %d\n", queue[front++]);
    }
}


// QUICK SORT
void swap(struct Product *a, struct Product *b) {
    struct Product temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int low, int high) {
    float pivot = products[high].price;
    int i = low - 1;

    for(int j = low; j < high; j++) {
        if(products[j].price < pivot) {
            i++;
            swap(&products[i], &products[j]);
        }
    }

    swap(&products[i + 1], &products[high]);
    return i + 1;
}

void quickSort(int low, int high) {
    if(low < high) {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}



int main() {
    int choice, id;

    while(1) {
        printf("\n\n===== PRODUCT CATALOG SYSTEM =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Linear Search\n");
        printf("4. Hash Search\n");
        printf("5. Sort by Price\n");
        printf("6. Push Recently Viewed\n");
        printf("7. Pop Recently Viewed\n");
        printf("8. Add Order\n");
        printf("9. Process Order\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                printf("Enter ID: ");
                scanf("%d", &id);
                linearSearch(id);
                break;

            case 4:
                printf("Enter ID: ");
                scanf("%d", &id);
                hashSearch(id);
                break;

            case 5:
                quickSort(0, count - 1);
                printf("Products Sorted by Price\n");
                break;

            case 6:
                printf("Enter Product ID: ");
                scanf("%d", &id);
                push(id);
                break;

            case 7:
                pop();
                break;

            case 8:
                printf("Enter Order ID: ");
                scanf("%d", &id);
                enqueue(id);
                break;

            case 9:
                dequeue();
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid Choice\n");
        }
    }
}