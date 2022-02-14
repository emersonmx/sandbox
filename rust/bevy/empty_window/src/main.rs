use bevy::{prelude::*, input::system::exit_on_esc_system};

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.0, 0.0, 0.0)))
        .insert_resource(WindowDescriptor {
            title: "Empty Window".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_system(exit_on_esc_system)
        .run();
}
