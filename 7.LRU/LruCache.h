#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define LRU_CACHE_SIZE 5

typedef struct node {
    struct node* prev;
    struct node* next;
    char* key;
    int value;
} Node;

typedef struct hashmap {
    int capacity;
    int size;
    Node* array[LRU_CACHE_SIZE];
} HashMap;

typedef struct dlist {
    Node *head;
    Node *tail;
} DList;

typedef struct lrucache {
    int itail;
    HashMap* map;
    DList* list;
} LRUCache;

int HashMap_Index(const char* key) {
    if(key == NULL) {
        return -1;
    }
    return atoi(key) % LRU_CACHE_SIZE;
}
int LRU_Get(LRUCache* lru, const char* key) {
    if(key == NULL || strlen(key) == 0) {
        errno = EACCES;
        perror("illegal call");
        exit(0);
    } 
    if(lru == NULL || lru->map == NULL || lru->map->size == 0) {
        return INT_MIN;
    }
    int index = -1;
    int origin_index = -1;
    index = HashMap_Index(key);
    origin_index = index;
    while (1) {
        
        if(lru->map->array[index] == NULL) {
            return INT_MIN;
        }
        if(strcmp(lru->map->array[index]->key, key) == 0) {
            break;
        }
        index = index == LRU_CACHE_SIZE-1 ? 0 : index+1;
        if(index == origin_index) {
            return INT_MIN;
        }
    }
    Node* p = lru->map->array[index];
    Node* q = NULL;
    if(p != lru->list->head) {
        if(p == lru->list->tail) {
            lru->list->tail = p->prev;
            p->prev->next = NULL;
            const char* tail_key = lru->list->tail->key;
            int tail_index = HashMap_Index(tail_key);
            while(strcmp(tail_key, lru->map->array[tail_index]->key) != 0) {
                tail_index = tail_index == LRU_CACHE_SIZE-1 ? 0 : tail_index+1;
            }
            lru->itail = tail_index;
        } else {
            q = p->prev;
            p->prev->next = p->next;
            q->next = p->next;
            p->next->prev = q;
            q = NULL;
        }
        lru->list->head->prev = p;
        p->next = lru->list->head;
        p->prev = NULL;
    }
    return lru->map->array[index]->value;
    
}
void LRU_Eminate(LRUCache* lru) {
    if(lru == NULL || lru->map == NULL || lru->map->size != LRU_CACHE_SIZE) {
        return;
    }
    lru->map->array[lru->itail] = NULL;
    lru->map->size = lru->map->size - 1;
    Node* p = lru->list->tail;
    lru->list->tail = lru->list->tail->prev;
    lru->list->tail->next = NULL;
    free(p);
    return;
}
LRUCache* LRU_Set(LRUCache* lru, const char* key, int value) {
    if(key == NULL || strlen(key) == 0) {
        errno = EACCES;
        perror("illegal call");
        return lru;
    }
    if(lru == NULL) {
        lru = (LRUCache*)malloc(sizeof(LRUCache));
        if(lru == NULL) {
            errno = ENOMEM;
            perror("malloc");
            exit(0);
        }
        lru->itail = -1;
        lru->map = NULL;
        lru->list = NULL;
    }
    if(lru->map == NULL) {
        lru->map = (HashMap*)malloc(sizeof(HashMap));
        if(lru->map == NULL) {
            errno = ENOMEM;
            perror("malloc");
            exit(0);
        }
        lru->map->size = 0;
        for(int i = 0; i < LRU_CACHE_SIZE; i++) {
            lru->map->array[i] = NULL;
        }
        lru->map->capacity = LRU_CACHE_SIZE;

        lru->list = (DList*)malloc(sizeof(DList));
        if(lru->list == NULL) {
            errno = ENOMEM;
            perror("malloc");
            exit(0);
        }
        lru->list->head = NULL;
        lru->list->tail = NULL;
    }
    printf("%d\n", lru->map->size);
    if(lru->map->size == LRU_CACHE_SIZE) {
        LRU_Eminate(lru);
    }
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        errno = ENOMEM;
        perror("malloc");
        exit(0);
    }
    node->key = strdup(key);
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    int index = 0;
    index = HashMap_Index(key);
    while(lru->map->array[index] != NULL) {
        index = index == LRU_CACHE_SIZE-1 ? 0 : index+1;
    }
    lru->map->array[index] = node;
    lru->map->size++;
    if(lru->list->head == NULL) {
        lru->list->head = node;
        lru->list->tail = node;
        lru->itail = index;
    } else {
        node->next = lru->list->head;
        lru->list->head->prev = node;
        lru->list->head = node;
    }
    return lru;
}

int main(int argc, char** argv) {
    LRUCache* lru = NULL;
    lru = LRU_Set(lru, "100", 100);
    lru = LRU_Set(lru, "101", 101);
    lru = LRU_Set(lru, "102", 102);
    lru = LRU_Set(lru, "103", 103);
    lru = LRU_Set(lru, "104", 104);
    lru = LRU_Set(lru, "105", 105);
    int x = LRU_Get(lru, "100");
    printf("%d\n", x == INT_MIN);
    return 0;
}