pub fn raindrops(n: u32) -> String {
    let mut result = String::new();
    if n % 3 == 0 {
        result = "Pling".into();
    }
    if n % 5 == 0 {
        result.push_str("Plang".into());
    }
    if n % 7 == 0 {
        result.push_str("Plong".into());
    }
    if result.is_empty() {
        result = n.to_string();
    }

    result
}
