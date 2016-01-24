#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>

void myClock();
void printClock(char f[], int color, int size, HANDLE hConsole, WORD saved_attributes);
void initClock(int *h, int *m, int *s);
void digitalClock(int h, int m, int s);
void readConfig(int *color, int *size, char *symbol);
void writeConfig(int color, int size, char symbol, HANDLE hConsole, WORD saved_attributes);
void initText(char f[], int h, int m, int s, char symbol, int size);

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
    if(GetAsyncKeyState(27)){
      break;
    }
    if(GetAsyncKeyState(67)){
        writeConfig(color, size, symbol, hConsole, saved_attributes);
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    }
      readConfig(&color, &size, &symbol);
      initClock(&h,&m,&s);
      char f[68]={};
      initText(f,h,m,s,symbol,size);
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

void initText(char f[], int h, int m, int s, char symbol, int size){
    int i=0, j=0, tempi=0;
    for(i=0, tempi=32; i<20; i+=4,tempi/=2){
        if(h%tempi/(tempi/2)){
            for(j=i;j<i+size;j++){
                f[j]=symbol;
            }
        }
    }
    for(tempi=64; i<44; i+=4, tempi/=2){
        if(m%tempi/(tempi/2)){
            for(j=i;j<i+size;j++){
                f[j]=symbol;
            }
        }
    }
    for(tempi=64; i<68; i+=4, tempi/=2){
        if(s%tempi/(tempi/2)){
            for(j=i;j<i+size;j++){
                f[j]=symbol;
            }
        }
    }
}

void printClock(char f[], int color, int size, HANDLE hConsole, WORD saved_attributes){
  WORD farbe;
  int i=0;
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
        farbe=0;    //Standard
        break;
  }
  printf("Binaere-Uhr:\n");
  for(i=0; i<size; i++){
      printf("H\t        ");
      SetConsoleTextAttribute(hConsole, farbe);
      printf("|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\n",
              f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8],f[9],f[10],f[11],
              f[12],f[13],f[14],f[15],f[16],f[17],f[18],f[19]);
      SetConsoleTextAttribute(hConsole, saved_attributes);
  }
  for(i=0; i<size; i++){
      printf("M\t");
      SetConsoleTextAttribute(hConsole, farbe);
      printf("|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\n",
              f[20],f[21],f[22],f[23],f[24],f[25],f[26],f[27],f[28],f[29],f[30],f[31],f[32],
              f[33],f[34],f[35],f[36],f[37],f[38],f[39],f[40],f[41],f[42],f[43]);
      SetConsoleTextAttribute(hConsole, saved_attributes);
  }
  for(i=0; i<size; i++){
      printf("S\t");
      SetConsoleTextAttribute(hConsole, farbe);
      printf("|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\t|%c%c%c%c|\n",
             f[44],f[45],f[46],f[47],f[48],f[49],f[50],f[51],f[52],f[53],f[54],f[55],f[56],
             f[57],f[58],f[59],f[60],f[61],f[62],f[63],f[64],f[65],f[66],f[67]);
      SetConsoleTextAttribute(hConsole, saved_attributes);
  }
  printf("\nESC druecken zum Verlassen...");
}

void digitalClock(int h, int m, int s){
  printf("Digitale-Uhr:\n");
  printf("Stunden: %d\tMinuten: %d\tSekunden: %d\n\n\n",h,m,s);
}

void readConfig(int *color, int *size, char *symbol){
    FILE *fp = fopen("C:/Users/Raphael/Desktop/clockconfig.txt","r");
        if(fp!=NULL){
            fscanf(fp,"%d\n",color);
            if(*color<1&&*color>4){
                *color=1;
            }
            fflush(stdin);
            fscanf(fp,"%c\n",symbol);
            fflush(stdin);
            fscanf(fp,"%d\n",size);
            if(*size<1&&*size>4){
                *size=1;
            }
            fflush(stdin);
        }
        fclose(fp);
}

void writeConfig(int color, int size, char symbol, HANDLE hConsole, WORD saved_attributes){
    int loop=1;

    while(!GetAsyncKeyState(13)){
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
    //fprintf(fp,"//This file is Computer Generated\n");
    fprintf(fp,"%d\n",color);

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    system("cls");
    printf("Bitte Symbol zur Anzeige der Uhr eingeben: ");
    fflush(stdin);
    symbol=getchar();
    fprintf(fp,"%c\n",symbol);

    while(loop){
        system("cls");
        printf("Bitte Groesse des Symbol-Feldes eingeben (1-4): ");
        char c=getchar();
        if(c>='1'&&c<='4'){
          size=c-48;
          fprintf(fp,"%d",size);
          break;
        }
    }
    fflush(stdin);
    fclose(fp);
}
