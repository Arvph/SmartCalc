#include "smart_calc.h"

bool is_function(char* ch, int i, int* len) {
  bool flag = false;

  if (ch[i] == 's' || ch[i] == 'c' || ch[i] == 't' || ch[i] == 'a' ||
      ch[i] == 'l') {
    if (ch[i + 1] == 'i' || ch[i + 1] == 'o' || ch[i + 1] == 'a') {
      if (ch[i + 2] == 'n' || ch[i + 2] == 's' || ch[i + 2] == 'g') {
        flag = true;
        if (len != NULL) {
          *len = 3;
        }
      }
    } else if (ch[i + 1] == 's' || ch[i + 1] == 'c' || ch[i + 1] == 't' ||
               ch[i + 1] == 'q') {
      flag = true;
      if (len != NULL) {
        *len = 4;
      }
    } else if (ch[i + 1] == 'n') {
      flag = true;
      if (len != NULL) {
        *len = 2;
      }
    } else if (ch[i - 1] == 'i' || ch[i - 1] == 'o' || ch[i - 1] == 'a') {
      if (ch[i - 2] == 'n' || ch[i - 2] == 's' || ch[i - 2] == 'g') {
        flag = true;
        if (len != NULL) {
          *len = 3;
        }
      }
    } else if (ch[i - 1] == 's' || ch[i - 1] == 'c' || ch[i - 1] == 't' ||
               ch[i - 1] == 'q') {
      flag = true;
      if (len != NULL) {
        *len = 4;
      }
    } else if (ch[i - 1] == 'n') {
      flag = true;
      if (len != NULL) {
        *len = 2;
      }
    }
  }
  return flag;
}

bool is_digit(char* ch, int i) {
  bool flag = false;
  if ((ch[i] >= '0' && ch[i] <= '9') || ch[i] == '.') {
    flag = true;
  } else if (ch[i] == 'x' || ch[i] == 'e' || ch[i] == 'E') {
    flag = true;
  }
  return flag;
}

bool is_operator(char ch) {
  bool flag = false;
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
      ch == '%') {
    flag = true;
  }
  return flag;
}

bool is_letter(char ch) {
  bool flag = false;
  if (ch == 'c' || ch == 'o' || ch == 's' || ch == 'i' || ch == 'n' ||
      ch == 't' || ch == 'a' || ch == 'l' || ch == 'g' || ch == 'q' ||
      ch == 'r') {
    flag = true;
  }
  return flag;
}

bool is_sin(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 's' && ch[i + 1] == 'i' && ch[i + 2] == 'n') {
    flag = true;
  }
  return flag;
}

bool is_cos(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 'c' && ch[i + 1] == 'o' && ch[i + 2] == 's') {
    flag = true;
  }
  return flag;
}

bool is_tan(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 't' && ch[i + 1] == 'a' && ch[i + 2] == 'n') {
    flag = true;
  }
  return flag;
}

bool is_asin(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 'a' && ch[i + 1] == 's' && ch[i + 2] == 'i' &&
      ch[i + 3] == 'n') {
    flag = true;
  }
  return flag;
}

bool is_acos(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 'a' && ch[i + 1] == 'c' && ch[i + 2] == 'o' &&
      ch[i + 3] == 's') {
    flag = true;
  }
  return flag;
}

bool is_atan(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 'a' && ch[i + 1] == 't' && ch[i + 2] == 'a' &&
      ch[i + 3] == 'n') {
    flag = true;
  }
  return flag;
}

bool is_ln(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 'l' && ch[i + 1] == 'n') {
    flag = true;
  }
  return flag;
}

bool is_log(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 'l' && ch[i + 1] == 'o' && ch[i + 2] == 'g') {
    flag = true;
  }
  return flag;
}

bool is_sqrt(char* ch, int i) {
  bool flag = false;
  if (ch[i] == 's' && ch[i + 1] == 'q' && ch[i + 2] == 'r' &&
      ch[i + 3] == 't') {
    flag = true;
  }
  return flag;
}

bool is_end(char ch) {
  bool flag = false;
  if (ch == '\0' || ch == '\n') {
    flag = true;
  }
  return flag;
}
