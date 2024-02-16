#include "smart_calc.h"

/*Function for trigonometrical caclculations*/
void f_calculation(double num, char* postfix, int i, stack_n* head_num,
                   int* flag) {
  if (is_sin(postfix, i)) {
    push_num(head_num, sin(num));
  } else if (is_cos(postfix, i)) {
    push_num(head_num, cos(num));
  } else if (is_tan(postfix, i)) {
    push_num(head_num, tan(num));
  } else if (is_asin(postfix, i)) {
    if (num >= -1 && num <= 1) {
      push_num(head_num, asin(num));
    } else {
      *flag = ERROR;
    }
  } else if (is_acos(postfix, i)) {
    if (num >= -1 && num <= 1) {
      push_num(head_num, acos(num));
    } else {
      *flag = ERROR;
    }
  } else if (is_atan(postfix, i)) {
    push_num(head_num, atan(num));
  } else if (is_ln(postfix, i)) {
    if (num > 0) {
      push_num(head_num, log(num));
    } else {
      *flag = ERROR;
    }
  } else if (is_log(postfix, i)) {
    if (num > 0) {
      push_num(head_num, log10(num));
    } else {
      *flag = ERROR;
    }
  } else if (is_sqrt(postfix, i)) {
    if (num >= 0) {
      push_num(head_num, sqrt(num));
    } else {
      *flag = ERROR;
    }
  } else if (postfix[i] == '~') {
    push_num(head_num, -num);
  } else if (postfix[i] == '&') {
    push_num(head_num, num);
  }
}

/*Function for simple caclculations*/
void o_calculations(double num_a, double num_b, char* postfix, int i,
                    stack_n* head_num, int* flag) {
  if (postfix[i] == '+') {
    push_num(head_num, num_a + num_b);
  } else if (postfix[i] == '-') {
    push_num(head_num, num_a - num_b);
  } else if (postfix[i] == '*') {
    push_num(head_num, num_a * num_b);
  } else if (postfix[i] == '/') {
    if (num_b != 0) {
      push_num(head_num, num_a / num_b);
    } else {
      *flag = ERROR;
    }
  } else if (postfix[i] == '^') {
    push_num(head_num, pow(num_a, num_b));
  } else if (postfix[i] == '%') {
    push_num(head_num, fmod(num_a, num_b));
  }
}

/*This function delete extra nulls that can be in the end of the result line*/
void delete_nulls(char* final_str, stack_n* head_num) {
  double result = pop_num(head_num);
  char buffer[MAX_SIZE] = {0};
  sprintf(buffer, "%.7f", result);
  int i = strlen(buffer) - 1;
  if (i <= 14) {
    sprintf(final_str, "%s", buffer);
    for (; final_str[i] == '0'; i--) {
      final_str[i] = '\0';
    }
    if (final_str[i] == '.' || final_str[i] == ',') {
      final_str[i] = '\0';
    }
  } else {
    sprintf(final_str, "%e", result);
  }
}

/*This function converts string line to double num*/
void str_to_double(char* buffer, int* len, stack_n* head_num) {
  if (*len > 0) {
    buffer[*len] = '\0';
    double num = atof(buffer);
    push_num(head_num, num);
    *len = 0;
  }
}

void calculation(char* postfix, double x, char* result) {
  stack_n head_num;
  init_num(&head_num);
  char buffer[MAX_SIZE];
  int buffer_len = 0, flag = OK;

  for (int i = 0; postfix[i] != '\0'; i++) {
    int f_len = 0;
    if (is_digit(postfix, i)) {
      if (postfix[i] == 'x') {
        push_num(&head_num, x);
      } else {
        buffer[buffer_len++] = postfix[i];
      }
    } else if (postfix[i] == ' ') {
      str_to_double(buffer, &buffer_len, &head_num);
    } else if (is_operator(postfix[i])) {
      str_to_double(buffer, &buffer_len, &head_num);
      double num_b = pop_num(&head_num);
      double num_a = pop_num(&head_num);
      o_calculations(num_a, num_b, postfix, i, &head_num, &flag);
    } else if (is_function(postfix, i, &f_len) || postfix[i] == '~' ||
               postfix[i] == '&') {
      str_to_double(buffer, &buffer_len, &head_num);
      double num = pop_num(&head_num);
      f_calculation(num, postfix, i, &head_num, &flag);
      if (f_len != 0) {
        i += f_len - 1;
      }
    } else if (is_letter(postfix[i])) {
    } else {
      flag = ERROR;
    }
  }
  str_to_double(buffer, &buffer_len, &head_num);
  if (flag == OK) {
    delete_nulls(result, &head_num);
  } else {
    sprintf(result, "%s", "ERROR");
  }
}