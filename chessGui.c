#include <gtk/gtk.h>
#include <stdio.h>
#include "convCoordinates.h"

static gboolean button_pressed (GtkWidget*, GdkEventButton*, GtkLabel*);
static const GdkColor green = {0, 0x9700, 0xe300, 0x6400};
static const GdkColor dbrown = {0,0xd300,0x8d00,0x4700};
static const GdkColor lbrown = {0,0xfb00,0xce00,0x9c00};
GdkColor prevColor;
int clicks = 0;
int player = 0;
GtkWidget *table, *prevEventbox, *hpane;
GtkLabel *prevLabel, *currentPlayer;
int move[4];
unsigned tableFrom[4];
int board[8][8];
/*container for the labels of the gui board*/
GtkWidget *labelBoard[8][8];

extern int guiMove(int player, int *move, int board[][8]);
/*initBoard method is in chess.c*/
extern void initBoard(int tmpBoard[][8]);
extern void resetPassantArrays(void);

int main (int argc, char *argv[])
{
	/*fill the board array with pieces*/
	initBoard(board);
	resetPassantArrays();
	GtkWidget *window, *label, *eventbox, *currentPlayerLabel;
	gtk_init (&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW (window), "Chess board");
  	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_widget_set_size_request(window, 680,350);
	currentPlayerLabel = gtk_label_new("Player: ");
	table = gtk_table_new (8,8,TRUE);
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
			label = gtk_label_new(pieces[p]);
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
			gtk_widget_modify_font(label, pango_font_description_from_string(
									"Serif 26"));
			/*put label into eventbox*/
			gtk_container_add(GTK_CONTAINER (eventbox), label);
			/*put eventbox into table*/
			gtk_table_attach(GTK_TABLE (table), eventbox,j,j+1,i,i+1,
					GTK_FILL, GTK_FILL, 0, 0);


			g_signal_connect(G_OBJECT (eventbox), "button_press_event",
					G_CALLBACK (button_pressed), (gpointer) label);
			gtk_widget_set_events(eventbox, GDK_BUTTON_PRESS_MASK);
			gtk_widget_realize(eventbox);

			p++;
		}
		oddRow = !oddRow;
	}

	/* add 0 spacing pixels between every row and column*/
	gtk_table_set_row_spacings (GTK_TABLE (table), 0);
	gtk_table_set_col_spacings (GTK_TABLE (table), 0);
	/*make a horizontal pane*/
	hpane = gtk_table_new(1,2,TRUE);
	/*add the table to the horizontal pane*/
	//gtk_container_add (GTK_CONTAINER (hpane), table);
	gtk_table_attach(GTK_TABLE (hpane), table, 0, 1, 0, 1,
			GTK_SHRINK, GTK_SHRINK, 0, 0);
	/*add game info to the horizontal pane*/
	currentPlayer = gtk_label_new("Current player:\nWhite");
	//gtk_container_add (GTK_CONTAINER (hpane), currentPlayer);
	gtk_table_attach(GTK_TABLE (hpane), currentPlayer, 1, 2, 0, 1,
			GTK_SHRINK, GTK_SHRINK, 5, 0);


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
char *tall[64]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63"};
int drawGuiBoard(GtkWidget *labels[][8], int cliBoard[][8]) {
		int i, j, p=0;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				gtk_label_set_text(labelBoard[i][j], convertClipieceToGuiPiece(cliBoard[i][j]));
				//gtk_label_set_text(labelBoard[i][j], tall[p]);
				p++;
			}
		}
		return 0;
}

static gboolean button_pressed (GtkWidget *eventbox, GdkEventButton *event,
			GtkLabel *label)
{
	unsigned left, right, top, bottom;

	if (event->type == GDK_BUTTON_PRESS)
	{
		if (!clicks) {
			gtk_widget_modify_bg(eventbox, GTK_STATE_NORMAL, &green);
			/*get coordinates of eventbox*/
			gtk_container_child_get(GTK_CONTAINER(table), eventbox,
					"left-attach", &left,
					"right-attach",&right,
					"top-attach",&top,
					"bottom-attach",&bottom,
					NULL);
			cfrom(right,top,move);
			/*save label*/
			prevLabel = label;
			prevEventbox = eventbox;
			/*save the current coordinates*/
			tableFrom[0] = left;
			tableFrom[1] = right;
			tableFrom[2] = top;
			tableFrom[4] = bottom;
			clicks = 1;
		} else {
			/*make move*/
			gtk_container_child_get(GTK_CONTAINER(table), eventbox,
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
			printf("player: %i\n",player);
			int u = guiMove(player, move, board);
			printf("%i %i %i %i\n", move[0],move[1],move[2],move[3]);
			if (!u) {
				drawGuiBoard(labelBoard, board);	
				player = !player; /*next players turn*/
				if (player) {
					gtk_label_set_text(currentPlayer, "Current player:\nBlack");
				} else {
					gtk_label_set_text(currentPlayer, "Current player:\nWhite");
				}
			}
		//	if (!u) {
		//		/*move was successfull*/

		//		/*move piece to last selected position*/
		//		const gchar *text = gtk_label_get_text (prevLabel);
		//		gtk_label_set_text(label, text);
		//		/*set prev position blank*/
		//		gtk_label_set_text(prevLabel,"    "); 
		//		player = !player; /*next players turn*/
		//	}
			clicks = 0;
		}
	}
	return FALSE;
}
