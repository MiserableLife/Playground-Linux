#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/SM/SMlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <assert.h>
#include <syslog.h>
#include <gio/gio.h>
Display *dpy;
Window win;
int scr;
//compile :
//eval gcc example.c -lX11 (pkg-config --cflags --libs glib-2.0 gio-2.0)
GDBusProxy* proxy;
static void
on_query_end_session(
    GDBusProxy *proxy,
    guint32 u
    )
{
  syslog(LOG_INFO, "on query end session %d" , u);
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
        "EndSessionResponse",
        g_variant_new ("(bs)",
          TRUE, "no problem"),
        G_DBUS_CALL_FLAGS_NONE,
        -1,
        NULL,
        NULL,
        NULL);
}
  static void
on_signal (GDBusProxy *proxy,
    gchar      *sender_name,
    gchar      *signal_name,
    GVariant   *parameters,
    gpointer    user_data)
{
  gchar *parameters_str;

  parameters_str = g_variant_print (parameters, TRUE);
  if(strcmp(signal_name, "QueryEndSession") ==0)
    on_query_end_session(proxy, g_variant_get_uint32(parameters));
  else if (strcmp(signal_name, "EndSession") ==0 )
    exit(0);

  g_print (" *** Received Signal: %s: %s\n",
      signal_name,
      parameters_str);
  g_free (parameters_str);
}

gboolean
register_client (void)
{
    GDBusConnection *session_bus;
    GError *error;
    GVariant* session_result;
    const gchar * objpath;
    error = NULL;

    session_bus = g_bus_get_sync (G_BUS_TYPE_SESSION,
                                  NULL,
                                  &error);


    if (error != NULL)
    {
        g_critical ("Unable to determine if session is running, could not get session bus: %s\n", error->message);
        g_clear_error (&error);

        return FALSE;
    }

    session_result = g_dbus_connection_call_sync (session_bus,
                                                  "org.gnome.SessionManager",
                                                  "/org/gnome/SessionManager",
                                                  "org.gnome.SessionManager",
                                                  "RegisterClient",
                                                  g_variant_new ("(ss)",
                                                    "mydesktop",
                                                    getenv("DESKTOP_AUTOSTART_ID")),
                                                  G_VARIANT_TYPE ("(o)"),
                                                  G_DBUS_CALL_FLAGS_NONE,
                                                  1000,
                                                  NULL,
                                                  &error);
    if (session_result != NULL)
    {
        g_variant_get (session_result, "(o)", &objpath);
        syslog(LOG_INFO, "obj path : %s",objpath);
        g_variant_unref (session_result);
    }
    else
    {
        g_clear_error (&error);
        return FALSE;
    }


    proxy = g_dbus_proxy_new_for_bus_sync (G_BUS_TYPE_SESSION,
        G_DBUS_PROXY_FLAGS_NONE,
        NULL, /* GDBusInterfaceInfo */
        "org.gnome.SessionManager",
        objpath,
        "org.gnome.SessionManager.ClientPrivate",
        NULL, /* GCancellable */
        &error);

    syslog(LOG_INFO, "make a proxy  : %d", !!proxy);

    g_signal_connect (proxy,
        "g-signal",
        G_CALLBACK (on_signal),
        NULL);

    //    g_object_unref (session_bus);
    return TRUE;
}

void send_spot(XIC ic, XPoint nspot) {
	XVaNestedList preedit_attr;
	preedit_attr = XVaCreateNestedList(0, XNSpotLocation, &nspot, NULL);
	XSetICValues(ic, XNPreeditAttributes, preedit_attr, NULL);
	XFree(preedit_attr);
}

int main() {
  static GMainLoop *loop = NULL;

//  xapp_util_get_session_is_running();
register_client();

	/* fallback to LC_CTYPE in env */
	setlocale(LC_CTYPE, "");
	XSetLocaleModifiers("");
	dpy = XOpenDisplay(NULL);
	scr = DefaultScreen(dpy);
	win = XCreateSimpleWindow(dpy,
			XDefaultRootWindow(dpy),
			0, 0, 100, 100, 5,
			BlackPixel(dpy, scr),
			BlackPixel(dpy, scr));
	XMapWindow(dpy, win);
	XIM xim = XOpenIM(dpy, NULL, NULL, NULL);
	XIC ic = XCreateIC(xim,
			/* the following are in attr, val format, terminated by NULL */
			XNInputStyle, XIMPreeditNothing | XIMStatusNothing,
			XNClientWindow, win,
			NULL);
	/* focus on the only IC */
	XSetICFocus(ic);
	/* capture the input */
	XSelectInput(dpy, win, KeyPressMask);

XPoint spot;
spot.x = 0;
spot.y = 0;
send_spot(ic, spot);

  loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (loop);
	static char *buff;
	size_t buff_size = 16;
	buff = (char *)malloc(buff_size);
	for (;;)
	{
		KeySym ksym;
		Status status;
		XEvent ev;
		XNextEvent(dpy, &ev);
		printf("miong!");
		fflush(stdout);
		if (XFilterEvent(&ev, None))
			continue;
		if (ev.type == KeyPress)
		{
			size_t c = Xutf8LookupString(ic, &ev.xkey,
					buff, buff_size - 1,
					&ksym, &status);
			if (status == XBufferOverflow)
			{
				printf("reallocate to the size of: %lu\n", c + 1);
				buff = (char*)realloc(buff, c + 1);
				c = Xutf8LookupString(ic, &ev.xkey,
						buff, c,
						&ksym, &status);
			}
			if (c)
			{
				spot.x += 20;
				spot.y += 20;
				send_spot(ic, spot);
				buff[c] = 0;
				printf("delievered string: %s\n", buff);
			}
		}
	}
}

