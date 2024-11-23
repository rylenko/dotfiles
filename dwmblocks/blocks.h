static const Block blocks[] = {
	/* Icon, command, update interval and update signal */
	{"", "weather-block", 60, 0},
	{"", "pkg-count-block", 15, 0},
	{"", "ram-block", 5, 0},
	{"", "net-block", 3, 0},
	{"", "battery-block", 5, 0},
	{"", "sound-block", 2, 1},
	{"", "dt-block", 5, 0},
};

static char delim[] = " ";
static unsigned int delimLen = 5;
