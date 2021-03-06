%{
	
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




%}

%union {
		char str[200];            
};

%token <str> INS 
%token <str> RECORD 
%token <str> NUM 
%token <str> GETT 
%token <str> AND 
%token <str> OR 
%token <str> UPDATE 
%token <str> DEL 
%token <str> INTO 
%token <str> IN
%token <str> SET 
%token <str> TO 
%token <str> WHERE 
%token <str> FROM
%token <str> VAR 
%token <str> STRING
%token <str> LB
%token <str> RB
%token <str> COLON
%token <str> REL_OP
%token <str> COMMA
%token NL

%type <str> CONDITION
%type <str> CONDITIONS
%type <str> FIELDS
%type <str> ACONDITIONS


%%
START: STMT START	{cond_size = 0;} 
		| STMT	{cond_size = 0;}

STMT: INS RECORD LB NUM COMMA STRING COMMA NUM COMMA STRING COMMA NUM COMMA NUM RB INTO VAR COLON NL	
{
	//printf("Emp insert %s %s %s %s %s %s %s %s\n", $2, $4, $6, $8, $10, $12, $14, $17);
	setMode(INSERT);
	setFile(EMP);
	insert_f($4, modifys($6,strlen($6)), $8, modifys($10,strlen($10)), $12, $14);
}

STMT: INS RECORD LB NUM COMMA STRING COMMA STRING RB INTO VAR COLON	NL				
{
	//printf("Dep insert %s %s %s %s %s\n", $2, $4, $6, $8, $11);
	setMode(INSERT);
	setFile(DEPT);
	dep_insert_f($4, modifys($6,strlen($6)), modifys($8,strlen($8)));
}

STMT: GETT FIELDS FROM VAR 
{	//printf("BOO %s\n",$4);
	if($4[0] == 'E')
		setFile(EMP);
	else
		{ 
		//printf("SGDIS");
		setFile(DEPT);
		}
}

		 WHERE CONDITIONS COLON NL		
{
	printf("Get\n");
	//printf("BOOM %s\n",$4);
	if($4[0] == 'E')
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

STMT: DEL RECORD FROM VAR 
{	if($4[0] == 'E')
		setFile(EMP);
	else 
		setFile(DEPT);
}
	WHERE CONDITIONS COLON NL		
{
	printf("Delete\n");
	if($4[0] == 'E')
		setFile(EMP);
	else 
		setFile(DEPT);

	setMode(DELETE);
	DELETE_f();

	cond_flag = 0;
	//printTable();
}

STMT: UPDATE RECORD IN VAR SET VAR TO NUM 
{	if($4[0] == 'E')
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

	WHERE CONDITIONS COLON NL 		
{
	printf("Update num\n");
	//printf("BOM %s \n", $8);
	//printf("FI: %d", field_dict($6));
	MODIFY_f(field_dict($6), $8);
	cond_flag = 0;
}

STMT: UPDATE RECORD IN VAR SET VAR TO STRING 
{	if($4[0] == 'E')
		setFile(EMP);
	else 
		setFile(DEPT);
}
	WHERE CONDITIONS COLON NL 		
{
	printf("Update string\n");
	printf("BOM%s \n", $8);
	printf("FI: %d", field_dict($6));
	MODIFY_f(field_dict($6), modifys($8, strlen($8)) );
	cond_flag = 0;
} 

FIELDS: VAR COMMA FIELDS {
							all_fields[field_size] = field_dict($1);
							field_size++;
						 }
		| VAR 			{
							all_fields[field_size] = field_dict($1);
							field_size++;
						 }

CONDITIONS: ACONDITIONS {
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
						} OR CONDITIONS 	
							
			| ACONDITIONS	
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
							

ACONDITIONS: CONDITION AND ACONDITIONS

			| CONDITION		
							

CONDITION: VAR REL_OP NUM
								{
		   							//printf("Condition %d\n", strcmp("=",$2));
		   							cond temp_cond;
		   							
		   							temp_cond.type = rel_dict($2);
		   							temp_cond.field = field_dict($1);
		   							
		   							strcpy(temp_cond.data, $3);
		   							//printf("QQ1 %d %d %s\n", temp_cond.type, temp_cond.field, temp_cond.data);
		   							all_conds[cond_size] = temp_cond;
		   							cond_size ++;
		   						}

		   | VAR REL_OP STRING 	{
		   							//printf("Condition %d\n", strcmp("=",$2));
		   							cond temp_cond;
		   							
		   							temp_cond.type = rel_dict($2);
		   							temp_cond.field = field_dict($1);
		   							
		   							strcpy(temp_cond.data, modifys($3, strlen($3)));

		   							//printf("QQ2 %d %d %s\n", temp_cond.type, temp_cond.field, temp_cond.data);
		   							all_conds[cond_size] = temp_cond;
		   							cond_size ++;
		   						}
%%



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


