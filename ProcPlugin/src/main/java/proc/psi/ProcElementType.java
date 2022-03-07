package proc.psi;

import com.intellij.psi.tree.IElementType;
import org.jetbrains.annotations.NonNls;
import org.jetbrains.annotations.NotNull;

import proc.ProcLanguage;

public class ProcElementType extends IElementType {

    public ProcElementType(@NotNull @NonNls String debugName) {
        super(debugName, ProcLanguage.INSTANCE);
    }

}
