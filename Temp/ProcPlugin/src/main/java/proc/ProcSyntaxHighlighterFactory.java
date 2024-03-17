package proc;

import com.intellij.openapi.fileTypes.SyntaxHighlighter;
import com.intellij.openapi.fileTypes.SyntaxHighlighterFactory;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.vfs.VirtualFile;
import org.jetbrains.annotations.NotNull;

/**
 * The factory provides a standard way for the IntelliJ Platform to instantiate the syntax highlighter for language files.
 */
public class ProcSyntaxHighlighterFactory extends SyntaxHighlighterFactory {

	@NotNull
	@Override
	public SyntaxHighlighter getSyntaxHighlighter(Project project, VirtualFile virtualFile) {
		return new ProcSyntaxHighlighter();
	}

}
