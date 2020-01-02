// Downloaded from https://developer.x-plane.com/code-sample/hello-world-sdk-3/

#include "OpenSceneryX.h"

PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "OpenSceneryX");
	strcpy(outSig, "openscenery.plugin");
	strcpy(outDesc, "OpenSceneryX Support Plugin.");

	XPLMCreateWindow_t params;
	params.structSize = sizeof(params);
	params.visible = 1;
	params.drawWindowFunc = draw_opensceneryx_window;
	// Note on "dummy" handlers:
	// Even if we don't want to handle these events, we have to register a "do-nothing" callback for them
	params.handleMouseClickFunc = dummy_mouse_handler;
	params.handleRightClickFunc = dummy_mouse_handler;
	params.handleMouseWheelFunc = dummy_wheel_handler;
	params.handleKeyFunc = dummy_key_handler;
	params.handleCursorFunc = dummy_cursor_status_handler;
	params.refcon = NULL;
	params.layer = xplm_WindowLayerFloatingWindows;
	// Opt-in to styling our window like an X-Plane 11 native window
	params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;

	// Set the window's initial bounds
	// Note that we're not guaranteed that the main monitor's lower left is at (0, 0)...
	// We'll need to query for the global desktop bounds!
	int left, bottom, right, top;
	XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
	params.left = left + 20;
	params.right = params.left + 300;
	params.top = top - 20;
	params.bottom = params.top - 50;

	g_window = XPLMCreateWindowEx(&params);

	// Position the window as a "free" floating window, which the user can drag around
	XPLMSetWindowPositioningMode(g_window, xplm_WindowPositionFree, -1);
	// Limit resizing our window: maintain a minimum width/height of 100 boxels and a max width/height of 300 boxels
	XPLMSetWindowResizingLimits(g_window, 200, 200, 300, 300);
	XPLMSetWindowTitle(g_window, "Sample Window");

	fetch_version();

	return g_window != NULL;
}

void fetch_version()
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://downloads.opensceneryx.com/library/version.txt");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();
}


PLUGIN_API void	XPluginStop(void)
{
	// Since we created the window, we'll be good citizens and clean it up
	XPLMDestroyWindow(g_window);
	g_window = NULL;
}

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void)  { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }

void	draw_opensceneryx_window(XPLMWindowID in_window_id, void * in_refcon)
{
	// Mandatory: We *must* set the OpenGL state before drawing
	// (we can't make any assumptions about it)
	XPLMSetGraphicsState(
						 0 /* no fog */,
						 0 /* 0 texture units */,
						 0 /* no lighting */,
						 0 /* no alpha testing */,
						 1 /* do alpha blend */,
						 1 /* do depth testing */,
						 0 /* no depth writing */
						 );

	int l, t, r, b;
	XPLMGetWindowGeometry(in_window_id, &l, &t, &r, &b);

	float col_white[] = {1.0, 1.0, 1.0}; // red, green, blue

	XPLMDrawString(col_white, l + 10, t - 20, "Welcome to the OpenSceneryX plugin!", NULL, xplmFont_Proportional);
}

