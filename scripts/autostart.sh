#!/bin/bash

bash ~/dwm/scripts/status-bar.sh  &
bash ~/dwm/scripts/tap-to-click.sh  &
feh --randomize --bg-fill ~/pictures &
libinput-gestures-setup start &
picom &
sleep 3 
fcitx &
nm-applet &
blueman-applet &
optimus-manager-qt &
