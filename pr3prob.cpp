#include <iostream>
#include <stack>
#include <sstream>
#include <cmath>

using namespace std;

bool isOperator(char c) // является ли символ оператором( тру-оператор, фолс-нет)
{ 
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isOperand(char c) // явл ли символ опреандом(от 0 до 9) тру-операнд, фолс-нет
{ 
    return (c >= '0' && c <= '9');
}

int precedence(char op) // возвращает приоритет оператора(чем выше число, тем выше приоритет)
{ 
    switch (op) {
    case '^': return 3;
    case '*':
    case '/': return 2;
    case '+':
    case '-': return 1;
    default: return -1;
    }
}

string infixToPostfix(const string& infixExpression) // преобразует инфиксное выражение в постфиксное(ОПН)
{ 
    stringstream postfix;
    stack<char> operators; //стек для хранения операторов 
    for (char c : infixExpression) // выходной поток для записи постфиксного выражения
    { 
        if (isOperand(c)) 
        {
            postfix << c;
        }
        else if (c == '(') 
        {
            operators.push(c); // добавляет 
        }
        else if (c == ')') 
        {
            while (!operators.empty() && operators.top() != '(') 
            {
                postfix << operators.top(); // верхний эл-т стека

                operators.pop(); // удаляет 
            }
            if (!operators.empty() && operators.top() == '(')  // проверка 
            {
                operators.pop();
            }
        }
        else if (isOperator(c)) 
        {
            while (!operators.empty() && precedence(c) <= precedence(operators.top())) 
            {
                postfix << operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }
    while (!operators.empty()) 
    {
        postfix << operators.top();
        operators.pop();
    }
    return postfix.str();
}

int performOperation(char operation, int operand1, int operand2) //выполнение операций над 2мя операндами с заданным оператором
{ 
    switch (operation) 
    {
     case '+': return operand1 + operand2;
     case '-': return operand1 - operand2;
     case '*': return operand1 * operand2;
     case '/': return operand1 / operand2;
     case '^': return pow(operand1, operand2);
     default: return 0;
    }
}

int evaluatePostfix(const string& expression) // вычисляет результат ОПН
{ 
    stack<int> operands; //стек для хранения операндов
    for (char c : expression) //последовательно обрабатывает символы постфиксного выражения.
    { 
        if (isOperand(c)) 
        {
            operands.push(c - '0');
        }
        else if (isOperator(c)) 
        {
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            int result = performOperation(c, operand1, operand2);
            operands.push(result);
        }
    }
    return operands.top();
}

/*bool isValidExpression(const string& infixExpression) //проверка корректности расстановки скобок в инфиксном выражении
{
    stack<char> parentheses; //стек для отслеживания открывающих и закрывающих скобок
    for (char c : infixExpression) 
    {
        if (c == '(')
        {
            parentheses.push(c);
        }
        else if (c == ')') 
        {
            if (parentheses.empty() || parentheses.top() != '(')
            {
                return false;
            }
            parentheses.pop();
        }
    }
    return parentheses.empty();
}*/
bool isValidExpression(const string& infixExpression) {
    stack<char> parentheses; // стек для отслеживания открывающих и закрывающих скобок
    bool hasOperand = false; // флаг, указывающий, был ли введен хотя бы один операнд
    bool hasOperator = false; // флаг, указывающий, был ли введен хотя бы один оператор
    bool isValid = true; // флаг, указывающий, является ли выражение допустимым

    for (char c : infixExpression) {
        if (isOperand(c)) {
            hasOperand = true;
        }
        else if (isOperator(c)) {
            hasOperator = true;
        }

        if (!isOperand(c) && !isOperator(c) && c != '(' && c != ')') {
            // Если символ не является ни операндом, ни оператором, ни скобкой, выражение недопустимо
            isValid = false;
            break;
        }
    }

    // Проверяем условия для корректности выражения
    if (!hasOperand || !hasOperator || !isValid) {
        return false;
    }

    for (char c : infixExpression) {
        if (c == '(') {
            parentheses.push(c);
        }
        else if (c == ')') {
            if (parentheses.empty() || parentheses.top() != '(') {
                return false;
            }
            parentheses.pop();
        }
    }

    return parentheses.empty();
}



int main() 
{
    setlocale(LC_ALL, "Russian");
    string infixExpression;
    bool exitProgram = false;
    do 
    {
     cout << "Введите инфиксное выражение: ";
     getline(cin, infixExpression);

     cout << "Инфиксное выражение: " << infixExpression << endl;

     if (isValidExpression(infixExpression)) 
     {
        string postfixExpression = infixToPostfix(infixExpression);
        cout << "Постфиксное выражение(ОПН): " << postfixExpression << endl;
        cout << "Результат: " << evaluatePostfix(postfixExpression) << endl;
     }
     else
     {
         cout << "Неверный ввод." << endl;
             continue; 
     }
     char choice;
     cout << "Вы хотите ввести другое выражение? (1/0): ";
     cin >> choice;
     cin.ignore(); // Очистка буфера ввода
     if (choice == '0') {
         exitProgram = true;
     }
    } while (!exitProgram);

    cout << "Хорошего дня!" << endl;

    return 0;
}
