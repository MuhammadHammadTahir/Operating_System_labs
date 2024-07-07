#include <stdio.h>

struct student{
  int id;
  int class;
  int reg;
};

int main(){
  struct student s1[3];
  for(int i=0;i<3;i++)
  {
  s1[i].id=2;
  s1[i].class=3;
  s1[i].reg=4;
  printf("%d\n%d\n%d\n",s1[i].id,s1[i].class,s1[i].reg);
  }
  

  return 0;
}
