# Cube3D - Raycasting 3D Maze Viewer

## Project Description

Cube3D is a program that implements a 3D maze viewer using raycasting. It simulates the inside of a maze from a first-person perspective with realistic wall textures and smooth user movement controls. The program was developed using **MLX42** (instead of MinilibX) and loads maps in the `.cub` format.

### Key Features:
- **Raycasting** for 3D maze visualization.
- Smooth window management (resize, minimize, etc.).
- Support for **multiple wall textures** (North, South, East, West) and customizable **floor/ceiling colors**.
- Keyboard controls for navigation:
  - Arrow keys: Look left and right.
  - W, A, S, D: Move forward, backward, and strafe.
  - ESC or window close: Exit the program cleanly.

### Requirements:
- **.cub** file for maze and scene configuration.
- Textures for walls (North, South, East, West).
- Floor and ceiling color definitions.
- The map must be closed by walls, and the player must have a valid spawn position (N, S, E, W).

---

## How to Build and Run

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/Cube3D.git
   cd Cube3D

2. **Build the project:**
    make
3. **Test the project:**
    bash ./tester.sh
4. **Play the game:**
    ./Cub3D maps/valid_maps/official_map.cub
