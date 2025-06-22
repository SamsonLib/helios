#[derive(Debug)]
#[derive(Clone)]
#[derive(PartialEq)]
pub struct Pos(pub i32, pub i32);

impl Pos {
    pub fn new(line: i32, index: i32) -> Pos {
        Pos(line, index)
    }
}