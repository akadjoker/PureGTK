#include "PureGTK.h"
#include "intern.h"

extern GHashTable *widgets;



//gtk_widget_set_size_request(child, width, height);	

void SetWidgetSize(int id, int width, int height)
{
    GtkWidget	*widget;
    widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
    g_assert(widget != NULL);
    gtk_widget_set_size_request(widget, width, height);
}



void ShowAllWidgets(int id)
{
 	GtkWidget *w;
	w = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(w != NULL);
	gtk_widget_show_all(w);
}
