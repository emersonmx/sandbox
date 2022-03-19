use bevy::{input::system::exit_on_esc_system, prelude::*};
use derive_more::{Deref, DerefMut};

const TILE_SIZE: usize = 64;
const SPRITESHEET_SIZE: (usize, usize) = (13, 8);

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Simple TileMap".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            ..Default::default()
        })
        .init_resource::<Handle<TextureAtlas>>()
        .add_plugins(DefaultPlugins)
        .add_startup_system_to_stage(StartupStage::PreStartup, setup_tilesheet)
        .add_startup_system(setup_camera)
        .add_startup_system(setup_map)
        .add_startup_system(setup_player)
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

fn setup_tilesheet(
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
    mut tilesheet: ResMut<Handle<TextureAtlas>>,
) {
    let texture_handle = asset_server.load("tilesheet.png");
    let texture_atlas = TextureAtlas::from_grid(
        texture_handle,
        Vec2::splat(TILE_SIZE as f32),
        SPRITESHEET_SIZE.0,
        SPRITESHEET_SIZE.1,
    );
    *tilesheet = texture_atlases.add(texture_atlas);
}

fn setup_camera(mut commands: Commands) {
    let mut camera = OrthographicCameraBundle::new_2d();
    camera.transform.scale = Vec3::splat(1.5);
    commands.spawn_bundle(camera);
}

fn setup_map(mut commands: Commands, tilesheet: Res<Handle<TextureAtlas>>) {
    for i in -4..=4 {
        for j in -5..=5 {
            commands.spawn_bundle(SpriteSheetBundle {
                texture_atlas: tilesheet.clone(),
                sprite: TextureAtlasSprite {
                    index: 89,
                    ..Default::default()
                },
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

            if i == -4 || i == 4 || j == -5 || j == 5 {
                commands.spawn_bundle(SpriteSheetBundle {
                    texture_atlas: tilesheet.clone(),
                    sprite: TextureAtlasSprite {
                        index: 98,
                        ..Default::default()
                    },
                    transform: Transform {
                        translation: Vec3::new(
                            (TILE_SIZE as i32 * j) as f32,
                            (TILE_SIZE as i32 * i) as f32,
                            1.0,
                        ),
                        ..Default::default()
                    },
                    ..Default::default()
                });
            }
        }
    }
}

fn setup_player(mut commands: Commands, tilesheet: Res<Handle<TextureAtlas>>) {
    commands
        .spawn_bundle(SpriteSheetBundle {
            texture_atlas: tilesheet.clone(),
            sprite: TextureAtlasSprite {
                index: 72,
                ..Default::default()
            },
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 1.0),
                ..Default::default()
            },
            ..Default::default()
        })
        .insert(Position { x: 0, y: 0 })
        .insert(MoveTimer(Timer::from_seconds(0.15, false)))
        .insert(Player);
}

fn move_player(
    time: Res<Time>,
    input: Res<Input<KeyCode>>,
    mut query: Query<(&mut Position, &mut MoveTimer), With<Player>>,
) {
    for (mut position, mut move_timer) in query.iter_mut() {
        move_timer.tick(time.delta());
        if !move_timer.finished() {
            continue;
        }

        if input.pressed(KeyCode::Left) {
            position.x -= 1;
            move_timer.reset();
        }
        if input.pressed(KeyCode::Right) {
            position.x += 1;
            move_timer.reset();
        }
        if input.pressed(KeyCode::Up) {
            position.y += 1;
            move_timer.reset();
        }
        if input.pressed(KeyCode::Down) {
            position.y -= 1;
            move_timer.reset();
        }

        position.x = position.x.clamp(-4, 4);
        position.y = position.y.clamp(-3, 3);
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
