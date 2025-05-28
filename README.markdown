# NexusPulse: A 2D Rhythm-Based Strategy Game

## Overview
NexusPulse is a unique 2D strategy game built in C++ using the SFML library. Players place energy pulses on a grid to align with rhythmic beats, activating nodes to clear levels. The game blends rhythm-based timing with strategic placement, creating a novel experience distinct from traditional rhythm or puzzle games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, rhythm mechanics, and strategic gameplay. By sponsoring NexusPulse via GitHub Sponsors, you support new features, level designs, and educational content for the community.

## Features
- **Rhythm-Based Gameplay**: Place pulses to match beat patterns and activate grid nodes.
- **Strategic Grid System**: Plan pulse placements to optimize node activation chains.
- **Minimalist Visuals**: Clean 2D graphics with dynamic pulse animations.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Extensible Codebase**: Modular C++ design for easy feature additions.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/nexuspulse.git
   cd nexuspulse
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./NexusPulse
   ```

## Gameplay
- **Objective**: Activate all nodes on the grid by placing energy pulses that align with the beat.
- **Controls**:
  - **Arrow Keys**: Navigate the grid cursor.
  - **Space**: Place an energy pulse.
  - **Enter**: Start/stop the rhythm cycle.
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Pulses emit energy waves in sync with a rhythmic beat. Strategically place pulses to hit nodes at the right time, chaining activations for higher scores.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (pulses, nodes).
- `src/Game.hpp`: Core game logic, rhythm system, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support NexusPulse’s development through [GitHub Sponsors](https://github.com/sponsors/samdshaba)! Your contributions fund:
- New rhythm patterns and levels.
- Advanced AI for dynamic beat generation.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by rhythm games and strategic grid-based puzzles.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor NexusPulse to power up innovative gameplay and learning!**
