use std::time::Duration;

use bevy::{prelude::*, window::close_on_esc, window::PresentMode};

const TILE_SIZE: usize = 64;
const SPRITESHEET_SIZE: (usize, usize) = (13, 8);

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .add_plugins(
            DefaultPlugins
                .set(WindowPlugin {
                    primary_window: Some(Window {
                        title: "Simple TileMap".to_owned(),
                        resolution: (640.0, 480.0).into(),
                        resizable: false,
                        ..default()
                    }),
                    ..default()
                })
                .set(ImagePlugin::default_nearest()),
        )
        .add_systems(Startup, setup)
        .add_systems(Update, move_player)
        .add_systems(Update, convert_position_to_translation)
        .add_systems(Update, close_on_esc)
        .run();
}

#[derive(Component)]
struct Player;

#[derive(Component)]
struct Position {
    x: i32,
    y: i32,
}

#[derive(Component)]
struct MoveTimer(Timer);

fn setup(
    mut commands: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
) {
    let mut camera = Camera2dBundle::default();
    camera.transform.scale = Vec3::splat(1.5);
    commands.spawn(camera);

    let texture_handle = asset_server.load("tilesheet.png");
    let texture_atlas = TextureAtlas::from_grid(
        texture_handle,
        Vec2::splat(TILE_SIZE as f32),
        SPRITESHEET_SIZE.0,
        SPRITESHEET_SIZE.1,
        None,
        None,
    );
    let tilesheet = texture_atlases.add(texture_atlas);

    for i in -4..=4 {
        for j in -5..=5 {
            commands.spawn(SpriteSheetBundle {
                texture_atlas: tilesheet.clone(),
                sprite: TextureAtlasSprite {
                    index: 89,
                    ..default()
                },
                transform: Transform {
                    translation: Vec3::new(
                        (TILE_SIZE as i32 * j) as f32,
                        (TILE_SIZE as i32 * i) as f32,
                        0.0,
                    ),
                    ..default()
                },
                ..default()
            });

            if i == -4 || i == 4 || j == -5 || j == 5 {
                commands.spawn(SpriteSheetBundle {
                    texture_atlas: tilesheet.clone(),
                    sprite: TextureAtlasSprite {
                        index: 98,
                        ..default()
                    },
                    transform: Transform {
                        translation: Vec3::new(
                            (TILE_SIZE as i32 * j) as f32,
                            (TILE_SIZE as i32 * i) as f32,
                            1.0,
                        ),
                        ..default()
                    },
                    ..default()
                });
            }
        }
    }

    commands
        .spawn(SpriteSheetBundle {
            texture_atlas: tilesheet.clone(),
            sprite: TextureAtlasSprite {
                index: 72,
                ..default()
            },
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 1.0),
                ..default()
            },
            ..default()
        })
        .insert(Position { x: 0, y: 0 })
        .insert(MoveTimer(Timer::new(
            Duration::from_secs_f32(0.15),
            TimerMode::Repeating,
        )))
        .insert(Player);
}

fn move_player(
    time: Res<Time>,
    input: Res<Input<KeyCode>>,
    mut query: Query<(&mut Position, &mut MoveTimer), With<Player>>,
) {
    for (mut position, mut move_timer) in query.iter_mut() {
        move_timer.0.tick(time.delta());
        if !move_timer.0.finished() {
            continue;
        }

        if input.pressed(KeyCode::Left) {
            position.x -= 1;
            move_timer.0.reset();
        }
        if input.pressed(KeyCode::Right) {
            position.x += 1;
            move_timer.0.reset();
        }
        if input.pressed(KeyCode::Up) {
            position.y += 1;
            move_timer.0.reset();
        }
        if input.pressed(KeyCode::Down) {
            position.y -= 1;
            move_timer.0.reset();
        }

        position.x = position.x.clamp(-4, 4);
        position.y = position.y.clamp(-3, 3);
    }
}

fn convert_position_to_translation(mut query: Query<(&Position, &mut Transform)>) {
    for (position, mut transform) in query.iter_mut() {
        transform.translation.x = (position.x * TILE_SIZE as i32) as f32;
        transform.translation.y = (position.y * TILE_SIZE as i32) as f32;
    }
}
