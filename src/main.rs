mod lexer;
mod pos;
mod token;

use std::fs;

use lexer::Lexer;

fn main() {
    println!("{:#?}",
        Lexer::tokenize(
            fs::read_to_string("input.txt").unwrap()
        )
    );
}