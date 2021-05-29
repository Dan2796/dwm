/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 22;       /* vert inner gap between windows */
static const unsigned int gappoh    = 22;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 22;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack-Regular:size=10", "FontAwesome:size=10"};
static const char dmenufont[]       = "Hack-Regular:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#7A0026"; 
static const char col_blue[]        = "#065F7A"; 
static const char col_orange[]      = "#7A4706"; 
static const char col_frost_1[]     = "#8fbcbb"; 
static const char col_frost_2[]     = "#88c0d0"; 
static const char col_frost_3[]     = "#81a1c1"; 
static const char col_frost_4[]     = "#5e81ac"; 
static const char col_aurora_1[]    = "#bf616a"; 
static const char col_aurora_2[]    = "#d08770"; 
static const char col_aurora_3[]    = "#ebcb8b"; 
static const char col_aurora_4[]    = "#a3be8c"; 
static const char col_aurora_5[]    = "#b48ead"; 
static const char col_polar_1[]     = "#2e3440"; 
static const char col_polar_2[]     = "#3b4252"; 
static const char col_polar_3[]     = "#434c5e"; 
static const char col_polar_4[]     = "#4c566a"; 
static const char col_snow_1[]      = "#d8dee9"; 
static const char col_snow_2[]      = "#e5e9f0"; 
static const char col_snow_3[]      = "#eceff4"; 
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_snow_1, col_polar_1, col_polar_2 },
	[SchemeSel]  = { col_snow_2, col_aurora_3, col_aurora_3},
	[SchemeStatus]  = { col_snow_1, col_polar_3,  "#000000" }, // Statusbar right, text then background
	[SchemeTagsSel]  = { col_polar_1, col_aurora_3,  "#000000"  }, // Tagbar left selected 
  [SchemeTagsNorm]  = { col_snow_1, col_polar_3,  "#000000"  }, // Tagbar left unselected 
  [SchemeInfoSel]  = { col_snow_1, col_polar_1,  "#000000"  }, // infobar middle selected 
  [SchemeInfoNorm]  = { col_snow_1, col_polar_1,  "#000000"  }, // infobar middle unselected 
};

/* tagging */
static const char *tags[] = { "", "2", "3", "4", "5", "6", "8", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	
  /* class      instance    title       tags mask     isfloating   canfocus isterminal noswallow monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           1,       0,         0,        -1 },
	{ "firefox",  NULL,       NULL,       0,            0,           1,       0,         0,        -1 },
	{ "qutebrowser",  NULL,       NULL,       0,            0,           1,       0,         0,        -1 },
	{ "st",       NULL,       NULL,       0,            0,           1,       1,         1,        -1 },
	{ "guvcview", NULL,       NULL,       0,            0,           1,       0,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* Kill volume status */
static const char *vol_kill[] = { "pkill", "-RTMIN+3", "dwmblocks", NULL};

/* Audio controls */

static const char *upvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL};
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL};
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL};
/* Shortcut programs */
static const char *bibleLaunch[] = { "/usr/bin/zathura", "~/docs/the_bible.pdf", NULL};
/* static const char *qute[] = { "/usr/bin/qutebrowser", NULL}; */
static const char *firefox[] = { "/usr/bin/firefox", NULL};
static const char *screenChange[] = { "screenChangeTP.sh", NULL};
static const char *nota_search[] = { "nota_search.sh", NULL};
static const char *open_nota[] = { "st", "ranger", "/home/dan/nota", NULL};
/* static const char *emailOpen[] = { "st", "neomutt", "-f", "All_Mail", NULL}; */
static const char *emailOpen[] = { "st", "neomutt", NULL};
static const char *emailSync[] = { "st", "mbsync", "-a", NULL};
static const char *emailNotMuch[] = { "st", "notmuch", "new", NULL};
static const char *passMaster[] = { "/usr/bin/passmenu", NULL};
static const char *calOpen[] = { "st", "/usr/bin/calcurse", NULL};
static const char *spotify_launch[] = { "/home/dan/btb/spotify_launcher.sh", NULL};
/* for volume keys */
# include <X11/XF86keysym.h>

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-l", "20", NULL }; */
static const char *dmenucmd[] = { "dmenu_run", "-l", "20", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_z,      spawn,          {.v = bibleLaunch } },
	{ MODKEY,                       XK_g,      spawn,          {.v = firefox } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = screenChange } },
	{ MODKEY,                       XK_n,      spawn,          {.v = nota_search } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = open_nota } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = emailOpen } },
  { MODKEY|ControlMask,           XK_m,      spawn,          {.v = emailSync } },
  { MODKEY|ControlMask,           XK_m,      spawn,          {.v = emailNotMuch } },
  { MODKEY|ControlMask,           XK_m,      spawn,          {.v = emailOpen } },
	{ MODKEY|ShiftMask,             XK_u,      spawn,          {.v = passMaster } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = calOpen } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = spotify_launch } },
	
  { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { 0,                            XF86XK_AudioLowerVolume,     spawn,          {.v = downvol } },
  { 0,                            XF86XK_AudioLowerVolume,     spawn,          {.v = vol_kill } },
  { 0,                            XF86XK_AudioMute,     spawn,          {.v = mutevol } },
  { 0,                            XF86XK_AudioMute,     spawn,          {.v = vol_kill } },
  { 0,                            XF86XK_AudioRaiseVolume,     spawn,          {.v = upvol } },
  { 0,                            XF86XK_AudioRaiseVolume,     spawn,          {.v = vol_kill } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_e,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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

