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
		new AttributesDescriptor("Keyword", ProcSyntaxHighlighter.KEYWORD),
		new AttributesDescriptor("Line comment", ProcSyntaxHighlighter.LINE_COMMENT),
		new AttributesDescriptor("Bad value", ProcSyntaxHighlighter.BAD_CHARACTER),
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
			"// Proc code example.\n" +
			"public interface MyInterface\n" +
			"	int a = 100\n\n" +
			"# You are reading the \".properties\" entry.\n" +
			"! The exclamation mark can also mark text as comments.\n" +
			"website = https://en.wikipedia.org/\n" +
			"language = English\n" +
			"# The backslash below tells the application to continue reading\n" +
			"# the value onto the next line.\n" +
			"message = Welcome to \\\n" +
			"          Wikipedia!\n" +
			"# Add spaces to the key\n" +
			"key\\ with\\ spaces = This is the value that could be looked up with the key \"key with spaces\".\n" +
			"# Unicode\n" +
			"tab : \\u0009";
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
