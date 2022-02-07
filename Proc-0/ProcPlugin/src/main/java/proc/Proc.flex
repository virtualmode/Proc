/* Proc scanner */

package proc;

import com.intellij.lexer.FlexLexer;
import com.intellij.psi.tree.IElementType;
import com.intellij.psi.TokenType;
import proc.ProcTokenType;

%%

%class ProcLexer
%implements FlexLexer
%unicode
%function advance
%type IElementType

CRLF=\R
WHITE_SPACE_CHAR=[\ \n\r\t\f]
VALUE_CHARACTER=[^\n\r\f\\] | "\\"{CRLF} | "\\".
END_OF_LINE_COMMENT=("#"|"!")[^\r\n]*
KEY_SEPARATOR=[:=]
KEY_SEPARATOR_SPACE=\ \t
KEY_CHARACTER=[^:=\ \n\r\t\f\\] | "\\"{CRLF} | "\\".
FIRST_VALUE_CHARACTER_BEFORE_SEP={VALUE_CHARACTER}
VALUE_CHARACTERS_BEFORE_SEP=([^:=\ \t\n\r\f\\] | "\\"{CRLF} | "\\".)({VALUE_CHARACTER}*)
VALUE_CHARACTERS_AFTER_SEP=([^\ \t\n\r\f\\] | "\\"{CRLF} | "\\".)({VALUE_CHARACTER}*)

%state IN_VALUE
%state IN_KEY_VALUE_SEPARATOR_HEAD
%state IN_KEY_VALUE_SEPARATOR_TAIL

%%

<YYINITIAL> {END_OF_LINE_COMMENT}        { yybegin(YYINITIAL); return ProcSymbolType.END_OF_LINE_COMMENT; }

<YYINITIAL> {KEY_CHARACTER}+             { yybegin(IN_KEY_VALUE_SEPARATOR_HEAD); return ProcSymbolType.KEY_CHARACTERS; }
<IN_KEY_VALUE_SEPARATOR_HEAD> {
    {KEY_SEPARATOR_SPACE}+       { yybegin(IN_KEY_VALUE_SEPARATOR_HEAD); return ProcSymbolType.WHITE_SPACE; }
    {KEY_SEPARATOR}             { yybegin(IN_KEY_VALUE_SEPARATOR_TAIL); return ProcSymbolType.KEY_VALUE_SEPARATOR; }
    {VALUE_CHARACTERS_BEFORE_SEP}     { yybegin(YYINITIAL); return ProcSymbolType.VALUE_CHARACTERS; }
    {CRLF}{WHITE_SPACE_CHAR}*  { yybegin(YYINITIAL); return ProcSymbolType.WHITE_SPACE; }
}
<IN_KEY_VALUE_SEPARATOR_TAIL> {
    {KEY_SEPARATOR_SPACE}+      { yybegin(IN_KEY_VALUE_SEPARATOR_TAIL); return ProcSymbolType.WHITE_SPACE; }
    {VALUE_CHARACTERS_AFTER_SEP}   { yybegin(YYINITIAL); return ProcSymbolType.VALUE_CHARACTERS; }
    {CRLF}{WHITE_SPACE_CHAR}*  { yybegin(YYINITIAL); return ProcSymbolType.WHITE_SPACE; }
}
<IN_VALUE> {VALUE_CHARACTER}+            { yybegin(YYINITIAL); return ProcSymbolType.VALUE_CHARACTERS; }
<IN_VALUE> {CRLF}{WHITE_SPACE_CHAR}*     { yybegin(YYINITIAL); return ProcSymbolType.WHITE_SPACE; }
{WHITE_SPACE_CHAR}+                      { return ProcSymbolType.WHITE_SPACE; }
[^]                                      { return ProcSymbolType.BAD_CHARACTER; }
