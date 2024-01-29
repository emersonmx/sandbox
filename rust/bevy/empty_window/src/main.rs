use bevy::{prelude::*, window::close_on_esc};

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.0, 0.0, 0.0)))
        .add_plugins(DefaultPlugins.set(WindowPlugin {
            primary_window: Some(Window {
                title: "Empty Window".to_owned(),
                resolution: (640.0, 480.0).into(),
                resizable: false,
                ..default()
            }),
            ..default()
        }))
        .add_systems(Update, close_on_esc)
        .run();
}
