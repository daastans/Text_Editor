#include<iostream>
#include<unistd.h>
#include<termios.h>

void EnableRawMode()
{
  struct termios raw;
  tcgetattr(STDIN_FILENO,&raw);
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
