package proc.psi;

import com.intellij.psi.tree.IElementType;
import org.jetbrains.annotations.NonNls;
import org.jetbrains.annotations.NotNull;

import proc.ProcLanguage;

public class ProcTokenType extends IElementType {

	public ProcTokenType(@NotNull @NonNls String debugName) {
		super(debugName, ProcLanguage.INSTANCE);
	}

	@Override
	public String toString() {
		return "ProcTokenType." + super.toString();
	}
}
