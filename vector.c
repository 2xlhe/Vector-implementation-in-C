#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 8
#define VEC(type, arg)(*(type*)arg)


typedef struct vector{
    void** data; // array of pointers
    size_t capacity;
    size_t used;
    size_t size_type;

    void (*init)(struct vector* v, size_t size_type);
    void (*resize)(struct vector* v);
    void (*free_vector)(struct vector* v);
    void (*add_item)(struct vector* v, void* data);
    void (*remove_item)(struct vector* v, int pos);
}vector;

void init(vector* v, size_t size_type){
    v->capacity = INIT_SIZE;
    v->used = 0;
    v->size_type = size_type;
    v->data = malloc(v->size_type * INIT_SIZE);
}

void resize(vector* v){
    v->capacity = v->capacity * 2;
    void** temp = malloc(v->capacity);
    memcpy(temp, v->data, v->used);
    v->data = temp;
}

void free_vector(vector* v){
    free(v->data);
}

void add_item(vector* v, void* data){
    if(v->used == v->capacity){ //known type_size
        resize(v);
    }

    v->data[v->used++] = data;
}

void remove_item(vector* v, int pos){
    for (int i = pos; i < v->used-1; i++){
        v->data[i] = v->data[i+1];
    }
    v->used--;
}

void init_vector(vector* v) {
    v->init = init;
    v->resize = resize;
    v->free_vector = free_vector;
    v->add_item = add_item;
    v->remove_item = remove_item;
}

int main(){
    vector chr, intg;
    init_vector(&chr); //char
    init_vector(&intg); //int
    
    chr.init(&chr, sizeof(char));
    intg.init(&intg, sizeof(int));

    printf("%zu", intg.capacity);


    char c[] = {'a', 'b', 'c', 'd'};
    int i[] = {1, 2, 3, 4};

    printf("Char vec: ");
    for (int j = 0; j < 4; j++) {
        add_item(&chr, &c[j]);
        printf("\npos %d: %c", j, VEC(char, chr.data[j]));
    }

    printf("\n\nInt vec: ");
    for (int j = 0; j < 4; j++) {
        add_item(&intg, &i[j]);
        printf("\npos %d: %d", j, VEC(int, intg.data[j]));
    }

    chr.remove_item(&chr, 2);

    printf("\n\nNew Char vec:");
    for (int j = 0; j < chr.used; j++) {
        printf("\npos %d, %c", j, VEC(char, chr.data[j]));
    }

    intg.remove_item(&intg, 1);

    printf("\n\nNew Int vec: ");
    for (int j = 0; j < intg.used; j++) {
        printf("\npos %d, %d", j, VEC(int, intg.data[j]));
    }

    chr.free_vector(&chr);
    intg.free_vector(&intg);

    return 0;
}