local astal = require("astal")
local monitor_file = astal.monitor_file
monitor_file("~/.cache/dwltags", function(file, event) if (event == 0) print(file) end)
