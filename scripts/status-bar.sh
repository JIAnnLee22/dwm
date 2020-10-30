#!/bin/bash

dwm_alsa () {
    VOL=$(amixer get Master | tail -n1 | sed -r "s/.*\[(.*)%\].*/\1/")
    printf "%s" "$SEP1"
        if [ "$VOL" -eq 0 ]; then
            printf "🔇"
        elif [ "$VOL" -gt 0 ] && [ "$VOL" -le 33 ]; then
            printf "🔈 %s%%" "$VOL"
        elif [ "$VOL" -gt 33 ] && [ "$VOL" -le 66 ]; then
            printf "🔉 %s%%" "$VOL"
        else
            printf "🔊 %s%%" "$VOL"
        fi
#    if [ "$IDENTIFIER" = "unicode" ]; then
#        if [ "$VOL" -eq 0 ]; then
#            printf "🔇"
#        elif [ "$VOL" -gt 0 ] && [ "$VOL" -le 33 ]; then
#            printf "🔈 %s%%" "$VOL"
#        elif [ "$VOL" -gt 33 ] && [ "$VOL" -le 66 ]; then
#            printf "🔉 %s%%" "$VOL"
#        else
#            printf "🔊 %s%%" "$VOL"
#        fi
#    else
#        if [ "$VOL" -eq 0 ]; then
#            printf "MUTE"
#        elif [ "$VOL" -gt 0 ] && [ "$VOL" -le 33 ]; then
#            printf "VOL %s%%" "$VOL"
#        elif [ "$VOL" -gt 33 ] && [ "$VOL" -le 66 ]; then
#            printf "VOL %s%%" "$VOL"
#        else
#            printf "VOL %s%%" "$VOL"
#        fi
#    fi
    printf "%s\n" "$SEP2"
}

print_mem(){
	memfree=$(($(grep -m1 'MemAvailable:' /proc/meminfo | awk '{print $2}') / 1024))
	echo -e "$memfree"
}

get_time_until_charged() {

	# parses acpitool's battery info for the remaining charge of all batteries and sums them up
	# sum_remaining_charge=$(acpitool -B | grep -E 'Remaining capacity' | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+ | bc);
	sum_remaining_charge=$(acpitool -B | grep -E 'Remaining capacity' | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+);

	# finds the rate at which the batteries being drained at
	# present_rate=$(acpitool -B | grep -E 'Present rate' | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+ | bc);
	present_rate=$(acpitool -B | grep -E 'Present rate' | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+);

	# divides current charge by the rate at which it's falling, then converts it into seconds for `date`
	seconds=$(bc <<< "scale = 10; ($sum_remaining_charge / $present_rate) * 3600");

	# prettifies the seconds into h:mm:ss format
	pretty_time=$(date -u -d @${seconds} +%T);

	echo $pretty_time;
}

get_battery_combined_percent() {

	# get charge of all batteries, combine them
	# total_charge=$(expr $(acpi -b | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+ | bc));
	total_charge=$(expr $(acpi -b | awk '{print $4}' | grep -Eo "[0-9]+" | paste -sd+));

	# get amount of batteries in the device
	battery_number=$(acpi -b | wc -l);

	percent=$(expr $total_charge / $battery_number);

	echo $percent;
}

get_battery_charging_status() {

	if $(acpi -b | grep --quiet Discharging)
	then
		echo "🔋";
	else # acpi can give Unknown or Charging if charging, https://unix.stackexchange.com/questions/203741/lenovo-t440s-battery-status-unknown-but-charging
		echo "🔌";
	fi
}



print_bat(){
	echo "$(get_battery_charging_status) $(get_battery_combined_percent)%, $(get_time_until_charged )";
}

R=$(print_mem)
S=$(dwm_alsa)
B=$(print_bat)
D=$(date +"%F %R" )




xsetroot -name "[💿${R}M][$S][$B]$D"
