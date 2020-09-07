# Engine Library Strucure

Engine is organized into a serries of subdirectories in an effort to keep the code managable. These directores are:
* Core/ -- contains all of the modules that are central to Engine and that will be included into the client code for direct use.
* Events/ -- contains the code that manages the event system.
* Math/ -- contains usefull math functions (TODO: no longer needed, glm is now used as the math library).
* Platform/ -- contains all of the platform specific code for operating systems and GPU backends.
* Render/ -- contains the rendering engine.
* Util/ -- contains usefull helper functions that are used internally by Engine.
