
#include "PureGTK.h"
#include "intern.h"

extern GHashTable *widgets;

static bool window_delete_event_callback(GtkWidget *widget, GdkEvent *e, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_CLOSE;
	event.close.id = widget_id;
	push_event(event);

	return true;
}

static void window_size_allocate_callback(GtkWidget *widget, GdkRectangle *allocation, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_RESIZE;
	event.resize.width = allocation->width;
	event.resize.height = allocation->height;
	event.resize.id = widget_id;
	push_event(event);
}



int OpenWindow(int id, int x, int y, int width, int height, const gchar *title)
{
	GtkWidget *window;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}



	g_signal_connect(window, "delete-event", G_CALLBACK(window_delete_event_callback), GINT_TO_POINTER(id));
	g_signal_connect(window, "size-allocate", G_CALLBACK(window_size_allocate_callback), GINT_TO_POINTER(id));

	add_widget(id, window);

	return (id);
}

void ShowWindow(int id)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_widget_show_all(w);
}

void SetWindowResizable(int id, bool resizable)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_set_resizable(GTK_WINDOW(w), resizable);
}

void SetWindowTitle(int id, const gchar *title)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_set_title(GTK_WINDOW(w), title);
}

void SetWindowPosition(int id, int x, int y)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_move(GTK_WINDOW(w), x, y);
}

void SetWindowSize(int id, int x, int y)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_resize(GTK_WINDOW(w), x, y);
}

void SetWindowMaximized(int id, bool maximized)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	if (maximized)
		gtk_window_maximize(GTK_WINDOW(w));
	else
		gtk_window_unmaximize(GTK_WINDOW(w));
}

void SetWindowFullscreen(int id, bool fullscreen)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	if (fullscreen)
		gtk_window_fullscreen(GTK_WINDOW(w));
	else
		gtk_window_unfullscreen(GTK_WINDOW(w));
}

void CloseWindow(int id)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_close(GTK_WINDOW(w));
}

void SetWindowOpacity(int id, double opacity)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_widget_set_opacity(w, opacity);
}

void SetWindowModal(int id, bool modal)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_set_modal(GTK_WINDOW(w), modal);
}

void SetWindowFocus(int id, int widget)
{
	GtkWidget *w;
	GtkWidget *component;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	component = g_hash_table_lookup(widgets, GINT_TO_POINTER(widget));
	g_assert(component != NULL);
	gtk_window_set_focus(GTK_WINDOW(w), component);
}

void SetWindowAttachedTo(int id, int widget)
{
	GtkWidget *w;
	GtkWidget *component;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	component = g_hash_table_lookup(widgets, GINT_TO_POINTER(widget));
	g_assert(component != NULL);
	gtk_window_set_attached_to(GTK_WINDOW(w), component);
}

void SetWindowGravity(int id, int gravity)
{
	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_window_set_gravity(GTK_WINDOW(w), gravity);
}

void SetWindowIcon(int id, const gchar *filename)
{
	GtkWidget *w;
	GdkPixbuf *icon;
	GError *error = NULL;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	icon = gdk_pixbuf_new_from_file(filename, &error);
	if (error != NULL)
	{
		Log(0, "SetWindowIcon: %s", error->message);
		g_error_free(error);
		return;
	}
	gtk_window_set_icon(GTK_WINDOW(w), icon);
}
