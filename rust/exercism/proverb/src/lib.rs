pub fn build_proverb(list: &[&str]) -> String {
    if list.is_empty() {
        String::new()
    } else {
        list.windows(2)
            .map(|pair| format!("For want of a {} the {} was lost.\n", pair[0], pair[1]))
            .chain(vec![format!("And all for the want of a {}.", list[0])])
            .fold(String::new(), |i, l| format!("{}{}", i, l))
    }
}
