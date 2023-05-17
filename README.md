# PureGTK Project - Simplifying GTK Widgets

This project consists of a shared library created in the C language and utilizing the GTK library to 
simplify the creation and handling of widgets and events.

## Objective

The goal of this library is to provide a simple and easy-to-use API, similar to PureBasic, for dealing with the 
creation and handling of widgets, as well as processing events more efficiently.

## Using Builder
<pre>

#include <stdio.h>
#include "PureGTK.h"
int main()
{
 
    InitLibrary();

    int builder = BuilderFromFile(ID_ANY,"res/ui/builder.ui");

    int win = WindowFromBuilder(builder,ID_ANY,"window");

    ButtomFromBuilder(builder,ID_ANY,"button1");

    ButtomFromBuilder(builder,ID_ANY,"button2");


    ButtomFromBuilder(builder,ID_ANY,"quit");

    ShowWindow(win);

	bool running = true;
	while (running)
	{
        Event event;
        while (ProcessEvents(&event))
        {
             switch (event.type)
            {
            case EVENT_RESIZE:
            {
                 break;
            }
            case EVENT_CLOSE:
            {

                 running = false;
                break;
            }
            case EVENT_BUTTON_CLICK:
            {
                printf("Botão clicado, ID do widget: %d\n", event.button.id );
                break;
            }
        
        }
	}
	
	FreeLibrary();
	return (0);
}

</pre>
##Buttons

<pre>

#include <stdio.h>
#include "PureGTK.h"
int main()
{
 
    InitLibrary();
    int win = OpenWindow(ID_ANY, 100, 100, 700, 600, "Exemplo");
    
    int fixed_id = FixedLayout(ID_ANY);
    AddLayoutChild(win, fixed_id);



    int id = ButtonWidget(ID_ANY);
        ButtonSetLabel(id, "Botão");
        
        FixedAdd(fixed_id, id, 5, 5);
    id = LabelWidget(ID_ANY, "Label");
         FixedAdd(fixed_id, id, 5, 50);
    id = SwitchWidget(ID_ANY, false);
         FixedAdd(fixed_id, id, 5, 100);

    id = MnemonicButtonWidget(ID_ANY, "Botão com _Mnemônico");
         FixedAdd(fixed_id, id, 5, 180);

    id = CheckboxWidget(ID_ANY, "Checkbox", false);
         FixedAdd(fixed_id, id, 100, 5);

    id = RadioWidget(ID_ANY, -1, "Radio 1");
            FixedAdd(fixed_id, id, 100, 50);
    id = RadioWidget(ID_ANY, id, "Radio 2");
            FixedAdd(fixed_id, id, 100, 100);
    id = RadioWidget(ID_ANY, id, "Radio 3");
            FixedAdd(fixed_id, id, 100, 150);


    int frame = FrameLayout(ID_ANY,  "Frame");
        FixedAdd(fixed_id,frame, 200, 50);
        WidgetSetSize(frame, 400, 80);

    int frame_fixed = FixedLayout(ID_ANY);
        AddLayoutChild(frame, frame_fixed);
        


     id =  RadioWidget(ID_ANY, -1, "Radio 1");
            FixedAdd(frame_fixed, id, 10, 10);
     id =  RadioWidget(ID_ANY, id, "Radio 2");
             FixedAdd(frame_fixed, id, 100, 10);
     id =  RadioWidget(ID_ANY, id, "Radio 3");
             FixedAdd(frame_fixed, id, 200, 10);



	ShowWindow(win);

	bool running = true;
	while (running)
	{
        Event event;
        while (ProcessEvents(&event))
        {
         //   printf("Evento recebido: %d\n", event.type);
            switch (event.type)
            {
            case EVENT_RESIZE:
            {
              //  printf("Janela redimensionada, ID do widget: %d   (%d:%d) \n", event.resize.id , event.resize.width, event.resize.height);
                break;
            }
            case EVENT_CLOSE:
            {

                printf("Janela fechada, ID do widget: %d\n", event.close.id);
                running = false;
                break;
            }
            case EVENT_BUTTON_CLICK:
            {
                printf("Botão clicado, ID do widget: %d\n", event.button.id );
                break;
            }
            case EVENT_CHECKBOX:
            {
                printf("Checkbox clicado, ID do widget: %d, Marcado: %s\n",                       event.button.id, event.button.checked ? "Sim" : "Não");
                break;
            }
            case EVENT_RADIO:
            {
                 printf("Radiobutton clicado, ID do widget: %d, Marcado: %s\n",                       event.button.id, event.button.checked ? "Sim" : "Não");
                break;
            }
            case EVENT_SWITCH:
            {
                printf("Switch clicado, ID do widget: %d, Marcado: %s\n",                       event.button.id, event.button.checked ? "Sim" : "Não");
                break;
            }
            case EVENT_ENTRY:
            {
                printf("Entry alterado, ID do widget: %d, Texto: %s\n",                       event.entry.id, event.entry.text);
                break;
            }
            case EVENT_ENTRY_CHANGED:
            {
                printf("Entry alterado, ID do widget: %d, Texto: %s\n",                       event.entry.id, event.entry.text);
                break;
            }
            case EVENT_VALUE_CHANGED:
            {

                break;
            }


        }
        }
	}
	
	FreeLibrary();
	return (0);
}

</pre>
