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

// Language terminals.
NEW_LINE=\r|\n|\r\n
WHITE_SPACE=[\s\t\f]

LINE_COMMENT=("//")[^\r\n]*
BLOCK_COMMENT=("/*")[^]*("*/")

LATIN_LETTER=[A-Za-z]
DECIMAL_DIGIT=[0123456789]
OTHER_LETTER=[∅]
OTHER_DIGIT=[∅]

LETTER={LATIN_LETTER}|{OTHER_LETTER}|{OTHER_DIGIT}
DIGIT={DECIMAL_DIGIT} // | LATIN_LETTER
IDENTIFIER={LETTER}({LETTER}|{DIGIT})*
NUMBER={DIGIT}+

// Auxiliary regular expressions.
STATEMENT_ERROR=[^\r\n\s\t\f]+

%%

<YYINITIAL> {

    // Identifiers: constructs.
    "class"               { return SymbolType.CLASS; }
    "enum"                { return SymbolType.ENUMERATION; }
    "interface"           { return SymbolType.INTERFACE; }

    // Identifiers: types.
    //"void"              { return SymbolType.VOID; } // #define void 0

    // Identifiers: scope (something like namespace) keywords.
    "using"               { return SymbolType.USING; }

    // Identifiers: access modifiers.
    "private"             { return SymbolType.PRIVATE; }
    "protected"           { return SymbolType.PROTECTED; }
    "public"              { return SymbolType.PUBLIC; }




    // Comments.
    {LINE_COMMENT}        { return SymbolType.LINE_COMMENT; }
    {BLOCK_COMMENT}       { return SymbolType.BLOCK_COMMENT; }



    // Other identifiers.
    {IDENTIFIER}          { return SymbolType.IDENTIFIER; }
    {NUMBER}              { return SymbolType.NUMBER; }

    // Special symbols.
    {NEW_LINE}            { return SymbolType.NEW_LINE; }
    {STATEMENT_ERROR}     { return SymbolType.STATEMENT_ERROR; }
    {WHITE_SPACE}         { return TokenType.WHITE_SPACE; }
}

[^]                       { return TokenType.BAD_CHARACTER; }
