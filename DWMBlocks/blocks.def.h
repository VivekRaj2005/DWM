//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
    /*Icon*/   /*Command*/                                                                                                       /*Update Interval*/ /*Update Signal*/

    // Battery: Space before icon, space after percentage
    {" 🔋 ", "echo \"$(cat /sys/class/power_supply/BAT1/capacity)% \"",                                                          30,                 2},

    // Updates: Space before icon, space after "packages"
    {" 📦 ", "echo \"$(checkupdates | wc -l) packages \"",                                                                       360,                9},

    // Memory: Space before icon, space after "RAM"
    {" 💻 ", "echo \"$(free -h | awk '/^Mem/ { print $3 }' | sed 's/i//g') RAM \"",                                              6,                  1},

    // Volume: Space before icon, space after volume level
    {" 🔊 ", "echo \"$(pactl get-sink-volume @DEFAULT_SINK@ | awk '{print $5}' | head -n1) \"",                                  0,                  10},

    // Clock: Space before icon, space after time
    {" 🕰 ", "date +'%b %d (%a) %I:%M%p '",                                                                                       60,                 0},
};

// Delimiter with spaces on both sides
static char delim[] = " | ";
static unsigned int delimLen = 5;
