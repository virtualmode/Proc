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

// Base terminals.
LATIN_LETTER         = [A-Za-z]
DECIMAL_DIGIT        = [0123456789]
OTHER_LETTER         = [∅]
OTHER_DIGIT          = [∅]

LEFT_PARENTHESIS     = \(
RIGHT_PARENTHESIS    = \)
LEFT_SQUARE_BRACKET  = \[
RIGHT_SQUARE_BRACKET = \]
LEFT_CURLY_BRACKET   = \{
RIGHT_CURLY_BRACKET  = \}
//SIGN               = [-+] // Part of operators?

LETTER               = {LATIN_LETTER} | {OTHER_LETTER} | {OTHER_DIGIT} // Other digit most probably can be treated as letter.
DIGIT                = {DECIMAL_DIGIT} | {LATIN_LETTER} // Digit is more complex than decimal digit.
IDENTIFIER           = {LETTER} ({LETTER} | {DECIMAL_DIGIT})+

LEADING_ZERO         = 0
NUMBER               = {DECIMAL_DIGIT}({DIGIT})+

// Comments.
LINE_COMMENT         = ("//")[^\r\n]*
BLOCK_COMMENT_START  = ("/*")
BLOCK_COMMENT_END    = ("*/")

// Auxiliary regular expressions.
NEW_LINE             = \r|\n|\r\n
STATEMENT_ERROR      = [^\r\n\s\t\f]+
WHITE_SPACE          = [\s\t\f]

%state BLOCK_COMMENT

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
    {BLOCK_COMMENT_START} { yybegin(BLOCK_COMMENT); }

    // Other identifiers.
    {IDENTIFIER}          { return SymbolType.IDENTIFIER; }
    {LEADING_ZERO}        { return SymbolType.LEADING_ZERO; }
    {NUMBER}              { return SymbolType.NUMBER; }

    // Special symbols.
    {NEW_LINE}            { return SymbolType.NEW_LINE; }
    {STATEMENT_ERROR}     { return SymbolType.STATEMENT_ERROR; }
    {WHITE_SPACE}         { return TokenType.WHITE_SPACE; }
}

<BLOCK_COMMENT> {
    <<EOF>> {
        yybegin(YYINITIAL);
        return TokenType.BAD_CHARACTER; // Can't find block comment end sequence.
    }
    {BLOCK_COMMENT_END} {
        yybegin(YYINITIAL);
        return SymbolType.BLOCK_COMMENT;
    }
    //[^] {}
}

[^]                       { return TokenType.BAD_CHARACTER; }
