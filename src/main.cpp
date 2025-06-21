#include "AST.cpp"

// Compiler class
class Compiler {
public:
    void compile(Program *program) {
        std::cout << "// Generated Source Code" << std::endl;
        std::cout << program->toSource() << std::endl;
    }
};

// Example usage
int main() {
    Program *program = new Program(
        new AssignmentExpression(
            "result",
            new BinaryExpression(
                new NumberExpression(10),
                BinaryOperator::Multiply,
                new BinaryExpression(
                    new VariableExpression("x"),
                    BinaryOperator::Add,
                    new NumberExpression(3)
                )
            )
        )
    );
    program->print();

    Compiler compiler;
    compiler.compile(program);

    delete program;

    return 0;
}