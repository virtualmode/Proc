package proc;

import com.intellij.lang.Language;

/**
 * Language implementation.
 */
public class ProcLanguage extends Language {

	public static final ProcLanguage INSTANCE = new ProcLanguage();

	private ProcLanguage() {
		super("Proc");
	}
}
