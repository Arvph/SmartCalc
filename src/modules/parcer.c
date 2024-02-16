#include "smart_calc.h"

int priority(char* ch, int i) {
  int flag = 0;
  if (ch[i] == '+' || ch[i] == '-') {
    flag = 1;
  } else if (ch[i] == '*' || ch[i] == '/') {
    flag = 2;
  } else if (is_function(ch, i, NULL) || ch[i] == '%') {
    flag = 3;
  } else if (ch[i] == '^') {
    flag = 4;
  } else if (ch[i] == '~' || ch[i] == '&') {
    flag = 5;
  }
  return flag;
}

void digit_to_postfix(bool* prev_digit, char* postfix, int* j, char ch) {
  if (*prev_digit) {
    postfix[*j] = ch;
    (*j)++;
  } else {
    if (*j != 0) {
      if (postfix[*j - 1] != ' ') {
        postfix[*j] = ' ';
      }
      (*j)++;
    }
    postfix[*j] = ch;
    (*j)++;
  }
  *prev_digit = true;
}

void minus_to_postfix(bool* prev_digit, char* origin, char* postfix, int i,
                      int* j, stack_o* head) {
  *prev_digit = false;
  char ch = origin[i];
  if (i == 0 || origin[i + 1] == '(' || origin[i - 1] == '(') {
    ch = '~';
  }
  while (!is_empty_oprt(head) &&
         priority(origin, i) <= priority(head->data, head->top)) {
    postfix[*j] = pop_oprt(head);
    (*j)++;
  }
  push_oprt(head, ch);
}

void open_brackets(stack_o* head, char ch, bool* prev_digit) {
  push_oprt(head, ch);
  *prev_digit = false;
}

int close_brackets(bool* prev_digit, char* postfix, int* j, stack_o* head) {
  int flag = OK;
  if (*prev_digit) {
    if (postfix[*j - 1] != ' ') {
      postfix[*j] = ' ';
    }
    (*j)++;
    *prev_digit = false;
  }
  while (!is_empty_oprt(head) && peek_oprt(head) != '(') {
    postfix[*j] = pop_oprt(head);
    (*j)++;
  }
  if (!is_empty_oprt(head) && peek_oprt(head) == '(') {
    pop_oprt(head);
    int tmp = 0;
    if (!is_empty_oprt(head) && is_function(head->data, head->top, &tmp)) {
      for (int i = 0; i < tmp; i++) {
        postfix[*j] = pop_oprt(head);
        (*j)++;
      }
    }
  } else {
    flag = ERROR;
  }
  return flag;
}

void func_to_postfix(stack_o* head, int len, char* origin, int i, char* postfix,
                     int* j) {
  if (postfix == NULL && origin != NULL) {
    int n = 0;
    char func_name[10] = {0};
    for (n = 0; n < len; n++) {
      func_name[n] = origin[i + n];
    }
    func_name[n + 1] = '\0';
    push_func(head, func_name);
  } else if (origin == NULL && postfix != NULL) {
    for (int n = 0; n < len; n++) {
      postfix[*j] = pop_oprt(head);
      (*j)++;
    }
    if (postfix[*j - 1] != ' ') {
      postfix[*j] = ' ';
      (*j)++;
    }
  }
}

void end_postfix(int* i, char* postfix, stack_o* head) {
  if (*i > 0) {
    postfix[*i] = ' ';
    (*i)++;
  }
  while (!is_empty_oprt(head)) {
    postfix[*i] = pop_oprt(head);
    (*i)++;
    if (!is_empty_oprt(head)) {
      postfix[*i] = ' ';
      (*i)++;
    }
  }
  postfix[*i] = '\0';
}

int to_postfix(const char* origin, char* postfix) {
  stack_o head_o;
  init_oprt(&head_o);

  int exit_status = OK;
  int f_len = 0;
  bool prev_digit = false;

  int i = 0, j = 0;
  for (; !is_end(origin[i]); i++) {
    if (origin[i] == ' ') {
      continue;
    } else if (is_digit(origin, i)) {
      digit_to_postfix(&prev_digit, postfix, &j, origin[i]);
    } else if (origin[i] == '-') {
      minus_to_postfix(&prev_digit, origin, postfix, i, &j, &head_o);
    } else if (origin[i] == '(') {
      open_brackets(&head_o, origin[i], &prev_digit);
    } else if (origin[i] == ')') {
      if (close_brackets(&prev_digit, postfix, &j, &head_o) !=
          OK) {  // нужен ли ! - ???
        exit_status = ERROR;
        break;
      }
    } else if (is_function(origin, i, &f_len)) {
      func_to_postfix(&head_o, f_len, origin, i, NULL, 0);
      i += (f_len - 1);
    } else {
      prev_digit = false;
      while (!is_empty_oprt(&head_o) &&
             priority(origin, i) <= priority(head_o.data, head_o.top)) {
        int tmp = 0;
        if (is_function(head_o.data, head_o.top, &tmp)) {
          func_to_postfix(&head_o, f_len, NULL, 0, postfix, &j);  // - ????
          postfix[j++] = ' ';
        } else if (head_o.data[head_o.top] != ' ') {
          postfix[j++] = pop_oprt(&head_o);
        } else {
          pop_oprt(&head_o);
        }
      }
      if (origin[i] == '+' && origin[i - 1] == '(') {
        push_oprt(&head_o, '&');
      } else {
        push_oprt(&head_o, origin[i]);
      }
    }
  }
  end_postfix(&j, postfix, &head_o);
  return exit_status;
}
