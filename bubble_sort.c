#include <iostream>

int main()
{
  int i, j, size;
  int arry[100];
  char ch;
  for(int i=0; i<100; i++)
  {
    printf("\nEnter the Interger Number : ");
    scanf("%d", &arry[i]);
    size++;
    printf("Do you want to add another number ? Y/N  : ");
    scanf(" %c", &ch);
    if(ch=='N' || ch =='n')
    {
      break;
    }
      else if (ch=='Y' || ch=='y') {
      continue;
      }
    else{
      printf("Wrong input\n");
      exit(1);
    }

    if (size >= 100)
    {
      printf("Maximum number of elements reached\n");
      break;
    }
  }

  int temp;
  for(i=0; i<size-1 ; i++)
  {
    for(j=0; j<size-i-1; j++)
    {
      if (arry[j] > arry[j + 1]) 
      {
        printf("Swap index %d with %d\n", j, j+1);
        temp = arry[j];
        arry[j] = arry[j + 1];
        arry[j + 1] = temp;
      }
    }

  }

  printf("\nSorted list = ");
  for(i=0;i<size;i++)
  {
    printf("%d ",arry[i]);
  }
}
