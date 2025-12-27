#include "stdio.h"


int first(int first_class[],int Economy[],int code_first[]);
int economy(int economy[],int first_class[],int code_economy[]);
int cancel(int [],int [],int [],int []);

int main(){

  int mune;
  int chair[10];
  int first_class[5],code_first[5];
  int econ0my[5],code_economy[5];


  do
  {    
    printf("===========mune===========\n");
    printf("1)first class\n");
    printf("2)Economy\n");
    printf("3)cancel tiket\n");
    printf("4)Exit\n");
   
    scanf("%d",&mune);

    if (mune == 1)
    {
      first(first_class,econ0my,code_first);
    }
    else if (mune == 2)
    {
      economy(econ0my,first_class,code_economy);
    }
    else if (mune == 3)
    {
      
      cancel(code_economy,code_first,first_class,econ0my);
    }
    
    
    
    

  } while (mune != 4);
  
  printf("Thank you use app");

  
  
}


int first(int first_class[],int Economy[],int code_first[]){

  int age[10];
  char name[10][20],x;
  int num;

  //int code[5];


  printf("**first class**\n");
  printf("Enter number chair:\t");
  scanf("%d",&num);
  
  
  for (int i = 0; i < num; i++)
  {
    
    printf("%d)my name is :\t",i+1);
    scanf("%s",name[i]);

    do{

    printf("code mli :\t");
    scanf("%d",&code_first[i]);

    if (code_first[i] <= 1000000000 || code_first[i] >= 9999999999)
    {
      printf("code interntional 10 number.\n");
    }
    
    
    }while(code_first[i] <= 1000000000 || code_first[i] >= 9999999999);

    do
    {
      
      printf("age :\t");
      scanf("%d",&age[i]);

      if (age[i] < 18)
      {
        printf("zero age 18. !!\n");
      }
      
    
    } while (age[i] < 18);
    

  }
  
  int qq = 0,sum = 0;

  while ( qq < num)
  {
    if (first_class[sum] != 1)
    {
      first_class[sum] = 1;
      qq++;
    }
    
    if (sum >= 5)
    {
      printf("Error\n\n");
    
      for (int i = 0; i < num; i++){
        
        sum--;
        first_class[sum] = 0;
        
    }

    printf("This section is full.\n");
    printf("Do you want to buy a ticket from the first class section?\ny or n\n");
    scanf(" %c",&x);

    if ( x == 'y' )
    {
      economy(first_class,Economy,code_first);

    }else{
      printf("The next flight is in 4 hours.\n\n");
    }
    


    return 1;
    
  }
    sum++;
    
  }
  

  printf("======================\n");
  
  for (int i = 0; i < num; i++)
  {
    printf("my name is:%s\n",name[i]);
    printf("code : %d\n",code_first[i]);
    printf("age : %d\n",age[i]);
    printf("type : first class\n\n");

    
  }

  return 0;
}

int economy(int economy[],int first_class[],int code_economy[]){

  int num;
  char name[5][20],x;
  int age[5];

  printf("**Economy**\n");
  printf("enter number chair:\t");
  scanf("%d",&num);

  for (int i = 0; i < num; i++)
  {
    printf("%d)my name is :\t",i+1);
    scanf("%s",name[i]);

    do
    {
      printf("code mli:\t");
      scanf("%d",&code_economy[i]);

      if ( code_economy[i] <= 1000000000 || code_economy[i] >= 9999999999 )
      {
        printf("code international 10 numbrer .\n");
      }
      
    } while ( code_economy[i] <= 1000000000 || code_economy[i] >= 9999999999);
    
    

    do
    {
      
      printf("age :\t");
      scanf("%d",&age[i]);

      if (age[i] < 18)
      {
        printf("zero age 18 .!!\n");
      }
      
    } while (age[i] < 18 );
    
  
  }


  int qq = 0,sum = 0;

  while ( qq < num)
  {
    if (economy[sum] != 1)
    {
      economy[sum] = 1;
      qq++;
    }
    
    if (sum >= 5)
    {
      printf("Error\n\n");
    
      for (int i = 0; i < num; i++){
        
        sum--;
        economy[sum] = 0;
        
    }

    printf("This section is full.\n");
    printf("Do you want to buy a ticket from the first class section?\ny or n\n");
    scanf(" %c",&x);

    if ( x == 'y' )
    {
      first(first_class,economy,code_economy);

    }else{
      printf("The next flight is in 4 hours.\n\n");
    }
    
    


    return 1;
    
  }
    sum++;
    
  }

  printf("======================\n");
  
  for (int i = 0; i < num; i++)
  {
    printf("my name is:%s\n",name[i]);
    printf("code : %d\n",code_economy[i]);
    printf("age : %d\n",age[i]);
    printf("type : Economy\n\n");

    
  }

  return 0;
}

int cancel(int code_economy[],int code_first[],int first_class[],int Economy[]){

  const int len = 5;

  
  int x,flag = 1,flag2 = 1;
  printf("**concel tiket **\n");
  do
  {

    printf("Enter number code international :\t");
    scanf("%d",&x);
    if (x <= 1000000000 || x >= 9999999999)
    {
      printf("number code international 10 .\n");
    }
    
  
  } while (x <= 1000000000 || x >= 9999999999);
  
 

  
  for (int  i = 0; i < len ; i++)
  {
    if ( x == code_economy[i])
    {
      Economy[i] = 0;
      flag = 0;
      break;
      
    }
    

  }
  
  if (flag == 0)
  {
    printf("reserv tiket concel shod.\n Tiket Economy.\n");
    return 0;
  }
  
  for (int i = 0; i < len; i++)
  {
    if (x == code_first[i])
    {
      first_class[i] = 0;
      flag2 = 0;
      break;
    }
    
  }
  
  if (flag2 == 0)
  {
    printf("reserv tiket concel shod.\n Tiket First Class.\n");
    return 0;
  }
  

  if (flag2 == 1 && flag == 1)
  {
    printf("not found code international.\n");
  }
  
  return 0;
}