use std::time::Duration;
use tokio::time::sleep;

#[tokio::main]
async fn main() {
    println!("Hello");
    sleep(Duration::from_secs(1)).await;
    println!("World");
}
