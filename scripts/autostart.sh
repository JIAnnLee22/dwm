#!/bin/bash

bash ~/dwm/scripts/status-bar.sh  &
bash ~/dwm/scripts/tap-to-click.sh  &
bash ~/dwm/scripts/bg-change.sh &
libinput-gestures-setup start &
picom &
sleep 3 
fcitx5 &
nm-applet &
blueman-applet &
optimus-manager-qt &
