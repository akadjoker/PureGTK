#ifndef INTERN_GTK_LIBRARY_H
#define INTERN_GTK_LIBRARY_H

#include <glib.h>
#include <glib.h>
#include <gtk/gtk.h>

int get_new_id();
int get_tag_table_id();
int get_tag_id();
int get_text_buffer_id();
int get_text_id();

void CleanTextInter();

void push_event(Event event);

void add_widget(int id, GtkWidget *widget);
void add_text_buffer(int id, GtkTextBuffer *buffer);
void add_text_item(int id, GtkTextIter *item);
void add_text_tag(int id, GtkTextTag *tag);
void add_text_tag_table(int id, GtkTextTagTable *tagTable);
GtkWidget *get_widget(int id);
GtkTextBuffer *get_text_buffer(int id);
GtkTextIter *get_text_item(int id);
GtkTextTag *get_text_tag(int id);
GtkTextTagTable *get_text_tag_table(int id);

void Log(int severity, const char *fmt, ...);

#endif 
