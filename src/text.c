

#include "PureGTK.h"
#include "intern.h"

extern GHashTable *widgets;
extern GHashTable *textBuffer;
extern GHashTable *textTag ;
extern GHashTable *textTagTable;
extern GHashTable *textItem;


static void entry_search_changed(GtkSearchEntry *search_entry, gpointer data)
{
    const char *text = gtk_entry_get_text(GTK_ENTRY(search_entry));
    int widget_id = GPOINTER_TO_INT(data);
	Event event = {0};
	event.type = EVENT_ENTRY_CHANGED;
	event.entry.text = text;
	event.entry.id = widget_id;
	push_event(event);
}


static void entry_activated_callback(GtkEntry *entry, gpointer data)
{
	int widget_id;

	widget_id = GPOINTER_TO_INT(data);

	const char *text = gtk_entry_get_text(entry);
	Event event = {0};
	event.type = EVENT_ENTRY;
	event.entry.text = text;
	event.entry.id = widget_id;

	push_event(event);
}


static void entry_changed_callback(GtkEntry *entry, gpointer data)
{
	int widget_id;

	widget_id = GPOINTER_TO_INT(data);

	const char *text = gtk_entry_get_text(entry);
	Event event = {0};
	event.type = EVENT_ENTRY_CHANGED;
	event.entry.text = text;
	event.entry.id = widget_id;

	push_event(event);
}

//***************************************************************************************************************************
// Text
//***************************************************************************************************************************
int EntrySearchWidget(int id,  const char *text)
{
	GtkWidget *widget;
	widget = gtk_search_entry_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
    g_signal_connect(widget, "activate", G_CALLBACK(entry_search_changed),  GINT_TO_POINTER(id));
	add_widget(id, widget);
	return (id);
}



//***************************************************************************************************************************
// Entry
//***************************************************************************************************************************

int EntryWidget(int id,const char *text)
{
	
	GtkWidget *widget;

	widget = gtk_entry_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
    gtk_entry_set_text(GTK_ENTRY(widget), text);
    g_signal_connect(widget, "activate", G_CALLBACK(entry_activated_callback), GINT_TO_POINTER(id));
    g_signal_connect(widget, "changed", G_CALLBACK(entry_changed_callback), GINT_TO_POINTER(id));
	add_widget(id, widget);
	return (id);
}




void EntrySetHasFrame(int id, bool editable)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_has_frame(GTK_ENTRY(widget), editable);
}

void EntrySetProgressFraction(int id, double fraction)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_progress_fraction(GTK_ENTRY(widget), fraction);
}

void EntrySetProgressPulseStep(int id, double fraction)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_progress_pulse_step(GTK_ENTRY(widget), fraction);
}

void EntrySetEditable(int id, bool editable)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_editable_set_editable(GTK_EDITABLE(widget), editable);
}





void EntrySetVisibility(int id, bool visible)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_visibility(GTK_ENTRY(widget), visible);
}

void EntrySetInvisibleChar(int id, char ch)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_invisible_char(GTK_ENTRY(widget), ch);
}

void EntrySetMaxLength(int id, int max_length)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_max_length(GTK_ENTRY(widget), max_length);
}

void EntrySetText(int id, const char *text)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_text(GTK_ENTRY(widget), text);
}


void EntrySetPlaceholderText(int id, const char *text)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_placeholder_text(GTK_ENTRY(widget), text);
}

void EntrySetAlignment(int id, float xalign)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_alignment(GTK_ENTRY(widget), xalign);
}

void EntrySetOverwriteMode(int id, bool overwrite)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_overwrite_mode(GTK_ENTRY(widget), overwrite);
}

void EntrySetAlignmen(int id, float xalign)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_alignment(GTK_ENTRY(widget), xalign);
}

void EntrySetWidthChars(int id, int n_chars)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_width_chars(GTK_ENTRY(widget), n_chars);
}


void EntrySetMaxWidthChars(int id, int n_chars)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_max_width_chars(GTK_ENTRY(widget), n_chars);
}


void EntrySetActivatesDefault(int id, bool setting)
{
	GtkWidget *widget;

	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_entry_set_activates_default(GTK_ENTRY(widget), setting);
}


//***********************************************************************************************************************
// Text Widget
//***********************************************************************************************************************

int TextWidget(int id)
{
	GtkWidget *widget;
	widget = gtk_text_view_new();
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
  	add_widget(id, widget);
	return (id);
}

int TextWidgetWithBuffer(int id, int buffer_id)
{
	GtkWidget *widget;
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(buffer_id));
	g_assert(buffer != NULL);
	widget = gtk_text_view_new_with_buffer(buffer);
	if (id == ID_ANY)
	{
		id = get_new_id();
	}
	add_widget(id, widget);
	return (id);
}

int GetTextViewBuffer(int id,int buffer_id)
{
	GtkWidget *widget;
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widget));
	if (buffer_id == ID_ANY)
	{
		buffer_id = get_text_buffer_id();
	}
  	add_text_buffer(buffer_id, buffer);
	return (buffer_id);
}

int GetTextTableTag(int id,int tagTable_id)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	
	GtkTextTagTable *tag = gtk_text_buffer_get_tag_table(buffer);
	g_assert(tag != NULL);
	if (tagTable_id == ID_ANY)
	{
		tagTable_id = get_tag_table_id();
	}
  	add_text_tag_table(tagTable_id, tag);
	return (tagTable_id);
}


void SetTextViewBuffer(int id,int buffer_id)
{
	GtkWidget *widget;
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(buffer_id));
	g_assert(buffer != NULL);
	widget = g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
	g_assert(widget != NULL);
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(widget), buffer);
}


//***********************************************************************************************************************
// Text Buffer
//***********************************************************************************************************************
int TextBuffer(int id)
{
	if (id == ID_ANY)
	{
		id = get_text_buffer_id();
	}
	GtkTextBuffer *buffer = gtk_text_buffer_new(NULL);
  	add_text_buffer(id, buffer);
	return (id);
}

int TextBufferTableTag(int id,int tagTableId)
{
	GtkTextBuffer   *buffer;
	GtkTextTagTable *tag;
	tag = g_hash_table_lookup(textTagTable, GINT_TO_POINTER(tagTableId));
	g_assert(tag != NULL);
	if (id == ID_ANY)
	{
		id = get_text_buffer_id();
	}
	buffer = gtk_text_buffer_new(tag);
  	add_text_buffer(id, buffer);
	return (id);
}


int StartTextIter(int id, int item_id)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);

	GtkTextIter *item = g_new(GtkTextIter, 1);
	if (item_id == ID_ANY)
	{
		item_id = get_text_id();
	}
	gtk_text_buffer_get_start_iter(buffer, item);
  	add_text_item(item_id, item);
	return (item_id);
}

int EndTextIter(int id, int item_id)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	GtkTextIter *item = g_new(GtkTextIter, 1);
	if (item_id == ID_ANY)
	{
		item_id = get_text_id();
	}
	gtk_text_buffer_get_end_iter(buffer, item);
  	add_text_item(item_id, item);
	return (item_id);
}

void SetBufferText(int id, const char *text,int len)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	gtk_text_buffer_set_text(buffer, text, len);
}

void TextInsertIter(int id, int item_id, const char *text,int len)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	

	GtkTextIter *item;
	
	item = g_hash_table_lookup(textItem, GINT_TO_POINTER(item_id));
	g_assert(item != NULL);
	gtk_text_buffer_insert(buffer, item, text, len);


}



void TextInsertTagByName(int id, int item_id, const char* tagName, const char *text,int len)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	

	GtkTextIter *item;
	item = g_hash_table_lookup(textItem, GINT_TO_POINTER(item_id));
	g_assert(item != NULL);
	
   gtk_text_buffer_insert_with_tags_by_name(buffer, item,text, len, tagName, NULL);
}

void TextInsertTag(int id, int item_id, int tag_id, const char *text,int len)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	

	GtkTextIter *item;
	item = g_hash_table_lookup(textItem, GINT_TO_POINTER(item_id));
	g_assert(item != NULL);

	GtkTextTag *tag;
	tag = g_hash_table_lookup(textTag, GINT_TO_POINTER(tag_id));
	g_assert(tag != NULL);

	gtk_text_buffer_insert_with_tags(buffer, item, text, len, tag, NULL);
}


void TextInsertAtCursor(int id, const char *text,int len)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	gtk_text_buffer_insert_at_cursor(buffer, text, len);
}





int GetTextBufferLineCount(int id)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	return (gtk_text_buffer_get_line_count(buffer));
}

int GetTextBufferCharCount(int id)
{
	GtkTextBuffer *buffer;
	buffer = g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
	g_assert(buffer != NULL);
	return (gtk_text_buffer_get_char_count(buffer));
}

//text view tags

int TextTag(int id, const  char  *name)
{
	GtkTextTag *tag;
	if (id == ID_ANY)
	{
		id = get_tag_id();
	}
	tag = gtk_text_tag_new(name);
  	add_text_tag(id, tag);
	return (id);
}

void SetTagIntProperty(int id, const char *name, int value)
{
	GtkTextTag *tag;
	tag = g_hash_table_lookup(textTag, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	g_object_set(tag, name, value, NULL);
}
void SetTagFloatProperty(int id, const char *name, float value)
{
	GtkTextTag *tag;
	tag = g_hash_table_lookup(textTag, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	g_object_set(tag, name, value, NULL);
}

void SetTagStringProperty(int id, const char *name, const char* value)
{
	GtkTextTag *tag;
	tag = g_hash_table_lookup(textTag, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	g_object_set(tag, name, value, NULL);
}



//Table Tag

int TextTableTag(int id)
{
	GtkTextTagTable *tag;
	if (id == ID_ANY)
	{
		id = get_tag_table_id();
	}
	tag = gtk_text_tag_table_new();
  	add_text_tag_table(id, tag);
	return (id);
}

void AddTextTableTag(int id,int tagId)
{
	GtkTextTagTable *tag;
	GtkTextTag *tagItem;
	tag = g_hash_table_lookup(textTagTable, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	tagItem = g_hash_table_lookup(textTag, GINT_TO_POINTER(tagId));
	g_assert(tagItem != NULL);
	gtk_text_tag_table_add(tag, tagItem);
	
}

int GetTextTableTagSize(int id)
{
	GtkTextTagTable *tag;
	tag = g_hash_table_lookup(textTagTable, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	return (gtk_text_tag_table_get_size(tag));
}

void RemoveTextTableTag(int id,int tagId)
{
	GtkTextTagTable *tag;
	GtkTextTag *tagItem;
	tag = g_hash_table_lookup(textTagTable, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	tagItem = g_hash_table_lookup(textTag, GINT_TO_POINTER(tagId));
	g_assert(tagItem != NULL);
	gtk_text_tag_table_remove(tag, tagItem);
}


bool FindTextTableTag(int id,const char *name, int tagId)
{
	GtkTextTagTable *tag;
	GtkTextTag *tagItem;
	tag = g_hash_table_lookup(textTagTable, GINT_TO_POINTER(id));
	g_assert(tag != NULL);
	tagItem = gtk_text_tag_table_lookup(tag, name);
	if (tagItem == NULL)
	{
		return false;
	}
	add_text_tag(tagId, tagItem);
	return true;
}