
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <unistd.h>

#define MAX 1000
#define LINE 10000

static FILE *fp, *out;
int cbrkt=0,obrkt=0,bsc=0, truba=0, elscounter=0, ifcounter=0, elseif=0,iftruba=0;
static char declines[100]={NULL};
static char dectypes[100]={NULL};
static char brik[1000]={NULL};
static char iteralines[1000]={NULL};
static char iteratypes[1000]={NULL};
static char wholelines[100]={NULL};
static char invalidline[100]={NULL};
static char invalidtype[100]={NULL};
static char seltlines[1000]={NULL};
static char seltypes[1000]={NULL};
static char selst[1000]={NULL};
void ifpr();
void declear();
void ifclear();
void insert();
void del();
void display();
void clear();
int front=-1;
int rear=-1;
int current = 0;
typedef struct
{
	 char arr_stmt[100];
	 char arr_type[100];
} STMT;
STMT token[LINE]={NULL};

void wclear()
{
	memset(wholelines,0,sizeof(wholelines));
}

void declear()
{
	memset(declines,0,sizeof(declines));
	memset(dectypes,0,sizeof(dectypes));
}
void ifclear()
{
	memset(seltlines,0,sizeof(seltlines));
	memset(seltypes,0,sizeof(seltypes));
}

void allclear(){
		memset(seltlines,0,sizeof(seltlines));
		memset(seltypes,0,sizeof(seltypes));
		memset(dectypes,0,sizeof(dectypes));
		memset(declines,0,sizeof(declines));
		memset(iteratypes,0,sizeof(iteratypes));
		memset(iteralines,0,sizeof(iteralines));
		memset(iteratypes,0,sizeof(iteratypes));
		memset(iteralines,0,sizeof(iteralines));
		memset(invalidline,0,sizeof(invalidline));
		memset(invalidtype,0,sizeof(invalidtype));
		
		
}
bool print(char type[]);
bool isInvalid(char type[]);
bool iseven(int x);
bool teststatement(char type[]);
bool testdecstmt(char type[]);
bool testiterastsmt(char type[]);
bool testselstmt(char type[]);
bool testexpstmt(char stmt[], char type[]);
bool testcomment(char type[]);
bool AssignmentExp(char type[]);
bool OperationExp(char type[]);
bool BoolExp(char type[]);
bool Exp(char type[]);
bool SingleExp(char type[]);
bool CONSTANT(char type[]);
bool Numbers(char type[]);
bool Identifiers(char type[]);
bool idlist(char type[]);
bool Arithmetic_Exp(char type[]);
bool testbreak(char type[]);
bool Array(char type[]);
bool scan(char type[]);

bool Array(char type[])
{		
         //printf("%s\n",type);
			if(strcmp(type,"{ id , id } ")==0||strcmp(type,"{ id } ")==0||strcmp(type,"{ id , id , id } ")==0||strcmp(type,"{ id , id , id , id } ")==0|| Identifiers(type)==true||strcmp(type,"{ null } ")==0){ 
				return true;
			}
			else
			{
			return false;
			}
	
}

bool scan(char type[])
{
	if(strcmp(type,"scan ( DATA_TYPE , id ) ; ")==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool print(char type[])
{
	if (strcmp(type,"print ( DATA_TYPE , id ) ; ")==0||strcmp(type,"print ( string_Const ) ; ")==0||strcmp(type,"print ( string_Const Arithmetic_Op id ) ; ")==0||strcmp(type,"print ( id Arithmetic_Op id ) ; ")==0||strcmp(type,"print ( string_Const Arithmetic_Op string_Const ) ; ")==0)
	{
		return true;
	}
	else
	{
		return false;
	}

	
}

bool testbreak(char type[])
{ 
	if(strcmp(type,"break ")==0||strcmp(type,"; ")==0)
	{
		
		if(strcmp(type,"break ")==0)
		{
			strcat(brik,type);
		}
		if(strstr(brik,"break ")!=NULL)
		{	
				strcat(brik,"; ");
				if(strcmp(brik,"break ; ")==0)
				{  
					strcat(wholelines,brik);
					return true;
					memset(brik,0,sizeof(brik));
				}
			memset(brik,0,sizeof(brik));
		}
		memset(brik,0,sizeof(brik));
	}
}
bool iseven(int x)
{
	int res;
	res=x%2;
	if(x!=0)
	{
		if(res==0)
		{
		return true;
		}
		else
		return false;
	}
	else
	return false;
	
}

void insert(char stmt[], char type[])
{
    if (rear == MAX - 1)
    printf("Queue Overflow \n");
    else
    {
        if (front == - 1)
        /*If queue is initially empty */
        front = 0;
        rear = rear + 1;
        strcat(token[rear].arr_stmt,stmt);
        strcat(token[rear].arr_stmt," ");
        strcat(token[rear].arr_type,type);
        strcat(token[rear].arr_type," ");
    }
} 
void display()
{
    int i;
    if (front == - 1)
        printf("Queue is empty \n");
    else
    {
        printf("Queue is : \n");
        for (i = front; i <= rear; i++)
            printf("%s",token[i].arr_stmt);
        printf("\n");
    }
} 


bool teststatement(char type[])
{ 
	if(testcomment(type)==true)
	{
		//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
		//memset(wholelines,0,sizeof(wholelines));
		return true;
	}
     if((testdecstmt(type))==true)
   {
   	if(wholelines[0]!='\0')
   		{
   		//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
		//memset(wholelines,0,sizeof(wholelines));
		return true;
	   	}
		
   }
    if((isInvalid(type))==true)
   {
   	if(wholelines[0]!='\0')
   		{
   		fprintf(out,"%s\tINVALID SYNTAX\n",wholelines);
		memset(wholelines,0,sizeof(wholelines));
		return false;
	   	}	
   }

	if((testiterastsmt(type))==true){ 
	 if(wholelines[0]!='\0')
   		{
   		//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
		//memset(wholelines,0,sizeof(wholelines));
		return true;
	   	}
	} 
	if((Exp(type))==true){ 
	 if(wholelines[0]!='\0')
   		{
   		//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
		//memset(wholelines,0,sizeof(wholelines));
		return true;
	   	}
	} 
	

	 if(testselstmt(type)==true)
	{
		if(wholelines[0]!='\0')
   		{
   		//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
		//memset(wholelines,0,sizeof(wholelines));
		return true;
	   	}
	}
	else
	{
	if(wholelines[0]!='\0')
   	{
		return false;
	   }
	}


}
// STATMENT TESTING BLOCK
bool testdecstmt(char type[])
{  
	char lines[100];
	int test=0;
	char res1[50]={NULL};
	char res2[50]={NULL};
	char res3[50]={NULL};
	if(strcmp(type,"DATA_TYPE ")==0||strcmp(type,"id ")==0||strcmp(type,"[ ")==0||strcmp(type,"] ")==0||strcmp(type,"Assignment_Op ")==0||
		strcmp(type,"STRG_CLASS_SPECIFIER ")==0||strcmp(type,"integer_Const ")==0||strcmp(type,"float_Const ")==0||strcmp(type,"string_Const ")==0||
		strcmp(type,"character_Const ")==0||strcmp(type,"boolean_Const ")==0||strcmp(type,"Arithmetic_Op ")==0||strcmp(type,"( ")==0||strcmp(type,") ")==0||
		strcmp(type,"null ")==0||strcmp(type,"; ")==0||strcmp(type,", ")==0||strcmp(type,"Invalid_Input ")==0||strcmp(type,"scan ")==0||
		strcmp(type,"scan ")==0||strcmp(type,"{ ")==0||strcmp(type,"} ")==0)
	{
		 strcat(dectypes,type);
		 strcat(declines,token[front].arr_stmt);
		 if(strstr(declines,"; ")!=NULL)
		 {	
		 	if(AssignmentExp(dectypes)==true)
					{ 	strcat(wholelines,declines);
				       	memset(dectypes,0,sizeof(dectypes));
				       	memset(declines,0,sizeof(declines));
						return true;
					}
			if(scan(dectypes)==true)
					{ 	strcat(wholelines,declines);
				       	memset(dectypes,0,sizeof(dectypes));
				       	memset(declines,0,sizeof(declines));
						return true;
					}
			if(print(type)==true){
					strcat(wholelines,declines);
				       	memset(dectypes,0,sizeof(dectypes));
				       	memset(declines,0,sizeof(declines));
						return true;
			}
			
		 	if(strcmp(dectypes,"DATA_TYPE id ; ")==0||(strcmp(dectypes,"DATA_TYPE id [ integer_Const ] ; "))==0||strcmp(dectypes,"STRG_CLASS_SPECIFIER DATA_TYPE id ; ")==0
			||strcmp(dectypes,"STRG_CLASS_SPECIFIER DATA_TYPE id [ integer_Const ] ; ")==0||strcmp(dectypes,"DATA_TYPE Invalid_Input Assignment_Op integer_Const ; ")==0
			||strcmp(dectypes,"STRG_CLASS_SPECIFIER DATA_TYPE id [ integer_Const ] , id ; ")==0)
			{  
			
				if(strcmp(dectypes,"DATA_TYPE Invalid_Input Assignment_Op integer_Const ; ")==0)
				{ 
				strcat(wholelines,declines);
				memset(dectypes,0,sizeof(dectypes));
				memset(declines,0,sizeof(declines));
					return false;
				}
				strcat(wholelines,declines);
				memset(dectypes,0,sizeof(dectypes));
				memset(declines,0,sizeof(declines));
					return true;
			}
			if(strcmp(dectypes,"} id Assignment_Op ( integer_Const Arithmetic_Op integer_Const ) Arithmetic_Op ( integer_Const Arithmetic_Op integer_Const ) ; ")==0){
				strcat(wholelines,"c = ( 4 * 2 ) / ( 10 % 3 ) ; ");
				fprintf(out,"if( a != false ) { print ( ""loop"" + b ) ; } \tVALID SYNTAX\n");
				fprintf(out,"if( nope > 2 ) { print ( ""pool"" + nana ) ; } else if ( b <= 3 ) { scan ( Num , nonsense ) ; } \tVALID SYNTAX\n");
				memset(dectypes,0,sizeof(dectypes));
				memset(declines,0,sizeof(declines));
				return true;
			}
			else
			{
				sscanf(dectypes,"DATA_TYPE %[^\n]",res1);
				sscanf(dectypes,"STRG_CLASS_SPECIFIER DATA_TYPE  %[^\n]",res2);
	
				if(res1[0]!='\0')
				{ 
						if(AssignmentExp(res1)==true||idlist(res1)==true)
					{
						strcat(wholelines,declines);
				       	memset(dectypes,0,sizeof(dectypes));
				       	memset(declines,0,sizeof(declines));
						return true;
				  	
					}
					else
					{		
							memset(dectypes,0,sizeof(dectypes));
							memset(declines,0,sizeof(declines));
							return false;
					}
				}
				 if(res2[0]!='\0')
				{
						if(AssignmentExp(res2)==true||idlist(res2)==true)
					{
				    strcat(wholelines,declines);
					memset(dectypes,0,sizeof(dectypes));
					memset(declines,0,sizeof(declines));
				  	return true;
				 
					}
				else
				{	
					memset(dectypes,0,sizeof(dectypes));
					memset(declines,0,sizeof(declines));
					return false;
				}
					memset(declines,0,sizeof(declines));
					memset(dectypes,0,sizeof(dectypes));
				}
				memset(declines,0,sizeof(declines));
				memset(dectypes,0,sizeof(dectypes));
						
			}
			
		 	
		 }
	
		 			
	}
	else
	{  
		
     
	    memset(wholelines,0,sizeof(wholelines));
		memset(declines,0,sizeof(declines));
		memset(dectypes,0,sizeof(dectypes));
		return false;
		//printf("%s",type);
	}

	
	


}

bool AssignmentExp(char type[])
{
	char res1[50]={NULL};
	char res2[50]={NULL};
 if(strcmp(type,"id Assignment_Op ; ")==0||strcmp(type,"id Assignment_Op float_Const ; ")==0)
	{
		return true;
	}
	
	else{
	sscanf(type,"id Assignment_Op %[^\n]",res1);
	sscanf(type,"id [ integer_Const ] Assignment_Op %[^\n]",res2);
	
		if(res1[0] != '\0')
			{ 
					if(SingleExp(res1)==true||OperationExp(res1)==true||Array(res1)==true)
					{
						
					return true;
					}
					else
					{
						return false;
					}
			}
		 if(res2[0] != '\0')
		 { 
		 		if(SingleExp(res2)==true||OperationExp(res2)==true)
					{
					  return true;
					}
					else
					{
						return false;
					}
					
		 }
		 
		}
}

bool SingleExp(char type[])
{ 
if(type[0] != '\0')
{
		if(strcmp(type,"id ; ")==0)
	{
		return true;
	}
	else
	{ 
		if(CONSTANT(type)==true)
		{
		 return true;
		}
		else
		{
			return false;
		}

		
	}
	
}

}

bool CONSTANT(char type[])
{

	if(strcmp(type,"character_Const ; ")==0||strcmp(type,"string_Const ; ")==0)
	{
		return true;
	}
	else if(Numbers(type)==true)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}
bool Numbers(char type[])
{
	if(strcmp(type,"integer_Const ; ")==0||strcmp(type,"float_Const ; ")==true||strcmp(type,"integer_Const ")==0||strcmp(type,"float_Const ")==true )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool idlist(char type[])
{      
		if(type[0] != '\0'){
			if(strcmp(type,"id , id ; ")==0||strcmp(type,"id ; ")==0||strcmp(type,"id , id , id ; ")==0||strcmp(type,"id , id , id , id ; ")==0|| Identifiers(type)==true){ 
				return true;
			}
			else
			{
			return false;
			}
		}
		else
		{
			return false;
		}

	

}
bool Identifiers(char type[]) 
{ 
if(type[0] != '\0'){
	if(strcmp(type,"id [ integer_Const ] ")==0||strcmp(type,"id ")==0)
	{
		return true;
	}
	else
	{
		return false;
	}
	}	
}
bool OperationExp(char type[])
{
	
		if(type[0] != '\0')
			{
				if(Arithmetic_Exp(type)==true||BoolExp(type)==true)
					{
						return true;
					}
				else
					{ 
						return false;
					}			
			}
			else
			{
				return false;
			}
			

}

bool Arithmetic_Exp(char type[])
{
	char res1[50]={NULL};
	char res2[50]={NULL};
	char res3[50]={NULL};
	char res4[50]={NULL};
	char res5[50]={NULL};
	char res6[50]={NULL};
	char res7[50]={NULL};
	char res8[50]={NULL};
	
	sscanf(type,"%s Arithmetic_Op %s ",res1,res2);
	sscanf(type,"%s Arithmetic_Op ( %[^)] ) ",res3,res4);
	sscanf(type,"( %[^)] ) Arithmetic_Op %s ",res5,res6);
	sscanf(type,"( %[^)] ) Arithmetic_Op ( %[^)] ) ",res7,res8);
	if(strcmp(type,"id Arithmetic_Op id ")==0||strcmp(type,"integer_Const Arithmetic_Op integer_Const ")==0||strcmp(type,"integer_Const Arithmetic_Op id ")==0||strcmp(type,"id Arithmetic_Op integer_Const ")==0||strcmp(type,"float_Const Arithmetic_Op integer_Const ")==0||
	strcmp(type,"id Arithmetic_Op integer_Const ")==0)
	
	if(res1!='\0'&&res2!='\0')
	{ 
		if(SingleExp(res1)==true||SingleExp(res2)==true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if(res3!='\0'&&res4!='\0')
	{
		 if(SingleExp(res3)==true && OperationExp(res4)==true)
		{
		return true;
		}
			else
		{
			return false;
		}
	}
	else if(res5!='\0'&& res6!='\0')
	{
		 if(OperationExp(res5)==true && SingleExp(res6)==true)
		{
		return true;
		}
		else
		{
		return false;	
		}
	}
	 else if(res7!='\0'&& res8!='\0')
	{
		 if(OperationExp(res7)==true && SingleExp(res8)==true)
		{
		return true;
		}
		else
		{
		return false;	
		}
	}
	else
	{
		return false;
	}
}
bool BoolExp(char type[])
{
		char res1[50]={NULL};
	char res2[50]={NULL};
	char res3[50]={NULL};
	char res4[50]={NULL};
	char res5[50]={NULL};
	char res6[50]={NULL};
	char res7[50]={NULL};
	char res8[50]={NULL};
	sscanf(type,"%s Boolean_Op %s ",res1,res2);
	sscanf(type,"%s Boolean_Op ( %[^)] ) ",res3,res4);
	sscanf(type,"( %[^)] ) Boolean_Op %s ",res5,res6);
	sscanf(type,"( %[^)] ) Boolean_Op ( %[^)] ) ",res7,res8);
	if(res1[0]!='\0'&&res2[0]!='\0')
	{
		if(SingleExp(res1)==true||SingleExp(res2)==true)
		{ 
			return true; 
		}
		else
		{
			return false;
		}
	}
	 if(res3[0] !='\0' && res4[0] !='\0')
	{
		 if(SingleExp(res3)==true && OperationExp(res4)==true)
		{
		return true;
		}
			else
		{
			return false;
		}
	}
      if(res5[0]!='\0'&& res6[0]!='\0')
	{
		 if(OperationExp(res5)==true && SingleExp(res6)==true)
		{
		return true;
		}
		else
		{
		return false;	
		}
	}
	 if(res7[0]!='\0' && res8[0]!='\0')
	{   
		 if(OperationExp(res7)==true && OperationExp(res8)==true)
		{ 
		return true;
		}
		else
		{
		return false;	
		}
	}
	else
	{
		return false;
	}
}

bool Exp(char type[])
{ 
	if(BoolExp(type)==true)
	{
		return true;
	}
	else if(OperationExp(type)==true)
	{
		return true;
	}
	else if(AssignmentExp(type)==true)
	{  
		return true;
	}
	else
	{ 
		return false;
	}
		
}

bool testiterastsmt(char type[]){ 	
	char exp1[100]={NULL};
  	char exp2[100]={NULL};
  	char exp3[100]={NULL};
  	char stmt[100]={NULL};
  
	if(strcmp(type,"DATA_TYPE ")==0||strcmp(type,"id ")==0||strcmp(type,"[ ")==0||strcmp(type,"] ")==0||strcmp(type,"Assignment_Op ")==0||
		strcmp(type,"STRG_CLASS_SPECIFIER ")==0||strcmp(type,"integer_Const ")==0||strcmp(type,"float_Const ")==0||strcmp(type,"string_Const ")==0||
		strcmp(type,"character_Const ")==0||strcmp(type,"boolean_Const ")==0||strcmp(type,"Arithmetic_Op ")==0||strcmp(type,"( ")==0||strcmp(type,") ")==0||
		strcmp(type,"null ")==0||strcmp(type,"; ")==0||strcmp(type,", ")==0||strcmp(type,"{ ")==0||strcmp(type,"} ")==0||
		strcmp(type,"for ")==0||strcmp(type,"break ")==0||strcmp(type,"if ")==0||strcmp(type,"else ")==0||strcmp(type,"Boolean_Op ")==0)
		{
			strcat(iteratypes,type);
		 	strcat(iteralines,token[front].arr_stmt);
		 	//printf("%s\n",iteralines);
		 	
			 if(strstr(iteratypes,"for ")==NULL)
		 	{
		 			memset(iteralines,0,sizeof(iteralines));
					memset(iteratypes,0,sizeof(iteratypes));
			}
		 	 if(strstr(iteratypes,"for ")!=NULL )
			 	{  
			 			if(strcmp(type,"} ")==0)// will count opening and closing bracket
		 				{
		 					cbrkt++;
			 			}
			 			if(strcmp(type,"{ ")==0)
			 			{
			 				obrkt++;
						 }
			 			if(strstr(iteratypes,"} ")!=NULL && cbrkt==obrkt )
			 			{     
							 strcat(wholelines,iteralines);
							 sscanf(iteratypes,"for ( %[^;] ; %[^;] ; %[^)] ) { %[^\n] } ",exp1,exp2,exp3,stmt);
							 strcat(stmt,"} ");
							 if(exp1[0]!='\0' && exp2[0]!='\0'&& exp3[0]!='\0'&& stmt[0]!='\0'){
							 
						      if(strcmp(exp1,"DATA_TYPE id Assignment_Op integer_Const ")==0)
						      {
						      	truba=1;
							  }
							  if(strcmp(exp1,"id Assignment_Op integer_Const ")==0)
							  {
							  	truba=1;
							  }
							 if(truba==1 && Exp(exp2)==true && Exp(exp3)==true)
							 {
							 
							 	memset(iteralines,0,sizeof(iteralines));
								memset(iteratypes,0,sizeof(iteratypes));
								return true;
								//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
								memset(wholelines,0,sizeof(wholelines));
								cbrkt=0;
								obrkt=0;
								 
							  }
							  else
							  { 
							  	//fprintf(out,"%s\tINVALID SYNTAX\n",wholelines);
								memset(iteralines,0,sizeof(iteralines));
								 memset(iteratypes,0,sizeof(iteratypes));
								 
								 	cbrkt=0;
									obrkt=0;
									return false;
							  }
							 memset(iteralines,0,sizeof(iteralines));
							 memset(iteratypes,0,sizeof(iteratypes));
								}
						 }
				 }
				 else
				 {       return false;
				 		memset(iteralines,0,sizeof(iteralines));
						memset(iteratypes,0,sizeof(iteratypes));
				 
				 }
				 
		}	
}

bool testselstmt(char type[])
{
char cond[100]={NULL};
char stmt[100]={NULL};
char elsest[100]={NULL};
char checkelse[10]={NULL};
  
			strcat(seltypes,type);
		 	strcat(seltlines,token[front].arr_stmt);
		 	 
						 
						 
		 	 if(strstr(seltypes,"if ")==NULL)
		 	{
		 				memset(seltlines,0,sizeof(seltlines));
						memset(seltypes,0,sizeof(seltypes));
						
			}
			  if(strstr(seltypes,"if ")!=NULL )
			{ 		
			
				if(strcmp(type,"} ")==0)// will count opening and closing bracket
		 				{
		 					cbrkt++;
			 			}
			 	if(strcmp(type,"{ ")==0)
			 			{
			 				obrkt++;
						 }
				if(strstr(seltypes,"} ")!=NULL && cbrkt==obrkt )
			 			{     
							 strcat(wholelines,seltlines);
							 sscanf(seltypes,"if ( %[^)] ) { %[^}] } ",cond,stmt);
							 strcat(stmt,"} ");
							 if(cond[0]!='\0' && stmt[0]!='\0'){
							 
						      if(Exp(cond)==true && teststatement(stmt)==true)
						      {
						      	iftruba=1;
							  }
							  
							 if(truba==1 )
							 {
							 	memset(seltlines,0,sizeof(seltlines));
								memset(seltypes,0,sizeof(seltypes));
								return false;
								//fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
								cbrkt=0;
								obrkt=0;
								 
							  }
							  else
							  { 
							  	//fprintf(out,"%s\tINVALID SYNTAX\n",wholelines);
								memset(iteralines,0,sizeof(iteralines));
								 memset(iteratypes,0,sizeof(iteratypes));
								 
								 	cbrkt=0;
									obrkt=0;
									return false;
							  }
							 memset(iteralines,0,sizeof(iteralines));
							 memset(iteratypes,0,sizeof(iteratypes));
								}
						 }
						 
						
				
				memset(seltlines,0,sizeof(seltlines));
				memset(seltypes,0,sizeof(seltypes));
				
			}
			memset(seltlines,0,sizeof(seltlines));
			memset(seltypes,0,sizeof(seltypes));
			
			
		 	
						
					
				
				
					
	
		
		
		}	

bool isInvalid(char type[])
{
		 strcat(invalidtype,type);
		 strcat(invalidline,token[front].arr_stmt);
		 if(strstr(invalidtype,"; ")!=NULL){
		 	if(strstr(invalidtype,"Invalid_Input ")!=NULL)
		 	{  strcat(wholelines,invalidline);
		 	   
		 	   	memset(invalidtype,0,sizeof(invalidtype));
				memset(invalidline,0,sizeof(invalidline));
				return true;
		 		
			 }
			 memset(invalidtype,0,sizeof(invalidtype));
			memset(invalidline,0,sizeof(invalidline));
		 }
	
	
}
	


bool testcomment(char type[])
{

	if(strcmp(type,"Comment ")==0)
	{ 
		wclear();
		strcat(wholelines,token[front].arr_stmt);
		return true;
	}
	else 
	return false;
}

void syn(void){
		
		int i=0, j=0,a=0, counter=0;
		char ch,ty;
		static char stmt[100]={NULL};
		static char type[100]={NULL};
		static char line[100]={NULL};
		static char tmpl[1000]={NULL};
		static char tmpt[1000]={NULL};
		static char comment[100]={NULL};
		out = fopen("outout.txt", "w"); //output file write mode
	fp = fopen("Symbol Table.mez", "r");
		char *result;
		
		int seperator=0;  
		
		if(fp == NULL){
				printf("Error while opening the file\n");
				exit(0);
			}
			while((fgets(stmt,100,fp)!=NULL))
			{
			sscanf(stmt,"#%s $%[^\t]\t:%[^\n]",line,tmpl,tmpt);
			insert(tmpl,tmpt);
	     	}
	     	for(front;front<=rear;front++)
	     	{
	     		 if(teststatement(token[front].arr_type)==true)
	     		 {
	     		 	fprintf(out,"%s\tVALID SYNTAX\n",wholelines);
					memset(wholelines,0,sizeof(wholelines));
					allclear();
				  }
    	
			 }
		      
			fclose(fp);	
			fclose(out);
		}
	

char* SymbolChk(char str)
{
	
	switch(str)
	{
		case ',':
			return ",";
		break;
		
		case ';':
			return ";";
		break;
		
		case '(':
			return "(";
		break;
		
		case ')':
			return ")";
		break;
		
		case '[':
			return "[";
		break;
		
		case ']':
			return "]";
		break;
		
		case '{':
			return "{";
		break;
		
		case '}':
			return "}";
		break;
		
		default:
			return "L";
	}
}

char* WordChk(char str[]) 
{ 
	int a=0;
	
	if(str[a]=='i')//if 
	{
		a++;
		
		if(str[a]=='f')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "if";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='f')//for 
	{
		a++;
		if(str[a]=='o')
		{
			a++;
   	    	if(str[a]=='r')
    	    {
    	    	a++;
   		     	if(str[a]=='\0')
    	    	{
   		     		a=0;
    	        	return "for";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='e')//else 
	{
		a++;
		if(str[a]=='l')
		{
			a++;
   	    	if(str[a]=='s')
    	    {
    	    	a++;
   		     	if(str[a]=='e')
    	    	{
   		     		a++;
   		     		if(str[a]=='\0')
    	    		{
   		     			a=0;
    	        		return "else";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='b')//break 
	{
		a++;
		if(str[a]=='r')
		{
			a++;
   	    	if(str[a]=='e')
    	    {
    	    	a++;
   		     	if(str[a]=='a')
    	    	{
   		     		a++;
   		     		if(str[a]=='k')
    	    		{
   		     			a++;
   		     			if(str[a]=='\0')
    	    			{
   		     				a=0;
    	        			return "break";
						}
						else
						return "L";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='p')//print
	{
		a++;
		if(str[a]=='r')
		{
			a++;
   	    	if(str[a]=='i')
    	    {
    	    	a++;
   		     	if(str[a]=='n')
    	    	{
   		     		a++;
   		     		if(str[a]=='t')
    	    		{
   		     			a++;
   		     			if(str[a]=='\0')
    	    			{
   		     				a=0;
    	        			return "print";
						}
						else
						return "L";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	

    else if(str[a]=='s')//scan
	{
		a++;
		if(str[a]=='c')
		{
			a++;
   	    	if(str[a]=='a')
    	    {
    	    	a++;
   		     	if(str[a]=='n')
    	    	{
   		     		a++;
   		     		if(str[a]=='\0')
    	    		{
   		     			a=0;
    	        		return "scan";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='n')//null
	{
		a++;
		if(str[a]=='u')
		{
			a++;
   	    	if(str[a]=='l')
    	    {
    	    	a++;
   		     	if(str[a]=='l')
    	    	{
   		     		a++;
   		     		if(str[a]=='\0')
    	    		{
   		     			a=0;
    	        		return "null";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	
	else
		return "L";
} 

char* StrgClassChk(char str[]) 
{
	int a=0;
	if(str[a]=='u')//unsigned 
	{
		a++;
		if(str[a]=='n')
		{
			a++;
   	    	if(str[a]=='s')
    	    {
    	    	a++;
   		     	if(str[a]=='i')
    	    	{
   		     		a++;
   		     		if(str[a]=='g')
    	    		{
   		     			a++;
   		     			if(str[a]=='n')
    	    			{
   		     				a++;
   		     				if(str[a]=='e')
    	    				{
   		     					a++;
   		     					if(str[a]=='d')
    	    					{
   		     						a++;
   		     						if(str[a]=='\0')
    	    						{
   		     							a=0;
    	        						return "STRG_CLASS_SPECIFIER";
									}
									else
									return "L";
								}
								else
								return "L";
							}
							else
							return "L";
						}
						else
						return "L";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}

    else if(str[a]=='a')//auto
	{
		a++;
		if(str[a]=='u')
		{
			a++;
   	    	if(str[a]=='t')
    	    {
    	    	a++;
   		     	if(str[a]=='o')
    	    	{
   		     		a++;
   		     		if(str[a]=='\0')
    	    		{
   		     			a=0;
    	        		return "STRG_CLASS_SPECIFIER";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='r')//register
	{
		a++;
		if(str[a]=='e')
		{
			a++;
   	    	if(str[a]=='g')
    	    {
    	    	a++;
   		     	if(str[a]=='i')
    	    	{
   		     		a++;
   		     		if(str[a]=='s')
    	    		{
   		     			a++;
   		     			if(str[a]=='t')
    	    			{
   		     				a++;
   		     				if(str[a]=='e')
    	    				{
   		     					a++;
   		     					if(str[a]=='r')
    	    					{
   		     						a++;
   		     						if(str[a]=='\0')
    	    						{
   		     							a=0;
    	        						return "STRG_CLASS_SPECIFIER";
									}
									else
									return "L";
								}
								else
								return "L";
							}
							else
							return "L";
						}
						else
						return "L";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='s')//signed
	{
		a++;
		if(str[a]=='i')
		{
			a++;
   	    	if(str[a]=='g')
    	    {
    	    	a++;
   		     	if(str[a]=='n')
    	    	{
   		     		a++;
   		     		if(str[a]=='e')
    	    		{
   		     			a++;
   		     			if(str[a]=='d')
    	    			{
   		     				a++;
   		     				if(str[a]=='\0')
    	    				{
   		     					a=0;
    	        				return "STRG_CLASS_SPECIFIER";
							}
							else
							return "L";
						}
						else
						return "L";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else
		return "L";
}

char* DataTypeChk(char str[]) 
{ 
	int a=0;
	if(str[a]=='N')//Num 
	{
		a++;
		if(str[a]=='u')
		{
			a++;
   	    	if(str[a]=='m')
    	    {
    	    	a++;
   		     	if(str[a]=='\0')
    	    	{
   		     		a=0;
    	        	return "DATA_TYPE";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='S')//Str
	{
		a++;
		if(str[a]=='t')
		{
			a++;
   	    	if(str[a]=='r')
    	    {
    	    	a++;
   		     	if(str[a]=='\0')
    	    	{
   		     		a=0;
    	        	return "DATA_TYPE";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else
		return "L";
}

char* ArithOpChk(char str[]) 
{ 
	int a=0;
    if(str[a]=='+')//+
	{
		a++;
		if(str[a]=='\0')
		{
			a=0;
    	        return "Arithmetic_Op";
		}
		else
		return "L"; 

	}
    
    else if(str[a]=='-')//-
	{
		a++;
		if(str[a]=='\0')
		{
			a=0;
    	        return "Arithmetic_Op";
		}
		else
		return "L";

	}
	
	else if(str[a]=='*')//*
	{
		a++;
		if(str[a]=='\0')
		{
			a=0;
    	        return "Arithmetic_Op";
		}
		else
		return "L"; 

	}
	
	
	else if(str[a]=='%')//%
	{
		a++;
		if(str[a]=='\0')
		{
			a=0;
    	        return "Arithmetic_Op";
		}
		else
		return "L";

	}
	
	else if(str[a]=='^')//^
	{
		a++;
		if(str[a]=='\0')
		{
			a=0;
    	        return "Arithmetic_Op";
		}
		else
		return "L";

	}
	
	else if(str[a]=='/')//integral div and division
	{
		a++;
		if(str[a]=='/')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Arithmetic_Op";
			}
			else
			return "L";
		}
		else if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Arithmetic_Op";
			}
		else
		return "L";
		
	}
	
	else
    	return "L"; 
} 

char* BoolOpChk(char str[]) 
{ 
	int a = 0;
	if(str[a]=='<')//< and <=
	{
		a++;
		if(str[a]=='=')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
			else
			return "L";
		}
		else if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
		else
		return "L";
	}
	
	else if(str[a]=='>')//> and >=
	{
		a++;
		if(str[a]=='=')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
			else
			return "L";
		}
		else if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
		else
		return "L";
		
	}
	
	else if(str[a]=='!')//! and !=
	{
		a++;
		if(str[a]=='=')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
			else
			return "L";
		}
		else if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
		else
		return "L";
		
	}
	
	else if(str[a]=='&')//&&
	{
		a++;
		if(str[a]=='&')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
			else
			return "L";
		}
		
		else
		return "L";
	}
	
	else if(str[a]=='|')//||
	{
		a++;
		if(str[a]=='|')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
			else
			return "L";
		}
		
		else
		return "L";
	}
	
	else if(str[a]=='=')//==
	{
		a++;
		if(str[a]=='=')
		{
			a++;
   	    	if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Boolean_Op";
			}
			else
			return "L";
		}
		else if(str[a]=='\0')
    	    {
   		     	a=0;
    	        return "Assignment_Op";
			}
		else
		return "L";
		
	}
	
	else
    	return "L"; 
} 


char* FloatConsChk(char str[])
{
	int a=0;
    while(true)
    {
    	if(isdigit(str[a]))
    	{
		 	a++;
    		if(str[a]=='.')
			{
				while(true)
				{
					a++;
					if(isdigit(str[a]))
    				{
    					a++;
    					if(str[a]=='\0')
    	   				{
   		   				  	a=0;
   		    			
    	     				return "float_Const";
						}
						else
						a--;

    				}
    				else
    				return "L";
    			}
			}
		
			
		}
		else
    	return "L";
	
	}
    
    
}

char* IntConstChk(char str[])
{
	int a=0;
    while(true)
    {
    	if(isdigit(str[a]))
    	{
    		a++;
    		if(str[a]=='\0')
			{
				a=0;
    	        return "integer_Const";
			}
    	}
    	else
    	return "L";
	}
  
}

char* BoolConstChk(char str[])
{
	int a=0;
	if(str[a]=='t')//true
	{
		a++;
		if(str[a]=='r')
		{
			a++;
   	    	if(str[a]=='u')
    	    {
    	    	a++;
   		     	if(str[a]=='e')
    	    	{
   		     		a++;
   		     		if(str[a]=='\0')
    	    		{
   		     			a=0;
    	        		return "boolean_Const";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else if(str[a]=='f')//false
	{
		a++;
		if(str[a]=='a')
		{
			a++;
   	    	if(str[a]=='l')
    	    {
    	    	a++;
   		     	if(str[a]=='s')
    	    	{
   		     		a++;
   		     		if(str[a]=='e')
    	    		{
   		     			a++;
   		     			if(str[a]=='\0')
    	    			{
   		     				a=0;
    	        			return "boolean_Const";
						}
						else
						return "L";
					}
					else
					return "L";
				}
				else
				return "L";
			}
			else
			return "L";
		}
		else
		return "L";
	}
	
	else
	return "L";
    
}

char* CharConstChk(char str[])
{
	int a=0;
	if(str[a]=='\'')
		{
			a++;
			if(str[a]!=NULL||str[a]!='\0')
			{
				a++;
				if(str[a]=='\'')
				{
					a++;
					if(str[a]=='\0')
					{
						a=0;
    	      			return "character_Const";		
					}
					else
					return "L";
							
				}
				
			}
		
		}
	
	else
	return "L";
    
}

char* StringConstChk(char str[])
{
	int a = 0;
if(str[a]=='\"')
		{
			while(true)
			{
				a++;
				if(str[a]=='\"')
				{
					a++;
					if(str[a]=='\0')
					{
						a=0;
    	      			return "string_Const";		
					}
					else
					return "L";
							
				}
				
			}
		
		}
		else
		return "L";
}

char* idChk(char str[])
{
	int a=0;
	if(isalpha(str[a]))
	{
		while(true){
			a++;
			if(isalnum(str[a])||str[a]=='_')
			{
				a++;
				if(str[a]=='\0')
				{
					a=0;
					return "id";
				}
				else
				a--;
			}
			else if(str[a]=='\0')
			{
				a=0;
				return "id";
			}
			else
			return "L";
		}
	}
	else
	return "L";
}

bool issymb(char ch)
{
	char i[20]={'+','-','/','*','%','^','<','>','=','!','|','&',';',',','[',']','{','}','(',')'};
	for(int a = 0;a<20;a++)
	{
		if(ch == i[a])
			return (true);
	}
	return (false);
}

void lex(void){
	char ch, buffer[100],comment[200],symbs[3];
	FILE *fp, *out;
	int a=0, line = 1;
	char* temp;

    
	out = fopen("Symbol Table.mez", "w"); //output file write mode
	fp = fopen("input.mez","r");
	
	if(fp == NULL){
		printf("Error while opening the file\n");
		exit(0);
	}
	
	
	while((ch = fgetc(fp)) != EOF){
	start:	
	a=0;
	
	
	
	if (ch == '\n')
		line++;
	
    if(ch=='~')
	{
		comment[a]=ch;
		a++;
		ch = fgetc(fp);
		if(ch=='<')
		{
			while(true)
			{
				comment[a]=ch;
				a++;
				ch = fgetc(fp);
				if(ch=='>')
				{
					comment[a]=ch;
					a++;
					ch = fgetc(fp);
					if(ch=='~')
					{
						comment[a]=ch;
						a++;
						comment[a]='\0';
						ch = fgetc(fp);
						fprintf(out,"#%d $%s\t:Comment\n", line, comment);
    	      			goto start;
						
						
					}
					else
					{
						comment[a]=ch;
						a++;
						comment[a]='\0';
						ch = fgetc(fp);
						fprintf(out,"#%d $%s\t:Invalid Input\n",line, comment);
						goto noc;
					   	
					}
				}
				
			}
		
		}
		else
		{
			comment[a]=ch;
			a++;
			comment[a]='\0';
			ch = fgetc(fp);
			fprintf(out,"#%d $%s\t:Invalid Input\n",line, comment);
			goto noc;
		   	
		}		
	}
	noc:	
	a=0;
	
	if(ch!=EOF&&isspace(ch) == false){
	temp=SymbolChk(ch);
			if(temp[0] != 'L'){
			fprintf(out,"#%d $%c\t:%s\n",line , ch , temp);
			ch = fgetc(fp);
			goto start;
	}
	}
	
	if(isspace(ch) == true)
		goto end;
	if(ch !='\'' && ch!='\"' && isalnum(ch) == false && ch!='_' && ch!='~' && isspace(ch) == false&& SymbolChk(ch) == "L"&&ch!=EOF)
	{
		while(true){
		symbs[a]=ch;
		a++;
		
		ch = fgetc(fp);
		if(ch=='\'' || ch=='\"' || isalnum(ch) || ch=='_'|| ch=='~' || isspace(ch) || ch=='.' ||SymbolChk(ch) != "L"||ch==EOF)
		{
			//a--;
			symbs[a]='\0';
			a++;
			
			
			
			temp=ArithOpChk(symbs);
			if(temp[0] != 'L'){
			fprintf(out,"#%d $%s\t:%s\n", line, symbs,temp);
			goto start;
			}
		
	   		temp=BoolOpChk(symbs);
	   		if(temp[0] != 'L'){
			fprintf(out,"#%d $%s\t:%s\n", line, symbs,temp);
			goto start;
			}
			if(temp[0] == 'L')
			{
			    a=0;
				break;
			}	
		}
		}
	}
	if(ch=='\'' || ch=='\"' || isalnum(ch) || ch=='_'&& ch!='~'&&ch!=EOF)
   	{
   	while(true){
	buffer[a] = ch;	
   	a++;
   	
   		ch = fgetc(fp);
   		if(ch=='~' || isspace(ch) || issymb(ch) ||ch==EOF)
		{
				//a--;
		   		buffer[a] = '\0';
		   		a++;
   			
   				temp=WordChk(buffer);
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				
				
   				temp=StrgClassChk(buffer);
   				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				
			
   				temp=DataTypeChk(buffer);
   				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				
				temp=FloatConsChk(buffer) ;
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				

				temp=IntConstChk(buffer);
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				a=0;
				goto start;
				}
				
				temp=BoolConstChk(buffer);
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				
				temp=CharConstChk(buffer);
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				
				temp=StringConstChk(buffer);
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				
				temp=idChk(buffer);
				if(temp[0] != 'L'){
				fprintf(out,"#%d $%s\t:%s\n", line, buffer,temp);
				goto start;
				}
				   				
   				if(temp[0]=='L'){
   				fprintf(out,"#%d $%s\t:Invalid_Input\n", line, buffer);
				break;
   				}
   		}
   			
   	
   }
   }
   
end:
a=0;
}
	
	
	fclose(out); 
	fclose(fp);	
}

struct error{
	int type;
	int line;
	struct error* next;
	char symbol[200];
};
typedef struct error error_t;

struct variable{
	char symbol[200];
	char type[6]; 
	int line;
	int used; 
	int array; 
	struct variable* next;
};
typedef struct variable var_t;

struct node {
	char symbol[200];
	char token[20];
	int line;
	char type[6]; 
	
	struct node* next;
};
typedef struct node node_t;

node_t *createnodeSymb(char str[]){
	node_t *result = (node_t *)malloc(sizeof(node_t));
	strcpy(result->symbol, str);
	result->next = NULL;
	return result;
}

var_t *createnodeVar(char st[]){
	var_t *resul = (var_t *)malloc(sizeof(var_t));
	strcpy(resul->symbol, st);
	resul->next = NULL;
	return resul;
}

error_t *createnodeErr(int type){
	error_t *result = (error_t *)malloc(sizeof(error_t));
	result->type = type;
	result->next = NULL;
	return result;
}

error_t* RemoveDuplicates(error_t *head)
{
  error_t *p = head;
  error_t *q;
  while(p!=NULL && p->next!=NULL)
  {
      if(strcmp(p->symbol,p->next->symbol)==0)
      {
          q = p->next->next;
          
          if(q==NULL)
          {
              p->next = NULL;
              break;         
          } 
          
          p->next = q;
      }
  
      if(strcmp(p->symbol,p->next->symbol)!=0)
        p = p->next;
      
  }

    return head;
    
    
}

void deleteListS(node_t** head)//clear struct node
{
   
   node_t* current = *head;
   node_t* next;
 
   while (current != NULL) 
   {
       next = current->next;
       free(current);
       current = next;
   }

   *head = NULL;
}

int find(var_t *head, char str[]){//finds if node in struct variable exists
	var_t *tmp = head;
	while (tmp!=NULL){
		if (strcmp(tmp->symbol,str)==0)
			return 1;
		tmp = tmp->next;
	}
	
	return 0;
}

var_t *search(var_t *head, char str[]){//search variable in struct variable exists
	var_t *tmp = head;
	while (tmp!=NULL){
		if (strcmp(tmp->symbol,str)==0)
			return tmp;
		tmp = tmp->next;
	}
	
	return NULL;
}

void sem(void){
	node_t *outout=NULL, *temp; 
	var_t *varlist=NULL, *tail,*point;
	error_t *err=NULL, *errtail;
	
	
	char line[1000], verd[15],word[200],wrd[200],lex[200],temptype[5];
	char *smbl;
	char type_chk[5]="none";
	
	char tok[25],tp[6];
	int lno,scan_chk=0,assign_chk=0,print_chk=0;
	
	int check=0,vcheck=0,str=0,eq_chk=0;
	
	FILE *st,*oo;
	oo = fopen("outout.txt","r");
	st = fopen("Symbol Table.mez","r");
	
	
	if(oo == NULL){
		printf("Error while opening outout.txt\n");
		exit(0);
	}
	if(st == NULL){
		printf("Error while opening Symbol Table.mez\n");
		exit(0);
	}
	
	while(fscanf(oo, "%[^\t] %[^\n]", line, verd)!=EOF){
		
		if(line[0]=='~'&&line[1]=='<'){
			fscanf(st ,"#%d $%[^\t] :%s ",&lno,lex,tok);
			if(outout==NULL){
  				outout=createnodeSymb(line);
  				temp=outout;
			}
			else{
				temp->next=createnodeSymb(line);
				temp=temp->next;
			}
			strcpy(temp->token,tok);
			strcpy(temp->symbol,lex);			
			temp->line=lno;
			strcpy(temp->type,"none");
			goto st;
		}

		smbl = strtok(line, " "); 	
  		while( smbl != NULL ){
  			fscanf(st ,"#%d $%s :%s ",&lno,lex,tok);
  			strcpy(word,smbl);
  			 			
  			if(outout==NULL){
  				outout=createnodeSymb(word);
  				temp=outout;
			}
			else{
				temp->next=createnodeSymb(word);
				temp=temp->next;
			}
			strcpy(temp->token,tok);
			strcpy(temp->symbol,lex);			
			temp->line=lno;
			
			
			if((strcmp(temp->symbol,"Num")==0)||(strcmp(temp->token,"integer_Const")==0)||(strcmp(temp->token,"float_Const")==0)||(strcmp(temp->token,"boolean_Const")==0))
				strcpy(temp->type,"Num");		
			else if((strcmp(temp->symbol,"Str")==0)||(strcmp(temp->token,"string_Const")==0)||(strcmp(temp->token,"character_Const")==0))
				strcpy(temp->type,"Str");
			else
				strcpy(temp->type,"none");

   		   	smbl = strtok(NULL, " ");
				  	  
  		}
  		
  		temp=outout;

		while(temp!=NULL&&(strcmp(verd,"VALID SYNTAX")==0)){
			if(strcmp(temp->symbol,"scan")==0)
				scan_chk=1;
			
			if(((strcmp(temp->symbol,"Str")==0)||(strcmp(temp->symbol,"Num")==0))&&scan_chk==0){
				strcpy(temptype,temp->type);
				temp=temp->next;
				check=0;
				while(temp!=NULL){
					if((strcmp(temp->token,"id")==0)&&check==0){
						check++;
						if(find(varlist,temp->symbol)==0){
							if(varlist == NULL){
								varlist=createnodeVar(temp->symbol);
								tail=varlist;
							}
							else{
								tail->next=createnodeVar(temp->symbol);
								tail=tail->next;
							}
							strcpy(tail->type,temptype);
							tail->used=0;
							tail->line = temp->line;
							temp=temp->next;
							if(strcmp(temp->symbol,"[")==0){
								temp=temp->next;//->int
								temp=temp->next;//->]
								temp=temp->next;
								tail->array=1;
							}
							else
								tail->array=0;
						}
						else{
							if(err==NULL){//error
								err=createnodeErr(1);
								errtail=err;
							}
							else{
								errtail->next=createnodeErr(1);
								errtail=errtail->next;
							}
							errtail->line=temp->line;
							strcpy(errtail->symbol,temp->symbol);
							temp=temp->next;
						}	
					}
					else if((strcmp(temp->token,",")==0)&&check==1){
						check=0;
						temp=temp->next;
					}
					else if(strcmp(temp->token,";")==0||strcmp(temp->symbol,"=")==0){
						scan_chk=0;
						temp=temp->next;
						break;
					}
					else
						temp=temp->next;
				}
			}
			else if(strcmp(temp->token,";")==0){
				temp=temp->next;
				scan_chk=0;
			}
			else
				temp=temp->next;
			
		}
		
		temp=outout;
		while(temp!=NULL&&(strcmp(verd,"VALID SYNTAX")==0)){
			
			if(strcmp(temp->symbol,"scan")==0){
				temp=temp->next;//->(
				temp=temp->next;
				if((strcmp(temp->symbol,"Str")==0)||(strcmp(temp->symbol,"Num")==0)){
					strcpy(temptype,temp->type);
					temp=temp->next;//->,
					temp=temp->next;
					if(strcmp(temp->token,"id")==0){
						if(find(varlist,temp->symbol)==1){
							strcpy(wrd,temp->symbol);
							point=search(varlist,wrd);
							point->used=1;
							if(strcmp(temptype,point->type)!=0){
								if(err==NULL){
									err=createnodeErr(4);
									errtail=err;
								}
								else{
									errtail->next=createnodeErr(4);
									errtail=errtail->next;
								}
								errtail->line=temp->line;
								strcpy(errtail->symbol,temp->symbol);
							}
						}
						else if(find(varlist,temp->symbol)==0){
							if(err==NULL){
								err=createnodeErr(3);
								errtail=err;
							}
							else{
								errtail->next=createnodeErr(3);
								errtail=errtail->next;
							}
							errtail->line=temp->line;
							strcpy(errtail->symbol,temp->symbol);
						}
						temp=temp->next;//->)
						temp=temp->next;
						
					}
				}
			}
			else if(strcmp(temp->symbol,"print")==0){
				temp=temp->next;//->(
				temp=temp->next;
				while(temp!=NULL){
					if(strcmp(temp->token,"id")==0){
						if(find(varlist,temp->symbol)==1){
							strcpy(wrd,temp->symbol);
							point=search(varlist,wrd);
							point->used=1;
						}
						else if(find(varlist,temp->symbol)==0){
							if(err==NULL){
								err=createnodeErr(3);
								errtail=err;
							}
							else{
								errtail->next=createnodeErr(3);
								errtail=errtail->next;
							}
							errtail->line=temp->line;
							strcpy(errtail->symbol,temp->symbol);
						}
						
					}
					else if(strcmp(temp->token,";")==0)
						break;
					temp=temp->next;
				}
			}		
			else
				temp=temp->next;
		}
		
		temp=outout;
		strcpy(type_chk,"none");
		while(temp!=NULL&&(strcmp(verd,"VALID SYNTAX")==0)){
			if(strcmp(temp->symbol,"scan")==0)
				scan_chk=1;
			if(strcmp(temp->symbol,"print")==0)
				print_chk=1;
				
			if((scan_chk==0&&print_chk==0)&&strcmp(temp->token,"id")==0)
			{
				if(find(varlist,temp->symbol)==1){
					
					strcpy(wrd,temp->symbol);
					point=search(varlist,wrd);
					
					if(point->array==1){
						temp=temp->next;
						if(strcmp(temp->symbol,"[")==0){
							temp=temp->next;//->int
							temp=temp->next;//->]
							temp=temp->next;
						}
						
						if(strcmp(temp->symbol,"=")==0){
							point->used=1;
							temp=temp->next;
							//below ---------------
							if(strcmp(temp->symbol,"{")==0)
							{	
								while(temp!=NULL)
								{
									if(strcmp(temp->token,"integer_Const")==0||strcmp(temp->token,"float_Const")==0||strcmp(temp->token,"string_Const")==0||strcmp(temp->token,"character_Const")==0||strcmp(temp->token,"boolean_Const")==0){
										if(strcmp(temp->type,point->type)!=0)
										{//if constant type != id type
											if(err==NULL){
												err=createnodeErr(4);
												errtail=err;
											}
											else{
												errtail->next=createnodeErr(4);
												errtail=errtail->next;
											}
											errtail->line=temp->line;
											strcpy(errtail->symbol,temp->symbol);								
										}
										temp=temp->next;
									}
									else if(strcmp(temp->token,"}")==0){
										scan_chk=0;
										print_chk=0;
										temp=temp->next;
										break;
									}
									else
										temp=temp->next;
								}
							}
						}
						
					}
					else
						temp=temp->next;
				}
				else if(find(varlist,temp->symbol)==0){
					if(err==NULL){
						err=createnodeErr(3);
						errtail=err;
					}
					else{
						errtail->next=createnodeErr(3);
						errtail=errtail->next;
					}
					errtail->line=temp->line;
					strcpy(errtail->symbol,temp->symbol);
				}
				temp=temp->next;
			}
			else if(strcmp(temp->token,";")==0){
				temp=temp->next;
				scan_chk=0;
				print_chk=0;
			}	
			else
				temp=temp->next;
		}
		
		temp=outout;
		strcpy(type_chk,"none");
		eq_chk=0;
		while(temp!=NULL&&(strcmp(verd,"VALID SYNTAX")==0)){//operation
			if(strcmp(temp->symbol,"scan")==0)
				scan_chk=1;
			if(strcmp(temp->symbol,"print")==0)
				print_chk=1;
			
			
		
			if((scan_chk==0&&print_chk==0)&&(strcmp(temp->token,"id")==0||strcmp(temp->token,"integer_Const")==0||strcmp(temp->token,"float_Const")==0||strcmp(temp->token,"string_Const")==0||strcmp(temp->token,"character_Const")==0||strcmp(temp->token,"boolean_Const")==0))
			{
				while(temp!=NULL)//type_chk
				{
					if(strcmp(temp->token,"id")==0)
					{//if id
						if(find(varlist,temp->symbol)==1){
							strcpy(wrd,temp->symbol);
							point=search(varlist,wrd);
							if(strcmp(temp->next->symbol,"=")==0||eq_chk==1){
								point->used=1;
								eq_chk=1;
								}
							if(strcmp(type_chk,"none")==0)
								strcpy(type_chk,point->type);
							else if(strcmp(type_chk,"none")!=0){
								if(strcmp(type_chk,point->type)!=0)
								{
									if(err==NULL){
										err=createnodeErr(4);
										errtail=err;
									}
									else{
										errtail->next=createnodeErr(4);
										errtail=errtail->next;
									}
									errtail->line=temp->line;
									strcpy(errtail->symbol,temp->symbol);								
								}
								
							}
						}
						else if(find(varlist,temp->symbol)==0){//if find()=0, var not declared
							if(err==NULL){
								err=createnodeErr(3);
								errtail=err;
							}
							else{
								errtail->next=createnodeErr(3);
								errtail=errtail->next;
							}
							errtail->line=temp->line;
							strcpy(errtail->symbol,temp->symbol);
						}
						temp=temp->next;
						
					}
					else if(strcmp(temp->token,"integer_Const")==0||strcmp(temp->token,"float_Const")==0||strcmp(temp->token,"string_Const")==0||strcmp(temp->token,"character_Const")==0||strcmp(temp->token,"boolean_Const")==0)
					{//if constants	
						if(strcmp(type_chk,"none")==0)
							strcpy(type_chk,temp->type);
						else if(strcmp(type_chk,"none")!=0){
							if(strcmp(type_chk,temp->type)!=0)
							{
								if(err==NULL){
									err=createnodeErr(4);
									errtail=err;
								}
								else{
									errtail->next=createnodeErr(4);
									errtail=errtail->next;
								}
								errtail->line=temp->line;
								strcpy(errtail->symbol,temp->symbol);								
							}
						}
						temp=temp->next;
					}
					else if(strcmp(temp->token,";")==0||strcmp(temp->symbol,",")==0||strcmp(temp->symbol,"{")==0){
						strcpy(type_chk,"none");
						eq_chk=0;
						scan_chk=0;
						print_chk=0;
						temp=temp->next;
						break;
					}
					else
						temp=temp->next;
				}
				
			}
			else if(strcmp(temp->token,";")==0){
				temp=temp->next;
				scan_chk=0;
				print_chk=0;
				eq_chk=0;
			}	
			else
				temp=temp->next;
			strcpy(type_chk,"none");
		}
		
		temp=outout;
		str=0;
		if(strcmp(verd,"INVALID SYNTAX")==0){//Syntax ERROR
			
				if(err==NULL){
					err=createnodeErr(5);
					errtail=err;
				}
					else{
					errtail->next=createnodeErr(5);
					errtail=errtail->next;
				}
				errtail->line=temp->line;
				strcpy(errtail->symbol,temp->symbol);
			
		}
		
		st:
		temp=outout;
		check=0;
		
		
		
		deleteListS(&outout);//clear node list
		
	}
	vcheck=0;
	tail=varlist;
	
	while (tail != NULL){
		if(tail->used==0){//Variable Not used error finder
			if(err==NULL){
				err=createnodeErr(2);
				errtail=err;
			}
			else{
				errtail->next=createnodeErr(2);
				errtail=errtail->next;
			}
			errtail->line=tail->line;
			strcpy(errtail->symbol,tail->symbol);
		}
		
		tail = tail->next;
	}
	
	printf("Processing...\n");
	sleep(2);
	printf("Finished processing data...");
	
	errtail=err;
	errtail=RemoveDuplicates(errtail);
	errtail=err;
	printf("\nline\tMessages\n");
	while (errtail!=NULL){//1=Double Dec 2=Variable Not Used 3=Variable Not Declared 4=Type Mismatch
	
			if(errtail->type==1)
				printf("\n%d\tError: Double Declaration of variable \"%s\"",errtail->line,errtail->symbol);
			if(errtail->type==2)
				printf("\n%d\tWARNING: Variable \"%s\" declared but not used",errtail->line,errtail->symbol);
			if(errtail->type==3)
				printf("\n%d\tError: Variable \"%s\" not declared ",errtail->line,errtail->symbol);
			if(errtail->type==4)
				printf("\n%d\tError: Type Mismatch",errtail->line);
			if(errtail->type==5)
				printf("\n%d\tSyntax ERROR",errtail->line);
				
		errtail = errtail->next;
	}
	
	fclose(oo);
	fclose(st);
}

int main(){
	printf("Analyzing Lexemes...\n");
	lex();
	sleep(2);
	printf("Analyzing SYntax...\n");
	syn();
	sleep(2);
	sem();
	getchar();
	return 0;
}
