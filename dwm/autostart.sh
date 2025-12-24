#!/bin/bash

feh --randomize --bg-fill ~/Pictures/wallpaper &
slstatus &
fcitx5 -d &
xautolock -time 5 -locker "$HOME/.config/dwm/scripts/lock_screen.sh" &
if ! pgrep -x "flameshot" > /dev/null
then
    flameshot &
fi
