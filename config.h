/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int refresh_rate        = 60;  /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int enable_noborder     = 1;   /* toggles noborder feature (0=disabled, 1=enabled) */
static const unsigned int borderpx            = 1;   /* border pixel of windows */
static const unsigned int snap                = 26;  /* snap pixel */
static const int swallowfloating              = 1;   /* 1 means swallow floating windows by default */
static const unsigned int systraypinning      = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft       = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing      = 5;   /* systray spacing */
static const int systraypinningfailfirst      = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor */
static const int showsystray                  = 1;   /* 0 means no systray */
static const int showbar                      = 1;   /* 0 means no bar */
static const int topbar                       = 1;   /* 0 means bottom bar */
#define ICONSIZE                              17    /* icon size */
#define ICONSPACING                           5     /* space between icon and title */
#define SHOWWINICON                           1     /* 0 means no winicon */
static const char *fonts[]                    = { "ShureTechMono Nerd Font:size=12", "NotoColorEmoji:pixelsize=12:antialias=true:autohint=true" };
static const char normbgcolor[]               = "#181A18";
static const char selbgcolor[]                = "#262626";
static const char normbordercolor[]           = "#181A18";
static const char selbordercolor[]            = "#F8F9FA";
static const char normfgcolor[]               = "#F8F9F1";
static const char selfgcolor[]                = "#FFFFFF";
static const char *colors[][3]                = {
    /*              fg            bg            border         */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const char *const autostart[] = {
  "xset", "s", "off", NULL,
  "xset", "s", "noblank", NULL,
  "xset", "-dpms", NULL,
  "dbus-update-activation-environment", "--systemd", "--all", NULL,
  "/usr/bin/lxpolkit", NULL,
  "set-xres", NULL,
  "dunst", NULL,
  "picom", "-b", "--config=/home/maarkov/.config/picom/picom.conf", NULL,
  "feh-bgp", NULL,
  "dwmblocks", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = {"一", "二", "三", "四", "五" };
static const char ptagf[] = "[%s %s]";  /* format of a tag label */
static const char etagf[] = "[%s]";     /* format of an empty tag */
static const int lcaselbl = 0;          /* 1 means make tag label lowercase */

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class                instance  title           tags mask  isfloating  isterminal  noswallow monitor */
    { "St",                 NULL,     NULL,           0,         0,          1,          0,        0 },
    { "alacritty",              NULL,     NULL,           0,         0,          1,          0,        0 },
    { "critty-fl",          NULL,     NULL,           0,         0,          1,          0,        0 },
    { "terminator",         NULL,     NULL,           0,         0,          1,          0,        0 },
    { "lutris",             NULL,     NULL,           0,         1,          0,          0,        0 },
    { "steam_app_default",  NULL,     NULL,           0,         1,          0,          0,        0 },
    { "mpv",							NULL,     NULL,           0,         1,          0,          0,        0 },
    { NULL,                 NULL,     "Event Tester", 0,         0,          0,          1,       -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;   /* number of clients in master area */
static const int resizehints = 0;   /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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
#define STATUSBAR "dwmblocks"
/* commands */
static const char *ftermcmd[] = { "alacritty", "--class=critty-fl", NULL };
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]     = { "alacritty", NULL };

static Key keys[] = {
    /* modifier                     key            function                argument */
    { MODKEY,                       XK_r,          spawn,                  {.v = launchercmd} }, // spawn rofi for launching other programs
	{ MODKEY,                       XK_x,          spawn,                  {.v = termcmd } }, // spawn a terminal
	{ MODKEY|ShiftMask,             XK_x,          spawn,                  {.v = ftermcmd } }, // spawn a floating terminal
    { MODKEY,                       XK_w,          spawn,                  SHCMD ("xdg-open https://")}, // open default browser
    { MODKEY,                       XK_p,          spawn,                  SHCMD ("full-shotgun")}, // capture full screen screenshot
	{ MODKEY|ShiftMask,             XK_p,          spawn,                  SHCMD ("sel-shotgun")}, // open flameshot gui for screenshot selection
	{ MODKEY|ControlMask,           XK_p,          spawn,                  SHCMD ("sel-clip-shotgun")}, // copy screenshot to clipboard
    { MODKEY,                       XK_e,          spawn,                  SHCMD ("pcmanfm")}, // open thunar file manager
    { MODKEY,                       XK_b,          spawn,                  SHCMD ("feh-bgp")}, // change wallpaper
    { 0,                            0x1008ff02,    spawn,                  SHCMD ("xbacklight -inc 10")}, // increase backlight brightness
    { 0,                            0x1008ff03,    spawn,                  SHCMD ("xbacklight -dec 10")}, // decrease backlight brightness
    { 0,                            0x1008ff1b,    spawn,                  SHCMD ("xbacklight -inc 10")}, // increase backlight brightness
    { 0,                            0x1008ff8e,    spawn,                  SHCMD ("xbacklight -dec 10")}, // decrease backlight brightness
    { 0,                            0x1008ff11,    spawn,                  SHCMD ("sb-voldown")}, // unmute volume
	{ 0,                            0x1008ff12,    spawn,                  SHCMD ("sb-voltoggle")}, // toggle mute/unmute
	{ 0,                            0x1008ff13,    spawn,                  SHCMD ("sb-volup")}, // unmute volume
    { MODKEY|ShiftMask,             XK_b,          togglebar,              {0} }, // toggle bar visibility
    { MODKEY,                       XK_j,          focusstack,             {.i = +1 } }, // focus on the next client in the stack
    { MODKEY,                       XK_k,          focusstack,             {.i = -1 } }, // focus on the previous client in the stack
    { MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } }, // move stack up
    { MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } }, // move stack down
    { MODKEY,                       XK_i,          incnmaster,             {.i = +1 } }, // decrease the number of clients in the master area
    { MODKEY,                       XK_d,          incnmaster,             {.i = -1 } }, // increase the number of clients in the master area
    { MODKEY,                       XK_h,          setmfact,               {.f = -0.05} }, // decrease the size of the master area compared to the stack area(s)
    { MODKEY,                       XK_l,          setmfact,               {.f = +0.05} }, // increase the size of the master area compared to the stack area(s)
    { MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} }, // increase size respective to other windows within the same area
    { MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} }, // decrease client size respective to other windows within the same area
    { MODKEY|ShiftMask,             XK_o,          setcfact,               {.f =  0.00} }, // reset client area
    { MODKEY,                       XK_Return,     zoom,                   {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
    { MODKEY,                       XK_Tab,        view,                   {0} }, // view last focused tag
    { MODKEY,                       XK_q,          killclient,             {0} }, // close the currently focused window
    { MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} }, // set tile layout
    { MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} }, // set floating layout
    { MODKEY,                       XK_m,          fullscreen,             {0} }, // toggles fullscreen for the currently selected client
    { MODKEY,                       XK_space,      setlayout,              {0} }, // toggles between current and previous layout
    { MODKEY|ShiftMask,             XK_m,          togglefloating,         {0} }, // toggles between tiled and floating arrangement for the currently focused client
    { MODKEY|ShiftMask,             XK_y,          togglefakefullscreen,   {0} }, // toggles "fake" fullscreen for the selected window
    { MODKEY,                       XK_0,          view,                   {.ui = ~0 } }, // view all tags on the current monitor
    { MODKEY,                       XK_comma,      focusmon,               {.i = -1 } }, // focus on the previous monitor, if any
    { MODKEY,                       XK_period,     focusmon,               {.i = +1 } }, // focus on the next monitor, if any
    { MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } }, // tag previous monitor
    { MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } }, // tag next monitor
    TAGKEYS(                        XK_1,                                  0)
    TAGKEYS(                        XK_2,                                  1)
    TAGKEYS(                        XK_3,                                  2)
    TAGKEYS(                        XK_4,                                  3)
    TAGKEYS(                        XK_5,                                  4)
    { MODKEY|ShiftMask,             XK_q,          quit,                   {0} }, // exit dwm
    { MODKEY|ControlMask,           XK_q,          spawn,                  SHCMD("$HOME/.config/rofi/powermenu.sh")}, // exit dwm
    { MODKEY|ControlMask|ShiftMask, XK_r,          spawn,                  SHCMD("systemctl reboot")}, // reboot system
    { MODKEY|ControlMask|ShiftMask, XK_p,          spawn,                  SHCMD("systemctl poweroff")}, // suspend system
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 2} },
    { ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
