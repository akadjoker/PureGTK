
#include "PureGTK.h"
#include "intern.h"


extern GHashTable	*widgets;


int	FixedLayout(int id)
{
	GtkWidget	*fixed;
	fixed = gtk_fixed_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, fixed);
//	Log(0, "FixedLayout: %d", id);
	return (id);
}

void FixedAdd(int id, int child_id, int x, int y)
{
	GtkWidget	*fixed;
	GtkWidget	*child;

	fixed = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(fixed != NULL);

	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	
	gtk_fixed_put(GTK_FIXED(fixed), child, x, y);
}

void FixedMove(int id, int child_id, int x, int y)
{
	GtkWidget	*fixed;
	GtkWidget	*child;

	fixed = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(fixed != NULL);
	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	gtk_fixed_move(GTK_FIXED(fixed), child, x, y);
}




void AddLayoutChild(int id, int child_id)
{
	GtkWidget	*layout;
	GtkWidget	*child;

	layout = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(layout != NULL);
	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	gtk_container_add(GTK_CONTAINER(layout), child);
}

//*********************************************************************************************************************
//FRAME LAYOUT
//*********************************************************************************************************************

int	FrameLayout(int id, const char *label)
{
	GtkWidget	*frame;
	frame = gtk_frame_new(label);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, frame);
	Log(0, "FrameLayout: %d", id);	
	return (id);
}


//*********************************************************************************************************************
//BOX LAYOUT
//*********************************************************************************************************************

int	BoxLayout(int id, Orientation orientation, int spacing)
{
	GtkWidget	*box;
	box = gtk_box_new((int)orientation, spacing);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, box);
	Log(0, "BoxLayout: %d", id);	
	return (id);
}

void BoxSetSpacing(int id, int spacing)
{
	GtkWidget	*box;
	box = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(box != NULL);
	gtk_box_set_spacing(GTK_BOX(box), spacing);
}

void BoxSetHomogeneous(int id, bool homogeneous)
{
	GtkWidget	*box;
	box = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(box != NULL);
	gtk_box_set_homogeneous(GTK_BOX(box), homogeneous);
}

void BoxPackStart(int id, int child_id, bool expand, bool fill, int padding)
{
	GtkWidget	*box;
	GtkWidget	*child;

	box = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(box != NULL);
	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	gtk_box_pack_start(GTK_BOX(box), child, expand, fill, padding);
}

void BoxPackEnd(int id, int child_id, bool expand, bool fill, int padding)
{
	GtkWidget	*box;
	GtkWidget	*child;

	box = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(box != NULL);
	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	gtk_box_pack_end(GTK_BOX(box), child, expand, fill, padding);
}

void BoxReorderChild(int id, int child_id, int position)
{
	GtkWidget	*box;
	GtkWidget	*child;

	box = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(box != NULL);
	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	gtk_box_reorder_child(GTK_BOX(box), child, position);
}

void SetBoxWidgetCenter(int id, int child_id)
{
	GtkWidget	*box;
	GtkWidget	*child;
	box = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(box != NULL);
	child = g_hash_table_lookup(widgets, GINT_TO_POINTER(child_id));
	g_assert(child != NULL);
	gtk_box_set_center_widget(GTK_BOX(box), child);
}

//************************************************************************************************************************************
//SCROLL VIEW LAYOUT
//************************************************************************************************************************************


int	ScrollViewLayout(int id)
{
	GtkWidget	*scrollview;
	scrollview = gtk_scrolled_window_new(NULL, NULL);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, scrollview);
	Log(0, "ScrollViewLayout: %d", id);	
	return (id);
}


