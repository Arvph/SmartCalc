#include "smart_calc.h"

// STACK FOR NUM
void init_num(stack_n* head) { head->top = -1; }

bool is_empty_num(stack_n* head) {
  bool flag = false;
  if (head->top == -1) {
    flag = true;
  }
  return flag;
}

bool is_full_num(stack_n* head) {
  bool flag = false;
  if (head->top >= MAX_SIZE - 1) {
    flag = true;
  }
  return flag;
}

void push_num(stack_n* head, double value) {
  if (!is_full_num(head)) {
    head->data[++head->top] = value;
  }
}

double pop_num(stack_n* head) {
  double res = 0.0;
  if (!is_empty_num(head)) {
    res = head->data[head->top--];
  }
  return res;
}

// STACK FOR OPERATIONS

void init_oprt(stack_o* head) { head->top = -1; }

bool is_empty_oprt(stack_o* head) {
  bool flag = false;
  if (head->top == -1) {
    flag = true;
  }
  return flag;
}

bool is_full_oprt(stack_o* head) {
  bool flag = false;
  if (head->top >= MAX_SIZE - 1) {
    flag = true;
  }
  return flag;
}

void push_oprt(stack_o* head, char value) {
  if (!is_full_oprt(head)) {
    head->data[++head->top] = value;
  }
}

void push_func(stack_o* head, char* value) {
  if (!is_full_oprt(head)) {
    for (int i = strlen(value) - 1; i >= 0; i--) {
      head->data[++head->top] = value[i];
    }
  }
}

char pop_oprt(stack_o* head) {
  double res = 0.0;
  if (!is_empty_oprt(head)) {
    res = head->data[head->top--];
  }
  return res;
}

char peek_oprt(stack_o* head) {
  double res = 0.0;
  if (!is_empty_oprt(head)) {
    res = head->data[head->top];
  }
  return res;
}
