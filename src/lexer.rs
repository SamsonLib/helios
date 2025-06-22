use crate::pos::Pos;
use crate::token::{Token, TokenType};

pub struct Lexer {
    input: String,
    line_pos: i32,
    index_pos: i32,
    read_pos: usize,
    ch: Option<char>,
}

impl Lexer {
    pub fn new(input: String) -> Self {
        let mut lexer = Lexer {
            input,
            line_pos: 0,
            index_pos: 0,
            read_pos: 0,
            ch: None,
        };
        lexer.read_char();
        lexer
    }

    fn read_number(&mut self) -> String {
        let mut number = String::new();

        while let Some(c) = self.ch {
            if c.is_ascii_digit() {
                number.push(c);
                self.read_char();
            } else {
                break;
            }
        }

        number
    }

    fn read_char(&mut self) {
        if self.read_pos >= self.input.len() {
            self.ch = None;
        } else {
            self.ch = self.input[self.read_pos..].chars().next();
        }

        if let Some(ch) = self.ch {
            // Move to next character
            self.read_pos += ch.len_utf8();

            if ch == '\n' {
                self.line_pos += 1;
                self.index_pos = 0;
            } else {
                self.index_pos += 1;
            }
        } else {
            // End of input
            self.read_pos += 1;
        }
    }

    fn next_token(&mut self) -> Token {
        // Skip whitespace
        while let Some(c) = self.ch {
            if c.is_whitespace() && c != '\n' {
                self.read_char();
            } else {
                break;
            }
        }

        let pos = Pos::new(self.line_pos, self.index_pos); // Update position after skipping

        let tok = match self.ch {
            Some(c) if c.is_ascii_digit() => {
                let num = self.read_number();
                return Token::new(TokenType::NumberLiteral, num, pos);
            }
            Some('+') | Some('-') | Some('*') | Some('/') => {
                Token::new(TokenType::Operator, self.ch.unwrap().to_string(), pos)
            }
            Some('(') | Some(')') => {
                Token::new(TokenType::Symbol, self.ch.unwrap().to_string(), pos)
            }
            Some('\n') => Token::new(TokenType::Newline, "\n".to_string(), pos),
            Some(c) => Token::new(TokenType::Identifier, c.to_string(), pos),
            None => Token::new(TokenType::EOF, "".to_string(), pos),
        };

        self.read_char();
        tok
    }


    pub fn tokenize(input: String) -> Vec<Token> {
        let mut lexer = Lexer::new(input);
        let mut tokens = Vec::new();

        loop {
            let tok = lexer.next_token();
            if tok.0 == TokenType::EOF {
                break;
            }
            tokens.push(tok);
        }

        tokens
    }
}
