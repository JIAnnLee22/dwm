#!/bin/bash

picom &
feh --randomize --bg-fill ~/Pictures &
slstatus &
fcitx5 -d &
if ! pgrep -x "flameshot" > /dev/null
then
    flameshot &
fi
