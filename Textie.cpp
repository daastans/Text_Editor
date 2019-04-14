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


  tcgetattr(STDIN_FILENO,&original_termios);
  atexit(DisableRawMode);//from stdlib.h
  struct termios raw=original_termios;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_lflag&=~(ECHO | ICANON | ISIG | IEXTEN);
  raw.c_cc[VMIN] = 0;//minimum character to read before returning input
  raw.c_cc[VTIME] = 1;//sets time to wait before returning input
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);

}
int main()
{
  EnableRawMode();
  char c;
  std::cout<<"Textie Version : 1 \r\n";// \r is use to bring pointer to start of line
  while(read(STDIN_FILENO,&c,1)==1 && c!='q')
  {
    if(iscntrl(c)) std::cout<<int(c)<<'\r'<<'\n';
    else std::cout<<int(c)<<"("<<c<<")"<<'\r'<<'\n';

  }
}
