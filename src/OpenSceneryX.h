#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include <string.h>
#include <stdio.h>

#define CURL_STATICLIB
#include "curl/curl.h"

#if IBM
	#include <windows.h>
#endif

#if IBM
	#include <GL/gl.h>
	#include <GL/glut.h>
#elif LIN
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#else
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#include <Carbon/Carbon.h>
#endif

#ifndef XPLM301
	#error This is made to be compiled against the XPLM301 SDK
#endif

// An opaque handle to the window we will create
static				XPLMWindowID	g_window;

// Our functions
void				draw_opensceneryx_window(XPLMWindowID in_window_id, void * in_refcon);
void				fetch_version();

// Callbacks we will register when we create our window
int					dummy_mouse_handler(XPLMWindowID in_window_id, int x, int y, int is_down, void * in_refcon) { return 0; }
XPLMCursorStatus	dummy_cursor_status_handler(XPLMWindowID in_window_id, int x, int y, void * in_refcon) { return xplm_CursorDefault; }
int					dummy_wheel_handler(XPLMWindowID in_window_id, int x, int y, int wheel, int clicks, void * in_refcon) { return 0; }
void				dummy_key_handler(XPLMWindowID in_window_id, char key, XPLMKeyFlags flags, char virtual_key, void * in_refcon, int losing_focus) { }
