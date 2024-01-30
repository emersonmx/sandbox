use bevy::{prelude::*, window::close_on_esc, window::PresentMode};

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(Time::<Fixed>::from_hz(60.0))
        .add_plugins(DefaultPlugins.set(WindowPlugin {
            primary_window: Some(Window {
                title: "Move Square".to_owned(),
                resolution: (640.0, 480.0).into(),
                resizable: false,
                present_mode: PresentMode::Immediate,
                ..default()
            }),
            ..default()
        }))
        .add_systems(Startup, setup)
        .add_systems(FixedUpdate, move_player)
        .add_systems(Update, close_on_esc)
        .run();
}

#[derive(Component)]
struct Player {
    speed: f32,
}

fn setup(mut commands: Commands) {
    commands.spawn(Camera2dBundle::default());

    commands
        .spawn(SpriteBundle {
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 0.0),
                scale: Vec3::new(20.0, 20.0, 0.0),
                ..default()
            },
            sprite: Sprite {
                color: Color::rgb(0.9, 0.9, 0.9),
                ..default()
            },
            ..default()
        })
        .insert(Player { speed: 200.0 });
}

fn move_player(
    input: Res<Input<KeyCode>>,
    fixed_time: Res<Time<Fixed>>,
    mut query: Query<(&Player, &mut Transform)>,
) {
    let delta = fixed_time.delta().as_secs_f32();
    let (player, mut transform) = query.single_mut();
    let mut velocity = Vec3::ZERO;

    velocity.x =
        (input.pressed(KeyCode::Right) as i32 - input.pressed(KeyCode::Left) as i32) as f32;
    velocity.y = (input.pressed(KeyCode::Up) as i32 - input.pressed(KeyCode::Down) as i32) as f32;

    if velocity == Vec3::ZERO {
        return;
    }

    transform.translation += velocity.normalize() * player.speed * delta
}
