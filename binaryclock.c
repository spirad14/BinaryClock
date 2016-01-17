#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>

void myClock();
void printClock(char f[]);
void initClock(int *h, int *m, int *s);
void digitalClock(int h, int m, int s);
void readConfig(int color, int size, char symbol);
void writeConfig();

int main(void)
{
    myClock();
    return 0;
}

void myClock(){
  int i=0, tempi=0, loop=1;
  int h,m,s;

  while(loop){
    if(GetAsyncKeyState(27)){
        break;
    }
    if(GetAsyncKeyState(67)){
        writeConfig();
    }

      initClock(&h,&m,&s);
      system("cls");
      digitalClock(h,m,s);
      char f[17] = {' '};
      for(i=0, tempi=32; i<5; i++,tempi/=2){
          if(h%tempi/(tempi/2)) f[i]='X';
      }
      for(i=5, tempi=64; i<11; i++, tempi/=2){
          if(m%tempi/(tempi/2)) f[i]='X';
      }
      for(i=11, tempi=64; i<17; i++, tempi/=2){
          if(s%tempi/(tempi/2)) f[i]='X';
      }
      printClock(f);

      sleep(1);
  }
}

void initClock(int *h, int *m, int *s){
  time_t t = time(0);
  time(&t);
  struct tm * time = localtime(&t);
  *h = time->tm_hour;
  *m = time->tm_min;
  *s = time->tm_sec;
}

void printClock(char f[]){
  printf("Binaere-Uhr:\n");
  printf("H\t     [%c]  [%c]  [%c]  [%c]  [%c]\n",f[0],f[1],f[2],f[3],f[4]);
  printf("M\t[%c]  [%c]  [%c]  [%c]  [%c]  [%c]\n",f[5],f[6],f[7],f[8],f[9],f[10]);
  printf("S\t[%c]  [%c]  [%c]  [%c]  [%c]  [%c]\n\n",f[11],f[12],f[13],f[14],f[15],f[16]);
  printf("ESC druecken zum Verlassen...");
}

void digitalClock(int h, int m, int s){
  printf("Digitale-Uhr:\n");
  printf("Stunden: %d\tMinuten: %d\tSekunden: %d\n\n\n",h,m,s);
}

void readConfig(int color, int size, char symbol){
    FILE *fp = fopen("C:/Users/Raphael/Desktop/clockconfig.txt","r");
    if(fp!=NULL){
        fscanf(fp,"%d",&color);
        fflush(stdin);
        fscanf(fp,"%d",&size);
        fflush(stdin);
        fscanf(fp,"%c",&symbol);
        fflush(stdin);
    }
    fclose(fp);
}

void writeConfig(){
    int color=0, size=0;
    char symbol=' ';

    readConfig(color, size, symbol);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    while(!GetAsyncKeyState(13)){
         system("cls");
         char w=' ', r=' ', gr=' ', g=' ';
         if(GetAsyncKeyState(VK_UP)&&color>0){
            color--;
         }
         if(GetAsyncKeyState(VK_DOWN)&&color<3){
            color++;
         }
         switch(color){
            case 0:
                w='X';
                break;
            case 1:
                r='X';
                break;
            case 2:
                gr='X';
                break;
            case 3:
                g='X';
                break;
            default: break;
         }
         printf("Waehle Farbe des Zeichens durch %c %c und bestaetige mit ENTER!\n",25,24);
         SetConsoleTextAttribute(hConsole, 15);
         printf("Weiss\t[%c]\n",w);
         SetConsoleTextAttribute(hConsole, 12);
         printf("Rot\t[%c]\n",r);
         SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
         printf("Gruen\t[%c]\n",gr);
         SetConsoleTextAttribute(hConsole, 14);
         printf("Gelb\t[%c]",g);
         SetConsoleTextAttribute(hConsole, saved_attributes);
         usleep(250000);
    }
    FILE *fp = fopen("C:/Users/Raphael/Desktop/clockconfig.txt","w");
    fprintf(fp,"%d",color);
    fclose(fp);
}
