#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MUL_CAPACITY 2

typedef struct {
  size_t capacity;
  size_t size;
  size_t element_size;
  void*  ptr;
} dynm;

void log_message(int TYPE) {
  char* message = NULL;
}

char valid_index(dynm* obj, size_t INDEX) {
  return INDEX >= 0 && INDEX < obj->size;
}

#define EXIT_CODE_GET_VALUE 2

void* get_value_index(dynm* obj, size_t INDEX) {
  if (valid_index(obj, INDEX)) {
    return (void*)((char*)obj->ptr + INDEX * obj->element_size);
  } else {
    log_message(EXIT_CODE_GET_VALUE);
  }

  return NULL;
}

#define EXIT_CODE_SET_VALUE 3

void* set_value_index(dynm* obj, const size_t INDEX, const void* value) {
  if (valid_index(obj, INDEX)) {
    memcpy((char*)obj->ptr + INDEX * obj->element_size, value, obj->element_size);
  } else {
    log_message(EXIT_CODE_SET_VALUE);
  }

  return NULL;
}

#define EXIT_CODE_PUSH_BACK 4

void push_back(dynm* obj, void* value) {
  if (!(obj->size + 1 <= obj->capacity)) {
    obj->capacity *= MUL_CAPACITY;

    void* temp_ptr = realloc(obj->ptr, obj->capacity * obj->element_size);

    if (!temp_ptr) {
      log_message(EXIT_CODE_PUSH_BACK);
    }

    obj->ptr = temp_ptr;
  }

  memcpy((char*)obj->ptr + obj->size * obj->element_size, value, obj->element_size);
  obj->size++;
}

#define EXIT_CODE_ZERO_SIZE 5

void pop_back(dynm* obj) {
  if (obj->size == 0) {
    log_message(EXIT_CODE_ZERO_SIZE);
  }

  obj->size--;
}

#define EXIT_CODE_ERASE_INDEX 6

void erase(dynm* obj, size_t INDEX) {
  if (valid_index(obj, INDEX)) {
    for (size_t i = INDEX; i < obj->size - 1; ++i) {
      memcpy((char*)obj->ptr + i * obj->element_size, (char*)obj->ptr + (i + 1) * obj->element_size, obj->element_size);
    }

    obj->size--;
  } else {
    log_message(EXIT_CODE_ERASE_INDEX);
  }
}

char is_empty(dynm* obj) {
  return obj->size == 0;
}

#define EXIT_CODE_INIT 1

dynm* init_dynm(const size_t element_size, const size_t init_size) {
  dynm* dynm_ptr = malloc(sizeof(dynm));

  if (!dynm_ptr) {
    fprintf(stderr, "error with init.\n");
    exit(EXIT_CODE_INIT);
  }

  dynm_ptr->ptr = malloc(element_size * init_size);

  if (!dynm_ptr->ptr) {
    fprintf(stderr, "error with init dynm data.\n");
    exit(EXIT_CODE_INIT);
  }

  dynm_ptr->size = 0;
  dynm_ptr->capacity = init_size;
  dynm_ptr->element_size = element_size;

  return dynm_ptr;
}

int main() {
/* size_t N = 10;

  dynm* vec = init_dynm(sizeof(int), N);

  for (size_t i = 0; i < N; ++i) {
    int v = i + 1;
    push_back(vec, &v);
  }

  pop_back(vec);
  
  int p = 10;
  set_value_index(vec, 4, &p);

  for (size_t i = 0; i < vec->size; ++i) {
    int* out = get_value_index(vec, i);
    printf("%d ", *out);
  }
*/
}
