/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "Noto Sans CJK SC:size=14" };
static const char dmenufont[]       = "Noto Sans CJK SC:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance    title       tags mask     isfloating   monitor */
	{ "Gimp",             NULL,       NULL,       0,            1,           -1 },
	{ "Telegram",             NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",          NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Android-studio",   NULL,       NULL,       1 << 8,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

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
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "80x24", NULL };
static const char *browsercmd[]  = { "/home/jiannlee22/dwm/scripts/browser.sh", NULL };
static const char *lightupcmd[]  = { "/home/jiannlee22/dwm/scripts/light-up.sh", NULL };
static const char *lightdowncmd[]  = { "/home/jiannlee22/dwm/scripts/light-down.sh", NULL };
static const char *volupcmd[]  = { "/home/jiannlee22/dwm/scripts/volup.sh", NULL };
static const char *voldowncmd[]  = { "/home/jiannlee22/dwm/scripts/voldown.sh", NULL };
static const char *bgchangecmd[]  = { "/home/jiannlee22/dwm/scripts/bg-change.sh", NULL };
static const char *suspendcmd[]  = { "/home/jiannlee22/dwm/scripts/suspend.sh", NULL };
static const char *qwertycmd[]  = { "/home/jiannlee22/dwm/scripts/qwerty.sh", NULL };
static const char *colemakcmd[]  = { "/home/jiannlee22/dwm/scripts/colemak.sh", NULL };

static Key keys[] = {
	/* modifier         key                        function        argument */
	{ 0,                XF86XK_MonBrightnessUp,    spawn,          {.v = lightupcmd } },
	{ 0,                XF86XK_MonBrightnessDown,  spawn,          {.v = lightdowncmd } },
	{ 0,                XF86XK_AudioRaiseVolume,   spawn,          {.v = volupcmd } },
	{ 0,                XF86XK_AudioLowerVolume,   spawn,          {.v = voldowncmd } },
	{ MODKEY,           XK_d,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,	          XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask, XK_Return,                 spawn,          {.v = scratchpadcmd } },
	{ MODKEY,	          XK_w,                      spawn,          {.v = browsercmd } },
	{ MODKEY,	          XK_b,                      spawn,          {.v = bgchangecmd } },
	{ MODKEY,	          XK_c,                      spawn,          {.v = colemakcmd } },
	{ MODKEY,	          XK_v,                      spawn,          {.v = qwertycmd } },
	{ MODKEY,           XK_f,                      togglebar,      {0} },
	{ MODKEY|ShiftMask, XK_j,                      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask, XK_k,                      incnmaster,     {.i = -1 } },
	{ MODKEY,           XK_j,                      setmfact,       {.f = -0.05} },
	{ MODKEY,           XK_k,                      setmfact,       {.f = +0.05} },
	{ MODKEY,           XK_e,                      hidewin,        {0} },
	{ MODKEY|ShiftMask, XK_e,                      restorewin,     {0} },
	{ MODKEY|ShiftMask, XK_z,      		             rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask, XK_x,      		             rotatestack,    {.i = -1 } },
	{ MODKEY,           XK_z,                      focusstack,     {.i = +1 } },
	{ MODKEY,           XK_x,                      focusstack,     {.i = -1 } },
	{ MODKEY,           XK_Tab,                    view,           {0} },
	{ MODKEY,	          XK_q,                      killclient,     {0} },
	{ MODKEY,           XK_i,                      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,           XK_o,                      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,           XK_p,                      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask, XK_p,                      spawn,          {.v = suspendcmd } },
	{ MODKEY,           XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask, XK_space,                  togglefloating, {0} },
	{ MODKEY,           XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,           XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,           XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,                 tagmon,         {.i = +1 } },
	{ MODKEY,           XK_minus,                  setgaps,        {.i = -1 } },
	{ MODKEY,           XK_equal,                  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask, XK_equal,                  setgaps,        {.i = 0  } },
	TAGKEYS(            XK_1,                                      0)
	TAGKEYS(            XK_2,                                      1)
	TAGKEYS(            XK_3,                                      2)
	TAGKEYS(            XK_4,                                      3)
	TAGKEYS(            XK_5,                                      4)
	TAGKEYS(            XK_6,                                      5)
	TAGKEYS(            XK_7,                                      6)
	TAGKEYS(            XK_8,                                      7)
	TAGKEYS(            XK_9,                                      8)
	{ MODKEY|ShiftMask, XK_q,                      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

