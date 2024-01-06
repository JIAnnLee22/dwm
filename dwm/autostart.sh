#!/bin/bash

picom &
feh --randomize --bg-fill ~/Pictures &
slstatus &
fcitx5 -d
sxhkd -c ~/.config/dwm/sxhkdrc &
