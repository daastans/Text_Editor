#include<iostream>
#include<unistd.h>
#include<stdlib.h>

#include<termios.h>

struct termios original_termios;
void DisableRawMode() {
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&original_termios);
}
void EnableRawMode()
{

  struct termios raw=original_termios;
  tcgetattr(STDIN_FILENO,&original_termios);
  atexit(DisableRawMode);//from stdlib.h
  raw.c_lflag&=~(ECHO);
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}
int main()
{
  EnableRawMode();
  char c;
  std::cout<<"Textie Version : 1 \n";
  while(read(STDIN_FILENO,&c,1)==1 && c!='q');
}
