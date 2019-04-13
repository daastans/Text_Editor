#include<iostream>
#include<unistd.h>

int main()
{
  char c;
  std::cout<<"Textie Version : 1 \n";
  while(read(STDIN_FILENO,&c,1)==1);
}
