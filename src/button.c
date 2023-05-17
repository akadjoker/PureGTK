
#include "PureGTK.h"
#include "intern.h"

extern GHashTable *widgets;




static void button_clicked_callback(GtkButton *button, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	gboolean is_checked = false;
	Event event = {0};
	event.type = EVENT_BUTTON_CLICK;
	event.button.id = widget_id;
	event.button.checked = is_checked;
	push_event(event);
}
static void button_pressed_callback(GtkButton *button, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_BUTTON_PRESS;
	event.button.id = widget_id;
	event.button.checked = false;
	push_event(event);
}

static void button_released_callback(GtkButton *button, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_BUTTON_RELEASE;
	event.button.id = widget_id;
	event.button.checked = false;
	push_event(event);
}


static void button_enter_callback(GtkToggleButton *button, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_BUTTON_ENTER;
	event.button.id = widget_id;
	event.button.checked = false;
	push_event(event);
}

static void button_leave_callback(GtkToggleButton *button, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_BUTTON_LEAVE;
	event.button.id = widget_id;
	event.button.checked = false;
	push_event(event);
}

static void switch_state_callback(GtkSwitch *checkbox, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	gboolean is_checked = gtk_switch_get_state(checkbox);
	Event event = {0};
	event.type = EVENT_SWITCH;
	event.button.checked = is_checked;
	event.button.id = widget_id;
	push_event(event);
	gtk_switch_set_state(checkbox, !is_checked);
}

static void checkbox_toggled_callback(GtkToggleButton *checkbox, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	gboolean is_checked = gtk_toggle_button_get_active(checkbox);
	Event event = {0};
	event.type = EVENT_CHECKBOX;
	event.button.checked = is_checked;
	event.button.id = widget_id;

	push_event(event);
}

static void radio_toggled_callback(GtkRadioButton *radio, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);
	gboolean is_checked = false;//gtk_toggle_button_get_active(radio);
	Event event = {0};
	event.type = EVENT_RADIO;
	event.button.checked = is_checked;
	event.button.id = widget_id;
	push_event(event);
}




int MnemonicButtonWidget(int id,  const gchar *label)
{
	GtkWidget *button;
	button = gtk_button_new_with_mnemonic(label);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), GINT_TO_POINTER(id));
	g_signal_connect(button, "pressed", G_CALLBACK(button_pressed_callback), GINT_TO_POINTER(id));
    g_signal_connect(button, "released", G_CALLBACK(button_released_callback), GINT_TO_POINTER(id));
    g_signal_connect(button, "enter", G_CALLBACK(button_enter_callback), GINT_TO_POINTER(id));
    g_signal_connect(button, "leave", G_CALLBACK(button_leave_callback), GINT_TO_POINTER(id));
	add_widget(id, button);
	Log(0, "MnemonicButtonWidget: %d", id);	
	return (id);
}

int ButtonWidget(int id)
{
	GtkWidget *button;
	button = gtk_button_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	g_signal_connect(button, "clicked", G_CALLBACK(button_clicked_callback), GINT_TO_POINTER(id));
	g_signal_connect(button, "pressed", G_CALLBACK(button_pressed_callback), GINT_TO_POINTER(id));
    g_signal_connect(button, "released", G_CALLBACK(button_released_callback), GINT_TO_POINTER(id));
    g_signal_connect(button, "enter", G_CALLBACK(button_enter_callback), GINT_TO_POINTER(id));
    g_signal_connect(button, "leave", G_CALLBACK(button_leave_callback), GINT_TO_POINTER(id));
	add_widget(id, button);
	Log(0, "ButtonWidget: %d", id);	

 GtkWidget *menu;
  GtkWidget *menu_item;

 // Cria o menu pop-up
  menu = gtk_menu_new();

  // Cria um item de menu e adiciona-o ao menu pop-up
  menu_item = gtk_menu_item_new_with_label("Item de menu");
  //g_signal_connect(menu_item, "activate", G_CALLBACK(on_menu_item_clicked), NULL);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

  // Anexa o menu pop-up ao botão
  gtk_menu_attach_to_widget(GTK_MENU(menu), button, NULL);



	return (id);
}

void ButtonSetLabel(int id, const gchar *label)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_button_set_label(GTK_BUTTON(button), label);
}



void ButtonSetImage(int id, const gchar *image)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	GtkWidget *pimage = gtk_image_new_from_file(image);
	if(pimage == NULL)
	{
		Log(1, "Could not load image: %s", image);
	} else 
	{
		gtk_button_set_image(GTK_BUTTON(button), pimage);
	}
}

void ButtonSetImagePosition(int id, int position)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_button_set_image_position(GTK_BUTTON(button), position);
}

void ButtonSetRelief(int id, int relief)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_button_set_relief(GTK_BUTTON(button), relief);
}

void ButtonSetUseUnderline(int id, bool setting)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_button_set_use_underline(GTK_BUTTON(button), setting);
}




void ButtonSetAlwaysShowImage(int id, bool setting)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_button_set_always_show_image(GTK_BUTTON(button), setting);
}






int SwitchWidget(int id, bool is_active)
{
	
	GtkWidget *button;
	button = gtk_switch_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	gtk_switch_set_active(GTK_SWITCH(button), is_active);
  	g_signal_connect(button, "state-set", G_CALLBACK(switch_state_callback), GINT_TO_POINTER(id));
	add_widget(id, button);
	return (id);
}

void SwitchSetActive(int id, bool value)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_switch_set_active(GTK_SWITCH(button), value);
}

bool SwitchGetActive(int id)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	return (gtk_switch_get_active(GTK_SWITCH(button)));
}


void SwitchSetState(int id, bool value)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	gtk_switch_set_state(GTK_SWITCH(button), value);
}

bool SwitchGetState(int id)
{
	GtkWidget *button;
	button = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(button != NULL);
	return (gtk_switch_get_state(GTK_SWITCH(button)));
}

int LabelWidget(int id,  const gchar *text)
{
	GtkWidget *label;

	label = gtk_label_new(text);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, label);
	return (id);
}

int CheckboxWidget(int id, const char *label, bool state)
{
	GtkWidget *checkbox;
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	checkbox = gtk_check_button_new_with_label(label);
	add_widget(id, checkbox);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), state);
	g_signal_connect(checkbox, "toggled", G_CALLBACK(checkbox_toggled_callback), GINT_TO_POINTER(id));
	add_widget(id, checkbox);
	return (id);
}

bool CheckboxGetState(int id)
{
	GtkWidget *checkbox;
	checkbox = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(checkbox != NULL);
	return (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox)));
}

void CheckboxSetState(int id, bool state)
{
	GtkWidget *checkbox;
	checkbox = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(checkbox != NULL);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbox), state);
}


int RadioWidget(int id, int group_id, const char *label)
{
	if (id == ID_ANY)
	{
		id = get_new_id();
	}

	GtkWidget *group_widget = NULL;
	if (group_id >= 0)
	{
		group_widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(group_id));
	}

	GtkWidget *radio = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(group_widget), label);
	add_widget(id, radio);

	
	g_signal_connect(radio, "toggled", G_CALLBACK(radio_toggled_callback), GINT_TO_POINTER(id));
	add_widget(id, radio);

	return (id);
}

bool RadioGetState(int id)
{
	GtkWidget *radio;
	radio = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(radio != NULL);
	return (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio)));
}

void RadioSetState(int id, bool state)
{
	GtkWidget *radio;
	radio = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(radio != NULL);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio), state);
}