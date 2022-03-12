package proc.psi;

import com.intellij.extapi.psi.PsiFileBase;
import com.intellij.openapi.fileTypes.FileType;
import com.intellij.psi.FileViewProvider;
import org.jetbrains.annotations.NotNull;

import proc.ProcFileType;
import proc.ProcLanguage;

/**
 * The top-level node of the tree of PsiElements for a Language file.
 */
public class ProcFile extends PsiFileBase {

	public ProcFile(@NotNull FileViewProvider viewProvider) {
		super(viewProvider, ProcLanguage.INSTANCE);
	}

	@NotNull
	@Override
	public FileType getFileType() {
		return ProcFileType.INSTANCE;
	}

	@Override
	public String toString() {
		return "Proc File";
	}

}
