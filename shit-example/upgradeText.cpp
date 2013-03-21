/* multiline-text-editor.c 
 Copyright (c) 2012, Frank Cox
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY FRANK COX ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL FRANK COX BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE. 
 */

#include <curses.h>
#include <string.h>

char* left(char *string, const int length);
void texteditor(char *text);

int main()
    {
    char message[1621]="";
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,TRUE);

    move(20,0);
    hline(ACS_CKBOARD,80);
    mvaddstr(21,0,"Press F1 to Exit Editor");
    mvaddstr(21,39,"Press F3 to Clear Message");
    mvaddstr(22,0,"Press CTRL-Y to Delete Current Line");

    texteditor(message);

    clear();
    addstr("Exited text editor");
    getch();
    endwin();
    printf("%s",message);
    return 0;
    }

void texteditor(char *text)
    {
    int ky=0,position=0,row,col;
    char *where, display[20][81];
    bool ins=false;

    while (ky !=KEY_F(1))
        {
        where=text;
        for (row=19; row > -1; row--)
            {
            move(row,0);
            clrtoeol();
            display[row][0]=127;
            display[row][1]='\0';
            }
        row=0;
        while (strlen(where) > 80 || strchr(where,'~') != NULL)
            {
            strncpy(display[row],where,80);
            display[row][80]='\0';
            if (strchr(display[row],'~') != NULL)
                {
                left(display[row],strchr(display[row],'~')-display[row]);
                }
            else
                left(display[row],strrchr(display[row],' ')-display[row]);
            mvprintw(row,0,"%s",display[row]);
            where+=strlen(display[row])+1;
            row++;
            }
        strcpy(display[row],where);
        mvprintw(row,0,"%s",display[row]);
        col=position;
        row=0;
        while (col > strlen(display[row]))
            {
            col-=strlen(display[row])+1;
            row++;
            }
        move(row,col);
        
        ky=getch();
            case KEY_F(3):
                memset(text,0,1621);
                position=0;
                break;
            case KEY_HOME:
                if (col)
                    {
                    position=0;
                    for (col=0; col < row; col++)
                        position += strlen(display[col])+1;
                    }
                break;
            case KEY_END:
                if (col < strlen(display[row]))
                    {
                    position=-1;
                    for (col=0; col <=row; col++)
                        position+=strlen(display[col])+1;
                    }
                break;
            case KEY_LEFT:
                if (position)
                    position--;
                break;
            case KEY_RIGHT:
                if (position < strlen(text))
                    position++;
                break;
            case KEY_UP:
                if (row)
                    {
                    if (col > strlen(display[row-1]))
                        position=strlen(display[row-1]);
                    else
                        position=col;
                    for (col=0; col < row-1; col++)
                        position+=strlen(display[col])+1;
                    }
                break;
            case KEY_DOWN:
                if (display[row+1][0] !=127 && row < 19)
                    {
                    if (col < strlen(display[row+1]))
                        position=col;
                    else
                        position=strlen(display[row+1]);
                    for (col=0; col <= row; col++)
                        position+=strlen(display[col])+1;
                    }   
                break;
            case KEY_IC: // insert key
                ins = !ins;
                if (ins)
                    mvaddstr(20,77,"INS");
                else
                    {
                    mvaddch(20,77,ACS_CKBOARD);
                    addch(ACS_CKBOARD);
                    addch(ACS_CKBOARD);
                    }
                break;
            case KEY_DC:  // delete key
                if (strlen(text))
                    memmove(&text[position],&text[position+1],1621-position);
                break;
            case KEY_BACKSPACE:
                if (strlen(text) && position)
                    {
                    position--;
                    memmove(&text[position],&text[position+1],1621-position);
                    }
                break;
            case 25: // ctrl-y
                position=0;
                for (col=0; col < row; col++)
                    position+=strlen(display[col])+1;
                memmove(&text[position],&text[position+strlen(display[row])+1],1621-position+strlen(display[row]));
                break;
            case 10: // return
                if (display[19][0] == 127 || display[19][0] == '~')
                    {
                    memmove(&text[position+1],&text[position],1621-position);
                    text[position]='~';
                    position++;
                    }
                break;

        }
    return;
    }
    

char* left(char *string, const int length)
    {
    if (strlen(string) > length)
        string[length]='\0';
    return string;
    }
