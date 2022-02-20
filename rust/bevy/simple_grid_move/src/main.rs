use bevy::{input::system::exit_on_esc_system, prelude::*};
use derive_more::{Deref, DerefMut};

const TILE_SIZE: usize = 64;

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Simple Grid Move".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_startup_system(setup)
        .add_system(move_player)
        .add_system(convert_position_to_translation)
        .add_system(exit_on_esc_system)
        .run();
}

#[derive(Component)]
struct Player;

#[derive(Component)]
struct Position {
    x: i32,
    y: i32,
}

#[derive(Component, Deref, DerefMut)]
struct MoveTimer(Timer);

fn setup(mut command: Commands, asset_server: Res<AssetServer>) {
    command.spawn_bundle(OrthographicCameraBundle::new_2d());

    for i in -4..=4 {
        for j in -5..=5 {
            command.spawn_bundle(SpriteBundle {
                texture: asset_server.load("ground.png"),
                transform: Transform {
                    translation: Vec3::new(
                        (TILE_SIZE as i32 * j) as f32,
                        (TILE_SIZE as i32 * i) as f32,
                        0.0,
                    ),
                    ..Default::default()
                },
                ..Default::default()
            });
        }
    }

    command
        .spawn_bundle(SpriteBundle {
            texture: asset_server.load("sprite.png"),
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 1.0),
                ..Default::default()
            },
            ..Default::default()
        })
        .insert(Position { x: 0, y: 0 })
        .insert(MoveTimer(Timer::from_seconds(0.15, true)))
        .insert(Player);
}

fn move_player(
    time: Res<Time>,
    input: Res<Input<KeyCode>>,
    mut query: Query<(&mut Position, &mut MoveTimer), With<Player>>,
) {
    for (mut position, mut move_timer) in query.iter_mut() {
        if !move_timer.tick(time.delta()).just_finished() {
            continue;
        }

        if input.pressed(KeyCode::Left) {
            position.x -= 1;
        }
        if input.pressed(KeyCode::Right) {
            position.x += 1;
        }
        if input.pressed(KeyCode::Up) {
            position.y += 1;
        }
        if input.pressed(KeyCode::Down) {
            position.y -= 1;
        }
    }
}

fn convert_position_to_translation(
    mut query: Query<(&Position, &mut Transform)>,
) {
    for (position, mut transform) in query.iter_mut() {
        transform.translation.x = (position.x * TILE_SIZE as i32) as f32;
        transform.translation.y = (position.y * TILE_SIZE as i32) as f32;
    }
}
