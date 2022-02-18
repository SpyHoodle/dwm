# perfectwm
My perfect build of suckless's dynamic window manager.

![perfectwm screenshot](https://file.coffee/u/Q40wCAOgRCEoOE.png)

# patches
- dwm-6.2-urg-border.diff
- dwm-alwayscenter-20200625-f04cac6.diff
- dwm-attachbottom-6.2.diff
- dwm-fancybar-20200423-ed3ab6b.diff
- dwm-movestack-20211115-a786211.diff
- dwm-pertag-20200914-61bb8b2.diff
- dwm-restartsig-20180523-6.2.diff
- dwm-status2d-6.3.diff
- dwm-statusallmons-6.2.diff
- dwm-sticky-6.1.diff
- dwm-stickyindicator-fancybarfix-6.2.diff
- dwm-swallow-20201211-61bb8b2.diff
- dwm-uselessgap-20211119-58414bee958f2.diff
- dwm-warp-6.2.diff

# programs
Some keybinds require external programs, such as:
- `F8` - **pulsemixer** (tui sound mixer)
- `media keys` - **pamixer** (volume), **playerctl** (control)
- `modkey + z` - **boomer** (zooming program)
- `modkey + c` - **gcolor2** (color picker)
- `modkey + p` - **plumber** (my plumbing script)
- `modkey + x` - **xkill** (kill x programs on click)
- `modkey + Shift + s` - **maim** (screenshotting)
- `modkey + Shift + l` - **bosskey** (screen locking)
- `modkey + Shift + x` - **powermenu** (shutdown, reboot, etc.)

# installation
**Note:** Install any extra programs needed for special keybinds (see above.)

Clone the git repository
```sh
git clone https://github.com/SpyHoodle/perfectwm
```
Change directory to perfectwm
```sh
cd perfectwm
```
Make and install perfectwm
```sh
make install
```
