#!/bin/sh

FILENAME=$HOME/Pictures/screenshot/$(date '+%y%m%d%H%M%S').png
grim -g "$(slurp)" $FILENAME
feh $FILENAME
