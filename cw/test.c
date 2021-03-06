#include<stdio.h>
#include<stdlib.h>

void start();
void help();
int check();
int valid(int,int);

int a[9][9]={{2,3,4,9,5,6,8,1,7}, //for storing the sudoko values
			 {0,5,7,8,1,4,2,6,3},
			 {0,8,6,3,7,2,4,5,9},
			 {5,4,9,6,8,1,7,3,2},
			 {6,1,8,7,2,3,5,9,4},
			 {7,2,3,4,9,5,6,8,1},
			 {3,9,2,5,6,7,1,4,8},
			 {4,7,5,1,3,8,9,2,6},
			 {8,6,1,2,4,9,3,7,5}};


void main()// MAIN FUNCTION CONTAINS CODE FOR CHOOSE OPTIONS
{
 int opt,d;
 int i,j,r,c,checks,flag;

 while(1)
 {
	
   printf("ENTER YOUR CHOICE\n");
   printf("1.START GAME\n");
   printf("2.HOW TO PLAY\n");
   printf("3.EXIT\n");
   printf("->");
   scanf("%d",&opt);
   switch(opt)
   {
    case 1:start();//TO PLAY THE GAME
	     break;
    case 2:help();//TO VIEW KEY
	     break;
    case 3:exit(0);//TO EXIT THE GAME
	     break;
    default:break;
   }
 }
}

void start()// CORE PART OF THE CODE
{
 int i,j,r,c,checks,flag;
 while(1)
 {
  
 for(i=0;i<9;i++)//PRINT THE SUDOKO
 {
  for(j=0;j<9;j++)
  {
   if(j==3||j==6)
   printf("|");
   printf(" %d ",a[i][j]);
  }
  printf("\n");
  if(i==2||i==5)
  printf("---------------------------\n");
 }
  checks=check();//CHECK() RETURNS VALUE LESS THEN OR EQUAL TO 243( 81(ROWS VERFICATION) + 81(COLUMN) + 81(BLOCKS) )

  if(checks==243)
  {
   printf("\nCONGRATULATIONS,YOU MADE IT. ");
   printf("\nPRESS ENTER TO GO BACK ");
   getchar();
   exit(0);
  }
  printf("\nENTER THE ROW AND COLUMN OF POSITION YOU WANT TO CHANGE");
  printf("\nENTER ROW( PRESS 99 TO GO TO MAIN MENU )->");
  scanf("%d",&r);//READS ROWS VALUE
  if(r==99)
  {
   return;
  }
  else
  {
   printf("\nENTER COLUMN->");
   scanf("%d",&c);//READS COLUMN VALUE
  }
  flag=valid(r-1,c-1);//R-1 BECAUSE ARRAY INDEXS FROM 0
  if(flag==1)//VALID FUNCTION RETURN 1 IF WE SELECTED POSITION IS NOT AN FIXED VALUE
  {
   printf("\nENETER THE VALUE ->");
   scanf("%d",&a[r-1][c-1]);
  }
  else
  {
   printf("\nYOU CAN NOT CHANGE IT POSITION.");
   getchar();
  }
 }
}
/*THIS VALID FUNCTION VERY IMPORTENT TO PREVENT CHANGING THE FIXED VALUES*/
int valid(int r, int c)
{
 if(r==1&&c==1)//THIS ARE FIXED POSITION INDEX'S
 return(0);
 else if(r==2&&c==2)
 return(0);
 else
 return(1); //RETUNS 1 IF THE POSITION IS NOT FIXED
}
 /*THIS CHECK FUNCTION TELLS WHTHER YOU SOLVED THE GAME ORE NOT*/
int check()
{
 int count=0,i,j,k,l,m,n,p,q;

 for(i=0;i<9;i++)// THIS CHECK BOTH ROWS AND COLUNS ELEMENTS ARE UNIQULY ARRENGED
 {
  for(j=0;j<9;j++)
  {
   p=0;
   q=0;
   for(k=0;k<9;k++)
   {
    if(a[i][j]==a[i][k])
    {
    p++;
    }
    if(a[j][i]==a[k][i])
    {
    q++;
    }
   }
   if(p==1)
   {
   count++;
   }
   if(q==1)
   {
   count++;
   }
  }
 }
 for(i=0;i<9;)// THIS CHECKS ELEMENTS IN EACH BLOCK ARE UNIQUE
 {
  for(j=0;j<9;)
  {
   for(k=i;k<i+3;k++)
   {
    for(l=j;l<j+3;l++)
    {
     p=0;
     for(m=i;m<i+3;m++)
     {
      for(n=j;n<j+3;n++)
      {
       if(a[k][l]==a[m][n])
       {
	 p++;
       }
      }
     }
     if(p==1)
     {
     count++;
     }
    }
   }
   j=j+3;
  }
  i=i+3;
 }
 
 	for(i=0;i<9;i++)//PRINT THE SUDOKO
	{
		for(j=0;j<9;j++)
		{
			if(a[i][j] == 0)
			{
				count--;
			}
		}
	}
 return(count);//RETURNS THE COUNT OF VERIFIVATIONS OF ALL ELEMENT IN ROWS,COLUMNS,BLOCKS
}

void help()//THIS FUNCTION IS NOT IMPORTENT, THIS IS ONLY FOR TO PRINT KEY OF THE ABOVE GAME
{
int b[9][9]={{2,3,4,9,5,6,8,1,7}, //KEY OF THE ABOVE SUDOKO
	     {9,5,7,8,1,4,2,6,3},
	     {1,8,6,3,7,2,4,5,9},
	     {5,4,9,6,8,1,7,3,2},
	     {6,1,8,7,2,3,5,9,4},
	     {7,2,3,4,9,5,6,8,1},
	     {3,9,2,5,6,7,1,4,8},
	     {4,7,5,1,3,8,9,2,6},
	     {8,6,1,2,4,9,3,7,5}};
int i,j;

for(i=0;i<9;i++)  // THIS NESTED FOR LOOP FOR PRINTING SUDOKO
 {
  for(j=0;j<9;j++)
  {
   if(j==3||j==6)
   printf("|");
   printf(" %d ",b[i][j]);
  }
  printf("\n");
  if(i==2||i==5)
  printf("-----------------------------\n");
 }
 printf("\nPRESS ENTER TO GO BACK");
getchar();//HOLDS THE OUTPUT UNTIL PRESS ENTER
}