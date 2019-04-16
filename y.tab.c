/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "mql.y" /* yacc.c:339  */

	
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

int yylex();
int yyerror(char *s);

int COUNT;
int INDEX_COUNT;
int OR_COUNT;
int MODE;
int FILE_NAME; 


enum COND{E,L,G,LE,GE};

enum FIELDS{eid=20,ename,eage,eaddress,salary,deptno, dnum, dname, dlocation};

enum MODES{GET=10, INSERT, MODIFY, DELETE};

enum FILES{EMP=35, DEPT};

int * current_indices;
int current_size;

typedef struct condition
{
    enum COND type;
    enum FIELDS field;
    char data[100];

    // char * data;
}cond;

typedef struct employee  
{ 
    int eid;
    char ename[30];
    // char * ename;
    int eage;
    char eaddress[100];
    // char * eaddress;
    int salary;
    int deptno;
}emp; 

typedef struct department
{
    int dnum; 
    char dname[30];
    char dlocation[100];    
}dep;

typedef struct header
{
    int count;
}header;

int rel_dict(char s[])
{
	if(!strcmp("=",s))
		return 0;
	else if(!strcmp("<",s))
		return 1;
	else if(!strcmp(">",s))
		return 2;
	else if(!strcmp("<=",s))
		return 3;
	else if(!strcmp(">=",s))
		return 4;
}

int field_dict(char s[])
{
	if(!strcmp("EID",s))
		return 20;
	else if(!strcmp("ENAME",s))
		return 21;
	else if(!strcmp("EAGE",s))
		return 22;
	else if(!strcmp("EADDRESS",s))
		return 23;
	else if(!strcmp("SALARY",s))
		return 24;
	else if(!strcmp("DEPTNO",s))
		return 25;
	else if(!strcmp("DNUM",s))
		return 26;
	else if(!strcmp("DNAME",s))
		return 27;
	else if(!strcmp("DLOCATION",s))
		return 28;
}

cond all_conds[20];
int cond_size = 0;
int cond_flag = 0;

int all_fields[10];
int field_size = 0;


char * modifys (char s[], int length)
{
	char* t = (char*)malloc(100);
	int ti = 0;
	for(int i=1;i<length-1;i++)
		t[ti++] = s[i];
	t[ti] = '\0';
	return t;

}

emp* read(){
    FILE *infile; 
    header hinput;
    emp input; 
      
    // Open person.dat for reading 
    infile = fopen ("EMP.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    fread(&hinput, sizeof(header),1,infile);

    int count = hinput.count;
    //printf("Count Read emp %d\n\n", count);
    COUNT = count;
    emp *rows = malloc(sizeof(emp) * count);

    // read file contents till end of file 
    int i=0;
    while(fread(&input, sizeof(emp), 1, infile)){ 
        // printf("%d\n", i);
        // printf ("eid = %d, ename= %s, eage= %d, eaddress = %s, salary = %d ,deptno= %d", input.eid, input.ename, input.eage, input.eaddress, input.salary,input.deptno); 
        rows[i].eid = input.eid;
        // rows[i].ename= input.ename;
        strcpy(rows[i].ename , input.ename);
        rows[i].eage= input.eage;
        strcpy(rows[i].eaddress , input.eaddress);
        // rows[i].eaddress= input.eaddress;
        rows[i].salary= input.salary;
        rows[i].deptno= input.deptno; 
        i++;
    }
    
    // for(i=0;i<count;i++){
    //     printf ("eid = %d, ename= %s, eage= %d, eaddress = %s, salary = %d ,deptno= %d", input.eid, input.ename, input.eage, input.eaddress, input.salary,input.deptno); 
             
    // }
    // close file 
    fclose (infile); 

    return rows;
}
dep* dep_read(){
    FILE *infile; 
    header hinput;
    dep input; 
      
    // Open person.dat for reading 
    infile = fopen ("DEPT.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    fread(&hinput, sizeof(header),1,infile);

    int count = hinput.count;
    //printf("Count Read dep %d\n\n", count);
    COUNT = count;
    dep *rows = malloc(sizeof(dep) * count);

    // read file contents till end of file 
    int i=0;
    while(fread(&input, sizeof(dep), 1, infile)){ 
        rows[i].dnum = input.dnum;
        strcpy(rows[i].dname , input.dname);
        strcpy(rows[i].dlocation , input.dlocation);
        i++;
    }
    //printf("I count %d\n",i);

    fclose (infile); 

    return rows;
}

void writeTable(){

    FILE *outfile; 
      
    // open file for writing 
    outfile = fopen ("EMP_R.txt", "w"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 


    emp* rows = read();

    int i;

    fprintf(outfile, "\n**********  Full Table  **********\n");
    fprintf (outfile, "%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");     
    
    for(i=0;i<COUNT;i++){
        fprintf (outfile, "%-10d%-20s%-10d%-30s%-10d%-10d\n", rows[i].eid, rows[i].ename, rows[i].eage, rows[i].eaddress, rows[i].salary,rows[i].deptno);         
    }
    free(rows);
  
    // close file 
    fclose (outfile); 
    return;
}

void dep_writeTable(){
    FILE *outfile; 
      
    // open file for writing 
    outfile = fopen ("DEPT_R.txt", "w"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 


    dep* rows = dep_read();

    int i;

    fprintf(outfile, "\n**********  Full Table  **********\n");
    fprintf (outfile, "%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation");           
    
    for(i=0;i<COUNT;i++){
        fprintf (outfile, "%-10d%-20s%-30s\n", rows[i].dnum, rows[i].dname, rows[i].dlocation);            
    }
    free(rows);
  
    // close file 
    fclose (outfile); 
    return;
}
void write(emp rows[],int count){
    FILE *outfile; 
      
    // open file for writing 
    outfile = fopen ("EMP.txt", "w"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 

    
    header h = {count};
    fwrite (&h, sizeof(header), 1, outfile); 

    int i;
    for (i = 0; i < count; ++i)
    {   
    fwrite (&rows[i], sizeof(emp), 1, outfile); 
    }
      
    if(fwrite != 0)  
        // printf("contents to Emp file written successfully !\n"); 
        ;
    else 
        printf("error writing file !\n"); 
  
    // close file 
    fclose (outfile); 
    writeTable();
    return;
}

void dep_write(dep rows[],int count){
    FILE *outfile; 
      
    // open file for writing 
    outfile = fopen ("DEPT.txt", "w"); 
    if (outfile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
        exit (1); 
    } 

    
    header h = {count};
    fwrite (&h, sizeof(header), 1, outfile); 

    int i;
    for (i = 0; i < count; ++i)
    {   
    fwrite (&rows[i], sizeof(dep), 1, outfile); 
    }
      
    if(fwrite != 0)  
        // printf("contents to Dept file written successfully !\n"); 
        ;
    else 
        printf("error writing file !\n"); 
  
    // close file 
    fclose (outfile); 
    dep_writeTable();
}





void printTable(){
    emp* rows = read();

    int i;

    printf("\n**********  Full Table  **********\n");
    printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");     
    
    for(i=0;i<COUNT;i++){
        printf ("%-10d%-20s%-10d%-30s%-10d%-10d\n", rows[i].eid, rows[i].ename, rows[i].eage, rows[i].eaddress, rows[i].salary,rows[i].deptno);         
    }
    free(rows);

    return;
}



void dep_printTable(){
    dep* rows = dep_read();

    int i;

    printf("\n**********  Full Table  **********\n");
    printf ("%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation");           
    
    for(i=0;i<COUNT;i++){
        printf ("%-10d%-20s%-30s\n", rows[i].dnum, rows[i].dname, rows[i].dlocation);            
    }
    free(rows);

    return;
}
void addRow(emp new){

    emp* rows = read();
    // int i;
    printf("\nThe following row is being added: \n\n");
    printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");         
    printf ("%-10d%-20s%-10d%-30s%-10d%-10d\n", new.eid, new.ename, new.eage, new.eaddress, new.salary,new.deptno);         

    COUNT++;
    rows = realloc(rows, sizeof(emp)*COUNT);
    rows[COUNT-1] = new;

    write(rows,COUNT);
    free(rows);
    return;
}
void dep_addRow(dep new){

    // printf("dep_addRow\n");
    dep* rows = dep_read();
    // int i;
    printf("\nThe following row is being added: \n\n");
    printf ("%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation");         
    printf ("%-10d%-20s%-30s\n", new.dnum, new.dname, new.dlocation);         

    COUNT++;
    rows = realloc(rows, sizeof(emp)*COUNT);
    rows[COUNT-1] = new;

    dep_write(rows,COUNT);
    free(rows);
    return;
}


bool belongsTo(int a[], int size, int x){
    int i=0;
    for(i=0;i<size;i++){
        if(a[i]==x)return true;
    }
    return false;
}

emp* generateRows(int ptr[],int size, bool show){

    FILE *infile; 
    header hinput;
    emp input; 
      
    // Open person.dat for reading 
    infile = fopen ("EMP.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    fread(&hinput, sizeof(header),1,infile);

    int count = hinput.count;
    // printf("Count Read %d\n\n", count);
    COUNT = count;
    emp *rows = malloc(sizeof(emp) * count);

    // read file contents till end of file 
    int i=0;
    while(fread(&input, sizeof(emp), 1, infile)){ 
        // printf("%d\n", i);
        // printf ("eid = %d, ename= %s, eage= %d, eaddress = %s, salary = %d ,deptno= %d", input.eid, input.ename, input.eage, input.eaddress, input.salary,input.deptno); 
        rows[i].eid = input.eid;
        // rows[i].ename= input.ename;
        strcpy(rows[i].ename , input.ename);
        rows[i].eage= input.eage;
        strcpy(rows[i].eaddress , input.eaddress);
        // rows[i].eaddress= input.eaddress;
        rows[i].salary= input.salary;
        rows[i].deptno= input.deptno; 
        i++;
    }

    emp* newrows = malloc(sizeof(emp)*size);
    int index = 0, x=0; 
    i =0;
    // while(x<COUNT && i<size){
    //     if(rows[x].eid==ptr[i]){
    //         printf ("%-10d%-20s%-10d%-30s%-10d%-10d\n", rows[x].eid, rows[x].ename, rows[x].eage, rows[x].eaddress, rows[x].salary,rows[x].deptno);
    //         newrows[index] = rows[x];
    //         index++;
    //         i++;
    //         x++;
    //     }else x++;
    // }

    for(x=0;x<COUNT;x++){
        if(belongsTo(ptr,size,rows[x].eid)){
            if(show)printf ("%-10d%-20s%-10d%-30s%-10d%-10d\n", rows[x].eid, rows[x].ename, rows[x].eage, rows[x].eaddress, rows[x].salary,rows[x].deptno);
            newrows[index] = rows[x];
            index++;
        }
    }
    fclose (infile); 

    free(rows); 
    return newrows;
}

dep* dep_generateRows(int ptr[],int size, bool show){

    FILE *infile; 
    header hinput;
    dep input; 
      
    // Open person.dat for reading 
    infile = fopen ("DEPT.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    fread(&hinput, sizeof(header),1,infile);

    int count = hinput.count;
    // printf("Count Read %d\n\n", count);
    COUNT = count;
    dep *rows = malloc(sizeof(dep) * count);

    // read file contents till end of file 
    int i=0;
    while(fread(&input, sizeof(dep), 1, infile)){ 
        rows[i].dnum = input.dnum;
        strcpy(rows[i].dname , input.dname);
        strcpy(rows[i].dlocation , input.dlocation);
        i++;
    }

    dep* newrows = malloc(sizeof(dep)*size);
    int index = 0, x=0; 
    i =0;

    for(x=0;x<COUNT;x++){
        if(belongsTo(ptr,size,rows[x].dnum)){
            if(show) printf ("%-10d%-20s%-30s\n", rows[x].dnum, rows[x].dname, rows[x].dlocation);     
            newrows[index] = rows[x];
            index++;
        }
    }
    fclose (infile); 

    free(rows); 
    return newrows;
}

int* getindicesAND(emp* rows,int rowsize,  cond conds[],int size){

    int i;

    int* indices = malloc(sizeof(int)*COUNT);
    int ind =0;
    int x;
    cond curr = conds[size-1];

    switch(curr.type)
    {
        case E:
            // printf("Case E\n");

            switch(curr.field)
            {
                case eid: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eid== x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case ename:;
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(!strcmp(rows[i].ename,curr.data)){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case eage: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eage== x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case eaddress: ;
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(!strcmp(rows[i].eaddress,curr.data)){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }

                    break;

                case salary: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].salary== x){
                            indices[ind] =rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case deptno: ;
                    x = atoi(curr.data);
                    for (int i = 0; i <rowsize; ++i)
                    {
                        if(rows[i].deptno== x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

            }
            break;

        case L:
            // printf("Case L\n");

            switch(curr.field)
            {
                case eid: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eid< x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case ename:;
                    printf("Less Than Not available for string\n");
                    break;

                case eage: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eage< x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case eaddress: ;
                    printf("Less Than Not available for string\n");
                    break;

                case salary: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].salary< x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case deptno: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].deptno< x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
            }
            break;
        case G:
            // printf("Case G\n");

            switch(curr.field)
            {
                case eid: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eid> x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case ename:;
                    
                    printf("Greater Than Not available for string\n");
                    break;

                case eage: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eage> x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case eaddress: ;
                    printf("Greater Than Not available for string\n");
                    break;

                case salary: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].salary> x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case deptno: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].deptno> x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
            }        
            break;
        case LE:
            // printf("Case LE\n");

            switch(curr.field)
            {
                case eid: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eid<= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case ename:;
                    printf("Less Than Not available for string\n");
                    break;

                case eage: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eage<= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case eaddress: ;
                    printf("Less Than Not available for string\n");
                    break;

                case salary: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].salary<= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case deptno: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].deptno<= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
            }
            break;
        case GE:
            // printf("Case GE\n");

            switch(curr.field)
            {
                case eid: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eid>= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case ename:;
                    printf("Greater Than Not available for string\n");
                    break;

                case eage: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].eage>= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case eaddress: ;
                    printf("Greater Than Not available for string\n");
                    break;

                case salary: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].salary>= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
                    break;

                case deptno: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].deptno>= x){
                            indices[ind] = rows[i].eid;
                            ind++;
                            // printf("%d added to query list\n", rows[i].eid);
                        }
                    }
            }
            break;                                                 
    }

    INDEX_COUNT = ind;
    if(size!=1){
        emp* currRows = generateRows(indices,ind, false);

        indices = getindicesAND(currRows,ind, conds, size-1);
    }

    free(rows);
    return indices;
}

int* dep_getindicesAND(dep* rows,int rowsize,  cond conds[],int size){

    int i;

    int* indices = malloc(sizeof(int)*COUNT);
    int ind =0;
    int x;
    cond curr = conds[size-1];

    switch(curr.type)
    {
        case E:
            // printf("Case E %d\n", curr.type);

            switch(curr.field)
            {
                case dnum: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].dnum== x){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }
                    break;

                case dname: ;
                    // printf("case dname\n");
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(!strcmp(rows[i].dname,curr.data)){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }
                    break;
                case dlocation: ;
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(!strcmp(rows[i].dlocation,curr.data)){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }

                    break;
            }
            break;

        case L:
            // printf("Case L\n");

            switch(curr.field)
            {
                case dnum: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].dnum< x){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }
                    break;
                case dname: ;
                    printf("Less Than Not available for string\n");
                    break;
                case dlocation: ;
                    printf("Less Than Not available for string\n");
                    break;
            }
            break;
        case G:
            // printf("Case G\n");

            switch(curr.field)
            {
                case dnum: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].dnum> x){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }
                    break;
                case dname: ;
                    printf("Greater Than Not available for string\n");
                    break;
                case dlocation: ;
                    printf("Greater Than Not available for string\n");
                    break;
            }        
            break;
        case LE:
            // printf("Case LE\n");

            switch(curr.field)
            {
                case dnum: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].dnum<= x){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }
                    break;
                case dname: ;
                    printf("Less Than Equal Not available for string\n");
                    break;
                case dlocation: ;
                    printf("Less Than Equal Not available for string\n");
                    break;
            }
            break;
        case GE:
            // printf("Case GE\n");

            switch(curr.field)
            {
                case dnum: ;
                    x = atoi(curr.data);
                    for (int i = 0; i < rowsize; ++i)
                    {
                        if(rows[i].dnum>= x){
                            indices[ind] = rows[i].dnum;
                            ind++;
                            // printf("%d added to query list\n", rows[i].dnum);
                        }
                    }
                    break;
                case dname: ;
                    printf("Greater Than Equal Not available for string\n");
                    break;
                case dlocation: ;
                    printf("Greater Than Equal Not available for string\n");
                    break;
            }
            break;                                                 
    }

    INDEX_COUNT = ind;
    if(size!=1){
        // printf("sdsd\n");
        dep* currRows = dep_generateRows(indices,ind, false);
        // printf("3\n");
        indices = dep_getindicesAND(currRows,ind, conds, size-1);
        // printf("3\n");
    }

    free(rows);
    return indices;
}


int* unionArr(int arr1[], int arr2[], int m, int n) 
{ 
    int i = 0, j = 0; 
    int * un = malloc(sizeof(int)*m+n);
    int count=0;
    while (i < m && j < n) 
    { 
    if (arr1[i] < arr2[j]){ 
        // printf("%d ",arr1[i]);
        un[count] = arr1[i++];
        count++;
    }
    else if (arr2[j] < arr1[i]){ 
        // printf("%d ",arr2[j]);
        un[count] = arr2[j++];
        count++;
    }
    else
    { 
        // printf("%d ",arr2[j]);
        un[count] = arr2[j++];
        count++;
        i++; 
    } 
    } 
    while(i < m){ 
        // printf("%d ",arr1[i]);
        un[count] = arr1[i++];
        count++;
    }
    while(j < n){ 
        // printf("%d ",arr2[j]);
        un[count] = arr2[j++];
        count++;
    }
    OR_COUNT = count;
    return un;
}

int* selectqAND(cond conds[],int size){

    emp* rows = read();
    int *ptr = getindicesAND(rows,COUNT,conds,size);

    // printf("indices Retrieved: \n");
    // for (int i = 0; i < INDEX_COUNT; ++i)
    // {
    //     printf("%d ",ptr[i]);
    // }
    // rows = read();
    // printf("\n\nAND QUERY:\n");
    // printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    // rows = generateRows(ptr, INDEX_COUNT);

    // printf("\n\n***********AND QUERY Completed***********\n\n");
    // free(rows);
    return ptr;
}
int* dep_selectqAND(cond conds[],int size){

    dep* rows = dep_read();
    int *ptr = dep_getindicesAND(rows,COUNT,conds,size);

    // printf("indices Retrieved: \n");
    // for (int i = 0; i < INDEX_COUNT; ++i)
    // {
        // printf("%d ",ptr[i]);
    // }
    return ptr;
}


int * selectqOR(cond conds1[], int size1, cond conds2[], int size2){
    int * indices1 = selectqAND(conds1, size1);
    int ind1 = INDEX_COUNT;
    int * indices2 = selectqAND(conds2, size2);
    int ind2 = INDEX_COUNT;
    int * UnionIndices = unionArr(indices1,indices2, ind1, ind2);

    free(indices1); free(indices2);


    // printf("\n\nOR QUERY:\n");
    // printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    // emp* rows = generateRows(UnionIndices,OR_COUNT);
    // free(rows);
    return UnionIndices;
}
int * selectqOR_ind(int indices1[], int ind1, cond conds2[], int size2){
    int * indices2 = selectqAND(conds2, size2);
    int ind2 = INDEX_COUNT;
    int * UnionIndices = unionArr(indices1,indices2, ind1, ind2);
    free(indices2);


    // printf("\n\nOR QUERY:\n");
    // printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    emp* rows = generateRows(UnionIndices,OR_COUNT, false);
    free(rows);
    return UnionIndices;
}
int * dep_selectqOR_ind(int indices1[], int ind1, cond conds2[], int size2){
    int * indices2 = dep_selectqAND(conds2, size2);
    int ind2 = INDEX_COUNT;
    int * UnionIndices = unionArr(indices1,indices2, ind1, ind2);
    free(indices2);


    // printf("\n\nOR QUERY:\n");
    // printf ("%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation"); 
    dep* rows = dep_generateRows(UnionIndices,OR_COUNT, false);
    free(rows);
    return UnionIndices;
}

void firstCond(cond conds[], int size){
    int * indices = selectqAND(conds, size);
    int ind = INDEX_COUNT;

    // printf("\n\n******* First Condition Evaluated *******\n");
    // printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    emp* rows = generateRows(indices,ind, false);
    free(rows);

    current_size = ind;
    current_indices = indices;
    // return indices;
}
void dep_firstCond(cond conds[], int size){
    // printf("dep_firstCond\n");
    int * indices = dep_selectqAND(conds, size);
    // printf("Dep_firstCOnd 2\n");
    int ind = INDEX_COUNT;

    // printf("\n\n******* First Condition Evaluated *******\n");
    // printf ("%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation"); 
    dep* rows = dep_generateRows(indices,ind, false);
    free(rows);

    current_size = ind;
    current_indices = indices;
    // return indices;
}
void FIRSTCOND_F(cond conds[], int size){
    if(FILE_NAME==EMP)firstCond(conds,size);
    else if(FILE_NAME == DEPT)dep_firstCond(conds,size);;
    // else cout<<"error FIRSTCOND_F File";

}
void nextCond(cond conds[], int size){
    int * indices1 = selectqOR_ind(current_indices, current_size, conds, size);
    int ind1 = OR_COUNT;


    // printf("\n\n******* Next Condition Condition Evaluated *******\n");
    // printf ("%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    emp* rows = generateRows(indices1,ind1, false);
    free(rows);

    // free(indices);

    current_size = ind1;
    current_indices = indices1;
    // return indices1;
}
void dep_nextCond(cond conds[], int size){
    int * indices1 = dep_selectqOR_ind(current_indices, current_size, conds, size);
    int ind1 = OR_COUNT;


    // printf("\n\n******* Next Condition Condition Evaluated *******\n");
    // printf ("%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation"); 
    dep* rows = dep_generateRows(indices1,ind1, false);
    free(rows);

    // free(indices);

    current_size = ind1;
    current_indices = indices1;
    // return indices1;
}

void NEXTCOND_F(cond conds[], int size){
    if(FILE_NAME==EMP)nextCond(conds,size);
    else if(FILE_NAME == DEPT)dep_nextCond(conds,size);;
    // else cout<<"error NEXTCOND_F File";

}



void setFile(int File){
    FILE_NAME = File;
}
void setMode(int Mode){
    MODE = Mode;
}

emp* get_generateRows(int ptr[],int size, int fields[], int size_fields){

    FILE *infile; 
    header hinput;
    emp input; 
      
    // Open person.dat for reading 
    infile = fopen ("EMP.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    fread(&hinput, sizeof(header),1,infile);

    int count = hinput.count;
    // printf("Count Read %d\n\n", count);
    COUNT = count;
    emp *rows = malloc(sizeof(emp) * count);

    // read file contents till end of file 
    int i=0;
    while(fread(&input, sizeof(emp), 1, infile)){ 
        // printf("%d\n", i);
        // printf ("eid = %d, ename= %s, eage= %d, eaddress = %s, salary = %d ,deptno= %d", input.eid, input.ename, input.eage, input.eaddress, input.salary,input.deptno); 
        rows[i].eid = input.eid;
        // rows[i].ename= input.ename;
        strcpy(rows[i].ename , input.ename);
        rows[i].eage= input.eage;
        strcpy(rows[i].eaddress , input.eaddress);
        // rows[i].eaddress= input.eaddress;
        rows[i].salary= input.salary;
        rows[i].deptno= input.deptno; 
        i++;
    }

    emp* newrows = malloc(sizeof(emp)*size);
    int index = 0, x=0; 
    i =0;
    // while(x<COUNT && i<size){
    //     if(rows[x].eid==ptr[i]){
    //         printf ("%-10d%-20s%-10d%-30s%-10d%-10d\n", rows[x].eid, rows[x].ename, rows[x].eage, rows[x].eaddress, rows[x].salary,rows[x].deptno);
    //         newrows[index] = rows[x];
    //         index++;
    //         i++;
    //         x++;
    //     }else x++;
    // }

    for(x=0;x<COUNT;x++){
        if(belongsTo(ptr,size,rows[x].eid)){
            // if(show)printf ("%-10d%-20s%-10d%-30s%-10d%-10d\n", rows[x].eid, rows[x].ename, rows[x].eage, rows[x].eaddress, rows[x].salary,rows[x].deptno);


            if(belongsTo(fields, size_fields, eid)){
                printf("%-10d", rows[x].eid);
            }
            if(belongsTo(fields, size_fields, ename)){
                printf("%-20s", rows[x].ename);
            }
            if(belongsTo(fields, size_fields, eage)){
                printf("%-10d", rows[x].eage);
            }
            if(belongsTo(fields, size_fields, eaddress)){
                printf("%-30s", rows[x].eaddress);
            }
            if(belongsTo(fields, size_fields, salary)){
                printf("%-10d", rows[x].salary);
            }
            if(belongsTo(fields, size_fields, deptno)){
                printf("%-10d", rows[x].deptno);
            }
            printf("\n");
            newrows[index] = rows[x];
            index++;
        }
    }
    fclose (infile); 

    free(rows); 
    return newrows;
}

dep* dep_get_generateRows(int ptr[],int size, int fields[], int size_fields){

    FILE *infile; 
    header hinput;
    dep input; 
      
    // Open person.dat for reading 
    infile = fopen ("DEPT.txt", "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opening file\n"); 
        exit (1); 
    } 
    fread(&hinput, sizeof(header),1,infile);

    int count = hinput.count;
    // printf("Count Read %d\n\n", count);
    COUNT = count;
    dep *rows = malloc(sizeof(dep) * count);

    // read file contents till end of file 
    int i=0;
    while(fread(&input, sizeof(dep), 1, infile)){ 
        rows[i].dnum = input.dnum;
        strcpy(rows[i].dname , input.dname);
        strcpy(rows[i].dlocation , input.dlocation);
        i++;
    }

    dep* newrows = malloc(sizeof(dep)*size);
    int index = 0, x=0; 
    i =0;

    for(x=0;x<COUNT;x++){
        if(belongsTo(ptr,size,rows[x].dnum)){
            // if(show) printf ("%-10d%-20s%-30s\n", rows[x].dnum, rows[x].dname, rows[x].dlocation);     

            if(belongsTo(fields, size_fields, dnum)){
                printf("%-10d", rows[x].dnum);
            }
            if(belongsTo(fields, size_fields, dname)){
                printf("%-20s", rows[x].dname);
            }
            if(belongsTo(fields, size_fields, dlocation)){
                printf("%-30s", rows[x].dlocation);
            }
            printf("\n");
            newrows[index] = rows[x];
            index++;
        }
    }
    fclose (infile); 

    free(rows); 
    return newrows;
}
void get_F(int fields[], int size){

    printf("Get QUERY:\n");
    // printf ("\n\n%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");

    printf("\n\n");

    if(belongsTo(fields, size, eid)){
        printf("%-10s", "eid");
    }
    if(belongsTo(fields, size, ename)){
        printf("%-20s", "ename");
    }
    if(belongsTo(fields, size, eage)){
        printf("%-10s", "eage");
    }
    if(belongsTo(fields, size, eaddress)){
        printf("%-30s", "eaddress");
    }
    if(belongsTo(fields, size, salary)){
        printf("%-10s", "salary");
    }
    if(belongsTo(fields, size, deptno)){
        printf("%-10s", "deptno");
    }
    printf("\n\n");
    /* printf("%d ", current_size);
    for(int i=0;i<current_size;i++)
    {
    	printf("%d ", current_indices[i]);
    } */
    emp* rows = get_generateRows(current_indices, current_size, fields, size);
    free(rows);

    return;
}
void dep_get_F(int fields[], int size){
    printf("Get QUERY:\n");
    // printf ("\n\n%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation"); 


    printf("\n\n");

    if(belongsTo(fields, size, dnum)){
        printf("%-10s", "dnum");
    }
    if(belongsTo(fields, size, dname)){
        printf("%-20s", "dname");
    }
    if(belongsTo(fields, size, dlocation)){
        printf("%-30s", "dlocation");
    }
    printf("\n\n");
    
    dep* rows = dep_get_generateRows(current_indices, current_size, fields, size);
    free(rows);

    return;
}

void GET_F(int fields[], int size){

    printf("\n********************************************************\n\n\n\n");
    if(FILE_NAME==EMP)get_F(fields, size);
    else if(FILE_NAME == DEPT)dep_get_F(fields, size);
    // else cout<<"error get_F File";

    printf("\n\n\n\n********************************************************\n");
    return;
}

// bool deptNo_exists(char num[]){
//     cond x = {E, dnum};
//     strcpy(x.data,  num);
//     cond carr[1]; 
//     carr[0] = x;
//     dep_firstCond(carr,1);

//     if(current_size)return true;
//     else return false;
// }

bool deptNo_exists(char num[]){
    dep* rows = dep_read();

    int x = atoi(num);
    int i, c = 0;;
    for(i=0;i<COUNT;i++){
        if(rows[i].dnum == x)c++;
    }

    free(rows);    
    if(c>1)printf("Warning Duplicate Dnums in Table\n");
    if(c==0)return false;
    if(c==1)return true;
}
bool eid_exists(char num[]){
    emp* rows = read();

    int x = atoi(num);
    int i, c = 0;;
    for(i=0;i<COUNT;i++){
        if(rows[i].eid == x)c++;
    }

    free(rows);    
    if(c>1)printf("Warning Duplicate eids in Table\n");
    if(c==0)return false;
    if(c==1)return true;    
}
bool deptNo_Dependancy_exists(int x){
    emp* rows = read();

    int i, c = 0;;
    for(i=0;i<COUNT;i++){
        if(rows[i].deptno == x)c++;
    }
    // printf("%d\n", c);
    free(rows);    
    if(c){
        printf("%d entries in EMP.txt are linked to dnum: %d. Cannot change!\n", c, x);
        return true;
    }
    if(c==0)return false;
}
void insert_f(char id[], char name[], char age[], char address[], char sal[], char dep[]){

    printf("\n********************************************************\n\n\n\n");
    printf("INSERT QUERY\n");
    cond x = {E, eid};
    strcpy(x.data,id);
    cond carr[1]; 
    carr[0] = x;
    firstCond(carr,1);

    if(current_size){
        printf("\n\nError: eid already in table!!\n");

        printf("\n\n\n\n********************************************************\n");
        return;
    }else if(!deptNo_exists(dep)){
        printf("Dept Number: %s Does not exist!!\n", dep);

        printf("\n\n\n\n********************************************************\n");
        return;
    }else{
        emp temp;
        temp.eid = atoi(id);
        strcpy(temp.ename, name);
        temp.eage= atoi(age);
        strcpy(temp.eaddress,address);
        temp.salary= atoi(sal);
        temp.deptno= atoi(dep);

        addRow(temp);

        printf("\n\n\n\n********************************************************\n");
        return;
    }
}
void dep_insert_f(char num[], char name[], char location[]){

    
    printf("\n********************************************************\n\n\n\n");
    printf("INSERT QUERY\n");
    cond x = {E, dnum};
    strcpy(x.data,num);
    cond carr[1]; 
    carr[0] = x;
    dep_firstCond(carr,1);

    if(current_size){
        printf("\n\nError: dnum already in table!!\n");

        printf("\n\n\n\n********************************************************\n");
        return;
    }else{
        dep temp;
        temp.dnum = atoi(num);
        strcpy(temp.dname, name);
        strcpy(temp.dlocation,location);

        dep_addRow(temp);

        printf("\n\n\n\n********************************************************\n");
        return;
    }
}


void delete_f(){
    printf("DELETE QUERY\n\nThe following rows are being deleted:\n\n");
    printf ("\n\n%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    emp* rows = generateRows(current_indices, current_size, true);
    free(rows);

    rows = read();

    emp temp[COUNT];
    int temp_size=0;


    int i;
    for(i=0;i<COUNT;i++){
        if(!belongsTo(current_indices,current_size,rows[i].eid)){
            temp[temp_size] = rows[i];
            temp_size++;
        }
    }

    write(temp, temp_size);
    // printTable();

    return;
}

void dep_delete_f(){
    printf("DELETE QUERY\n\nThe following rows are being deleted:\n\n");


    printf ("\n\n%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation");     
    dep* rows = dep_generateRows(current_indices, current_size, true);
    free(rows);

    rows = dep_read();

    dep temp[COUNT];
    int temp_size=0;

    int i;
    for(i =0; i<COUNT;i++){
        if(belongsTo(current_indices,current_size,rows[i].dnum)){
            if(deptNo_Dependancy_exists(rows[i].dnum)){
                temp[temp_size] = rows[i];
                temp_size++;                
            }
        }
    }
    for(i=0;i<COUNT;i++){
        if(!belongsTo(current_indices,current_size,rows[i].dnum)){
                temp[temp_size] = rows[i];
                temp_size++;
        }
    }

    dep_write(temp, temp_size);
    // dep_printTable();

    return;
}
void DELETE_f(){
    if(FILE_NAME==EMP)delete_f();
    else if(FILE_NAME == DEPT)dep_delete_f();
    // else cout<<"error DELETE_F File";

    return;
}


void modify_f(int field, char data[]){
    printf("MODIFY QUERY\n\nThe following rows are being modified:\n\n");
    printf ("\n\n%-10s%-20s%-10s%-30s%-10s%-10s\n\n", "eid", "ename", "eage", "eaddress", "salary","deptno");
    emp* rows = generateRows(current_indices, current_size, true);
    free(rows);
    rows = read();

    int i, x;
    int c = COUNT;
    for(i=0;i<c;i++){
        if(belongsTo(current_indices,current_size,rows[i].eid)){
            // printf("sds\n");
            switch(field){
                    case eid: ;
                        if(eid_exists(data)){
                            printf("eid: %s already exists\nNo Modification Made!\n", data);
                        }else{
                            x = atoi(data);
                            rows[i].eid = x;
                        }
                        break;

                    case ename:;
                        strcpy(rows[i].ename, data);
                        break;

                    case eage: ;
                        x = atoi(data);

                        rows[i].eage = x;
                        break;

                    case eaddress: ;
                        strcpy(rows[i].eaddress, data);

                        break;

                    case salary: ;
                        x = atoi(data);
                        rows[i].salary = x;
                        break;

                    case deptno: ;
                        if (deptNo_exists(data))
                        {       
                            x = atoi(data);                    
                            rows[i].deptno = x;
                        }else{
                            printf("\n\nDept Number: %s Does not exist!!\nNo Modification Made\n", data);
                        }
                        break;
            }
        }
    }

    write(rows, c);
    // printTable();

    return;
}

void dep_modify_f(int field, char data[]){
    printf("MODIFY QUERY\n\nThe following rows are being modified:\n\n");
    printf ("\n\n%-10s%-20s%-30s\n\n", "dnum", "dname", "dlocation");     
    dep* rows = dep_generateRows(current_indices, current_size, true);
    free(rows);

    rows = dep_read();

    int i, x, c = COUNT;
    for(i=0;i<c;i++){
        if(belongsTo(current_indices,current_size,rows[i].dnum)){

            switch(field){
                    case dnum: ;
                        if(deptNo_exists(data)){
                            printf("dnum: %s already exists\nNo Modification Made!\n", data);
                        }else if (deptNo_Dependancy_exists(rows[i].dnum))
                        {
                            ;
                        }
                        else{
                            x = atoi(data);
                            rows[i].dnum= x;
                        }
                        break;

                    case dname:;
                        strcpy(rows[i].dname, data);
                        break;

                    case dlocation: ;
                        strcpy(rows[i].dlocation, data);

                        break;
            }
        }
    }

    dep_write(rows, c);
    // dep_printTable();

    return;
}

void MODIFY_f(int field, char data[]){


    printf("\n********************************************************\n\n\n\n");
    if(FILE_NAME == EMP)modify_f(field, data);
    else if(FILE_NAME == DEPT)dep_modify_f(field, data);
    // else cout<<"error MODIFY_f FILE";

    printf("\n\n\n\n********************************************************\n");
    return;
}





#line 1802 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INS = 258,
    RECORD = 259,
    NUM = 260,
    GETT = 261,
    AND = 262,
    OR = 263,
    UPDATE = 264,
    DEL = 265,
    INTO = 266,
    IN = 267,
    SET = 268,
    TO = 269,
    WHERE = 270,
    FROM = 271,
    VAR = 272,
    STRING = 273,
    LB = 274,
    RB = 275,
    COLON = 276,
    REL_OP = 277,
    COMMA = 278,
    NL = 279
  };
#endif
/* Tokens.  */
#define INS 258
#define RECORD 259
#define NUM 260
#define GETT 261
#define AND 262
#define OR 263
#define UPDATE 264
#define DEL 265
#define INTO 266
#define IN 267
#define SET 268
#define TO 269
#define WHERE 270
#define FROM 271
#define VAR 272
#define STRING 273
#define LB 274
#define RB 275
#define COLON 276
#define REL_OP 277
#define COMMA 278
#define NL 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 1737 "mql.y" /* yacc.c:355  */

		char str[200];            

#line 1894 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 1911 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   71

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  25
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  22
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  81

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   279

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1771,  1771,  1772,  1774,  1782,  1791,  1790,  1821,  1820,
    1842,  1841,  1866,  1865,  1880,  1884,  1889,  1889,  1906,  1928,
    1930,  1933,  1947
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INS", "RECORD", "NUM", "GETT", "AND",
  "OR", "UPDATE", "DEL", "INTO", "IN", "SET", "TO", "WHERE", "FROM", "VAR",
  "STRING", "LB", "RB", "COLON", "REL_OP", "COMMA", "NL", "$accept",
  "START", "STMT", "$@1", "$@2", "$@3", "$@4", "FIELDS", "CONDITIONS",
  "$@5", "ACONDITIONS", "CONDITION", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279
};
# endif

#define YYPACT_NINF -32

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-32)))

#define YYTABLE_NINF -19

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,     2,   -12,     4,     5,    12,     1,    -6,    -5,     3,
       8,     7,   -32,   -32,    16,   -12,     0,     9,    10,     6,
     -32,   -32,    11,   -32,    14,    13,    17,    18,    15,    19,
      21,    19,    -4,    20,    22,    23,    30,    -3,    24,    25,
      26,    -2,    27,    31,    19,   -32,   -32,    28,    29,    38,
     -32,   -32,   -32,    19,   -32,    35,    39,   -32,    32,    36,
     -32,    19,    19,    51,    37,    40,    41,    34,    42,    43,
      44,    54,   -32,   -32,   -32,    45,    49,    46,    48,    47,
     -32
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     3,     0,    15,     0,
       0,     0,     1,     2,     0,     0,     0,     0,     0,     0,
      14,     6,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    20,     0,     0,     0,
       0,     0,     0,     0,     0,    10,    12,     0,     0,     0,
      21,    22,     7,     0,    19,     0,     0,     9,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,    11,    13,     0,     0,     0,     0,     0,
       4
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,    58,   -32,   -32,   -32,   -32,   -32,    55,   -31,   -32,
     -19,   -32
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,    25,    27,    55,    56,     9,    34,    43,
      35,    36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      38,    39,    45,    50,     1,     8,     7,     2,    10,    11,
       3,     4,    12,    14,    40,    46,    51,    21,    15,    16,
      17,    19,    60,    18,    26,    54,    22,    23,    29,    24,
      65,    66,    28,    31,    30,    37,    33,    44,    32,    53,
       0,     0,    41,    42,   -18,    47,    49,    58,    48,    59,
      61,    52,    57,    64,    62,    63,    67,    71,    68,    75,
      77,    69,    70,    78,    13,    76,    72,    73,    74,    79,
      20,    80
};

static const yytype_int8 yycheck[] =
{
      31,     5,     5,     5,     3,    17,     4,     6,     4,     4,
       9,    10,     0,    19,    18,    18,    18,    17,    23,    16,
      12,     5,    53,    16,    13,    44,    17,    17,    15,    23,
      61,    62,    18,    15,    17,    14,    17,     7,    23,     8,
      -1,    -1,    22,    21,    21,    21,    20,    18,    23,    11,
      15,    24,    24,    17,    15,    23,     5,    23,    21,     5,
      11,    21,    21,    17,     6,    20,    24,    24,    24,    21,
      15,    24
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     9,    10,    26,    27,     4,    17,    32,
       4,     4,     0,    26,    19,    23,    16,    12,    16,     5,
      32,    17,    17,    17,    23,    28,    13,    29,    18,    15,
      17,    15,    23,    17,    33,    35,    36,    14,    33,     5,
      18,    22,    21,    34,     7,     5,    18,    21,    23,    20,
       5,    18,    24,     8,    35,    30,    31,    24,    18,    11,
      33,    15,    15,    23,    17,    33,    33,     5,    21,    21,
      21,    23,    24,    24,    24,     5,    20,    11,    17,    21,
      24
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    25,    26,    26,    27,    27,    28,    27,    29,    27,
      30,    27,    31,    27,    32,    32,    34,    33,    33,    35,
      35,    36,    36
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,    19,    13,     0,     9,     0,     9,
       0,    13,     0,    13,     3,     1,     0,     4,     1,     3,
       1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 1771 "mql.y" /* yacc.c:1646  */
    {cond_size = 0;}
#line 3029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 1772 "mql.y" /* yacc.c:1646  */
    {cond_size = 0;}
#line 3035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 1775 "mql.y" /* yacc.c:1646  */
    {
	//printf("Emp insert %s %s %s %s %s %s %s %s\n", $2, $4, $6, $8, $10, $12, $14, $17);
	setMode(INSERT);
	setFile(EMP);
	insert_f((yyvsp[-15].str), modifys((yyvsp[-13].str),strlen((yyvsp[-13].str))), (yyvsp[-11].str), modifys((yyvsp[-9].str),strlen((yyvsp[-9].str))), (yyvsp[-7].str), (yyvsp[-5].str));
}
#line 3046 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 1783 "mql.y" /* yacc.c:1646  */
    {
	//printf("Dep insert %s %s %s %s %s\n", $2, $4, $6, $8, $11);
	setMode(INSERT);
	setFile(DEPT);
	dep_insert_f((yyvsp[-9].str), modifys((yyvsp[-7].str),strlen((yyvsp[-7].str))), modifys((yyvsp[-5].str),strlen((yyvsp[-5].str))));
}
#line 3057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 1791 "mql.y" /* yacc.c:1646  */
    {	//printf("BOO %s\n",$4);
	if((yyvsp[0].str)[0] == 'E')
		setFile(EMP);
	else
		{ 
		//printf("SGDIS");
		setFile(DEPT);
		}
}
#line 3071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 1802 "mql.y" /* yacc.c:1646  */
    {
	printf("Get\n");
	//printf("BOOM %s\n",$4);
	if((yyvsp[-5].str)[0] == 'E')
		setFile(EMP);
	else
		{ 
		//printf("SGDIS");
		setFile(DEPT);
		}

	setMode(GET);

	GET_F(all_fields, field_size);
	field_size = 0;	
	cond_flag = 0;
}
#line 3093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 1821 "mql.y" /* yacc.c:1646  */
    {	if((yyvsp[0].str)[0] == 'E')
		setFile(EMP);
	else 
		setFile(DEPT);
}
#line 3103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 1827 "mql.y" /* yacc.c:1646  */
    {
	printf("Delete\n");
	if((yyvsp[-5].str)[0] == 'E')
		setFile(EMP);
	else 
		setFile(DEPT);

	setMode(DELETE);
	DELETE_f();

	cond_flag = 0;
	//printTable();
}
#line 3121 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 1842 "mql.y" /* yacc.c:1646  */
    {	if((yyvsp[-4].str)[0] == 'E')
	{
		printf("WOO\n");	
		setFile(EMP);
	}
		
	else
	{
		printf("WEE\n");
		setFile(DEPT);
	} 
		
}
#line 3139 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 1857 "mql.y" /* yacc.c:1646  */
    {
	printf("Update num\n");
	//printf("BOM %s \n", $8);
	//printf("FI: %d", field_dict($6));
	MODIFY_f(field_dict((yyvsp[-7].str)), (yyvsp[-5].str));
	cond_flag = 0;
}
#line 3151 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 1866 "mql.y" /* yacc.c:1646  */
    {	if((yyvsp[-4].str)[0] == 'E')
		setFile(EMP);
	else 
		setFile(DEPT);
}
#line 3161 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 1872 "mql.y" /* yacc.c:1646  */
    {
	printf("Update string\n");
	printf("BOM%s \n", (yyvsp[-5].str));
	printf("FI: %d", field_dict((yyvsp[-7].str)));
	MODIFY_f(field_dict((yyvsp[-7].str)), modifys((yyvsp[-5].str), strlen((yyvsp[-5].str))) );
	cond_flag = 0;
}
#line 3173 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 1880 "mql.y" /* yacc.c:1646  */
    {
							all_fields[field_size] = field_dict((yyvsp[-2].str));
							field_size++;
						 }
#line 3182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 1884 "mql.y" /* yacc.c:1646  */
    {
							all_fields[field_size] = field_dict((yyvsp[0].str));
							field_size++;
						 }
#line 3191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 1889 "mql.y" /* yacc.c:1646  */
    {
								if(cond_flag == 0)
								{
									FIRSTCOND_F(all_conds, cond_size);
									cond_flag = 1;
									cond_size = 0;
									
								}
								else
								{
									//printf("COND_SIZE: %d ", cond_size);
									NEXTCOND_F(all_conds, cond_size);
									cond_size = 0;
									//printf("COND_SIZE: %d ", cond_size);
								}
						}
#line 3212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 1907 "mql.y" /* yacc.c:1646  */
    {
							if(cond_flag == 0)
							{
								/* for(int i =0; i<cond_size; i++)
									printf("B: %d %d %s \n",all_conds[i].type, all_conds[i].field, all_conds[i].data);
								//printf("COND_SIZE: %d ", cond_size); */
								FIRSTCOND_F(all_conds, cond_size);
								cond_flag = 1;
								cond_size = 0;
								
							}
							else
							{
								//printf("COND_SIZE: %d ", cond_size);
								NEXTCOND_F(all_conds, cond_size);
								cond_size = 0;
								
							}
						}
#line 3236 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 1934 "mql.y" /* yacc.c:1646  */
    {
		   							//printf("Condition %d\n", strcmp("=",$2));
		   							cond temp_cond;
		   							
		   							temp_cond.type = rel_dict((yyvsp[-1].str));
		   							temp_cond.field = field_dict((yyvsp[-2].str));
		   							
		   							strcpy(temp_cond.data, (yyvsp[0].str));
		   							//printf("QQ1 %d %d %s\n", temp_cond.type, temp_cond.field, temp_cond.data);
		   							all_conds[cond_size] = temp_cond;
		   							cond_size ++;
		   						}
#line 3253 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 1947 "mql.y" /* yacc.c:1646  */
    {
		   							//printf("Condition %d\n", strcmp("=",$2));
		   							cond temp_cond;
		   							
		   							temp_cond.type = rel_dict((yyvsp[-1].str));
		   							temp_cond.field = field_dict((yyvsp[-2].str));
		   							
		   							strcpy(temp_cond.data, modifys((yyvsp[0].str), strlen((yyvsp[0].str))));

		   							//printf("QQ2 %d %d %s\n", temp_cond.type, temp_cond.field, temp_cond.data);
		   							all_conds[cond_size] = temp_cond;
		   							cond_size ++;
		   						}
#line 3271 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3275 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1960 "mql.y" /* yacc.c:1906  */




int main()
{
	//enum COND{E,L,G,LE,GE};

	//enum FIELDS{eid=20,ename,eage,eaddress,salary,deptno, dnum, dname, dlocation};

	int c1= 0;
    dep d_input1 = {10, "HR", "Mumbai"}; 
    c1++;
    dep d_input2 = {20, "ACCTS", "Delhi"}; 
    c1++;
    dep d_arr[2];
    d_arr[0] = d_input1;
    d_arr[1] = d_input2;
    dep_write(d_arr,c1);

    int c= 0;
    emp input1 = {101, "Kiran", 43, "HYD", 23000, 10}; 
    c++;
    emp input2 = {103, "Mohan", 31, "CHE", 21000, 20}; 
    c++;
    emp input3 = {104, "John", 53, "HYD", 43000, 10}; 
    c++;
    emp arr[3];
    arr[0] = input1;
    arr[1] = input2;
    arr[2] = input3;
   
    write(arr,c);


    //printTable();

	while(yyparse());
}


