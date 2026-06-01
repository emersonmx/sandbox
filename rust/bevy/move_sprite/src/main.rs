use bevy::{
    core::FixedTimestep, input::system::exit_on_esc_system, prelude::*, window::PresentMode,
};

const TILE_SIZE: usize = 64;
const TIME_STEP: f32 = 1.0 / 60.0;

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Move Sprite".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            present_mode: PresentMode::Immediate,
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_startup_system(setup)
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIME_STEP as f64))
                .with_system(move_player),
        )
        .add_system(exit_on_esc_system)
        .run();
}

#[derive(Component)]
struct Player {
    speed: f32,
}

fn setup(mut commands: Commands, asset_server: Res<AssetServer>) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());

    for i in -4..=4 {
        for j in -5..=5 {
            commands.spawn_bundle(SpriteBundle {
                texture: asset_server.load("ground/ground_06.png"),
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

    commands
        .spawn_bundle(SpriteBundle {
            texture: asset_server.load("player/face.png"),
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 1.0),
                ..Default::default()
            },
            ..Default::default()
        })
        .insert(Player { speed: 300.0 });
}

fn move_player(input: Res<Input<KeyCode>>, mut query: Query<(&Player, &mut Transform)>) {
    let (player, mut transform) = query.single_mut();
    let mut velocity = Vec3::ZERO;

    velocity.x =
        (input.pressed(KeyCode::Right) as i32 - input.pressed(KeyCode::Left) as i32) as f32;
    velocity.y = (input.pressed(KeyCode::Up) as i32 - input.pressed(KeyCode::Down) as i32) as f32;

    if velocity == Vec3::ZERO {
        return;
    }

    transform.translation += velocity.normalize() * player.speed * TIME_STEP;
}
