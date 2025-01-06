
#include <stdio.h>
#include <stdlib.h>


// 定义哈希表节点结构体
typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
} HashNode;

// 定义哈希表结构体
typedef struct HashMap {
    HashNode **table;
    int size;
} HashMap;

// 初始化哈希表
HashMap *createHashMap(int size) {
    HashMap *map = (HashMap *) malloc(sizeof(HashMap));
    map->size = size;
    map->table = (HashNode **) malloc(size * sizeof(HashNode *));
    for (int i = 0; i < size; i++) {
        map->table[i] = NULL;
    }
    return map;
}

// 哈希函数，简单的取模法
int hashFunction(int key, int size) {
    return key % size;
}

// 插入键值对到哈希表
void put(HashMap *map, int key, int value) {
    int index = hashFunction(key, map->size);
    HashNode *node = map->table[index];
    if (node == NULL) {
        // 如果该位置为空，直接插入新节点
        HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;
        map->table[index] = newNode;
    } else {
        // 如果该位置已有节点，遍历链表看是否已存在该key，存在则更新值，不存在则插入新节点到链表头部
        while (node != NULL) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
        newNode->key = key;
        newNode->value = value;
        newNode->next = map->table[index];
        map->table[index] = newNode;
    }
}

// 根据键查找对应的值
int get(HashMap *map, int key) {
    int index = hashFunction(key, map->size);
    HashNode *node = map->table[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;  // 没找到返回 -1
}

// 释放哈希表内存
void freeHashMap(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        HashNode *node = map->table[i];
        while (node != NULL) {
            HashNode *next = node->next;
            free(node);
            node = next;
        }
    }
    free(map->table);
    free(map);
}

int main() {
    HashMap *map = createHashMap(10);
    put(map, 1, 100);
    put(map, 2, 200);
    put(map, 11, 300);  // 11 % 10 = 1 ，会产生哈希冲突，链地址法处理

    printf("Value for key 1: %d\n", get(map, 1));
    printf("Value for key 2: %d\n", get(map, 2));
    printf("Value for key 11: %d\n", get(map, 11));

    freeHashMap(map);

    return 0;
}