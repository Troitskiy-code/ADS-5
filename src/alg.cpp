// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> opStack;
  std::string postfix;

  std::map<char, int> priority;
  priority['+'] = 1;
  priority['-'] = 1;
  priority['*'] = 2;
  priority['/'] = 2;

  for (size_t idx = 0; idx < inf.size(); ++idx) {
    char ch = inf[idx];

    if (ch >= '0' && ch <= '9') {
      postfix += ch;
      while (idx + 1 < inf.size() &&
             inf[idx + 1] >= '0' && inf[idx + 1] <= '9') {
        ++idx;
        postfix += inf[idx];
      }
      postfix += ' ';
    } else if (ch == '(') {
      opStack.push(ch);
    } else if (ch == ')') {
      while (!opStack.isempty() && opStack.get() != '(') {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
      }
      if (!opStack.isempty()) {
        opStack.pop();
      }
    } else if (priority.count(ch) != 0) {
      while (!opStack.isempty() && opStack.get() != '(' &&
             priority[opStack.get()] >= priority[ch]) {
        postfix += opStack.get();
        postfix += ' ';
        opStack.pop();
      }
      opStack.push(ch);
    }
  }

  while (!opStack.isempty()) {
    if (opStack.get() != '(') {
      postfix += opStack.get();
      postfix += ' ';
    }
    opStack.pop();
  }

  if (!postfix.empty()) {
    postfix.pop_back();
  }
  return postfix;
}

int eval(const std::string& pref) {
  TStack<int, 100> valStack;

  for (size_t pos = 0; pos < pref.size(); ++pos) {
    char token = pref[pos];
    if (token == ' ') continue;

    if (token >= '0' && token <= '9') {
      int num = token - '0';
      while (pos + 1 < pref.size() &&
             pref[pos + 1] >= '0' && pref[pos + 1] <= '9') {
        ++pos;
        num = num * 10 + (pref[pos] - '0');
      }
      valStack.push(num);
    } else {
      int right = valStack.get();
      valStack.pop();
      int left = valStack.get();
      valStack.pop();

      int res = 0;
      switch (token) {
        case '+': res = left + right; break;
        case '-': res = left - right; break;
        case '*': res = left * right; break;
        case '/': res = left / right; break;
      }
      valStack.push(res);
    }
  }
  return valStack.get();
}
