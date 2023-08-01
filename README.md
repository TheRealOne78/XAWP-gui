<p align="center">
  <img src="./icons/logo_gradient_v2.svg" width="50%">
</p>

# XAWP-gui - **DEPRECATED**

## Deprecation announcement

Because the project advanced a little and so the visions did, XAWP-gui will be merged into [OAWP-gui](https://github.com/OAWP/OAWP-gui.git). This is because OAWP visions X11, Wayland, macOS and Windows support, so making separate basecodes would be burdensome, and continuing this project would make transitioning to OAWP even harder.

The XAWP project will still continue under the [Open Animated Wallpaper Player](https://github.com/OAWP/OAWP.git) (OAWP) with the XAWP codename, along with WAWP, WinAWP and MAWP.

The new repository is available at [https://github.com/OAWP/OAWP-gui.git](https://github.com/OAWP/OAWP-gui.git).

## XAWP-gui

Frontend GUI manager for the XAWP animated wallpaper player.

Written in C with the GTK+ toolkit.

## TODO:
* [X] Create a basic GTK UI
* [ ] Add a fancy history list in the start menu with image preview and options
* [X] Create a [SVG logo](./icons/logo_gradient_v2.svg) with X derived from the [Xorg/X11 logo](https://www.x.org/wiki/)
* [ ] Get values from config file with libconfig
* [ ] Write configuration text with the C file stream
* [ ] Check for versions of configurations file and update them if needed, with a user prompt
* [ ] Implement an image converting system with the [MagickWand API](https://imagemagick.org/script/magick-wand.php)
* [ ] Link everything else to propper callback functions
* [ ] Add verbose and concise error popups
* [ ] Write the _rest_ of the program :D

## Wiki
Get help from the [wiki](https://github.com/TheRealOne78/XAWP/wiki)!

## Quick note!
Work in progress, not even alpha state.
