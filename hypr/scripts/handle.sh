#!/bin/sh

handle() {
	line=$1
	if [[ "$line" = openwindow* ]]; then
		read -r window_address workspace window_class <<<$(echo "$line" | awk -F "[>,]" '{print $3,$4,$5}')
		if [[ "$workspace" = "special:dropdown" && "$window_class" != "kitty-dropdown" ]]; then
			hyprctl dispatch movetoworkspace e+0,address:0x${window_address}
			hyprctl dispatch togglespecialworkspace dropdown
		fi
	fi
}

socat -U - UNIX-CONNECT:/tmp/hypr/$HYPRLAND_INSTANCE_SIGNATURE/.socket2.sock | while read -r line; do handle "$line"; done

