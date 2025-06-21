#include <iostream>

class Node {
public:
    virtual ~Node() = default;
};

class Expression : public Node {
public:
    virtual void print() const = 0;  // For demonstration
};

// Numeric literal expression
class NumberExpression : public Expression {
public:
    double value;

    NumberExpression(double value) : value(value) {}

    void print() const override {
        std::cout << value;
    }
};

class VariableExpression : public Expression {
public:
    const char* name;

    VariableExpression(const char* name) : name(name) {}

    void print() const override {
        std::cout << name;
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
};

// Example usage
int main() {
    Program *program = new Program(
        new BinaryExpression(
            new NumberExpression(5),
            BinaryOperator::Multiply,
            new BinaryExpression(
                new NumberExpression(2),
                BinaryOperator::Add,
                new VariableExpression("x")
            )
        )
    );
    program->print();

    delete program;

    return 0;
}
