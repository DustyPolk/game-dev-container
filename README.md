# Game Development with Raylib in a Dev Container

This project provides a development environment for creating games using C and C++ with the Raylib library. The setup is designed to be used within a development container, ensuring that all necessary dependencies are installed and configured correctly.

## Getting Started

To get started with this project, follow these steps:

1. **Clone the Repository**:
   Clone this repository to your local machine using the following command:
   ```
   git clone https://github.com/yourusername/game-dev-container.git
   ```

2. **Open in Visual Studio Code**:
   Open the cloned repository in Visual Studio Code. Make sure you have the Remote - Containers extension installed.

3. **Reopen in Container**:
   Once the project is open, you will see a prompt to reopen the folder in a container. Click on "Reopen in Container". This will build the Docker image defined in the `.devcontainer/Dockerfile` and set up the environment.

## Development Environment

The development container is configured with the following:

- **C and C++ Compilers**: The container includes GCC and G++ for compiling C and C++ code.
- **Raylib**: The Raylib library is installed for game development, providing functions for graphics, audio, and input handling.

## Building the Project

To build the project, you can use the provided Makefile. Open a terminal in the container and run the following command:

```
make
```

This will compile the `main.c` file and link it with the Raylib library.

## Running the Game

After building the project, you can run the game using the following command:

```
./main
```

This will execute the compiled game, and you should see a window created by Raylib.

## Additional Information

For more information on Raylib and its features, visit the [Raylib official website](https://www.raylib.com/).

Feel free to modify the source code in the `src` directory to create your own game! Happy coding!