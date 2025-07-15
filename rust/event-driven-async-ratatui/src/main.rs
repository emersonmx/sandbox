mod app;
mod events;

use crate::app::App;

#[tokio::main]
async fn main() -> anyhow::Result<()> {
    let terminal = ratatui::init();
    let result = App::default().run(terminal).await;
    ratatui::restore();
    result
}
