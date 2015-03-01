#include <gtk/gtk.h>
#include <stdio.h>
#include "int2utf8.h"

static gboolean button_pressed (GtkWidget*, GdkEventButton*, GtkLabel *[][8]);
static const GdkRGBA green  = {0.5899, 0.8867, 0.3906, 1};
static const GdkRGBA dbrown = {0.8242, 0.5508, 0.2773, 1};
static const GdkRGBA lbrown = {0.9805, 0.8047, 0.6094, 1};
GdkColor prevColor;
int clicks = 0;
int player = 0;
GtkWidget *table, *prevEventbox, *hpane, *infogrid, *textview, *scroll_win;
GtkTextBuffer *buffer;
GtkTextIter txtiter;
GtkLabel *currentPlayer, *row_label, *col_label;

char note[5];
char mnum[11]; // max int size is 10 chars long + 0 char
int move[4]; //src row col; dest row col 
int board[8][8];
int movecnt = 0;

extern int makemove(int player, int *move, int board[][8]);
/*initBoard method is in chess.c*/
extern void initBoard(int tmpBoard[][8]);
extern void resetPassantArrays(void);

int main (int argc, char *argv[])
{
	/*fill the board array with pieces*/
	initBoard(board);
	resetPassantArrays();
	GtkWidget *window, *eventbox;
    GtkLabel *label;
	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW (window), "Chess board");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_widget_set_size_request(window, 680,350);
	//table = gtk_grid_new (8,8,TRUE);
	table = gtk_grid_new ();
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
			eventbox = gtk_event_box_new();
			if (oddRow) {
				if (oddCol) {
					gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &lbrown);
					oddCol = 0;
				} else {
					gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &dbrown);
					oddCol = 1;
				}
			} else {
				if (oddCol) {
					gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &dbrown);
					oddCol = 0;
				} else {
					gtk_widget_override_background_color(eventbox, GTK_STATE_NORMAL, &lbrown);
					oddCol = 1;
				}
			}

			gtk_event_box_set_above_child(GTK_EVENT_BOX(eventbox),FALSE);
			gtk_widget_override_font((GtkWidget *) label, pango_font_description_from_string(
									"Serif 26"));
			/*put label into eventbox*/
			gtk_container_add(GTK_CONTAINER (eventbox), (GtkWidget *) label);
			/*put eventbox into table*/
      gtk_grid_attach((GtkGrid *) table, eventbox,j+1,i,1,1);


			g_signal_connect(G_OBJECT (eventbox), "button_press_event",
					G_CALLBACK (button_pressed), (gpointer) labelBoard);

			gtk_widget_set_events(eventbox, GDK_BUTTON_PRESS_MASK);
            /*Dont need widget_realize
             * connect to a signal that will be called 
             * after the widget is realized automatically
             * in g_signal_connect(window)
			gtk_widget_realize(eventbox);*/

			p++;
		}
		oddRow = !oddRow;
	}

  /* add square row names */
  gtk_widget_override_font((GtkWidget *) label, pango_font_description_from_string("Serif 16"));
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
  scroll_win = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_set_size_request(scroll_win, 250,415);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll_win),
  GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
  gtk_container_add(GTK_CONTAINER (scroll_win), textview);
  gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) scroll_win,0,1,1,1);
	currentPlayer = (GtkLabel *) gtk_label_new("Current player: White");
  gtk_grid_attach((GtkGrid *) infogrid, (GtkWidget *) currentPlayer,0,0,1,1);
  gtk_grid_attach((GtkGrid *) hpane, (GtkWidget *) infogrid, 1,0,1,1);



	/*add table to window*/
	gtk_container_add (GTK_CONTAINER (window), hpane);
	gtk_widget_show_all (window);
	g_signal_connect_swapped(G_OBJECT(window), "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
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

void algebraic_notation(char *note, int *move, int board[][8])
{
  int piece = board[move[1]][move[0]];
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
  note[2] = move[3] + 97;
  note[3] = move[2] + 48;
  note[4] = 0;

  if (piece == 1 || piece == 7) {
    note[1] = move[3] + 97;
    note[2] = move[2] + 48;
    note[3] = 0;
  }
}

static gboolean button_pressed (GtkWidget *ebox, GdkEventButton *event,
			GtkLabel *labelBoard[][8])
{
	unsigned left, top, width, height;

	if (event->type == GDK_BUTTON_PRESS)
	{
		if (!clicks) {
			gtk_widget_override_background_color(ebox, GTK_STATE_NORMAL, &green);
			/*get coordinates of eventbox*/
			gtk_container_child_get(GTK_CONTAINER(table), ebox,
					"left-attach", &left,
					"top-attach",&top,
					"width",&width,
					"height",&height,
					NULL);
      //store the position you move from. It will be used to move the pieces in the board array
      // subtract 1 from left because the row numbers are part of the label table
      move[0] = left-1;
      move[1] = top;
			/*save label*/
			prevEventbox = ebox;
			/*save the current coordinates*/
			clicks = 1;
		} else {
			/*make move*/
			gtk_container_child_get(GTK_CONTAINER(table), ebox,
					"left-attach",  &left,
					"top-attach",   &top,
					"width", &width,
					"height",&height,
					NULL);
      //store the position you move to. It will be used to move the pieces in the board array
      // subtract 1 from left because the row numbers are part of the label table
      move[2] = left-1;
      move[3] = top;
			/*color back to normal*/
			if ((move[0]+move[1])&1){
				/*odd square, lightbrown color*/
				gtk_widget_override_background_color(prevEventbox, GTK_STATE_NORMAL, &dbrown);
			} else {
				/*even square, darkbrown color*/
				gtk_widget_override_background_color(prevEventbox, GTK_STATE_NORMAL, &lbrown);
			}
      algebraic_notation(note, move, board);
			int u = makemove(player, move, board);
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
	}
	return FALSE;
}
