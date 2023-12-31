#ifndef CLITA_PARSER_H
#define CLITA_PARSER_H

#include "lexer.h"

typedef enum {
    Program,
    SymbolDeclaration,
    SymbolAssignment,
    BlockStatement,
    SymbolLiteral,
    NumericLiteral,
    BooleanLiteral,
    BinaryExpr,    // kajy
    ComparisonExpr,// vina
    UnaryExpr,
    Pragma
} NodeType;

typedef struct ProgramNode ProgramNode;
typedef struct SymbolDeclarationNode SymbolDeclarationNode;
typedef struct SymbolAssignmentNode SymbolAssignmentNode;
typedef struct Block Block;
typedef struct Statement Statement;
typedef struct Expression Expression;
typedef struct LiteralExpr LiteralExpr;
typedef struct BinaryExprNode BinaryExprNode;
typedef struct UnaryExprNode UnaryExprNode;
typedef struct ComparisonExprNode ComparisonExprNode;
typedef struct NumericLiteralNode NumericLiteralNode;
typedef struct BooleanLiteralNode BooleanLiteralNode;
typedef struct SymbolLiteralNode SymbolLiteralNode;
typedef struct PragmaNode PragmaNode;

struct SymbolLiteralNode {
    NodeType type;
    char *name;
};

struct BooleanLiteralNode {
    NodeType type;
    bool value;
};

struct NumericLiteralNode {
    NodeType type;
    int value;
};

struct BinaryExprNode {
    NodeType type;
    LiteralExpr *left;
    char *op;// + , - , * , /
    Expression *right;
};

struct ComparisonExprNode {
    NodeType type;
    NumericLiteralNode *left;
    char *op;// <, <=, >, >=, =
    NumericLiteralNode *right;
};

struct UnaryExprNode {
    NodeType type;
    char *op;// '-', '--', '++'
    LiteralExpr *expr;
};

struct SymbolDeclarationNode {
    NodeType type;
    SymbolLiteralNode *identifier;
    Expression *init;
};

struct SymbolAssignmentNode {
    NodeType type;
    SymbolLiteralNode *identifier;
    Expression *val;
};

struct PragmaNode {
    NodeType type;
    char *name;
    NumericLiteralNode *argument;
};

struct LiteralExpr {
    NodeType type;
    union {
        NumericLiteralNode numericLiteral;
        SymbolLiteralNode symbolLiteral;
        BooleanLiteralNode booleanLiteral;
    };
};

struct Expression {
    NodeType type;
    union {
        BinaryExprNode binaryExpr;
        UnaryExprNode unaryExpr;
        LiteralExpr literalExpr;
    };
};

struct Statement {
    NodeType type;
    union {
        SymbolDeclarationNode symbolDeclaration;
        SymbolAssignmentNode symbolAssignment;
    };
};

struct Block {
    NodeType type;
    Statement *statements;
    size_t stmt_c;
};

struct ProgramNode {
    NodeType type;
};

typedef struct {
    Token *tokens;
    size_t tokens_len;
    size_t pos;
} Parser;

Parser create_parser(Lexer *l);

Token *consume(Parser *p);
Token *p_peek(Parser *p);
void consume_dot(Parser *p);

/**
 * (Backtracking)
 * look forward nth token.
 * Primarily used to test different rules of a same production.
 *
 * When analyzing data such as "2 + 3", it is important to search for a possible token after the `numeric` when trying to determine its meaning.
 * we should parse a `BinaryExpression` if it's an operator token, else a `NumericLiteral`
 */
Token *look_ahead(Parser *p, size_t n);

// Todo: ASTNodes printer (visitor)
// Todo: extract parser utils such as 'expect' along with their err message

SymbolDeclarationNode *parse_symbol_declaration(Parser *p);
SymbolAssignmentNode *parse_symbol_assignment(Parser *p);
PragmaNode *parse_pragma(Parser *p);
Statement *parse_statement(Parser *p);
Block *parse_block(Parser *p);

SymbolLiteralNode *parse_symbol_literal(Parser *p);
NumericLiteralNode *parse_numeric_literal(Parser *p);
BooleanLiteralNode *parse_boolean_literal(Parser *p);
ComparisonExprNode *parse_comparison_expr(Parser *p);
BinaryExprNode *parse_binary_expr(Parser *p);
UnaryExprNode *parse_unary_expr(Parser *p);
LiteralExpr *parse_literal_expr(Parser *p);
Expression *parse_expression(Parser *p);

ProgramNode parse(char *source_text);

#endif//CLITA_PARSER_H
