package proc;

import com.intellij.lexer.Lexer;
import com.intellij.openapi.editor.DefaultLanguageHighlighterColors;
import com.intellij.openapi.editor.HighlighterColors;
import com.intellij.openapi.editor.colors.TextAttributesKey;
import com.intellij.openapi.fileTypes.SyntaxHighlighterBase;
import com.intellij.psi.TokenType;
import com.intellij.psi.tree.IElementType;
import org.jetbrains.annotations.NotNull;

import proc.psi.SymbolType;

import static com.intellij.openapi.editor.colors.TextAttributesKey.createTextAttributesKey;

/**
 * Language syntax highlighter class extends SyntaxHighlighterBase.
 * As recommended in Color Scheme Management, language highlighting text attributes are specified as
 * a dependency on one of standard Intellij Platform keys.
 */
public class ProcSyntaxHighlighter extends SyntaxHighlighterBase {

	// Comments.
	public static final TextAttributesKey COMMENT = createTextAttributesKey("PROC_COMMENT", DefaultLanguageHighlighterColors.LINE_COMMENT);

	private static final TextAttributesKey[] COMMENT_KEYS = new TextAttributesKey[] { COMMENT };


	// Keywords.
	public static final TextAttributesKey KEYWORD = createTextAttributesKey("PROC_KEYWORD", DefaultLanguageHighlighterColors.KEYWORD);
	public static final TextAttributesKey KEYWORDS_CONTROL = createTextAttributesKey("PROC_KEYWORDS_CONTROL", DefaultLanguageHighlighterColors.KEYWORD);

	private static final TextAttributesKey[] KEYWORD_KEYS = new TextAttributesKey[] { KEYWORD };
	private static final TextAttributesKey[] KEYWORDS_CONTROL_KEYS = new TextAttributesKey[] { KEYWORDS_CONTROL };


	// Definition.
	public static final TextAttributesKey DEFINITION_CLASS = createTextAttributesKey("PROC_DEFINITION_CLASS", DefaultLanguageHighlighterColors.CLASS_NAME);

	private static final TextAttributesKey[] DEFINITION_KEYS = new TextAttributesKey[] { DEFINITION_CLASS };


	// Это скорее группы, на которые делятся лексемы или синтаксические конструкции.
	public static final TextAttributesKey IDENTIFIER = createTextAttributesKey("PROC_IDENTIFIER", DefaultLanguageHighlighterColors.IDENTIFIER);
	public static final TextAttributesKey NUMBER = createTextAttributesKey("PROC_NUMBER", DefaultLanguageHighlighterColors.NUMBER);
	public static final TextAttributesKey BAD_CHARACTER = createTextAttributesKey("PROC_BAD_CHARACTER", HighlighterColors.BAD_CHARACTER);
	public static final TextAttributesKey PLAIN_TEXT = TextAttributesKey.createTextAttributesKey("PROC_PLAIN_TEXT", HighlighterColors.TEXT);
	public static final TextAttributesKey STRING = TextAttributesKey.createTextAttributesKey("PROC_STRING", DefaultLanguageHighlighterColors.STRING);

	private static final TextAttributesKey[] IDENTIFIER_KEYS = new TextAttributesKey[] { IDENTIFIER };
	private static final TextAttributesKey[] NUMBER_KEYS = new TextAttributesKey[] { NUMBER };
	private static final TextAttributesKey[] BAD_CHAR_KEYS = new TextAttributesKey[] { BAD_CHARACTER };
	private static final TextAttributesKey[] PLAIN_TEXT_KEYS = new TextAttributesKey[] { PLAIN_TEXT };
	private static final TextAttributesKey[] STRING_KEYS = new TextAttributesKey[] { STRING };
	private static final TextAttributesKey[] EMPTY_KEYS = new TextAttributesKey[0];


	/*
	public static final TextAttributesKey SEPARATOR = createTextAttributesKey("PROC_SEPARATOR", DefaultLanguageHighlighterColors.OPERATION_SIGN);
	public static final TextAttributesKey KEY = createTextAttributesKey("PROC_KEY", DefaultLanguageHighlighterColors.KEYWORD);
	public static final TextAttributesKey VALUE = createTextAttributesKey("PROC_VALUE", DefaultLanguageHighlighterColors.STRING);
	private static final TextAttributesKey[] SEPARATOR_KEYS = new TextAttributesKey[] {SEPARATOR};
	private static final TextAttributesKey[] KEY_KEYS = new TextAttributesKey[] {KEY};
	private static final TextAttributesKey[] VALUE_KEYS = new TextAttributesKey[] {VALUE};
	*/

	@NotNull
	@Override
	public Lexer getHighlightingLexer() {
		return new ProcLexerAdapter();
	}

	@Override
	public TextAttributesKey @NotNull [] getTokenHighlights(IElementType tokenType) {
		if (ProcParserDefinition.KEYWORDS_CONTROL.contains(tokenType)) {
			return KEYWORDS_CONTROL_KEYS;
		}
		if (ProcParserDefinition.KEYWORDS.contains(tokenType)) {
			return KEYWORD_KEYS;
		}
		if (ProcParserDefinition.DEFINITIONS.contains(tokenType)) {
			return DEFINITION_KEYS;
		}
		if (tokenType.equals(SymbolType.IDENTIFIER)) {
			return IDENTIFIER_KEYS;
		}
		if (tokenType.equals(SymbolType.NUMBER)) {
			return NUMBER_KEYS;
		}
		if (tokenType.equals(SymbolType.STRING)) {
			return STRING_KEYS;
		}

		if (tokenType.equals(SymbolType.DELIMITER)) {
			return PLAIN_TEXT_KEYS;
		}

		/*
		if (tokenType.equals(SymbolType.SEPARATOR)) {
			return SEPARATOR_KEYS;
		}
		if (tokenType.equals(SymbolType.KEY)) {
			return KEY_KEYS;
		}
		if (tokenType.equals(SymbolType.VALUE)) {
			return VALUE_KEYS;
		}
		*/

		if (ProcParserDefinition.COMMENTS.contains(tokenType)) {
			return COMMENT_KEYS;
		}
		if (tokenType.equals(TokenType.BAD_CHARACTER)) {
			return BAD_CHAR_KEYS;
		}
		return EMPTY_KEYS;
	}

}
