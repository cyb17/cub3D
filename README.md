# cub3D

`cub3D` is a small first-person maze renderer written in C for the 42
curriculum. Inspired by the early _Wolfenstein 3D_ engine, it uses raycasting
and MiniLibX to turn a two-dimensional map into a textured 3D scene.

![cub3D demo](./cub3D.gif)

## Features

- DDA-based raycasting rendered one screen column at a time
- Direction-specific wall textures
- Configurable floor and ceiling colors
- Player movement, strafing, rotation, and wall collision
- Strict `.cub` configuration and map validation
- Clean shutdown with `Esc` or the window close button
- Bonus minimap
- Bonus interactive doors with open and closed textures

## Dependencies

This repository includes the Linux/X11 version of MiniLibX and targets Linux.
It requires a C compiler, Make, X11 development headers, Xext, BSD development
utilities, and zlib.

Debian / Ubuntu:

```bash
sudo apt update
sudo apt install build-essential xorg libx11-dev libxext-dev libbsd-dev zlib1g-dev
```

Fedora:

```bash
sudo dnf group install "Development Tools"
sudo dnf install libX11-devel libXext-devel libbsd-devel zlib-devel
```

Arch Linux:

```bash
sudo pacman -S base-devel libx11 libxext libbsd zlib
```

An active graphical X11 session is required to open the game window.

### macOS

The included `mlx_linux` library and Makefile do not target native macOS. The
recommended approach is to run the project in a Linux desktop virtual machine:

1. Create an Ubuntu or another Linux desktop virtual machine.
2. Install the Linux dependencies listed above.
3. Copy or share the repository with the virtual machine.
4. Build and run the project from the virtual machine's graphical session.

## Build

Build the mandatory version:

```bash
make
```

Build the bonus version:

```bash
make bonus
```

Available Make targets:

```bash
make          # Build the mandatory executable
make bonus    # Build the bonus executable
make clean    # Remove object files
make fclean   # Remove object files and executables
make re       # Rebuild the mandatory version
```

## Run

Run the mandatory version with a `.cub` scene file:

```bash
./cub3D map.cub
```

Run the bonus version:

```bash
./cub3D_bonus map.cub
```

## Controls

| Key           | Action        |
| ------------- | ------------- |
| `W`           | Move forward  |
| `S`           | Move backward |
| `A`           | Strafe left   |
| `D`           | Strafe right  |
| `Left Arrow`  | Rotate left   |
| `Right Arrow` | Rotate right  |
| `Esc`         | Quit          |

Bonus controls:

| Key     | Action                                        |
| ------- | --------------------------------------------- |
| `M`     | Toggle the minimap                            |
| `Space` | Open or close the door in front of the player |

## Scene format

The program accepts one `.cub` file containing texture paths, floor and ceiling
colors, and a map.

```text
N ./textures/north.xpm
S ./textures/south.xpm
W ./textures/west.xpm
E ./textures/east.xpm
C 0,76,153
F 96,96,96

111111111
100000001
100010001
10N000001
111111111
```

Configuration identifiers:

| Identifier | Meaning                   |
| ---------- | ------------------------- |
| `N`        | North-facing wall texture |
| `S`        | South-facing wall texture |
| `W`        | West-facing wall texture  |
| `E`        | East-facing wall texture  |
| `C`        | Ceiling RGB color         |
| `F`        | Floor RGB color           |

Map characters:

| Character          | Meaning                             |
| ------------------ | ----------------------------------- |
| `1`                | Wall                                |
| `0`                | Walkable floor                      |
| `N`, `S`, `E`, `W` | Player start and initial direction  |
| Space              | Empty area outside the playable map |
| `2`                | Open door in the bonus version      |
| `3`                | Closed door in the bonus version    |

A valid map must:

- Be enclosed by walls
- Contain exactly one player start
- Use only supported map characters
- Keep walkable tiles separated from exterior spaces
- Avoid tab characters in the map section
- Place all six configuration elements before the map
- Use RGB components between `0` and `255`

## How it works

For every vertical screen column, the engine:

1. Calculates a ray direction from the player and camera plane.
2. Uses DDA to advance through the grid until a wall or door is hit.
3. Computes the perpendicular wall distance to avoid fisheye distortion.
4. Selects the texture associated with the wall direction.
5. Samples a vertical texture column and writes it to the image buffer.
6. Draws the configured ceiling and floor colors around the wall slice.

## Project structure

```text
.
├── bonus/        Bonus renderer, minimap, and door interaction
├── includes/     Mandatory and bonus headers
├── libft/        Custom C utility library
├── mandatory/    Parser, raycaster, rendering, and input handling
├── mlx_linux/    MiniLibX for Linux/X11
├── textures/     Wall and door XPM textures
├── big_map.cub   Additional example scene
├── map.cub       Default example scene
└── Makefile
```
