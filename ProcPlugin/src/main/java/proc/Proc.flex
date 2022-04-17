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

// Components of base terminals.
LATIN_LETTER           = [A-Za-z]
DECIMAL_DIGIT          = [0123456789]
OTHER_LETTER           = [\u0401\u0451\u0410-\u044f] // Cyrillic letters [ЁёА-я]
OTHER_DIGIT            = [∅] // Joke stub.

SLASH                  = \/
ASTERISK               = \*

LEFT_PARENTHESIS       = \(
RIGHT_PARENTHESIS      = \)
LEFT_SQUARE_BRACKET    = \[
RIGHT_SQUARE_BRACKET   = \]
LEFT_CURLY_BRACKET     = \{
RIGHT_CURLY_BRACKET    = \}

UNDERLINE              = \_

LETTER                 = {LATIN_LETTER} | {OTHER_LETTER} | {OTHER_DIGIT} // Other digit most probably can be treated as letter.
DIGIT                  = {DECIMAL_DIGIT} | {LATIN_LETTER} // Digit is more complex than decimal digit.

// TODO Unapproved terminals
DELIMITER              = [\<\>\(\)\[\]\{\}\:\;\.\,\=\"\'\`\|\!\@\#\$\%\^\&\*\+\-\/\~]
STATEMENT_ERROR        = [^\<\>\(\)\[\]\{\}\:\;\.\,\=\"\'\`\|\!\@\#\$\%\^\&\*\+\-\/\~0123456789\r\n\s\t\f]+

// Base terminals.
NUMBER                 = ({LATIN_LETTER} | {DECIMAL_DIGIT})+
IDENTIFIER             = ({UNDERLINE} | {LETTER})+
                         ({UNDERLINE} | {LETTER} | {DIGIT})*
BAD_IDENTIFIER         = ({UNDERLINE} | {LETTER} | {DIGIT})+


// Comments.
LINE_COMMENT           = ("//")[^\r\n]*
BLOCK_COMMENT_START    = {SLASH}{ASTERISK}
BLOCK_COMMENT_END      = {ASTERISK}{SLASH}

// Auxiliary regular expressions.
NEW_LINE               = \r|\n|\r\n
WHITE_SPACE            = [\s\t\f]

%state BLOCK_COMMENT, NUMBER_BLOCK

%%

<YYINITIAL> {

    // Identifiers: constructs.
    "class"                  { return SymbolType.CLASS; }
    "enum"                   { return SymbolType.ENUMERATION; }
    "interface"              { return SymbolType.INTERFACE; }

    // Identifiers: types.
    //"void"              { return SymbolType.VOID; } // #define void 0

    // Identifiers: scope (something like namespace) keywords.
    "using"                  { return SymbolType.USING; }

    // Identifiers: access modifiers.
    "private"                { return SymbolType.PRIVATE; }
    "protected"              { return SymbolType.PROTECTED; }
    "public"                 { return SymbolType.PUBLIC; }

    "return"                 { return SymbolType.RETURN; }
    "const"                  { return SymbolType.CONSTANT; }
    "static"                 { return SymbolType.STATIC; }

    // Comments.
    {LINE_COMMENT}           { return SymbolType.LINE_COMMENT; }
    {BLOCK_COMMENT_START}    { yybegin(BLOCK_COMMENT); }

    // Other identifiers.
    {NUMBER}                 { return SymbolType.NUMBER; }
    {IDENTIFIER}             { return SymbolType.IDENTIFIER; }
    {BAD_IDENTIFIER}         { return TokenType.BAD_CHARACTER; }

    // Special symbols.
    {NEW_LINE}               { return SymbolType.NEW_LINE; }
    {DELIMITER}              { return SymbolType.DELIMITER; }
    //{STATEMENT_ERROR}        { return SymbolType.STATEMENT_ERROR; }
    {WHITE_SPACE}            { return TokenType.WHITE_SPACE; }
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
    [^] {}
}

//<NUMBER_BLOCK> {
//    {NUMBER_TAIL} {
//        yybegin(YYINITIAL);
//        return SymbolType.NUMBER;
//    }
//    [^] { yybegin(YYINITIAL); }
//}

[^]                       { return TokenType.BAD_CHARACTER; }
