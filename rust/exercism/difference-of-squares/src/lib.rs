pub fn square_of_sum(n: u32) -> u32 {
    let nums: u32 = (1..=n).sum();
    nums * nums
}

pub fn sum_of_squares(n: u32) -> u32 {
    (1..=n).map(|i| i * i).sum()
}

pub fn difference(n: u32) -> u32 {
    square_of_sum(n) - sum_of_squares(n)
}
