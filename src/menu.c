

#include "PureGTK.h"
#include "intern.h"

extern GHashTable *widgets;


static void on_menu_item_clicked(GtkMenuItem *menu_item, gpointer data) 
{
    int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_MENU;
	event.menu.id = widget_id;
    event.menu.label = gtk_menu_item_get_label(menu_item);
 
    //Log(0,"on_menu_item_clicked: %d %s", widget_id, event.menu.label);

	push_event(event);

    
}

/*
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);

    GtkWidget *file_menu_item = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_menu_item);

    GtkWidget *file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu_item), file_menu);

    GtkWidget *exit_menu_item = gtk_menu_item_new_with_label("Exit");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_menu_item);
    g_signal_connect(exit_menu_item, "activate", G_CALLBACK(on_exit_menu_item_activate), NULL);
*/
int MenuWidget(int id) 
{
   GtkWidget *menu = gtk_menu_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
    add_widget(id, menu);
   return id;
}
// int MenuItemWidget(int itemId, int menuId, int submenuId, const char* label) 
// {
//     GtkWidget *menu = gtk_menu_new();
// 	if (menuId == ID_ANY)
// 	{
// 		menuId = get_new_id();
// 	}
//     add_widget(menuId, menu);

//     GtkWidget *menu_item = gtk_menu_item_new_with_label(label);
//     if (submenuId == ID_ANY)
//     {
//         submenuId = get_new_id();
//     }
//     add_widget(submenuId, menu_item);
//     g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), GINT_TO_POINTER(menu_item));

//     GtkWidget *item_menu_parent = g_hash_table_lookup(widgets, GINT_TO_POINTER(itemId));
//     g_assert(item_menu_parent != NULL);

//     gtk_menu_item_set_submenu(GTK_MENU_ITEM(item_menu_parent), menu);

//     gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

//     return menuId;
// }

int MenuSeparatorWidget(int itemId, int menuId) 
{
    
    GtkWidget *menu_item = gtk_separator_menu_item_new();
    if (itemId == ID_ANY)
    {
        itemId = get_new_id();
    }
    add_widget(itemId, menu_item);


    GtkWidget *menu = g_hash_table_lookup(widgets, GINT_TO_POINTER(menuId));
    g_assert(menu != NULL);    


    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    return menuId;
}

int MenuBarWidget(int id) 
{
   GtkWidget *menu = gtk_menu_bar_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
    add_widget(id, menu);
   return id;
}


int AppendMenuItemWidget(int id, const char *label, int menu_id) 
{
    GtkWidget *menu = g_hash_table_lookup(widgets, GINT_TO_POINTER(menu_id));
    g_assert(menu != NULL);
    GtkWidget *menu_item = gtk_menu_item_new_with_mnemonic(label);
    if (id == ID_ANY)
    {
        id = get_new_id();
    }
    add_widget(id, menu_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), GINT_TO_POINTER(id));

//     g_signal_connect(exit_menu_item, "activate", G_CALLBACK(on_exit_menu_item_activate), NULL);


    return id;
}
int PrependMenuItemWidget(int id, const char *label, int menu_id) 
{
    GtkWidget *menu = g_hash_table_lookup(widgets, GINT_TO_POINTER(menu_id));
    g_assert(menu != NULL);
    GtkWidget *menu_item = gtk_menu_item_new_with_mnemonic(label);
    if (id == ID_ANY)
    {
        id = get_new_id();
    }
    add_widget(id, menu_item);
    gtk_menu_shell_prepend(GTK_MENU_SHELL(menu), menu_item);
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), GINT_TO_POINTER(id));
    return id;
}
int IncertMenuItemWidget(int id, const char *label, int menu_id, int position) 
{
    GtkWidget *menu = g_hash_table_lookup(widgets, GINT_TO_POINTER(menu_id));
    g_assert(menu != NULL);
    GtkWidget *menu_item = gtk_menu_item_new_with_mnemonic(label);
    if (id == ID_ANY)
    {
        id = get_new_id();
    }
    add_widget(id, menu_item);
    gtk_menu_shell_insert(GTK_MENU_SHELL(menu), menu_item, position);
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), GINT_TO_POINTER(id));
    return id;
}



void AttachMenu(int menu_id, int widgetID) 
{
    GtkWidget *menu = g_hash_table_lookup(widgets,  GINT_TO_POINTER(menu_id));
    g_assert(menu != NULL);

    GtkWidget *widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(widgetID));
    g_assert(widget != NULL);
   
    gtk_menu_attach_to_widget(GTK_MENU(menu), widget, NULL);
   
}

void SetMenuItemSubMenu(int menuId, int submenuId) 
{
    GtkWidget *menu = g_hash_table_lookup(widgets,  GINT_TO_POINTER(menuId));
    g_assert(menu != NULL);

    GtkWidget *submenu = g_hash_table_lookup(widgets, GINT_TO_POINTER(submenuId));
    g_assert(submenu != NULL);
   
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(submenu), menu);
   
}