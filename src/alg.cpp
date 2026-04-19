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

  for (size_t i = 0; i < inf.size(); ++i) {
    char ch = inf[i];

    if (ch >= '0' && ch <= '9') {
      postfix += ch;
      while (i + 1 < inf.size() &&
             inf[i + 1] >= '0' && inf[i + 1] <= '9') {
        ++i;
        postfix += inf[i];
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

int eval(const std::string& post) {
  TStack<int, 100> valStack;

  for (size_t i = 0; i < post.size(); ++i) {
    char ch = post[i];

    if (ch == ' ') {
      continue;
    }

    if (ch >= '0' && ch <= '9') {
      int num = ch - '0';
      while (i + 1 < post.size() &&
             post[i + 1] >= '0' && post[i + 1] <= '9') {
        ++i;
        num = num * 10 + (post[i] - '0');
      }
      valStack.push(num);
    } else {
      int right = valStack.get();
      valStack.pop();
      int left = valStack.get();
      valStack.pop();

      int result = 0;
      switch (ch) {
        case '+': result = left + right; break;
        case '-': result = left - right; break;
        case '*': result = left * right; break;
        case '/': result = left / right; break;
      }
      valStack.push(result);
    }
  }

  return valStack.get();
}
