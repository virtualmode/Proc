package proc;

import com.intellij.openapi.fileTypes.LanguageFileType;
import org.jetbrains.annotations.NonNls;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;

/**
 * Language file type is defined by subclassing LanguageFileType.
 */
public class ProcFileType extends LanguageFileType {

	public static final ProcFileType INSTANCE = new ProcFileType();

	private ProcFileType() {
		super(ProcLanguage.INSTANCE);
	}

	@Override
	public @NonNls
	@NotNull String getName() {
		return "Proc File";
	}

	@Override
	public @NotNull String getDescription() {
		return "Proc language file";
	}

	@Override
	public @NotNull String getDefaultExtension() {
		return "proc";
	}

	@Override
	public @Nullable Icon getIcon() {
		return ProcIcons.FILE;
	}
}
