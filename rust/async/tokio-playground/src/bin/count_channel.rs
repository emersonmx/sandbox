use std::time::Duration;
use tokio::{sync::mpsc, time::sleep};

#[tokio::main]
async fn main() {
    let (tx, mut rx) = mpsc::channel(8);

    let producer = tokio::spawn(async move {
        for i in 0..100 {
            let tx = tx.clone();
            tokio::spawn(async move {
                sleep(Duration::from_millis((i % 5 + 1) * 500)).await;
                tx.send(format!("task {i} done.")).await.unwrap();
            });
        }
    });

    let consumer = tokio::spawn(async move {
        while let Some(res) = rx.recv().await {
            println!("{res}");
        }
    });

    let _ = tokio::join!(producer, consumer);
}
