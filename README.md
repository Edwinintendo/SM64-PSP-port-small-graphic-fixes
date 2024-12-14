# Super Mario 64 Port

- This repo contains a full decompilation of Super Mario 64 (J), (U), and (E) with minor exceptions in the audio subsystem.
- Naming and documentation of the source code and data structures are in progress.
- Efforts to decompile the Shindou ROM steadily advance toward a matching build.
- Beyond Nintendo 64, it can also target Linux and Windows natively.

This repo does not include all assets necessary for compiling the game.
A prior copy of the game is required to extract the assets.

## Building native executables

### Sony PSP
Notes: Docker desktop is used for this tutorial. Everything is done in Windows, I don't know if it works on other platforms.

**There is a file in the ``psp/`` folder called ``snd_eng.prx``**
- This file is used to accelerate the sound generation and increase performance. 
- It belongs next to the EBOOT.PBP or PRX.

**Fixed textures live in the psp/textures/ folder. copy these into textures/, overwrite the extracted ones, and rebuild**

**Windows Instructions**
1. 1. Install Docker Desktop on your system
2. Place a Super Mario 64 ROM called `baserom.<VERSION>.z64` into the repository's root directory for asset extraction, where `VERSION` can be `us`, `jp`, or `eu`. **Note: Only US supported**
3. Go to the directory where your dockerfile is. You can do it from the Docker Desktop terminal with cd: /path/where/is/the/Dockerfile
**Example: cd/C:\Users\user\Downloads\sm64-port-master**
4. Once you are in the dockerfile path, run the command: docker build . -t sm64_psp 
**(All this in the Docker Desktop terminal)**
5. Now, to compile the game run the following command, (change this path, and put the path where the project is): docker run --rm -v /c/Users/user/Downloads/sm64-port-master: /sm64 sm64 make TARGET_PSP=1 pbp VERSION=us -j4
6. After this, you should start with the compilation, first extracting the game assets, at the end a folder called "build" will appear in the project path, the game will be in: "build\us_psp\mario64".

### Troubleshooting (For Any Platform)

1. If you get `make: gcc: command not found` or `make: gcc: No such file or directory` although the packages did successfully install, you probably launched the wrong MSYS2. Read the instructions again. The terminal prompt should contain "MINGW32" or "MINGW64" in purple text, and **NOT** "MSYS".
2. If you get `Failed to open baserom.us.z64!` you failed to place the baserom in the repository. You can write `ls` to list the files in the current working directory. If you are in the `sm64-port` directory, make sure you see it here.
3. If you get `make: *** No targets specified and no makefile found. Stop.`, you are not in the correct directory. Make sure the yellow text in the terminal ends with `sm64-port`. Use `cd <dir>` to enter the correct directory. If you write `ls` you should see all the project files, including `Makefile` if everything is correct.
4. If you get any error, be sure MSYS2 packages are up to date by executing `pacman -Syu` and `pacman -Su`. If the MSYS2 window closes immediately after opening it, restart your computer.
5. When you execute `gcc -v`, be sure you see `Target: i686-w64-mingw32` or `Target: x86_64-w64-mingw32`. If you see `Target: x86_64-pc-msys`, you either opened the wrong MSYS start menu entry or installed the incorrect gcc package.

## ROM building

It is possible to build N64 ROMs as well with this repository. See https://github.com/n64decomp/sm64 for instructions.

## Project Structure

```
sm64
├── actors: object behaviors, geo layout, and display lists
├── asm: handwritten assembly code, rom header
│   └── non_matchings: asm for non-matching sections
├── assets: animation and demo data
│   ├── anims: animation data
│   └── demos: demo data
├── bin: C files for ordering display lists and textures
├── build: output directory
├── data: behavior scripts, misc. data
├── doxygen: documentation infrastructure
├── enhancements: example source modifications
├── include: header files
├── levels: level scripts, geo layout, and display lists
├── lib: SDK library code
├── rsp: audio and Fast3D RSP assembly code
├── sound: sequences, sound samples, and sound banks
├── src: C source code for game
│   ├── audio: audio code
│   ├── buffers: stacks, heaps, and task buffers
│   ├── engine: script processing engines and utils
│   ├── game: behaviors and rest of game source
│   ├── goddard: Mario intro screen
│   ├── menu: title screen and file, act, and debug level selection menus
│   └── pc: port code, audio and video renderer
├── text: dialog, level names, act names
├── textures: skybox and generic texture data
└── tools: build tools
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to
discuss what you would like to change.

Run `clang-format` on your code to ensure it meets the project's coding standards.
