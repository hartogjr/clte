/** @author  Simon de Hartog <simon@fs2a.pro>
 * @copyright Fs2a Ltd. (c) 2018
 * vim:set ts=2 sw=2 noexpandtab: */
%{
#include <string>
%}

%option debug
%option nodefault
%option yyclass="CLTE::Parser"
%option noyywrap
%option c++

%%
%{
	yylval = lval;
%}
