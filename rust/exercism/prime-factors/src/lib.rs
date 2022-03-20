pub fn factors(n: u64) -> Vec<u64> {
    Vec::new()
}

fn is_prime(n: u64) -> bool {
    let limit = (n as f64).sqrt() as u64;

    for i in 2..=limit {
        if n % i == 0 {
            return false;
        }
    }

    true
}
