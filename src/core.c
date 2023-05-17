
#include "PureGTK.h"
#include "intern.h"

GHashTable *widgets = NULL;
GHashTable *textBuffer = NULL;
GHashTable *textItem = NULL;
GHashTable *textTag = NULL;
GHashTable *textTagTable = NULL;

#define MAX_EVENTS 500

static Event event_stack[MAX_EVENTS];
static int top = -1;

#define CONSOLE_COLOR_RESET "\033[0m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_PURPLE "\033[1;35m"
#define CONSOLE_COLOR_CYAN "\033[0;36m"

void Log(int severity, const char *fmt, ...)
{
    /* Determine strings for the type and colour */
    const char *type;
    const char *color;
    switch (severity)
    {
    case 0:
        type = "info";
        color = CONSOLE_COLOR_GREEN;
        break;
    case 1:
        type = "error";
        color = CONSOLE_COLOR_RED;
        break;
    case 2:
        type = "warning";
        color = CONSOLE_COLOR_PURPLE;
        break;
    default:
        break; /* Unreachable */
    }

    /* Obtain the current date and time */
    time_t rawTime;
    struct tm *timeInfo;
    char timeBuffer[80];

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(timeBuffer, sizeof(timeBuffer), "[%H:%M:%S]", timeInfo);

    /* Format for printing to the console (with colours) */
    char consoleFormat[1024];
    snprintf(consoleFormat, 1024, "PureGTK %s%s %s%s%s: %s\n", CONSOLE_COLOR_CYAN,
             timeBuffer, color, type, CONSOLE_COLOR_RESET, fmt);

    va_list argptr;

    /* Print to the console */
    va_start(argptr, fmt);
    vprintf(consoleFormat, argptr);
    va_end(argptr);
}

void push_event(Event event)
{
    if (top < MAX_EVENTS - 1)
    {
        top++;
        event_stack[top] = event;
    }
}

Event pop_event(void)
{
    Event event;

    if (top >= 0)
    {
        event = event_stack[top];
        top--;
    }
    return (event);
}

bool ProcessEvents(Event *event)
{
    while (gtk_events_pending())
    {
        // gtk_main_iteration();
        gtk_main_iteration_do(0);

        if (top >= 0)
        {
            *event = pop_event();
            return true;
        }
    }
    return (false);
}

void add_widget(int id, GtkWidget *widget)
{
    g_hash_table_insert(widgets, GINT_TO_POINTER(id), widget);
}

void add_text_buffer(int id, GtkTextBuffer *buffer)
{
    g_hash_table_insert(textBuffer, GINT_TO_POINTER(id), buffer);
}

void add_text_item(int id, GtkTextIter *item)
{
    g_hash_table_insert(textItem, GINT_TO_POINTER(id), item);
}

void add_text_tag(int id, GtkTextTag *tag)
{
    g_hash_table_insert(textTag, GINT_TO_POINTER(id), tag);
}

void add_text_tag_table(int id, GtkTextTagTable *tagTable)
{
    g_hash_table_insert(textTagTable, GINT_TO_POINTER(id), tagTable);
}

int get_new_id()
{
    int id = 1;
    GList *keys = g_hash_table_get_keys(widgets);
    GList *current_key = keys;

    // Percorre as chaves da hash table
    while (current_key != NULL)
    {
        int widget_id = GPOINTER_TO_INT(current_key->data);
        if (id <= widget_id)
        {
            id = widget_id + 1;
        }

        current_key = g_list_next(current_key);
    }

    // Verifica se o ID já existe na tabela hash
    while (g_hash_table_contains(widgets, GINT_TO_POINTER(id)))
    {
        id++;
    }

    g_list_free(keys);
    return id;
}

int get_text_buffer_id()
{
    int id = 1;
    GList *keys = g_hash_table_get_keys(textBuffer);
    GList *current_key = keys;
    while (current_key != NULL)
    {
        int widget_id = GPOINTER_TO_INT(current_key->data);
        if (id <= widget_id)
        {
            id = widget_id + 1;
        }
        current_key = g_list_next(current_key);
    }
    while (g_hash_table_contains(textBuffer, GINT_TO_POINTER(id)))
    {
        id++;
    }
    g_list_free(keys);
    return id;
}

int get_text_id()
{
    int id = 1;
    GList *keys = g_hash_table_get_keys(textItem);
    GList *current_key = keys;
    while (current_key != NULL)
    {
        int widget_id = GPOINTER_TO_INT(current_key->data);
        if (id <= widget_id)
        {
            id = widget_id + 1;
        }
        current_key = g_list_next(current_key);
    }
    while (g_hash_table_contains(textItem, GINT_TO_POINTER(id)))
    {
        id++;
    }
    g_list_free(keys);
    return id;
}

int get_tag_id()
{
    int id = 1;
    GList *keys = g_hash_table_get_keys(textTag);
    GList *current_key = keys;
    while (current_key != NULL)
    {
        int widget_id = GPOINTER_TO_INT(current_key->data);
        if (id <= widget_id)
        {
            id = widget_id + 1;
        }
        current_key = g_list_next(current_key);
    }
    while (g_hash_table_contains(textTag, GINT_TO_POINTER(id)))
    {
        id++;
    }
    g_list_free(keys);
    return id;
}

int get_tag_table_id()
{
    int id = 1;
    GList *keys = g_hash_table_get_keys(textTagTable);
    GList *current_key = keys;
    while (current_key != NULL)
    {
        int widget_id = GPOINTER_TO_INT(current_key->data);
        if (id <= widget_id)
        {
            id = widget_id + 1;
        }
        current_key = g_list_next(current_key);
    }
    while (g_hash_table_contains(textTag, GINT_TO_POINTER(id)))
    {
        id++;
    }
    g_list_free(keys);
    return id;
}

GtkWidget *get_widget(int id)
{
    return g_hash_table_lookup(widgets, GINT_TO_POINTER(id));
}

GtkTextBuffer *get_text_buffer(int id)
{
    return g_hash_table_lookup(textBuffer, GINT_TO_POINTER(id));
}

GtkTextIter *get_text_item(int id)
{
    return g_hash_table_lookup(textItem, GINT_TO_POINTER(id));
}

GtkTextTag *get_text_tag(int id)
{
    return g_hash_table_lookup(textTag, GINT_TO_POINTER(id));
}

GtkTextTagTable *get_text_tag_table(int id)
{
    return g_hash_table_lookup(textTagTable, GINT_TO_POINTER(id));
}

void remove_widget(int id)
{
    g_hash_table_remove(widgets, GINT_TO_POINTER(id));
}

void remove_text_buffer(int id)
{
    g_hash_table_remove(textBuffer, GINT_TO_POINTER(id));
}

void remove_text_item(int id)
{
    g_hash_table_remove(textItem, GINT_TO_POINTER(id));
}

void remove_text_tag(int id)
{
    g_hash_table_remove(textTag, GINT_TO_POINTER(id));
}

void remove_text_tag_table(int id)
{
    g_hash_table_remove(textTagTable, GINT_TO_POINTER(id));
}



// static gboolean log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
// {
//     Log(0, "%s", message);
//     return TRUE;
// }

void CleanTextInter()
{
 
    g_hash_table_remove_all(textItem);
}

void InitLibrary()
{
    gtk_init(0, NULL);
    //gdk_threads_init(); // Inicializa as threads do GDK
    //g_log_set_handler(NULL, G_LOG_LEVEL_DEBUG, log_handler, NULL);
    widgets = g_hash_table_new(g_direct_hash, g_direct_equal);
    textBuffer = g_hash_table_new(g_direct_hash, g_direct_equal);

    // textItem = g_hash_table_new(g_direct_hash, g_direct_equal);
    textItem = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, g_free);

    textTag = g_hash_table_new(g_direct_hash, g_direct_equal);
    textTagTable = g_hash_table_new(g_direct_hash, g_direct_equal);
}

void FreeLibrary(void)
{
    CleanTextInter();
    g_hash_table_destroy(widgets);
    g_hash_table_destroy(textBuffer);
    g_hash_table_destroy(textItem);
    g_hash_table_destroy(textTag);
    g_hash_table_destroy(textTagTable);

    // gtk_main_quit();
}
