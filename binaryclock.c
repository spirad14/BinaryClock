#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>

void myClock();
void printClock(char f[], int color, int size, HANDLE hConsole, WORD saved_attributes);
void initClock(int *h, int *m, int *s);
void digitalClock(int h, int m, int s);
void readConfig(int *color, int *size, char *symbol);
void writeConfig(int color, int size, char symbol, HANDLE hConsole, WORD saved_attributes);
void initText(char f[], int h, int m, int s, char symbol);

int main(void)
{
    myClock();
    return 0;
}

void myClock(){
  int loop=1;
  int h,m,s;
  int color=1, size=1;
  char symbol='X';

  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
  WORD saved_attributes;

  GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
  saved_attributes = consoleInfo.wAttributes;

  while(loop){
    if(GetAsyncKeyState(VK_ESCAPE)){
      break;
    }
    if(GetAsyncKeyState('C')){
        writeConfig(color, size, symbol, hConsole, saved_attributes);
        GetAsyncKeyState(VK_SPACE); //Clear
        GetAsyncKeyState('C');//Clear
    }
      readConfig(&color, &size, &symbol);
      initClock(&h,&m,&s);
      char f[17]={};
      initText(f,h,m,s,symbol);
      system("cls");
      digitalClock(h,m,s);
      printClock(f,color,size,hConsole,saved_attributes);
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

void initText(char f[], int h, int m, int s, char symbol){
    int i=0, tempi=0;
    for(i=0, tempi=32; i<5; i++,tempi/=2){
        if(h%tempi/(tempi/2)){
            f[i]=symbol;
        }
    }
    for(tempi=64; i<11; i++, tempi/=2){
        if(m%tempi/(tempi/2)){
            f[i]=symbol;
        }
    }
    for(tempi=64; i<17; i++, tempi/=2){
        if(s%tempi/(tempi/2)){
            f[i]=symbol;
        }
    }
}

void printClock(char f[], int color, int size, HANDLE hConsole, WORD saved_attributes){
  WORD farbe;
  int i=0, j=0;
  switch(color){
    case 1:
        farbe=15;   //Weiss
        break;
    case 2:
        farbe=12;   //Rot
        break;
    case 3:
        farbe=10;   //Gruen
        break;
    case 4:
        farbe=14;   //Gelb
        break;
    default:
        farbe=7;    //Standard
        break;
  }
  printf("Binaere-Uhr:\n\n");
  for(j=0; j<size; j++) {
      printf("H\t    ");
      for(i=0; i<size; i++){
          printf(" ");
      }
      printf("|");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[0]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[1]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[2]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[3]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[4]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|\n");
  }
  printf("\n");
  for(j=0; j<size; j++) {
      printf("M\t|");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[5]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[6]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[7]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[8]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[9]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[10]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|\n");
  }
  printf("\n");
  for(j=0; j<size; j++) {
      printf("S\t|");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[11]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[12]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[13]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[14]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[15]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|  |");
      SetConsoleTextAttribute(hConsole, farbe);
      for(i=0; i<size; i++){
          printf("%c",f[16]);
      }
      SetConsoleTextAttribute(hConsole, saved_attributes);
      printf("|\n");
  }
  printf("\n");
  printf("\nESC druecken zum Verlassen...");
}

void digitalClock(int h, int m, int s){
  printf("Stunden: %d\tMinuten: %d\tSekunden: %d\n\n\n",h,m,s);
}

void readConfig(int *color, int *size, char *symbol){
    FILE *fp = fopen("C:/Users/Raphael/Desktop/clockconfig.txt","r");
    int tempi=0;
        if(fp!=NULL){
            fscanf(fp,"%d\n",&tempi);
            if(tempi<1||tempi>4){
                *color=1;
            }
            else{
                *color=tempi;
            }
            fflush(stdin);
            fscanf(fp,"%c\n",symbol);
            fflush(stdin);
            fscanf(fp,"%d\n",&tempi);
            if(tempi<1||tempi>5){
                *size=1;
            }
            else{
                *size=tempi;
            }
            fflush(stdin);
        }
        fclose(fp);
}

void writeConfig(int color, int size, char symbol, HANDLE hConsole, WORD saved_attributes){
    int loop=1;
    while(!GetAsyncKeyState(VK_RETURN)){
        fflush(stdin);
         system("cls");
         char w=' ', r=' ', gr=' ', g=' ';
         if(GetAsyncKeyState(VK_UP)&&(color>=2)){
            color--;
         }
         if(GetAsyncKeyState(VK_DOWN)&&(color<=3)){
            color++;
         }
         switch(color){
            case 1:
                w=symbol;
                break;
            case 2:
                r=symbol;
                break;
            case 3:
                gr=symbol;
                break;
            case 4:
                g=symbol;
                break;
            default: break;
         }
         printf("Waehle Farbe des Zeichens durch %c %c und bestaetige mit ENTER!\n",25,24);
         SetConsoleTextAttribute(hConsole, 15);
         printf("Weiss\t[%c]\n",w);
         SetConsoleTextAttribute(hConsole, 12);
         printf("Rot\t[%c]\n",r);
         SetConsoleTextAttribute(hConsole, 10);
         printf("Gruen\t[%c]\n",gr);
         SetConsoleTextAttribute(hConsole, 14);
         printf("Gelb\t[%c]",g);
         SetConsoleTextAttribute(hConsole, saved_attributes);
         usleep(250000);
    }

    FILE *fp = fopen("C:/Users/Raphael/Desktop/clockconfig.txt","w");
    fprintf(fp,"%d\n",color);

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    system("cls");
    printf("Bitte Symbol zur Anzeige der Uhr eingeben: ");
    fflush(stdin);
    symbol=getchar();
    fprintf(fp,"%c\n",symbol);

    while(loop){
        system("cls");
        printf("Bitte Groesse des Symbol-Feldes eingeben (1-5): ");
        char c=getchar();
        if(c>='1'&&c<='5'){
          size=c-48;
          fprintf(fp,"%d",size);
          break;
        }
    }
    fprintf(fp,"\n//This file is Computer Generated\n");
    fclose(fp);
}
