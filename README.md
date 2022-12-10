# About
Author: einojo

Title: chess with GTK-3 GUI

This project was started when I took my first C course. I started wirintg the GUI when I wanted to learn about GTK+.
The quality of the code reflects this.

Below is a screenshot of the GUI version in play
![(Screenshot of Chess GUI)](/images/chess.png)

# Dependencies

The project only builds and runs on Linux.

The project depends on GTK-3 to build, on ubuntu the development files for the GTK-3 library can be installed with the following command:

```
sudo apt install libgtk-3-dev
```

In addition to `libgtk-3-dev` the project needs `make` and `gcc` to build.

# How to build

Run `make` in the repository directory, this will produce two binaries. One commandline version of the game `chessCLI` and a GTK-3 GUI version `chessGUI`.

## Windows

For windows the mingw64 cross compiler is needed. Ubuntu does not have mingw64-gtk3 available
so for building for windows I suggest using fedora, where it can be installed with
`sudo dnf install mingw64-gtk3`. 
