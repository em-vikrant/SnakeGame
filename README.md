# SnakeGame
A retro style snake game written in C++ with the help of raylib.

## Compilation
This project requires statically precompiled **raylib** library in order to build it successfully.  
Before compiling the ***SnakeGame*** repo, clone the raylib from the official _github_ repository [Raylib GitHub](https://github.com/raysan5/raylib)

### On Windows - MingW
Open the cmd  
Goto _src_ dir in the cloned **raylib** repo  

execute the command:
```
mingw32-make -f Makefile all
```

After a while it will get completely build.  
***raylib/src*** directory will have _raylib.h_, _raymath.h_ and _libraylib.a_ files.  
Copy _libraylib.a_ file and paste it at _SnakeGame/lib/_ overwritting pre-existing library over there.  
Similary copy _raylib.h_ and _raymath.h_ and paste them at _SnakeGame/in/_.  

Also, change paths for images in _SnakeGame/inc/app_cfg.h_ file  

Now in **SnakeGame** repo, execute this command to make a build.
```
mingw32-make -f Makefile all
```

Check _SnakeGame/build_ dir to find the game executable.

