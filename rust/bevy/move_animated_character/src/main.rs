use bevy::{prelude::*, window::close_on_esc, window::PresentMode};

const TILE_SIZE: usize = 64;
const SPRITESHEET_SIZE: (usize, usize) = (3, 4);

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(Time::<Fixed>::from_hz(60.0))
        .add_plugins(DefaultPlugins.set(WindowPlugin {
            primary_window: Some(Window {
                title: "Move Animated Character".to_string(),
                resolution: (640.0, 480.0).into(),
                resizable: false,
                present_mode: PresentMode::Immediate,
                ..default()
            }),
            ..default()
        }))
        .add_systems(Startup, setup)
        .add_systems(Update, animate_sprite)
        .add_systems(Update, move_player)
        .add_systems(Update, close_on_esc)
        .run();
}

#[derive(Component)]
struct Player;

#[derive(Component, PartialEq, Copy, Clone, Debug)]
enum CharacterState {
    Idle,
    Moving,
}

#[derive(Component, Debug, Deref, DerefMut)]
struct Speed(f32);

#[derive(Component, Debug, Deref, DerefMut)]
struct Velocity(Vec3);

#[derive(Component)]
struct AnimationIndices(usize, usize);

#[derive(Component, Deref, DerefMut)]
struct AnimationTimer(Timer);

fn setup(
    mut commands: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
) {
    let texture_handle = asset_server.load("player/spritesheet.png");
    let texture_atlas = TextureAtlas::from_grid(
        texture_handle,
        Vec2::splat(TILE_SIZE as f32),
        SPRITESHEET_SIZE.0,
        SPRITESHEET_SIZE.1,
        None,
        None,
    );
    let texture_atlas_handle = texture_atlases.add(texture_atlas);
    let animation_indices = AnimationIndices(6, 8);

    commands.spawn(Camera2dBundle::default());

    commands.spawn((
        Player,
        Speed(300.0),
        Velocity(Vec3::ZERO),
        SpriteSheetBundle {
            texture_atlas: texture_atlas_handle,
            sprite: TextureAtlasSprite::new(animation_indices.0),
            transform: Transform::from_translation(Vec3::new(0.0, 0.0, 1.0)),
            ..default()
        },
        animation_indices,
        AnimationTimer(Timer::from_seconds(0.15, TimerMode::Repeating)),
        CharacterState::Idle,
    ));
}

fn animate_sprite(
    time: Res<Time>,
    mut query: Query<(
        &AnimationIndices,
        &mut AnimationTimer,
        &mut TextureAtlasSprite,
        &CharacterState,
    )>,
) {
    for (indices, mut timer, mut sprite, state) in &mut query {
        if state == &CharacterState::Idle {
            sprite.index = indices.0;
            continue;
        }
        timer.tick(time.delta());
        if timer.just_finished() {
            sprite.index = if sprite.index == indices.1 {
                indices.0
            } else {
                sprite.index + 1
            };
        }
    }
}

fn move_player(
    time: Res<Time>,
    input: Res<Input<KeyCode>>,
    mut query: Query<
        (
            &Speed,
            &mut Velocity,
            &mut AnimationIndices,
            &mut TextureAtlasSprite,
            &mut CharacterState,
            &mut Transform,
        ),
        With<Player>,
    >,
) {
    for (speed, mut velocity, mut indicies, mut sprite, mut state, mut transform) in &mut query {
        let up = if input.pressed(KeyCode::Up) {
            1.0
        } else {
            0.0
        };
        let down = if input.pressed(KeyCode::Down) {
            -1.0
        } else {
            0.0
        };
        let left = if input.pressed(KeyCode::Left) {
            -1.0
        } else {
            0.0
        };
        let right = if input.pressed(KeyCode::Right) {
            1.0
        } else {
            0.0
        };
        let x_axis = left + right;
        let y_axis = down + up ;
        let input_velocity = Vec3::new(x_axis, y_axis, 0.0);

        if input.just_pressed(KeyCode::Up) {
            *indicies = AnimationIndices(0, 2);
            sprite.index = indicies.0;
        }

        if input.just_pressed(KeyCode::Down) {
            *indicies = AnimationIndices(6, 8);
            sprite.index = indicies.0;
        }

        if input.just_pressed(KeyCode::Left) {
            *indicies = AnimationIndices(9, 11);
            sprite.index = indicies.0;
        }

        if input.just_pressed(KeyCode::Right) {
            *indicies = AnimationIndices(3, 5);
            sprite.index = indicies.0;
        }

        if input.any_just_released([KeyCode::Up, KeyCode::Down, KeyCode::Left, KeyCode::Right]) {
            velocity.0 = Vec3::ZERO;
        }

        if input_velocity == Vec3::ZERO {
            *state = CharacterState::Idle;
            return;
        }

        velocity.0 = input_velocity;

        *state = CharacterState::Moving;
        transform.translation += velocity.normalize() * speed.0 * time.delta_seconds();
    }
}
