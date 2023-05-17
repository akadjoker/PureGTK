
#include "PureGTK.h"
#include "intern.h"
extern GHashTable *widgets;

//*******************************************************************************************************************************
// SpinButton
//*******************************************************************************************************************************

static void spin_value_changed(GtkSpinButton *w, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);

	Event event = {0};
	event.type = EVENT_VALUE_CHANGED;
	event.value.data = gtk_spin_button_get_value(w);
	event.value.id = widget_id;
	push_event(event);
}

void SpinButtonSetSnapToTicks(int id, bool snap)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_set_snap_to_ticks(GTK_SPIN_BUTTON(widget), snap);
	}
}

int SpinButtonWidget(int id, double min, double max, double step)
{
	GtkWidget *widget;
	widget = gtk_spin_button_new_with_range(min, max, step);

	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	g_signal_connect(widget, "value-changed", G_CALLBACK(spin_value_changed), GINT_TO_POINTER(id));
	add_widget(id, widget);
	return (id);
}

void SpinButtonSetDigits(int id, int digits)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_set_digits(GTK_SPIN_BUTTON(widget), digits);
	}
}

int SpinButtonGetDigits(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_spin_button_get_digits(GTK_SPIN_BUTTON(widget)));
	}
	return (0);
}

void SpinButtonSetIncrements(int id, double step, double page)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_set_increments(GTK_SPIN_BUTTON(widget), step, page);
	}
}

void SpinButtonSetRange(int id, double min, double max)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_set_range(GTK_SPIN_BUTTON(widget), min, max);
	}
}

void SpinButtonSetWrap(int id, bool wrap)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(widget), wrap);
	}
}

void SpinButtonSetNumeric(int id, bool numeric)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(widget), numeric);
	}
}

double SpinButtonGetValue(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_spin_button_get_value(GTK_SPIN_BUTTON(widget)));
	}
	return (0);
}

int SpinButtonGetIntValue(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget)));
	}
	return (0);
}

// gtk_spin_button_spin
void SpinButtonOrientaion(int id, int direction, double increment)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_spin_button_spin(GTK_SPIN_BUTTON(widget), direction, increment);
	}
}

//*******************************************************************************************************************************
// Scale Bar
//*******************************************************************************************************************************

static void range_value_changed(GtkRange *w, gpointer data)
{
	int widget_id = GPOINTER_TO_INT(data);

	Event event = {0};
	event.type = EVENT_VALUE_CHANGED;
	event.value.data = gtk_range_get_value(w);
	event.value.id = widget_id;

	push_event(event);
}

/*
void              gtk_scale_add_mark           (GtkScale        *scale,
												gdouble          value,
												GtkPositionType  position,
												const gchar     *markup);
void              gtk_scale_clear_marks        (GtkScale        *scale);
*/

int ScaleWidget(int id, Orientation orientation, double min, double max, double step)
{
	GtkWidget *widget;
	widget = gtk_scale_new_with_range((int)orientation, min, max, step);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	g_signal_connect(widget, "value-changed", G_CALLBACK(range_value_changed), GINT_TO_POINTER(id));
	add_widget(id, widget);
	return (id);
}

void SetScaleDigits(int id, int digits)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_scale_set_digits(GTK_SCALE(widget), digits);
	}
}

int GetScaleDigits(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_scale_get_digits(GTK_SCALE(widget)));
	}
	return (0);
}

void SetScaleDrawValue(int id, bool draw_value)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_scale_set_draw_value(GTK_SCALE(widget), draw_value);
	}
}

bool GetScaleDrawValue(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_scale_get_draw_value(GTK_SCALE(widget)));
	}
	return (0);
}

void SetScaleHasOrigin(int id, bool has_origin)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_scale_set_has_origin(GTK_SCALE(widget), has_origin);
	}
}

bool GetScaleHasOrigin(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_scale_get_has_origin(GTK_SCALE(widget)));
	}
	return (0);
}

void SetScaleValuePos(int id, int pos)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_scale_set_value_pos(GTK_SCALE(widget), pos);
	}
}

int GetScaleValuePos(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		return (gtk_scale_get_value_pos(GTK_SCALE(widget)));
	}
	return (0);
}

void AddScaleMark(int id, double value, PositionType position, const char *markup)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_scale_add_mark(GTK_SCALE(widget), value, (int)position, markup);
	}
}

void ClearScaleMarks(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	if (widget)
	{
		gtk_scale_clear_marks(GTK_SCALE(widget));
	}
}

//*******************************************************************************************************************************
// PrograssBar
//*******************************************************************************************************************************
// static void progress_value_changed(GtkProgressBar *w, gpointer data)
// {
// 	int widget_id = GPOINTER_TO_INT(data);

// 	Event event = {0};
// 	event.type = EVENT_VALUE_CHANGED;
// 	event.value.data = gtk_progress_bar_get_fraction(w);
// 	event.value.id = widget_id;
// 	push_event(event);
// }

// static void progress_value_pulse(GtkProgressBar *w, gpointer data)
// {
// 	int widget_id = GPOINTER_TO_INT(data);

// 	Event event = {0};
// 	event.type = EVENT_VALUE;
// 	event.value.data = gtk_progress_bar_get_fraction(w);
// 	event.value.id = widget_id;
// 	push_event(event);
// }

int ProgressBarWidget(int id)
{

	GtkWidget *widget;
	widget = gtk_progress_bar_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, widget);
	return (id);
}

void SetProgressBarOrientation(int id, Orientation orientation)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
  	GtkOrientable *orw=  GTK_ORIENTABLE(progress_bar);
	g_assert(orw != NULL);			
	gtk_orientable_set_orientation(orw,(int)orientation);
}

int GetProgressBarOrientation(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	GtkOrientable *orw=  GTK_ORIENTABLE(progress_bar);
	g_assert(orw != NULL);
	return (gtk_orientable_get_orientation(orw));
}

void SetProgressBarText(int id, const char *text)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	gtk_progress_bar_set_text(progress_bar, text);
}

const char *GetProgressBarText(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	return (gtk_progress_bar_get_text(progress_bar));
}

void SetProgressBarFraction(int id, double fraction)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	gtk_progress_bar_set_fraction(progress_bar, fraction);
}

double GetProgressBarFraction(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	return (gtk_progress_bar_get_fraction(progress_bar));
}

void SetProgressBarPulseStep(int id, double fraction)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	gtk_progress_bar_set_pulse_step(progress_bar, fraction);
}


double GetProgressBarPulseStep(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	return (gtk_progress_bar_get_pulse_step(progress_bar));
}


void SetProgressBarInverted(int id, bool inverted)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	gtk_progress_bar_set_inverted(progress_bar, inverted);

}

bool GetProgressBarInverted(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	return (gtk_progress_bar_get_inverted(progress_bar));
}

void SetProgressBarEllipsize(int id, EllipsizeMode mode)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	gtk_progress_bar_set_ellipsize(progress_bar, (int)mode);
}


int GetProgressBarEllipsize(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	return (gtk_progress_bar_get_ellipsize(progress_bar));
}


void SetProgressBarShowText(int id, bool show_text)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	gtk_progress_bar_set_show_text(progress_bar, show_text);

}

bool GetProgressBarShowText(int id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkProgressBar *progress_bar = GTK_PROGRESS_BAR(widget);
	g_assert(progress_bar != NULL);
	return gtk_progress_bar_get_show_text(progress_bar);
}
