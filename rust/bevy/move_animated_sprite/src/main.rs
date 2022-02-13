use bevy::{
    core::FixedTimestep, input::system::exit_on_esc_system, prelude::*,
};

const TIME_STEP: f32 = 1.0 / 60.0;

#[derive(Component, Debug)]
struct Player;

#[derive(Component, Debug)]
struct Speed(f32);

#[derive(Component, Debug)]
enum Direction {
    Up,
    Right,
    Down,
    Left,
}

#[derive(Component)]
struct AnimationTimer(Timer);

fn setup_camera(mut command: Commands) {
    command.spawn_bundle(OrthographicCameraBundle::new_2d());
}

fn setup_player(
    mut command: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
) {
    let texture_handle = asset_server.load("player/spritesheet.png");
    let texture_atlas =
        TextureAtlas::from_grid(texture_handle, Vec2::new(64.0, 64.0), 3, 4);
    let texture_atlas_handle = texture_atlases.add(texture_atlas);
    command
        .spawn_bundle(SpriteSheetBundle {
            texture_atlas: texture_atlas_handle,
            transform: Transform {
                translation: Vec3::new(0.0, 0.0, 0.0),
                ..Default::default()
            },
            ..Default::default()
        })
        .insert(Player)
        .insert(Speed { 0: 300.0 })
        .insert(Direction::Down)
        .insert(AnimationTimer(Timer::from_seconds(0.1, true)));
}

fn move_player(
    input: Res<Input<KeyCode>>,
    mut query: Query<(&Speed, &mut Direction, &mut Transform), With<Player>>,
) {
    let (speed, mut direction, mut transform) = query.single_mut();
    let mut velocity = Vec3::ZERO;

    if input.pressed(KeyCode::Up) {
        velocity.y += 1.0;
        *direction = Direction::Up;
    }
    if input.pressed(KeyCode::Right) {
        velocity.x += 1.0;
        *direction = Direction::Right;
    }
    if input.pressed(KeyCode::Down) {
        velocity.y -= 1.0;
        *direction = Direction::Down;
    }
    if input.pressed(KeyCode::Left) {
        velocity.x -= 1.0;
        *direction = Direction::Left;
    }

    if velocity == Vec3::ZERO {
        return;
    }

    transform.translation += velocity.normalize() * speed.0 * TIME_STEP;
}

fn update_player_sprite(
    time: Res<Time>,
    texture_atlases: Res<Assets<TextureAtlas>>,
    mut query: Query<(
        &Direction,
        &Speed,
        &mut AnimationTimer,
        &mut TextureAtlasSprite,
        &Handle<TextureAtlas>,
    )>,
) {
    for (direction, speed, mut timer, mut sprite, texture_atlas_handle) in
        query.iter_mut()
    {
        timer.0.tick(time.delta());
        if timer.0.just_finished() {
            let texture_atlas =
                texture_atlases.get(texture_atlas_handle).unwrap();
            sprite.index = (sprite.index + 1) % texture_atlas.textures.len();
        }
    }
}

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Hello Sprite".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            vsync: true,
            ..Default::default()
        })
        .add_plugins(DefaultPlugins)
        .add_startup_system(setup_camera)
        .add_startup_system(setup_player)
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIME_STEP as f64))
                .with_system(move_player),
        )
        .add_system(update_player_sprite)
        .add_system(exit_on_esc_system)
        .run();
}
