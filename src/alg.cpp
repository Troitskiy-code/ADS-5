// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> operatorStack;
  std::string postfixExpr;

  std::map<char, int> operatorPriority = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
  };

  for (size_t index = 0; index < inf.size(); ++index) {
    char currentChar = inf[index];

    if (currentChar >= '0' && currentChar <= '9') {
      postfixExpr += currentChar;
      while (index + 1 < inf.size() && inf[index + 1] >= '0' && inf[index + 1] <= '9') {
        ++index;
        postfixExpr += inf[index];
      }
      postfixExpr += ' ';
    }
    else if (currentChar == '(') {
      operatorStack.push(currentChar);
    }
    else if (currentChar == ')') {
      while (!operatorStack.isempty() && operatorStack.get() != '(') {
        postfixExpr += operatorStack.get();
        postfixExpr += ' ';
        operatorStack.pop();
      }
      if (!operatorStack.isempty()) {
        operatorStack.pop();
      }
    }
    else if (operatorPriority.count(currentChar) != 0) {
      while (!operatorStack.isempty() && operatorStack.get() != '(' &&
             operatorPriority[operatorStack.get()] >= operatorPriority[currentChar]) {
        postfixExpr += operatorStack.get();
        postfixExpr += ' ';
        operatorStack.pop();
      }
      operatorStack.push(currentChar);
    }
  }

  while (!operatorStack.isempty()) {
    if (operatorStack.get() != '(') {
      postfixExpr += operatorStack.get();
      postfixExpr += ' ';
    }
    operatorStack.pop();
  }

  if (!postfixExpr.empty()) {
    postfixExpr.pop_back();
  }

  return postfixExpr;
}

int eval(const std::string& pref) {
  TStack<int, 100> operandStack;

  for (size_t pos = 0; pos < pref.size(); ++pos) {
    char token = pref[pos];

    if (token == ' ') {
      continue;
    }

    if (token >= '0' && token <= '9') {
      int number = token - '0';
      while (pos + 1 < pref.size() && pref[pos + 1] >= '0' && pref[pos + 1] <= '9') {
        ++pos;
        number = number * 10 + (pref[pos] - '0');
      }
      operandStack.push(number);
    }
    else {
      int rightOperand = operandStack.get();
      operandStack.pop();
      int leftOperand = operandStack.get();
      operandStack.pop();

      int calculationResult = 0;
      switch (token) {
        case '+': calculationResult = leftOperand + rightOperand; break;
        case '-': calculationResult = leftOperand - rightOperand; break;
        case '*': calculationResult = leftOperand * rightOperand; break;
        case '/': calculationResult = leftOperand / rightOperand; break;
      }

      operandStack.push(calculationResult);
    }
  }

  // Результат находится на вершине стека
  return operandStack.get();
}
