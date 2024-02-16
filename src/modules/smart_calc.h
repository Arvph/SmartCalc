#ifndef SMART_CALC_H
#define SMART_CALC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

#define OK 1
#define ERROR 0

// STACK FOR NUM
typedef struct Stack_num {
  double data[MAX_SIZE];
  int top;
} stack_n;

// STACK FOR OPERATORS
typedef struct Stack_oprt {
  char data[MAX_SIZE];
  int top;
} stack_o;

// *** STACK ***
void init_num(stack_n* head);
bool is_empty_num(stack_n* head);
bool is_full_num(stack_n* head);
void push_num(stack_n* head, double value);
double pop_num(stack_n* head);

void init_oprt(stack_o* head);
bool is_empty_oprt(stack_o* head);
bool is_full_oprt(stack_o* head);
void push_oprt(stack_o* head, char value);
void push_func(stack_o* head, char* value);
char pop_oprt(stack_o* head);
char peek_oprt(stack_o* head);

// *** PARCER ***
bool is_digit(char* ch, int i);
bool is_function(char* ch, int i, int* len);
bool is_operator(char ch);
bool is_letter(char ch);
bool is_sin(char* ch, int i);
bool is_cos(char* ch, int i);
bool is_tan(char* ch, int i);
bool is_asin(char* ch, int i);
bool is_acos(char* ch, int i);
bool is_atan(char* ch, int i);
bool is_ln(char* ch, int i);
bool is_log(char* ch, int i);
bool is_sqrt(char* ch, int i);
bool is_end(char ch);

// *** CALCULUS ***
int to_postfix(const char* origin, char* postfix);
void calculation(char* postfix, double x, char* result);

// *** VALIDATION ***
void credit(double amount, int month, double percent, int c_type, char* res_monthly, char* res_last, char* res_overpay, char* res_total);

#endif
