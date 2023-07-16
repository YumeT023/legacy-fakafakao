#ifndef CLITA_PARSER_H
#define CLITA_PARSER_H

#include "lexer.h"

typedef enum {
    SymbolDeclaration,
    SymbolAssignment,
    SymbolLiteral,
    NumericLiteral,
    BinaryExpr,
    UnaryExpr,
} NodeType;

typedef struct {
    NodeType type;
    char *name;
} SymbolLiteralNode;


typedef struct {
    NodeType type;
    int value;
} NumericLiteralNode;

typedef struct {
    NodeType type;
    NumericLiteralNode *left;
    char *op;// + , - , * , /, <, >, <=, >=
    NumericLiteralNode *right;
} BinaryExprNode;

typedef struct {
    NodeType type;
    char op; // '-'
    NumericLiteralNode *expr;
} UnaryExprNode;

typedef union {
    SymbolLiteralNode symbolLiteralNode;
    NumericLiteralNode numericLiteralNode;
    BinaryExprNode binaryExprNode;
    UnaryExprNode unaryExprNode;
} Expression;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *initialValue;
} SymbolDeclarationNode;

typedef struct {
    NodeType type;
    SymbolLiteralNode *identifier;
    NumericLiteralNode *value;
} SymbolAssignmentNode;

typedef struct {
    Token *tokens;
    size_t tokens_len;
    size_t pos;
} Parser;

Parser create_parser(size_t initial_capacity);

Token *consume(Parser *p);
Token *p_peek(Parser *p);

SymbolDeclarationNode *parse_symbol_declaration(Parser *p);
SymbolAssignmentNode *parse_symbol_assignment(Parser *p);
SymbolLiteralNode *parse_symbol_literal(Parser *p);
NumericLiteralNode *parse_numeric_literal(Parser *p);
BinaryExprNode *parse_binary_expr(Parser *p);
UnaryExprNode *parse_unary_expr(Parser *p);

#endif//CLITA_PARSER_H
