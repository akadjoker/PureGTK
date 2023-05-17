
#include "PureGTK.h"
#include "intern.h"

extern GHashTable *widgets;

static void on_list_box_row_activated(GtkListBox *list_box, GtkListBoxRow *row, gpointer data)
{

    int widget_id = GPOINTER_TO_INT(data);
    Event event = {0};
    event.type = EVENT_LIST;
    event.list.id = widget_id;
    event.list.index = gtk_list_box_row_get_index(row);
    event.list.selected = gtk_list_box_row_is_selected(row);
    push_event(event);

    Log(0, "Row %d activated\n", gtk_list_box_row_get_index(row));
}
// static void on_row_selected(GtkListBox *list_box, GtkListBoxRow *row, gpointer user_data)
// {
//     if (row)
//     {
//         g_print("Row %d selected\n", gtk_list_box_row_get_index(row));
//     }
//     else
//         g_print("No row selected\n");
// }


static void on_activate_cursor_row(GtkListBox *list_box, gpointer user_data)
{
    g_print("Cursor row activated\n");
}

static void on_move_cursor(GtkListBox *list_box, GtkMovementStep step, gint count, gpointer user_data)
{
    g_print("Cursor moved\n");
}
static void on_select_all(GtkListBox *list_box, gpointer user_data)
{
    g_print("Select all rows\n");
}
static void on_unselect_all(GtkListBox *list_box, gpointer user_data)
{
    g_print("Unselect all rows\n");
}

int ListBoxWidget(int id)
{
    GtkWidget *widget;
    widget = gtk_list_box_new();
    if (id == ID_ANY)
    {
        id = get_new_id();
    }
    g_signal_connect(widget, "row-activated", G_CALLBACK(on_list_box_row_activated), GINT_TO_POINTER(id));
    g_signal_connect(widget, "select-all", G_CALLBACK(on_select_all), GINT_TO_POINTER(id));
    g_signal_connect(widget, "unselect-all", G_CALLBACK(on_unselect_all), GINT_TO_POINTER(id));
    g_signal_connect(widget, "activate-cursor-row", G_CALLBACK(on_activate_cursor_row), GINT_TO_POINTER(id));
    g_signal_connect(widget, "move-cursor", G_CALLBACK(on_move_cursor), GINT_TO_POINTER(id));
    add_widget(id, widget);
    return (id);
}

int ListBoxRowWidget(int id)
{
    GtkWidget *widget;
    widget = gtk_list_box_row_new();
    if (id == ID_ANY)
    {
        id = get_new_id();
    }
    add_widget(id, widget);
    return (id);
}

void InsertListBoxWidget(int id, int child_id, int position)
{
    GtkWidget *widget = get_widget(id);
    g_assert(widget != NULL);
    GtkWidget *child = get_widget(child_id);
    g_assert(child != NULL);
    gtk_list_box_insert(GTK_LIST_BOX(widget), child, position);
}

void PrependListBoxWidget(int id, int child_id)
{
    GtkWidget *widget = get_widget(id);
    g_assert(widget != NULL);
    GtkWidget *child = get_widget(child_id);
    g_assert(child != NULL);
    gtk_list_box_prepend(GTK_LIST_BOX(widget), child);
}



// void ListBoxRemove(int id, int child_id)
// {
//     GtkWidget *widget = get_widget(id);
//     GtkWidget *child = get_widget(child_id);
//     gtk_container_remove(GTK_CONTAINER(widget), child);
// }

// void ListBoxRemoveAll(int id)
// {
//     GtkWidget *widget = get_widget(id);
//     gtk_container_foreach(GTK_CONTAINER(widget), (GtkCallback)gtk_widget_destroy, NULL);
// }

// void ListBoxSetHeader(int id, int child_id)
// {
//     GtkWidget *widget = get_widget(id);
//     GtkWidget *child = get_widget(child_id);
//     gtk_list_box_set_header(GTK_LIST_BOX(widget), child);
// }

// void ListBoxSetFooter(int id, int child_id)
// {
//     GtkWidget *widget = get_widget(id);
//     GtkWidget *child = get_widget(child_id);
//     gtk_list_box_set_footer(GTK_LIST_BOX(widget), child);
// }

// void ListBoxSetSelectionMode(int id, int mode)
// {
//     GtkWidget *widget = get_widget(id);
//     gtk_list_box_set_selection_mode(GTK_LIST_BOX(widget), mode);
// }

// void ListBoxSetActivateOnSingleClick(int id, bool activate)
// {
//     GtkWidget *widget = get_widget(id);
//     gtk_list_box_set_activate_on_single_click(GTK_LIST_BOX(widget), activate);
// }

// void ListBoxSetRowSelected(int id, int row_id, bool selected)
// {
//     GtkWidget *widget = get_widget(id);
//     GtkWidget *row = get_widget(row_id);
//     gtk_list_box_select_row(GTK_LIST_BOX(widget), GTK_LIST_BOX_ROW(row));
// }

// int ListBoxGetSelectedRow(int id)
// {
//     GtkWidget *widget = get_widget(id);
//     GtkWidget *row = gtk_list_box_get_selected_row(GTK_LIST_BOX(widget));
//     return (get_widget_id(row));
// }

// // int ListBoxGetSelectedRows(int id)
// // {
// //     GtkWidget *widget = get_widget(id);
// //     GList *rows = gtk_list_box_get_selected_rows(GTK_LIST_BOX(widget));
// //     int *ids = malloc(sizeof(int) * g_list_length(rows));
// //     int i = 0;
// //     while (rows)
// //     {
// //         ids[i] = get_widget_id(rows->data);
// //         rows = g_list_next(rows);
// //         i++;
// //     }
// //     return (ids);
// // }