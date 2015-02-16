#include <gtk/gtk.h>
#include <stdio.h>
#include "convCoordinates.h"

static gboolean button_pressed (GtkWidget*, GdkEventButton*, GtkLabel *[][8]);
static const GdkColor green = {0, 0x9700, 0xe300, 0x6400};
static const GdkColor dbrown = {0,0xd300,0x8d00,0x4700};
static const GdkColor lbrown = {0,0xfb00,0xce00,0x9c00};
GdkColor prevColor;
int clicks = 0;
int player = 0;
GtkWidget *table, *prevEventbox, *hpane;
GtkLabel *currentPlayer;
int move[4];
unsigned tableFrom[4];
int board[8][8];

extern int guiMove(int player, int *move, int board[][8]);
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
	table = gtk_grid_new (8,8,TRUE);
    /*container for the labels of the gui board*/
    GtkLabel *labelBoard[8][8];
	/*one is larger to make the squares wider*/	
	char *pieces[64] = { "♜", "♞", "♝","♛","♚","♝","♞","♜",
						 "♟", "♟", "♟","♟","♟","♟","♟","♟",
						 "    ", "    ", "    ","    ","    ","    ","    ","    ",
						 "    ", "    ", "    ","    ","    ","    ","    ","    ",
						 "    ", "    ", "    ","    ","    ","    ","    ","    ",
						 "    ", "    ", "    ","    ","    ","    ","    ","    ",
						 "♙", "♙", "♙","♙","♙","♙","♙","♙",
						 "♖", "♘", "♗","♕","♔","♗","♘","♖"};

	int i,j;
	int p = 0;
	int oddCol = 1;
	int oddRow = 1;
	for (i = 0; i < 8; i ++) {
		for (j = 0; j < 8; j++) {
			label = (GtkLabel *) gtk_label_new(pieces[p]);
			/*put the label into the container for easy access when mocing pieces*/
			labelBoard[i][j]=label;
			eventbox = gtk_event_box_new();
			if (oddRow) {
				if (oddCol) {
					gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &lbrown);
					oddCol = 0;
				} else {
					gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &dbrown);
					oddCol = 1;
				}
			} else {
				if (oddCol) {
					gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &dbrown);
					oddCol = 0;
				} else {
					gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &lbrown);
					oddCol = 1;
				}
			}
			gtk_event_box_set_above_child(GTK_EVENT_BOX(eventbox),FALSE);
			gtk_widget_modify_font((GtkWidget *) label, pango_font_description_from_string(
									"Serif 26"));
			/*put label into eventbox*/
			gtk_container_add(GTK_CONTAINER (eventbox), (GtkWidget *) label);
			/*put eventbox into table*/
      gtk_grid_attach(table, eventbox,j,i,1,1);


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

	/*make a horizontal pane*/
	hpane = gtk_grid_new(1,2,TRUE);
	/*add the table to the horizontal pane*/
  gtk_grid_attach(hpane, table, 0, 0, 1,1);
	/*add game info to the horizontal pane*/
	currentPlayer = (GtkLabel *) gtk_label_new("Current player:\nWhite");
  gtk_grid_attach(hpane, (GtkWidget *) currentPlayer,1,0,1,1);


	/*add table to window*/
	gtk_container_add (GTK_CONTAINER (window), hpane);
	gtk_widget_show_all (window);
	g_signal_connect_swapped(G_OBJECT(window), "destroy",
		G_CALLBACK(gtk_main_quit), NULL);
	gtk_main();
	return 0;
}

/*takes a number 0-12 and converts it to unicode chess piece or blank square*/
char *convertClipieceToGuiPiece(int cliPiece){
	if (cliPiece == 1) {
		return "♙";
	}
	else if (cliPiece == 2) {
		return "♘";
	}
	else if (cliPiece == 3) {
		return "♗";
	}
	else if (cliPiece == 4) {
		return "♖";
	}
	/*queen*/
	else if (cliPiece == 5) {
		return "♕";
	}
	/*king*/
	else if (cliPiece == 6) {
		return "♔";
	}
	else if (cliPiece == 7) {
		return "♟";
	}
	else if (cliPiece == 8) {
		return "♞";
	}
	else if (cliPiece == 9) {
		return "♝";
	}
	else if (cliPiece == 10) {
		return "♜";
	}
	/*queen*/
	else if (cliPiece == 11) {
		return "♛";
	}
	/*king*/
	else if (cliPiece == 12) {
		return "♚";
	} else {
		return "    ";
	}

}
int drawGuiBoard(GtkLabel *labels[][8], int cliBoard[][8]) {
		int i, j;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				gtk_label_set_text(labels[i][j], convertClipieceToGuiPiece(cliBoard[i][j]));
			}
		}
		return 0;
}

static gboolean button_pressed (GtkWidget *ebox, GdkEventButton *event,
			GtkLabel *labelBoard[][8])
{
	unsigned left, right, top, bottom;

	if (event->type == GDK_BUTTON_PRESS)
	{
		if (!clicks) {
			gtk_widget_modify_bg(ebox, GTK_STATE_NORMAL, &green);
			/*get coordinates of eventbox*/
            printf("test\n");
			gtk_container_child_get(GTK_CONTAINER(table), ebox,
					"left-attach", &left,
					"right-attach",&right,
					"top-attach",&top,
					"bottom-attach",&bottom,
					NULL);
            printf("test2\n");
			cfrom(right,top,move);
			/*save label*/
			prevEventbox = ebox;
			/*save the current coordinates*/
			tableFrom[0] = left;
			tableFrom[1] = right;
			tableFrom[2] = top;
			tableFrom[4] = bottom;
			clicks = 1;
		} else {
			/*make move*/
			gtk_container_child_get(GTK_CONTAINER(table), ebox,
					"left-attach", &left,
					"right-attach",&right,
					"top-attach",&top,
					"bottom-attach",&bottom,
					NULL);
			cto(right,top,move);
			/*color back to normal*/
			if ((move[0]+move[1])&1){
				/*odd square, lightbrown color*/
				gtk_widget_modify_bg(prevEventbox, GTK_STATE_NORMAL, &dbrown);
			} else {
				/*even square, darkbrown color*/
				gtk_widget_modify_bg(prevEventbox, GTK_STATE_NORMAL, &lbrown);
			}
			int u = guiMove(player, move, board);
			if (!u) {
				drawGuiBoard(labelBoard, board);	
				player = !player; /*next players turn*/
				if (player) {
					gtk_label_set_text(currentPlayer, "Current player:\nBlack");
				} else {
					gtk_label_set_text(currentPlayer, "Current player:\nWhite");
				}
			}
			clicks = 0;
		}
	}
	return FALSE;
}
