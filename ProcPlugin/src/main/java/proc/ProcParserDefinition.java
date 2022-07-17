package proc;

import com.intellij.lang.ASTNode;
import com.intellij.lang.ParserDefinition;
import com.intellij.lang.PsiParser;
import com.intellij.lexer.Lexer;
import com.intellij.openapi.project.Project;
import com.intellij.psi.FileViewProvider;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiFile;
import com.intellij.psi.TokenType;
import com.intellij.psi.tree.IFileElementType;
import com.intellij.psi.tree.TokenSet;
import org.jetbrains.annotations.NotNull;

import proc.parser.ProcParser;
import proc.psi.ProcFile;
import proc.psi.SymbolType;

/**
 * Language parser is defined by subclassing ParserDefinition.
 */
public class ProcParserDefinition implements ParserDefinition {

	public static final TokenSet KEYWORDS_CONTROL = TokenSet.create(
		SymbolType.RETURN,
		SymbolType.FOR,
		SymbolType.DO,
		SymbolType.WHILE,
		SymbolType.IF,
		SymbolType.ELSE
	);

	public static final TokenSet KEYWORDS = TokenSet.create(
		SymbolType.PRIVATE,
		SymbolType.PROTECTED,
		SymbolType.PUBLIC,
		SymbolType.USE,
		SymbolType.USING,
		SymbolType.CLASS,
		SymbolType.INTERFACE,
		SymbolType.ENUMERATION,
		SymbolType.CONSTANT,
		SymbolType.STATIC,

		SymbolType.VAR,
		SymbolType.VOID,
		SymbolType.BOOL,
		SymbolType.OBJECT
	);

	public static final TokenSet COMMENTS = TokenSet.create(
		SymbolType.LINE_COMMENT,
		SymbolType.BLOCK_COMMENT
	);

	public static final TokenSet WHITE_SPACES = TokenSet.create(TokenType.WHITE_SPACE);

	public static final IFileElementType FILE = new IFileElementType(ProcLanguage.INSTANCE);

	@NotNull
	@Override
	public Lexer createLexer(Project project) {
		return new ProcLexerAdapter();
	}

	@NotNull
	@Override
	public TokenSet getWhitespaceTokens() {
		return WHITE_SPACES;
	}

	@NotNull
	@Override
	public TokenSet getCommentTokens() {
		return COMMENTS;
	}

	@NotNull
	@Override
	public TokenSet getStringLiteralElements() {
		return TokenSet.EMPTY;
	}

	@NotNull
	@Override
	public PsiParser createParser(final Project project) {
		return new ProcParser();
	}

	@Override
	public IFileElementType getFileNodeType() {
		return FILE;
	}

	@Override
	public PsiFile createFile(FileViewProvider viewProvider) {
		return new ProcFile(viewProvider);
	}

	@Override
	public SpaceRequirements spaceExistenceTypeBetweenTokens(ASTNode left, ASTNode right) {
		return SpaceRequirements.MAY;
	}

	@NotNull
	@Override
	public PsiElement createElement(ASTNode node) {
		return SymbolType.Factory.createElement(node);
	}

}
