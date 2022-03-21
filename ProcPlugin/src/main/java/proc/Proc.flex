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
STATEMENT_ERROR=[^\r\n\s\t\f]+

LINE_COMMENT=("//")[^\r\n]*

DECIMAL_DIGIT=\d
LATIN_LETTER=[A-Za-z]

%%

<YYINITIAL> {
    // Keywords.
    "private"             { return SymbolType.PRIVATE; }
    "protected"           { return SymbolType.PROTECTED; }
    "public"              { return SymbolType.PUBLIC; }

    // Comments.
    {LINE_COMMENT}        { return SymbolType.LINE_COMMENT; }

    // Special symbols.
    {WHITE_SPACE}         { return TokenType.WHITE_SPACE; }
    {NEWLINE}             { return SymbolType.NEWLINE; }
    {STATEMENT_ERROR}     { return SymbolType.STATEMENT_ERROR; }
}

[^]                       { return TokenType.BAD_CHARACTER; }
