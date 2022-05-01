package proc;

import javax.swing.*;
import java.util.Map;

import com.intellij.openapi.editor.colors.TextAttributesKey;
import com.intellij.openapi.fileTypes.SyntaxHighlighter;
import com.intellij.openapi.options.colors.AttributesDescriptor;
import com.intellij.openapi.options.colors.ColorDescriptor;
import com.intellij.openapi.options.colors.ColorSettingsPage;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

/**
 * The color settings page adds the ability for users to customize color settings for the highlighting in language files.
 */
public class ProcColorSettingsPage implements ColorSettingsPage {

	private static final AttributesDescriptor[] DESCRIPTORS = new AttributesDescriptor[]{
		//new AttributesDescriptor("Key", ProcSyntaxHighlighter.KEY),
		//new AttributesDescriptor("Separator", ProcSyntaxHighlighter.SEPARATOR),
		//new AttributesDescriptor("Value", ProcSyntaxHighlighter.VALUE),
		new AttributesDescriptor("Text", ProcSyntaxHighlighter.TEXT),
		new AttributesDescriptor("Identifier", ProcSyntaxHighlighter.IDENTIFIER),
		new AttributesDescriptor("Number", ProcSyntaxHighlighter.NUMBER),
		new AttributesDescriptor("Keyword", ProcSyntaxHighlighter.KEYWORD),
		new AttributesDescriptor("Line comment", ProcSyntaxHighlighter.LINE_COMMENT),
		new AttributesDescriptor("Bad value", ProcSyntaxHighlighter.BAD_CHARACTER)
	};

	@Nullable
	@Override
	public Icon getIcon() {
		return ProcIcons.FILE;
	}

	@NotNull
	@Override
	public SyntaxHighlighter getHighlighter() {
		return new ProcSyntaxHighlighter();
	}

	@NotNull
	@Override
	public String getDemoText() {
		return
			"/*\n" +
			"	Proc code example.\n" +
			"*/\n" +
			"public interface Идентификатор\n" +
			"	int _privateField = -0100 // Line comment example.\n\n" +
			"	protected int PossibleIdentifier = (16)fafafafa\n\n" +
			"	public 3[4] 24_BadIdentifier = +1210\n" +
			"	public int Exponential = 0.3218e+8\n" +
			"	public (10:10:10)24:60:60 Time = 12:30:45 // TODO Rethink?\n\n" +
			"// Scope example.\n" +
			"for (int i = 0; i < 10; i++)\n" +
			"	write(\"iteration \" + i + '.')\n\n\n";
	}

	@Nullable
	@Override
	public Map<String, TextAttributesKey> getAdditionalHighlightingTagToDescriptorMap() {
		return null;
	}

	@Override
	public AttributesDescriptor @NotNull [] getAttributeDescriptors() {
		return DESCRIPTORS;
	}

	@Override
	public ColorDescriptor @NotNull [] getColorDescriptors() {
		return ColorDescriptor.EMPTY_ARRAY;
	}

	@NotNull
	@Override
	public String getDisplayName() {
		return "Proc";
	}

}
