#include <gtk/gtk.h>
#include <stdio.h>
#include "int2utf8.h"
#include <chess.h>

static gboolean button_pressed (GtkWidget*, GtkButton*, GtkLabel *[][8]);
int clicks = 0;
int player = 0;
GtkWidget *table, *prevEventbox, *hpane, *infogrid, *textview, *scroll_win;
GtkTextBuffer *buffer;
GtkTextIter txtiter;
GtkLabel *currentPlayer, *row_label, *col_label;

char note[5];
char mnum[12]; // max int size is 11 chars (if you inlude the - sign) long + 0 char
struct Move mov;
int board[8][8];
int movecnt = 0;

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
    /*fill the board array with pieces*/
    initBoard(board);
    resetPassantArrays();
    GtkWidget *window, *eventbox;
    GtkLabel *label;
    GtkGesture *gesture;
    window = gtk_application_window_new (app);
    gtk_window_set_title(GTK_WINDOW (window), "Chess board");
    gtk_widget_set_size_request(window, 680,350);
    //table = gtk_grid_new (8,8,TRUE);
    table = gtk_grid_new ();
    GtkStyleContext *context;
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path (provider,
            "style/chessGUI.css");
    context = gtk_widget_get_style_context (table);
    gtk_style_context_add_provider (context,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER);

    /*container for the labels of the gui board*/
    GtkLabel *labelBoard[8][8];
    /*one is larger to make the squares wider*/	
    char *pieces[64] = { "♜", "♞", "♝","♛","♚","♝","♞","♜",
        "♟", "♟", "♟","♟","♟","♟","♟","♟",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "♙", "♙", "♙","♙","♙","♙","♙","♙",
        "♖", "♘", "♗","♕","♔","♗","♘","♖"};
    int i,j;
    int p = 0;
    int oddCol = 1;
    int oddRow = 1;
    for (i = 0; i < 8; i ++) {
        for (j = 0; j < 8; j++) {
            label = (GtkLabel *) gtk_label_new(pieces[p]);
            /* set the size of the label to avoid that they are resized when there is no piece in the row */
            gtk_widget_set_size_request((GtkWidget *) label, 56, 56);
            /*put the label into the container for easy access when mocing pieces*/
            labelBoard[i][j]=label;
            gesture = gtk_gesture_click_new();
            eventbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);;
            context = gtk_widget_get_style_context (eventbox);
            gtk_style_context_add_provider (context,
                    GTK_STYLE_PROVIDER(provider),
                    GTK_STYLE_PROVIDER_PRIORITY_USER);
            if (oddRow) {
                if (oddCol) {
                    gtk_widget_set_name (eventbox, "lightbrown");
                    oddCol = 0;
                } else {
                    gtk_widget_set_name (eventbox, "darkbrown");
                    oddCol = 1;
                }
            } else {
                if (oddCol) {
                    gtk_widget_set_name (eventbox, "darkbrown");
                    oddCol = 0;
                } else {
                    gtk_widget_set_name (eventbox, "lightbrown");
                    oddCol = 1;
                }
            }

            /*put label into eventbox*/
            gtk_box_append(GTK_BOX (eventbox), (GtkWidget *) label);
            /*put eventbox into table*/
            gtk_grid_attach((GtkGrid *) table, eventbox,j+1,i,1,1);


            g_signal_connect(gesture, "released", G_CALLBACK (button_pressed), labelBoard);

            p++;
        }
        oddRow = !oddRow;
    }
    /* add square row names */
    sprintf(mnum,"%s","`");
    for (i = 1; i < 9; i++) {
        mnum[0]++; // mnums first char becomes 'a', then 'b', then 'c' etc.
        label = (GtkLabel *) gtk_label_new(mnum);
        gtk_widget_set_size_request((GtkWidget *) label, 0, 30);
        gtk_grid_attach((GtkGrid *) table,(GtkWidget *) label,i,9,1,1);
    }
    i = 8;
    for (j = 0; j < 8; j++) {
        sprintf(mnum,"%d",i--);
        label = (GtkLabel *) gtk_label_new(mnum);
        gtk_widget_set_size_request((GtkWidget *) label, 30, 0);
        gtk_grid_attach((GtkGrid *) table,(GtkWidget *) label,0,j,1,1);
    }

    /*make a horizontal pane*/
    //hpane = gtk_grid_new(1,2,TRUE);
    hpane = gtk_grid_new();
    /*add the table to the horizontal pane*/
    gtk_grid_attach((GtkGrid *) hpane, table, 0, 0, 1,1);

    /* create a vertical grid containing game info.
     * the first  widget is shows the current player
     * and the second widget is a textview showing last moves
     */
    infogrid = gtk_grid_new();
    textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview), FALSE);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview), GTK_WRAP_WORD);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
    gtk_text_view_set_left_margin (GTK_TEXT_VIEW (textview), 10);
    gtk_text_view_set_right_margin (GTK_TEXT_VIEW (textview), 10);

    /*add game info textview to the scroll window 
     * and the scroll window and current player label to infogrid.
     * Finally add the info grid to the hpane, right of the chess board.*/
    scroll_win = gtk_scrolled_window_new ();
    gtk_widget_set_size_request(scroll_win, 250,415);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll_win),
            GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW (scroll_win), textview);
    gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) scroll_win,0,1,1,1);
    currentPlayer = (GtkLabel *) gtk_label_new("Current player: White");
    gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) currentPlayer,0,0,1,1);
    gtk_grid_attach((GtkGrid *) hpane, (GtkWidget *) infogrid, 1,0,1,1);



    /*add table to window*/
    gtk_window_set_child(GTK_WINDOW (window), hpane);
    gtk_widget_show(window);
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_window_destroy), NULL);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}




int drawGuiBoard(GtkLabel *labels[][8], int cliBoard[][8])
{
		int i, j;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				gtk_label_set_text(labels[i][j], convertClipieceToGuiPiece(cliBoard[i][j]));
			}
		}
		return 0;
}

void algebraic_notation(char *note, struct Move mov, int board[][8])
{
  int piece = board[mov.currRow][mov.currCol];
  note[0] = ' ';
  if (piece == 2 || piece == 8) {
    note[1] = 'N';
  } else if (piece == 3 || piece == 9) {
    note[1] = 'B';
  } else if (piece == 4 || piece == 10) {
    note[1] = 'R';
  } else if (piece == 5 || piece == 11) {
    note[1] = 'Q';
  } else if (piece == 6 || piece == 12) {
    note[1] = 'K';
  } 
  note[2] = mov.nextRow + 97;
  note[3] = mov.nextCol + 48;
  note[4] = 0;

  if (piece == 1 || piece == 7) {
    note[1] = mov.nextRow + 97;
    note[2] = mov.nextCol + 48;
    note[3] = 0;
  }
}

static gboolean button_pressed (GtkWidget *ebox, GtkButton *event,
			GtkLabel *labelBoard[][8])
{
    // prevEventbox = eventbox;// Just set the prevEventbox to avoid nullpointer exception
    int left, top, width, height;

    if (!clicks) {
        gtk_widget_set_name (ebox, "selected");
        /*get coordinates of eventbox*/
        gtk_grid_query_child(GTK_GRID(table), ebox,
                &left, &top, &width, &height);
        //store the position you move from. It will be used to move the pieces in the board array
        // subtract 1 from left because the row numbers are part of the label table
        mov.currCol = left-1;
        mov.currRow = top;
        /*save label*/
        prevEventbox = ebox;
        /*save the current coordinates*/
        clicks = 1;
    } else {
        /*make move*/
        gtk_grid_query_child(GTK_GRID(table), ebox,
                &left, &top, &width, &height);
        //store the position you move to. It will be used to move the pieces in the board array
        // subtract 1 from left because the row numbers are part of the label table
        mov.nextCol = left-1;
        mov.nextRow = top;
        /*nolor back to normal*/
        if ((mov.currCol+mov.currRow)&1){
            /*odd square, darkbrown color*/
            //gtk_widget_override_background_color(prevEventbox, GTK_STATE_NORMAL, &dbrown);
            gtk_widget_set_name (prevEventbox, "darkbrown"); 
        } else {
            /*even square, lightbrown color*/
            gtk_widget_set_name (prevEventbox, "lightbrown"); 
        }
        algebraic_notation(note, mov, board);
        int u = makemove(player, mov, board);
        if (!u) {
            buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
            gtk_text_buffer_get_end_iter(buffer, &txtiter);
            if (!player) {
                sprintf(mnum,"%d",++movecnt);
                gtk_text_buffer_insert(buffer, &txtiter, " ", -1);
                gtk_text_buffer_insert(buffer, &txtiter, mnum, -1);
                gtk_text_buffer_insert(buffer, &txtiter, ".", -1);
            }
            /* Update the GUI board */
            drawGuiBoard(labelBoard, board);	
            /* Update the game info */
            gtk_text_buffer_insert(buffer, &txtiter, note, -1);

            player = !player; 
            if (player) {
                gtk_label_set_text(currentPlayer, "Current player: Black");
            } else {
                gtk_label_set_text(currentPlayer, "Current player: White");
            }
        }
        clicks = 0;
    }
    return TRUE;
}
