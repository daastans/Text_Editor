#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<termios.h>

struct termios original_termios;
void die(const char* s)
{
  perror(s);
  exit(1);
}
void DisableRawMode() {
  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&original_termios)==-1)
    die("tcsetattr");
}
void EnableRawMode()
{
  if(tcgetattr(STDIN_FILENO,&original_termios)==-1)
    die("tcgetattr");
  atexit(DisableRawMode);//from stdlib.h
  struct termios raw=original_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag&=~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_cc[VMIN] = 0;//minimum character to read before returning input
  raw.c_cc[VTIME] = 1;//sets time to wait before returning input

  if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw)==-1) die("tcsetattr");

}
int main()
{
  EnableRawMode();
  char c;
  std::cout<<"Textie Version : 1 \r\n";// \r is use to bring pointer to start of line
  while(1)
  {
    read(STDIN_FILENO,&c,1);
    if(iscntrl(c)) std::cout<<int(c)<<'\r'<<'\n';
    else std::cout<<int(c)<<"("<<c<<")"<<'\r'<<'\n';
    if(c=='q') break;

  }
}
