use std::time::Duration;

use benimator::{AnimationPlugin, Play, SpriteSheetAnimation};
use bevy::{
    core::FixedTimestep, input::system::exit_on_esc_system, prelude::*,
};

const TIME_STEP: f32 = 1.0 / 60.0;
const SPRITESHEET_SIZE: (usize, usize) = (3, 4);

fn main() {
    App::new()
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .insert_resource(WindowDescriptor {
            title: "Move Animated Character".to_string(),
            width: 640.0,
            height: 480.0,
            resizable: false,
            ..Default::default()
        })
        .init_resource::<PlayerAnimations>()
        .add_plugins(DefaultPlugins)
        .add_plugin(AnimationPlugin::default())
        .add_startup_system_to_stage(
            StartupStage::PreStartup,
            create_player_animations,
        )
        .add_startup_system(setup_camera)
        .add_startup_system(setup_player)
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIME_STEP as f64))
                .with_system(move_player),
        )
        .add_system(change_animation)
        .add_system(exit_on_esc_system)
        .run();
}

#[derive(Component, Debug)]
struct Player;

#[derive(Component, PartialEq, Copy, Clone, Debug)]
enum CharacterState {
    Idle,
    Moving,
}

#[derive(Component, Debug)]
struct Speed(f32);

#[derive(Component, Copy, Clone, Debug)]
enum Direction {
    Up,
    Right,
    Down,
    Left,
}

#[derive(Default)]
struct PlayerAnimations {
    up: Handle<SpriteSheetAnimation>,
    right: Handle<SpriteSheetAnimation>,
    down: Handle<SpriteSheetAnimation>,
    left: Handle<SpriteSheetAnimation>,
}

#[derive(Bundle)]
struct PlayerBundle {
    speed: Speed,
    character_state: CharacterState,
    direction: Direction,
    _p: Player,

    animation: Handle<SpriteSheetAnimation>,

    #[bundle]
    spritesheet: SpriteSheetBundle,
}

fn create_player_animations(
    mut animations: ResMut<PlayerAnimations>,
    mut assets: ResMut<Assets<SpriteSheetAnimation>>,
) {
    animations.up = assets.add(SpriteSheetAnimation::from_range(
        0..=2,
        Duration::from_millis(150),
    ));
    animations.right = assets.add(SpriteSheetAnimation::from_range(
        3..=5,
        Duration::from_millis(150),
    ));
    animations.down = assets.add(SpriteSheetAnimation::from_range(
        6..=8,
        Duration::from_millis(150),
    ));
    animations.left = assets.add(SpriteSheetAnimation::from_range(
        9..=11,
        Duration::from_millis(150),
    ));
}

fn setup_camera(mut command: Commands) {
    command.spawn_bundle(OrthographicCameraBundle::new_2d());
}

fn setup_player(
    mut command: Commands,
    asset_server: Res<AssetServer>,
    mut texture_atlases: ResMut<Assets<TextureAtlas>>,
    animations: ResMut<PlayerAnimations>,
) {
    let texture_handle = asset_server.load("player/spritesheet.png");
    let texture_atlas = TextureAtlas::from_grid(
        texture_handle,
        Vec2::splat(64.0),
        SPRITESHEET_SIZE.0,
        SPRITESHEET_SIZE.1,
    );
    let texture_atlas_handle = texture_atlases.add(texture_atlas);

    command.spawn_bundle(PlayerBundle {
        speed: Speed(300.0),
        character_state: CharacterState::Idle,
        direction: Direction::Down,
        _p: Player,
        animation: animations.down.clone(),
        spritesheet: SpriteSheetBundle {
            texture_atlas: texture_atlas_handle,
            ..Default::default()
        },
    });
}

fn move_player(
    input: Res<Input<KeyCode>>,
    mut query: Query<
        (&Speed, &mut CharacterState, &mut Direction, &mut Transform),
        With<Player>,
    >,
) {
    for (&Speed(speed), mut state, mut direction, mut transform) in
        query.iter_mut()
    {
        let mut velocity = Vec3::ZERO;

        if input.pressed(KeyCode::Left) {
            velocity.x -= 1.0;
            *direction = Direction::Left;
        }
        if input.pressed(KeyCode::Right) {
            velocity.x += 1.0;
            *direction = Direction::Right;
        }
        if input.pressed(KeyCode::Up) {
            velocity.y += 1.0;
            *direction = Direction::Up;
        }
        if input.pressed(KeyCode::Down) {
            velocity.y -= 1.0;
            *direction = Direction::Down;
        }

        if velocity == Vec3::ZERO {
            *state = CharacterState::Idle;
            return;
        }

        *state = CharacterState::Moving;
        transform.translation += velocity.normalize() * speed * TIME_STEP;
    }
}

fn change_animation(
    mut command: Commands,
    animations: Res<PlayerAnimations>,
    mut query: Query<(
        Entity,
        &Direction,
        &CharacterState,
        &mut TextureAtlasSprite,
        &mut Handle<SpriteSheetAnimation>,
    )>,
) {
    for (entity, direction, character_state, mut sprite, mut animation) in
        query.iter_mut()
    {
        let row = *direction as usize;

        if *character_state == CharacterState::Idle {
            sprite.index = row * SPRITESHEET_SIZE.0;
            command.entity(entity).remove::<Play>();
            continue;
        }

        command.entity(entity).insert(Play);

        *animation = match direction {
            Direction::Up => animations.up.clone(),
            Direction::Right => animations.right.clone(),
            Direction::Down => animations.down.clone(),
            Direction::Left => animations.left.clone(),
        }
    }
}
