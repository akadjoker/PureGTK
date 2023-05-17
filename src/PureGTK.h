#ifndef PURE_GTK_LIBRARY_H
#define PURE_GTK_LIBRARY_H

#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
#include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
typedef enum bool
{
	false = 0,
	true = !false
} bool;
#define BOOL_TYPE
#endif

#ifdef _WIN32
    #ifdef LIBRARY_EXPORTS
        #define LIBRARY_API __declspec(dllexport)
    #else
        #define LIBRARY_API __declspec(dllimport)
    #endif
#else
    #define LIBRARY_API __attribute__((visibility("default")))
#endif


#define ID_ANY -1
typedef void *POINTER;
typedef unsigned char Uint8;

typedef enum
{
	RELIEF_NORMAL,
	RELIEF_HALF,
	RELIEF_NONE
} ReliefStyle;

typedef enum
{
  HORIZONTAL,
  VERTICAL
} Orientation;

typedef enum
{
  POS_LEFT,
  POS_RIGHT,
  POS_TOP,
  POS_BOTTOM
} PositionType;

typedef enum {
  ELLIPSIZE_NONE,
  ELLIPSIZE_START,
  ELLIPSIZE_MIDDLE,
  ELLIPSIZE_END
} EllipsizeMode;

typedef enum
{
  SPIN_STEP_FORWARD,
  SPIN_STEP_BACKWARD,
  SPIN_PAGE_FORWARD,
  SPIN_PAGE_BACKWARD,
  SPIN_HOME,
  SPIN_END,
  SPIN_USER_DEFINED
} SpinType;

typedef enum
{
	GRAVITY_NORTH_WEST = 1,
	GRAVITY_NORTH,
	GRAVITY_NORTH_EAST,
	GRAVITY_WEST,
	GRAVITY_CENTER,
	GRAVITY_EAST,
	GRAVITY_SOUTH_WEST,
	GRAVITY_SOUTH,
	GRAVITY_SOUTH_EAST,
	GRAVITY_STATIC
} Gravity;

typedef enum 
{
  FONT_WEIGHT_THIN = 100,
  FONT_WEIGHT_ULTRALIGHT = 200,
  FONT_WEIGHT_LIGHT = 300,
  FONT_WEIGHT_SEMILIGHT = 350,
  FONT_WEIGHT_BOOK = 380,
  FONT_WEIGHT_NORMAL = 400,
  FONT_WEIGHT_MEDIUM = 500,
  FONT_WEIGHT_SEMIBOLD = 600,
  FONT_WEIGHT_BOLD = 700,
  FONT_WEIGHT_ULTRABOLD = 800,
  FONT_WEIGHT_HEAVY = 900,
  FONT_WEIGHT_ULTRAHEAVY = 1000
} FontWeight;

typedef enum
{
	VALUE_DOUBLE = 0,
	VALUE_INT = 1
} VALUE_TYPE;

typedef enum
{
	EVENT_NONE = 0,
	EVENT_CLOSE,
	EVENT_RESIZE,
	EVENT_MENU,
	EVENT_BUTTON_CLICK,
	EVENT_BUTTON_PRESS,
	EVENT_BUTTON_RELEASE,
	EVENT_BUTTON_ENTER,
	EVENT_BUTTON_LEAVE,
	EVENT_CHECKBOX,
	EVENT_RADIO,
	EVENT_SWITCH,
	EVENT_ENTRY,
	EVENT_ENTRY_CHANGED,
	EVENT_VALUE,
	EVENT_VALUE_CHANGED,
    EVENT_LIST,
	EVENT_LIST_CHANGED,
	EVENT_KEY_PRESSED,
	EVENT_KEY_RELEASED,
	EVENT_MOUSE_PRESSED,
	EVENT_MOUSE_RELEASED,
	EVENT_MOUSE_MOVED,
	EVENT_MOUSE_DRAGGED,
	EVENT_MOUSE_ENTERED,
	EVENT_MOUSE_EXITED,
	EVENT_MOUSE_WHEEL,
	EVENT_PAINT,
	EVENT_TIMER,
	EVENT_USER
} EventType;

typedef struct EventResize
{
	int id; // widget id
	int width;
	int height;
} EventResize;

typedef struct EventClose
{
	int id; // widget id
} EventClose;

typedef struct EventButton
{
	int id;
	const char *label;
	bool checked;
} EventButton;

typedef struct EventEntry
{
	int id;
	const char *text;
} EventEntry;

typedef struct EventList
{
	int   id;
	const char *text;
	int   index;
	bool selected;
} EventList;

typedef union Value
{
	double d;
	int i;
} Value;

typedef struct EventValue
{
	int id;
	double data;
} EventValue;


typedef struct EventMenu
{
	int id;
	const char *label;
} EventMenu;

typedef struct Event
{
	Uint8 type;
	EventResize resize;
	EventClose close;
	EventButton button;
	EventEntry entry;
	EventValue value;
	EventMenu menu;
	EventList list;
} Event;

#if defined(__cplusplus)
extern "C" {            // Prevents name mangling of functions
#endif

LIBRARY_API void InitLibrary(void);
LIBRARY_API void FreeLibrary(void);
LIBRARY_API bool ProcessEvents(Event *event);

LIBRARY_API int OpenWindow(int id, int x, int y, int width, int height, const char *title);
LIBRARY_API void ShowWindow(int id);
LIBRARY_API void CloseWindow(int id);
LIBRARY_API void SetWindowSize(int id, int width, int height);
LIBRARY_API void SetWindowPosition(int id, int x, int y);
LIBRARY_API void SetWindowTitle(int id, const char *title);
LIBRARY_API void SetWindowIcon(int id, const char *icon);
LIBRARY_API void SetWindowResizable(int id, bool setting);
LIBRARY_API void SetWindowOpacity(int id, double opacity);
LIBRARY_API void SetWindowModal(int id, bool modal);
LIBRARY_API void SetWindowFocus(int id, int widget);
LIBRARY_API void SetWindowAttachedTo(int id, int widget);
LIBRARY_API void SetWindowGravity(int id, int gravity);
LIBRARY_API void SetWindowMaximized(int id, bool maximized);
LIBRARY_API void SetWindowFullscreen(int id, bool fullscreen);

// layouts
LIBRARY_API  int FixedLayout(int id);
LIBRARY_API void FixedAdd(int id, int child_id, int x, int y);
LIBRARY_API void FixedMove(int id, int child_id, int x, int y);

LIBRARY_API int FrameLayout(int id, const char *label);
LIBRARY_API int ScrollViewLayout(int id);

LIBRARY_API int	 BoxLayout(int id, Orientation orientation, int spacing);
LIBRARY_API void BoxSetSpacing(int id, int spacing);
LIBRARY_API void BoxSetHomogeneous(int id, bool setting);
LIBRARY_API void BoxPackStart(int id, int child_id, bool expand, bool fill, int padding);
LIBRARY_API void BoxPackEnd(int id, int child_id, bool expand, bool fill, int padding);
LIBRARY_API void BoxReorderChild(int id, int child_id, int position);
LIBRARY_API void SetBoxWidgetCenter(int id, int child_id);

LIBRARY_API void AddLayoutChild(int id, int child_id);

// widgets

LIBRARY_API int  ButtonWidget(int id);
LIBRARY_API void ButtonSetLabel(int id, const char *label);
LIBRARY_API void ButtonSetRelief(int id, int relief);
LIBRARY_API void ButtonSetImage(int id, const char *image);
LIBRARY_API void ButtonSetImagePosition(int id, int position);
LIBRARY_API void ButtonSetAlwaysShowImage(int id, bool setting);
LIBRARY_API void ButtonSetUseUnderline(int id, bool setting);
LIBRARY_API void ButtonSetFocusOnClick(int id, bool setting);
LIBRARY_API void ButtonSetAlignment(int id, float xalign, float yalign);
LIBRARY_API void ButtonSetUseStock(int id, bool setting);

LIBRARY_API int LabelWidget(int id, const char *text);
LIBRARY_API int MnemonicButtonWidget(int id, const char *label);

LIBRARY_API int  SwitchWidget(int id, bool value);
LIBRARY_API bool SwitchGetState(int id);
LIBRARY_API void SwitchSetState(int id, bool value);
LIBRARY_API bool SwitchGetActive(int id);
LIBRARY_API void SwitchSetActive(int id, bool value);

LIBRARY_API int  CheckboxWidget(int id, const char *label, bool state);
LIBRARY_API bool CheckboxGetState(int id);
LIBRARY_API void CheckboxSetState(int id, bool state);

LIBRARY_API int  RadioWidget(int id, int group_id, const char *label);
LIBRARY_API bool RadioGetState(int id);
LIBRARY_API void RadioSetState(int id, bool state);

LIBRARY_API void SetWidgetSize(int id, int width, int height);
LIBRARY_API void ShowAllWidgets(int id);

// Text
LIBRARY_API int  EntrySearchWidget(int id, const char *text);
LIBRARY_API int  EntryWidget(int id, const char *text);

LIBRARY_API void EntrySetText(int id, const char *text);
LIBRARY_API void EntrySetProgressFraction(int id, double fraction);
LIBRARY_API void EntrySetProgressPulse(int id);
LIBRARY_API void EntrySetHasFrame(int id, bool editable);
LIBRARY_API void EntrySetEditable(int id, bool editable);
LIBRARY_API void EntrySetMaxLength(int id, int max);
LIBRARY_API void EntrySetVisibility(int id, bool visible);
LIBRARY_API void EntrySetActivatesDefault(int id, bool setting);
LIBRARY_API void EntrySetPlaceholderText(int id, const char *text);
LIBRARY_API void EntrySetAlignmen(int id, float xalign);
LIBRARY_API void EntrySetPlaceholderText(int id, const char *text);
LIBRARY_API void EntrySetInvisibleChar(int id, char ch);
LIBRARY_API void EntrySetOverwriteMode(int id, bool overwrite);
LIBRARY_API void EntrySetMaxLength(int id, int max_length);
LIBRARY_API void EntrySetWidthChars(int id, int n_chars);
LIBRARY_API void EntrySetMaxWidthChars(int id, int n_chars);




// Text View
LIBRARY_API int TextWidget(int id);
LIBRARY_API int TextWidgetWithBuffer(int id, int buffer_id);

LIBRARY_API int  GetTextViewBuffer(int id, int buffer_id);
LIBRARY_API void SetTextViewBuffer(int id, int buffer_id);
LIBRARY_API int  GetTextTableTag(int id, int tagTable_id);

// TextBuffer
LIBRARY_API int TextBuffer(int id);
LIBRARY_API int TextBufferTableTag(int id, int tagTableId);

LIBRARY_API void SetBufferText(int id, const char *text, int len);
LIBRARY_API void TextInsertIter(int id, int item_id, const char *text, int len);
LIBRARY_API void TextInsertAtCursor(int id, const char *text, int len);
LIBRARY_API void TextInsertTag(int id, int iterId, int tagId, const char *text,int len);
LIBRARY_API void TextInsertTagByName(int id, int item_id, const char* tagName, const char *text,int len);

LIBRARY_API int GetTextBufferLineCount(int id);
LIBRARY_API int GetTextBufferCharCount(int id);

// text interators
LIBRARY_API int StartTextIter(int id, int item_id);
LIBRARY_API int EndTextIter(int id, int item_id);

// Text Buffer Tags
LIBRARY_API int  TextTag(int id, const char *name);
LIBRARY_API void SetTagIntProperty(int id, const char *name, int value);
LIBRARY_API void SetTagFloatProperty(int id, const char *name, float value);
LIBRARY_API void SetTagStringProperty(int id, const char *name, const char *value);

// Text Buffer Tag Table
LIBRARY_API int  TextTableTag(int id);
LIBRARY_API void AddTextTableTag(int id, int tagId);
LIBRARY_API void RemoveTextTableTag(int id, int tagId);
LIBRARY_API int  GetTextTableTagSize(int id);
LIBRARY_API bool FindTextTableTag(int id, const char *name, int tagId);

//Bars/Values

LIBRARY_API int  SpinButtonWidget(int id, double min, double max, double step);
LIBRARY_API void SpinButtonSetDigits(int id, int digits);
LIBRARY_API void SpinButtonSetValue(int id, double value);
LIBRARY_API void SpinButtonSetRange(int id, double min, double max);
LIBRARY_API void SpinButtonSetIncrements(int id, double step, double page);
LIBRARY_API void SpinButtonSetWraps(int id, bool wraps);
LIBRARY_API void SpinButtonSetSnapToTicks(int id, bool snap);
LIBRARY_API void SpinButtonSetNumeric(int id, bool numeric);
LIBRARY_API void SpinButtonOrientaion(int id, int direction, double increment);
LIBRARY_API int SpinButtonGetDigits(int id);
LIBRARY_API double SpinButtonGetValue(int id);
LIBRARY_API int    SpinButtonGetIntValue(int id);


LIBRARY_API int  ScaleWidget(int id,  Orientation orientation, double min, double max, double step);
LIBRARY_API void SetScaleDigits(int id, int digits);
LIBRARY_API void SetScaleDrawValue(int id, bool draw_value);
LIBRARY_API void SetScaleHasOrigin(int id, bool has_origin);
LIBRARY_API void AddScaleMark(int id, double value, PositionType position, const char *markup);
LIBRARY_API void ClearScaleMarks(int id);
LIBRARY_API void SetScaleValuePos(int id, int pos);
LIBRARY_API int  GetScaleValuePos(int id);
LIBRARY_API int  GetScaleDigits(int id);
LIBRARY_API bool GetScaleHasOrigin(int id);
LIBRARY_API bool GetScaleDrawValue(int id);


LIBRARY_API int  ProgressBarWidget(int id);
LIBRARY_API void SetProgressBarOrientation(int id, Orientation orientation);
LIBRARY_API void SetProgressBarFraction(int id, double fraction);
LIBRARY_API void SetProgressBarPulseStep(int id,double step);
LIBRARY_API void SetProgressBarText(int id, const char *text);
LIBRARY_API void SetProgressBarShowText(int id, bool show_text);
LIBRARY_API void SetProgressBarInverted(int id, bool inverted);
LIBRARY_API double GetProgressBarFraction(int id);
LIBRARY_API double GetProgressBarPulseStep(int id);
LIBRARY_API void   SetProgressBarEllipsize(int id, EllipsizeMode mode);
LIBRARY_API bool   GetProgressBarShowText(int id);
LIBRARY_API int    GetProgressBarEllipsize(int id);
LIBRARY_API bool   GetProgressBarInverted(int id);
LIBRARY_API const char *GetProgressBarText(int id);
LIBRARY_API int GetProgressBarOrientation(int id);

//MENUS
LIBRARY_API int MenuWidget(int id) ;
LIBRARY_API int MenuBarWidget(int id) ;
LIBRARY_API int MenuSeparatorWidget(int itemId, int menuId) ;


LIBRARY_API void  AttachMenu(int menu_id, int widgetID);
LIBRARY_API void  SetMenuItemSubMenu(int menuId, int submenuId) ;

//menu items
LIBRARY_API int AppendMenuItemWidget(int id, const char *label, int menu_id) ;
LIBRARY_API int PrependMenuItemWidget(int id, const char *label, int menu_id) ;
LIBRARY_API int InsertMenuItemWidget(int id, const char *label, int menu_id, int pos) ;

//LISTS
LIBRARY_API int ListBoxWidget(int id);
LIBRARY_API int ListBoxRowWidget(int id);


LIBRARY_API void InsertListBoxWidget(int id, int child_id, int position);
LIBRARY_API void PrependListBoxWidget(int id, int child_id);


#if defined(__cplusplus)
}            
#endif




#endif // GTK_LIBRARY_H
