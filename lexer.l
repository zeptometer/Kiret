%{
#include "common.h"
#include "object.h"
#include "parser.h"

int yywrap(void){ return 1;}
%}

SYMBOL ([a-zA-Z0-9]|"\!"|"\%"|"\&"|"\-"|"\="|"\@"|"\_"|"\~"|"\/"|"\:"|"\$"|"\*"|"\+"|"\."|"\<"|"\>"|"\?"|"\^")+

%%

[ |\t|\n]+  ;
"\("|"\)"|"\."|"\'"  {return yytext[0];}

[0-9]+(\.[0-9]+)? { yylval = makeKrtNumber(atof(yytext));
		   return ATOM;}

{SYMBOL} { yylval = makeKrtSymbol(yytext);
           return ATOM; }

#t { yylval = makeKrtBool(1);
     return ATOM; }

#f { yylval = makeKrtBool(0);
     return ATOM; }

. yyerror("Error: illegal char");

%%
