use bevy::{prelude::*, window::WindowResolution};

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::linear_rgb(0.0, 0.0, 0.0)))
        .add_plugins(DefaultPlugins.set(WindowPlugin {
            primary_window: Some(Window {
                title: "Empty Window".to_owned(),
                resolution: WindowResolution::new(640, 480),
                resizable: false,
                ..default()
            }),
            ..default()
        }))
        .run();
}
