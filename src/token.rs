use crate::pos::Pos;

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Clone)]
pub enum TokenType {
    Identifier,
    NumberLiteral,
    Operator,
    Symbol,
    Newline,
    EOF
}

#[derive(Debug)]
#[derive(PartialEq)]
#[derive(Clone)]
pub struct Token(pub TokenType, pub String, pub Pos);

impl Token {
    pub fn new(token_type: TokenType, value: String, pos: Pos) -> Token {
        Token(token_type, value, pos)
    }
}