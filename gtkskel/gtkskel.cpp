#include <gtk/gtk.h>
#include "embed.h"
#include "EmbeddingSetup.h"
#include "srvlistener.h"

#include <iostream>

GtkWidget *g_notebook;
GtkWidget *g_entry;
GtkWidget *g_statusbar;
GtkWidget *g_viewport;
MozView *myMozView;
SrvListener *myMozListener;

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window;
    gint w=800,h=600;
    
    gtk_init (&argc, &argv);
    myMozView = new MozView();
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 1024,600);
    g_signal_connect(window, "delete_event", gtk_main_quit, NULL);

    GtkWidget *box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);


    GtkWidget *buttons_box = gtk_hbox_new (FALSE, 0);

    gtk_box_pack_start(GTK_BOX(box), buttons_box, FALSE, FALSE, 0);

    GtkWidget *toolbar = gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 0);

    //g_notebook = gtk_notebook_new();
    g_viewport = gtk_viewport_new(NULL, NULL);

    g_entry = gtk_entry_new();

    GtkToolItem *toolitem = gtk_tool_item_new();
    gtk_container_add(GTK_CONTAINER(toolitem), g_entry);
    gtk_tool_item_set_expand(toolitem, TRUE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), toolitem, 0);

    toolitem = gtk_tool_button_new_from_stock(GTK_STOCK_ADD);
    gtk_tool_button_set_label(GTK_TOOL_BUTTON(toolitem), "New Tab");
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), toolitem, 1);

    gtk_box_pack_start(GTK_BOX(box), g_viewport, TRUE, TRUE, 0);

    g_statusbar = gtk_statusbar_new();
    gtk_box_pack_start(GTK_BOX(box), g_statusbar, FALSE, FALSE, 0);


    int res = myMozView->CreateBrowser(g_viewport, 0, 0, 1024-50, 600-50, 0);

    myMozListener = new SrvListener(myMozView);

    myMozView->SetListener(myMozListener);

    if(argc < 2)
    	myMozView->LoadURI("http://www.mozilla.org");
    else myMozView->LoadURI(argv[1]);

    gtk_widget_show_all(window);

    gtk_main ();
    
    return 0;
}
