/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define BROWSER "librewolf"
#define TERM "st-256color"
#define TERM_CLASS "st-256color"

/* appearance */
static unsigned int baralpha = 0xd0;
static unsigned int borderalpha = OPAQUE;
/* border pixel of windows */
static const unsigned int borderpx = 2;
static const unsigned int gappx = 15;
/* snap pixel */
static const unsigned int snap = 32;
/* 1 means swallow floating windows by default */
static const int swallowfloating = 0;
/* 0 means no bar */
static const int showbar = 1;
/* 0 means bottom bar */
static const int topbar = 1;
static const char *fonts[] = {
	"Iosevka, Iosevka Medium:style=Regular:size=13",
	"Noto Color Emoji:style=Regular:size=11",
};
static const char barfg[] = "#bbbbbb";
static const char barbg[] = "#000000";
static const char barborder[] = "#000000";
static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { "#bbbbbb", "#222222", "#444444" },
	[SchemeSel] = { "#eeeeee", "#005577", barfg  },
	[SchemeStatus] = { barfg, barbg, barborder },
	[SchemeTagsSel] = { barfg, barbg, barborder },
	[SchemeTagsNorm] = { barfg, barbg, barborder },
	[SchemeInfoSel] = { barfg, barbg, barborder },
	[SchemeInfoNorm] = { barfg, barbg, barborder },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *      WM_CLASS(STRING) = instance, class
	 *      WM_NAME(STRING) = title
	 */
	/* class      inst  title           tags isfloat isterm noswallow monitor */
	{ TERM_CLASS, NULL, NULL,           0,   0,      1,     0,        -1 },
	{ "Display",  NULL, NULL,           0,   1,      0,     0,        -1 },
	{ "mpv",      NULL, NULL,           3,   0,      0,     0,        -1 },
	{ NULL,       NULL, "Event Tester", 0,   0,      0,     1,        -1 },
};

/* layout(s) */
/* factor of master area size [0.05..0.95] */
static const float mfact = 0.55;
/* number of clients in master area */
static const int nmaster = 1;
/* 1 means respect size hints in tiled resizals */
static const int resizehints = 0;
/* 1 will force focus on the fullscreen window */
static const int lockfullscreen = 1;

static const Layout layouts[] = {
	/* symbol arrange function */
	{ "[]=",  tile }, /* first entry is default */
	{ "><>",  NULL }, /* no layout function means floating behavior */
	{ "[M]",  monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} },

/* keys */
#include "movestack.c"
static const Key keys[] = {
	/* modifier         key        function        argument */
	{ MODKEY,           XK_a,      spawn,          {.v = (const char *[]){ "get-app-class", NULL }} },
	{ MODKEY,           XK_b,      spawn,          {.v = (const char *[]){ TERM, "-e", "bluetoothctl", NULL }} },
	{ MODKEY|ShiftMask, XK_b,      togglebar,      {0} },
	{ MODKEY,           XK_d,      spawn,          {.v = (const char *[]){ "dmenu_run", NULL }} },
	{ MODKEY,           XK_f,      fullscreen,     {0} },
	{ MODKEY|ShiftMask, XK_f,      togglefloating, {0} },
	{ MODKEY,           XK_g,      setgaps,        {.i = -1} },
	{ MODKEY|ShiftMask, XK_g,      setgaps,        {.i = +1} },
	{ MODKEY,           XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_j,      focusstack,     {.i = +1} },
	{ MODKEY|ShiftMask, XK_j,      movestack,      {.i = +1} },
	{ MODKEY,           XK_i,      incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask, XK_i,      incnmaster,     {.i = -1} },
	{ MODKEY,           XK_k,      focusstack,     {.i = -1} },
	{ MODKEY|ShiftMask, XK_k,      movestack,      {.i = -1} },
	{ MODKEY,           XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_m,      spawn,          {.v = (const char *[]){ "dmenu-menu", NULL }} },
	{ MODKEY,           XK_n,      spawn,          {.v = (const char *[]){ "pkill", "-SIGUSR1", "herbe", NULL }} },
	{ MODKEY|ShiftMask, XK_n,      spawn,          {.v = (const char *[]){ TERM, "-e", "nmtui", NULL }} },
	{ MODKEY|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY,           XK_t,      spawn,          {.v = (const char *[]){ "toggle-touchpad", NULL }} },
	{ MODKEY,           XK_u,      spawn,          {.v = (const char *[]){ "dmenu-handle-link", NULL }} },
	{ MODKEY,           XK_v,      spawn,          {.v = (const char *[]){ "virt-manager", NULL }} },
	{ MODKEY,           XK_w,      spawn,          {.v = (const char *[]){ BROWSER, NULL }} },
	{ MODKEY|ShiftMask, XK_w,      spawn,          {.v = (const char *[]){ "dmenu-set-wallpaper", NULL }} },
	{ MODKEY,           XK_x,      spawn,          {.v = (const char *[]){ "nekoray", NULL }} },
	{ MODKEY,           XK_z,      zoom,           {0} },
	{ MODKEY,           XK_Print,  spawn,          {.v = (const char *[]){ "make-screenshot", NULL }} },
	{ MODKEY,           XK_Return, spawn,          {.v = (const char *[]){ TERM, NULL }} },
	{ MODKEY,           XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask, XK_slash,  killclient,     {0} },
	{ MODKEY,           XK_space,  setlayout,      {0} },
	{ MODKEY,           XK_comma,  focusmon,       {.i = -1} },
	{ MODKEY|ShiftMask, XK_comma,  tagmon,         {.i = -1} },
	{ MODKEY,           XK_period, focusmon,       {.i = +1} },
	{ MODKEY|ShiftMask, XK_period, tagmon,         {.i = +1} },
	TAGKEYS(            XK_1,                      0)
	TAGKEYS(            XK_2,                      1)
	TAGKEYS(            XK_3,                      2)
	TAGKEYS(            XK_4,                      3)
	TAGKEYS(            XK_5,                      4)
	TAGKEYS(            XK_6,                      5)
	TAGKEYS(            XK_7,                      6)
	TAGKEYS(            XK_8,                      7)
	TAGKEYS(            XK_9,                      8)
	{ MODKEY,           XK_equal,  spawn,          {.v = (const char *[]){ "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL }} },
	{ MODKEY,           XK_equal,  spawn,          {.v = (const char *[]){ "pkill", "-RTMIN+1", "dwmblocks", NULL }} },
	{ MODKEY,           XK_minus,  spawn,          {.v = (const char *[]){ "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL }} },
	{ MODKEY,           XK_minus,  spawn,          {.v = (const char *[]){ "pkill", "-RTMIN+1", "dwmblocks", NULL }} },
	{ MODKEY|ShiftMask, XK_minus,  spawn,          {.v = (const char *[]){ "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL }} },
	{ MODKEY|ShiftMask, XK_minus,  spawn,          {.v = (const char *[]){ "pkill", "-RTMIN+1", "dwmblocks", NULL }} },
};

/* button definitions */
/*
click can be:
- ClkTagBar
- ClkLtSymbol
- ClkStatusText
- ClkWinTitle
- ClkClientWin
- ClkRootWin
*/
static const Button buttons[] = {
	/* click         event   button   function        argument */
	{ ClkLtSymbol,   0,      Button1, setlayout,      {0} },
	{ ClkLtSymbol,   0,      Button3, setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,   0,      Button2, zoom,           {0} },
	{ ClkStatusText, 0,      Button2, spawn,          {.v = (const char *[]){ TERM, NULL }} },
	{ ClkClientWin,  MODKEY, Button1, movemouse,      {0} },
	{ ClkClientWin,  MODKEY, Button2, togglefloating, {0} },
	{ ClkClientWin,  MODKEY, Button3, resizemouse,    {0} },
	{ ClkTagBar,     0,      Button1, view,           {0} },
	{ ClkTagBar,     0,      Button3, toggleview,     {0} },
	{ ClkTagBar,     MODKEY, Button1, tag,            {0} },
	{ ClkTagBar,     MODKEY, Button3, toggletag,      {0} },
};

