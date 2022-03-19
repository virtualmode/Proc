/* Proc scanner */
package proc;

import com.intellij.lexer.FlexLexer;
import com.intellij.psi.tree.IElementType;
import com.intellij.psi.TokenType;

import proc.psi.SymbolType;

%%

%class ProcLexer
%implements FlexLexer
%unicode
%function advance
%type IElementType
%eof{ return;
%eof}

%{
    // TODO You can add code here.
%}

NEWLINE=\r|\n|\r\n
WHITE_SPACE=[\s\t\f]
END_OF_LINE_COMMENT=("//")[^\r\n]*

//FIRST_VALUE_CHARACTER=[^ \n\f\\] | "\\"{CRLF} | "\\".
//VALUE_CHARACTER=[^\n\f\\] | "\\"{CRLF} | "\\".
//SEPARATOR=[:=]
//KEY_CHARACTER=[^:=\ \n\t\f\\] | "\\ "

//%state WAITING_VALUE

%%

<YYINITIAL> {
    // KEYWORD.
    "private"             { return SymbolType.PRIVATE; }
    "protected"           { return SymbolType.PROTECTED; }
    "public"              { return SymbolType.PUBLIC; }

    {END_OF_LINE_COMMENT} { return SymbolType.COMMENT; }
    {NEWLINE}             { return SymbolType.NEWLINE; }
    {WHITE_SPACE}         { return TokenType.WHITE_SPACE; }
}

[^]                       { return TokenType.BAD_CHARACTER; }

/*
<YYINITIAL> {END_OF_LINE_COMMENT}                           { yybegin(YYINITIAL); return SymbolType.COMMENT; }

<YYINITIAL> {KEY_CHARACTER}+                                { yybegin(YYINITIAL); return SymbolType.KEY; }

<YYINITIAL> {SEPARATOR}                                     { yybegin(WAITING_VALUE); return SymbolType.SEPARATOR; }

<WAITING_VALUE> {CRLF}({CRLF}|{WHITE_SPACE})+               { yybegin(YYINITIAL); return TokenType.WHITE_SPACE; }

<WAITING_VALUE> {WHITE_SPACE}+                              { yybegin(WAITING_VALUE); return TokenType.WHITE_SPACE; }

<WAITING_VALUE> {FIRST_VALUE_CHARACTER}{VALUE_CHARACTER}*   { yybegin(YYINITIAL); return SymbolType.VALUE; }

({CRLF}|{WHITE_SPACE})+                                     { yybegin(YYINITIAL); return TokenType.WHITE_SPACE; }

[^]                                                         { return TokenType.BAD_CHARACTER; }
*/
