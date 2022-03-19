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

	// Это скорее группы, на которые делятся лексемы или синтаксические конструкции.
	public static final TextAttributesKey KEYWORD = createTextAttributesKey("PROC_KEYWORD", DefaultLanguageHighlighterColors.KEYWORD);
	public static final TextAttributesKey COMMENT = createTextAttributesKey("PROC_COMMENT", DefaultLanguageHighlighterColors.LINE_COMMENT);
	public static final TextAttributesKey BAD_CHARACTER = createTextAttributesKey("PROC_BAD_CHARACTER", HighlighterColors.BAD_CHARACTER);

	private static final TextAttributesKey[] KEYWORD_KEYS = new TextAttributesKey[] { KEYWORD };
	private static final TextAttributesKey[] COMMENT_KEYS = new TextAttributesKey[] {COMMENT};
	private static final TextAttributesKey[] BAD_CHAR_KEYS = new TextAttributesKey[] {BAD_CHARACTER};
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
		if (ProcParserDefinition.KEYWORDS.contains(tokenType)) {
			return KEYWORD_KEYS;
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
		if (tokenType.equals(SymbolType.COMMENT)) {
			return COMMENT_KEYS;
		}
		if (tokenType.equals(TokenType.BAD_CHARACTER)) {
			return BAD_CHAR_KEYS;
		}
		return EMPTY_KEYS;
	}

}
