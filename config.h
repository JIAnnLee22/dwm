/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
static const int viewontag          = 1;     /* switch view on tag */
static const char *fonts[]          = { "monospace:size=12", "WenQuanYi Zen Hei:size=12" };
static const char dmenufont[]       = "Source Han Sans CN Normal:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      						instance    title       tags mask isfloating   monitor    float x,y,w,h    	floatborderpx*/
	{ "jetbrains-studio", 		NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
	{ "wechat.exe",       		NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
	{ "telegram-desktop", 		NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
	{ "yesplaymusic",     		NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
	{ "scrcpy",     					NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
	{ "org.gnome.Nautilus",  	NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
	{ "feh",  								NULL,    		NULL, 			0,   			1,   				 -1, 				-1,-1,-1,-1,			0},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "tabbed", "-c", "-r", "2", "st", "-w", "", NULL };
static const char *termTmuxcmd[]  = { "tabbed", "-c", "-r", "2", "st", "-w", "", "-e", "tmux", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *scratchpadTmuxcmd[] = { "st", "-t", scratchpadname, "-w", "", "-g", "120x34", "-e", "tmux", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *slockcmd[]  = { "slock", NULL, NULL};
static const char *changebgcmd[]  = { "feh", "--randomize", "--bg-fill", "/home/jiannlee22/Pictures", NULL};
static const char *screenshotcmd[]  = { "flameshot", "gui", NULL};
static const char *roficmd[]  = { "rofi", "-show", "drun", NULL};
static const char *surfcmd[]  = { "tabbed", "-c", "-n", "surf", "surf", "-e", NULL};
static const char *qutebrowsercmd[]  = { "qutebrowser", NULL};
static const char *filescmd[]  = { "nautilus", NULL};
static const char *toggletouchpadcmd[]  = { "synclient", "TouchpadOff=$(synclient", "-l" "|", "grep", "-c", "'TouchpadOff.*=.*0')", NULL};
static const char *brightcmd[2][4]  = {{ "brightnessctl", "s", "2%+", NULL}, { "brightnessctl", "s", "2%-", NULL}};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = filescmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = screenshotcmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termTmuxcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = changebgcmd } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = surfcmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = qutebrowsercmd } },
	{ MODKEY,                       XK_o,      spawn,          {.v = slockcmd } },
	{ MODKEY,                       XF86XK_TouchpadToggle,      spawn,          {.v = toggletouchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z, 	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_s,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             XK_s,      togglescratch,  {.v = scratchpadTmuxcmd } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brightcmd[0] } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brightcmd[1] } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

