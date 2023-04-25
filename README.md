# About
Author: einojo

Title: chess with GTK-4 GUI

This project was started when I took my first C course. I started wirintg the GUI when I wanted to learn about GTK+.
The quality of the code reflects this.

Below is a screenshot of the GUI version in play
![(Screenshot of Chess GUI)](/images/chess.png)

# Dependencies

The project only builds and runs on Linux.

The project depends on GTK-4 to build, on ubuntu the development files for the GTK-4 library can be installed with the following command:

```
sudo apt install libgtk-4-dev
```

In addition to `libgtk-4-dev` the project needs `make` and `gcc` to build.

# How to build

Run `make` in the repository directory, this will produce two binaries. One commandline version of the game `chessCLI` and a GTK-4 GUI version `chessGUI`.

# GTK-3

If you want to build with GTK-3, checkout tag `0.1.0`.
