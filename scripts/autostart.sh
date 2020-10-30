#!/bin/bash

sleep 3 
bash ~/dwm/scripts/status.sh  &
bash ~/dwm/scripts/tap-to-click.sh  &
bash ~/dwm/scripts/bg-change.sh &
libinput-gestures-setup start &
picom &
fcitx5 &
optimus-manager-qt &
