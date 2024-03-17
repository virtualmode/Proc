package proc;

import com.intellij.lexer.FlexAdapter;

/**
 * The JFlex lexer needs to be adapted to the IntelliJ Platform Lexer API.
 * This is done by subclassing FlexAdapter.
 */
public class ProcLexerAdapter extends FlexAdapter {

	public ProcLexerAdapter() {
		super(new ProcLexer(null));
	}
}
