use bevy::{input::system::exit_on_esc_system, prelude::*};

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Simple Mouse Grab".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            vsync: true,
            ..Default::default()
        })
        .init_resource::<CursorState>()
        .add_plugins(DefaultPlugins)
        .add_system(toggle_grab)
        .add_system(exit_on_esc_system)
        .run();
}

struct CursorState {
    visible: bool,
    grab: bool,
}

impl Default for CursorState {
    fn default() -> Self {
        Self {
            visible: true,
            grab: false,
        }
    }
}

fn toggle_grab(
    input: Res<Input<KeyCode>>,
    mut windows: ResMut<Windows>,
    mut cursor_state: ResMut<CursorState>,
) {
    let window = windows.get_primary_mut().unwrap();
    if input.just_pressed(KeyCode::V) {
        cursor_state.visible = !cursor_state.visible;
        window.set_cursor_visibility(cursor_state.visible);
    }
    if input.just_pressed(KeyCode::G) {
        cursor_state.grab = !cursor_state.grab;
        window.set_cursor_lock_mode(cursor_state.grab);
    }
}
