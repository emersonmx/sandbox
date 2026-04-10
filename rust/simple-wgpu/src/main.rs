use simple_wgpu::App;
use winit::event_loop::EventLoop;

fn main() -> anyhow::Result<()> {
    let subscriber = tracing_subscriber::FmtSubscriber::builder()
        .with_env_filter(
            tracing_subscriber::EnvFilter::try_from_default_env()
                .unwrap_or_else(|_| "simple_wgpu=info".into()),
        )
        .finish();
    tracing::subscriber::set_global_default(subscriber)?;

    let event_loop = EventLoop::with_user_event().build()?;
    let mut app = App::new(&event_loop);
    event_loop.run_app(&mut app)?;

    Ok(())
}
