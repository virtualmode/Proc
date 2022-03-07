package proc;

import com.intellij.lexer.FlexAdapter;

public class ProcLexerAdapter extends FlexAdapter {

    public ProcLexerAdapter() {
        super(new ProcLexer(null));
    }
}
