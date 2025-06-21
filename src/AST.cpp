#include <iostream>
#include <string>

// Base AST Node
class Node {
public:
    virtual ~Node() = default;
};

class Expression : public Node {
public:
    virtual void print() const = 0;
    virtual std::string toSource() const = 0;
};

// Numeric literal expression
class NumberExpression : public Expression {
public:
    double value;

    NumberExpression(double value) : value(value) {}

    void print() const override {
        std::cout << value;
    }

    std::string toSource() const override {
        return std::to_string(value);
    }
};

class VariableExpression : public Expression {
public:
    const char* name;

    VariableExpression(const char* name) : name(name) {}

    void print() const override {
        std::cout << name;
    }

    std::string toSource() const override {
        return std::string(name);
    }
};

class AssignmentExpression : public Expression {
public:
    const char* name;
    Expression* value;

    AssignmentExpression(const char* name, Expression* value) : name(name), value(value) {}

    void print() const override {
        std::cout << name << " = ";
        value->print();
    }

    std::string toSource() const override {
        return std::string(name) + " = " + value->toSource() + ";";
    }

    ~AssignmentExpression() {
        delete value;
    }
};

// Enum for binary operators
enum class BinaryOperator {
    Add,
    Subtract,
    Multiply,
    Divide
};

// Binary operation expression
class BinaryExpression : public Expression {
public:
    Expression *left;
    Expression *right;
    BinaryOperator op;

    BinaryExpression(Expression *left, BinaryOperator op, Expression *right)
        : left(left), op(op), right(right) {}

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << " " << getOperatorSymbol(op) << " ";
        right->print();
        std::cout << ")";
    }

    std::string toSource() const override {
        return "(" + left->toSource() + " " + getOperatorSymbol(op) + " " + right->toSource() + ")";
    }

    ~BinaryExpression() {
        delete left;
        delete right;
    }

private:
    const char getOperatorSymbol(BinaryOperator op) const {
        switch (op) {
            case BinaryOperator::Add: return '+';
            case BinaryOperator::Subtract: return '-';
            case BinaryOperator::Multiply: return '*';
            case BinaryOperator::Divide: return '/';
            default: return '?';
        }
    }
};

// Program node
class Program : public Node {
public:
    Expression *expression;

    Program(Expression *expression) : expression(expression) {}

    void print() const {
        expression->print();
        std::cout << std::endl;
    }

    std::string toSource() const {
        return expression->toSource();
    }

    ~Program() {
        delete expression;
    }
};

