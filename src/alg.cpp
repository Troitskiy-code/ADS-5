// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> ops;
  std::string out;

  std::map<char, int> pr;
  pr['+'] = 1;
  pr['-'] = 1;
  pr['*'] = 2;
  pr['/'] = 2;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];

    if (c >= '0' && c <= '9') {
      out += c;
      while (i + 1 < inf.size() &&
             inf[i + 1] >= '0' && inf[i + 1] <= '9') {
        ++i;
        out += inf[i];
      }
      out += ' ';
    } else if (c == '(') {
      ops.push(c);
    } else if (c == ')') {
      while (!ops.isempty() && ops.get() != '(') {
        out += ops.get();
        out += ' ';
        ops.pop();
      }
      if (!ops.isempty()) {
        ops.pop();
      }
    } else if (pr.count(c) != 0) {
      while (!ops.isempty() && ops.get() != '(' &&
             pr[ops.get()] >= pr[c]) {
        out += ops.get();
        out += ' ';
        ops.pop();
      }
      ops.push(c);
    }
  }

  while (!ops.isempty()) {
    if (ops.get() != '(') {
      out += ops.get();
      out += ' ';
    }
    ops.pop();
  }

  if (!out.empty()) {
    out.pop_back();
  }

  return out;
}

int eval(const std::string& pref) {
  TStack<int, 100> st;

  for (size_t i = 0; i < pref.size(); ++i) {
    char c = pref[i];

    if (c == ' ') {
      continue;
    }

    if (c >= '0' && c <= '9') {
      int num = c - '0';
      while (i + 1 < pref.size() &&
             pref[i + 1] >= '0' && pref[i + 1] <= '9') {
        ++i;
        num = num * 10 + (pref[i] - '0');
      }
      st.push(num);
    } else {
      int b = st.get();
      st.pop();
      int a = st.get();
      st.pop();

      int res = 0;
      if (c == '+') {
        res = a + b;
      } else if (c == '-') {
        res = a - b;
      } else if (c == '*') {
        res = a * b;
      } else if (c == '/') {
        res = a / b;
      }

      st.push(res);
    }
  }

  return st.get();
}
