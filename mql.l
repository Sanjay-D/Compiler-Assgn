%{
	#include<stdlib.h>
	#include "y.tab.h"
%}


%%

AND     {return AND; }
DELETE	{return DEL;}
FROM	{return FROM;}
GET     {return GETT; }
IN 		{return IN;}
INSERT 	{return INS;}
INTO	{return INTO;}
OR      {return OR; }
RECORD	{return RECORD;}
SET 	{return SET;}
TO 		{return TO;}
UPDATE	{return UPDATE;}
WHERE	{return WHERE;}

[1-9][0-9]* {strcpy(yylval.str,yytext); return NUM;}
\"[A-Za-z0-9.]+\" {strcpy(yylval.str,yytext);return STRING;}
[A-Za-z_][A-Za-z0-9.]* {strcpy(yylval.str,yytext); return VAR;}
\( {strcpy(yylval.str,yytext); return LB;}
\) {strcpy(yylval.str,yytext); return RB;}
\; {strcpy(yylval.str,yytext); return COLON;}
">="|"<="|"!="|"="|"<"|">" {strcpy(yylval.str,yytext); return REL_OP;}
,	{strcpy(yylval.str,yytext); return COMMA;}
\n 	{return NL;}
. ;
%%