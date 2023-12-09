#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define ECKE_OBEN_LINKS     '\xDA'
#define ECKE_OBEN_RECHTS    '\xBF'
#define ECKE_UNTEN_LINKS    '\xC0'
#define ECKE_UNTEN_RECHTS   '\xD9'
#define HORIZONTAL          '\xC4'
#define VERTIKAL            '\xB3'



void printField(char field[80][80], int x, int y) {
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            printf("%c", field[i][j]);
        }
        printf("\n");
    }
}


void set_lines(char field[80][80], int width, int height) {
    //ganz Links
    for (int i = 0; i < height; i++) {
        field[i][1] = VERTIKAL;
    }

    //ganz Links
    for (int i = 0; i < height; i++) {
        field[i][18] = VERTIKAL;
    }

    //ganz Links
    for (int i = 0; i < height; i++) {
        field[i][36] = VERTIKAL;
    }

    //ganz Links
    for (int i = 0; i < height; i++) {
        field[i][53] = VERTIKAL;
    }
}


void set_train(char spielfeld[80][80], int object_position_x, int object_position_y, int object_len_y, int object_len_x) {
    // Platzieren des Objekts im Spielfeld
        //Oberste Zeile
    spielfeld[object_position_y][object_position_x] = ECKE_OBEN_LINKS;
    for (int k = 0; k < object_len_y - 2; ++k) {
        spielfeld[object_position_y][object_position_x + 1 + k] = HORIZONTAL;
    }
    spielfeld[object_position_y][object_position_x + object_len_y - 1] = ECKE_OBEN_RECHTS;
    //Mitte
    for (int i = 0; i < object_len_x - 2; i++) {
        spielfeld[object_position_y + 1 + i][object_position_x] = VERTIKAL;
        for (int j = 0; j < object_len_y - 2; j++) {
            spielfeld[object_position_y + 1 + i][object_position_x + 1 + j] = ' ';
        }
        spielfeld[object_position_y + 1 + i][object_position_x + object_len_y - 1] = VERTIKAL;
    }
    //Unten
    spielfeld[object_position_y + object_len_x - 1][object_position_x] = ECKE_UNTEN_LINKS;
    for (int k = 0; k < object_len_y - 2; ++k) {
        spielfeld[object_position_y + object_len_x - 1][object_position_x + 1 + k] = HORIZONTAL;
    }
    spielfeld[object_position_y + object_len_x - 1][object_position_x + object_len_y - 1] = ECKE_UNTEN_RECHTS;
}




int main() {
    //Größe des Spielfeldes
    int screen_height = 25, 
        screen_width = 55;
    int y = 3,
        z = 2;

    //Startposition des Spielers
    int player_position_x = 27, 
        player_position_y = 22;
    //Schrittgröße nach links oder rechts
    int step_size = 18;
    

    char spielfeld[80][80];
    char user_input = ' ';

    //Deklerationen für ein Objekt
    //Startposition auf dem Feld
    int train_position_x = 5, 
        train_position_y = 0;
    //Maße des Objekts
    int train_len_x = 15,
        train_len_y = 16;




    //aussteigen wenn ESC gedrückt wurde
    while (user_input != '\x1B') {
        system("cls");


        //erstellen vom Spielfeld
        for (int i = 0; i < screen_height; ++i) {
            for (int j = 0; j < screen_width; ++j) {
                spielfeld[i][j] = '.';
            }
        }



        //Spieler setzen
        spielfeld[player_position_y][player_position_x] = 'O';



        //Züge platzieren
        //1. Bahn
        set_train(spielfeld, ((screen_width - 3 * train_len_x - 2 * y)/2), train_position_y, train_len_x, train_len_y);

        //2.Bahn
        set_train(spielfeld, (screen_width - 2 * train_len_x - y - z), train_position_y + 2, train_len_x, train_len_y);

        //3.bahn
        set_train(spielfeld, (screen_width - train_len_x - ((screen_width - 3 * train_len_x - 2 * y)/2)), train_position_y, train_len_x, train_len_y);



        set_lines(spielfeld, screen_width, screen_height);

        //Spielfeld ausgeben
        printField(spielfeld, screen_width, screen_height);


        //Spieler Eingabe
        if (_kbhit()) {
            user_input = _getch();

            switch (user_input) {
            case 'w':
                player_position_y = (player_position_y - 1 + screen_height) % screen_height;
                break;
            case 's':
                player_position_y = (player_position_y + 1) % screen_height;
                break;
            case 'a':
                player_position_x = (player_position_x - step_size + screen_width) % screen_width;
                break;
            case 'd':
                player_position_x = (player_position_x + step_size) % screen_width;
                break;
            default:
                break;
            }
        }


        //Bewege Objekt nach unten
        train_position_y++;
        
        //Warte in mSd
        Sleep(50);
    }
    return 0;
}
