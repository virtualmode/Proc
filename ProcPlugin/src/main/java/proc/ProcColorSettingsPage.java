package proc;

import javax.swing.*;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.nio.charset.StandardCharsets;
import java.util.Map;

import com.intellij.openapi.editor.colors.TextAttributesKey;
import com.intellij.openapi.fileTypes.SyntaxHighlighter;
import com.intellij.openapi.options.colors.AttributesDescriptor;
import com.intellij.openapi.options.colors.ColorDescriptor;
import com.intellij.openapi.options.colors.ColorSettingsPage;
import com.intellij.openapi.util.io.StreamUtil;
import com.intellij.openapi.util.text.StringUtil;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

/**
 * The color settings page adds the ability for users to customize color settings for the highlighting in language files.
 */
public class ProcColorSettingsPage implements ColorSettingsPage {

	private static final AttributesDescriptor[] DESCRIPTORS = new AttributesDescriptor[] {

		// Comments.
		new AttributesDescriptor("Comments//Comment", ProcSyntaxHighlighter.COMMENT), // #808080.

		// Keywords.
		new AttributesDescriptor("Keywords//Control", ProcSyntaxHighlighter.KEYWORDS_CONTROL), // #D8A0DF.
		new AttributesDescriptor("Keywords//Keyword", ProcSyntaxHighlighter.KEYWORD), // #569CD6.

		// TODO Regroup values.
		new AttributesDescriptor("Plain Text", ProcSyntaxHighlighter.TEXT),
		new AttributesDescriptor("Identifier", ProcSyntaxHighlighter.IDENTIFIER), // #DCDCDC.
		new AttributesDescriptor("Number", ProcSyntaxHighlighter.NUMBER), // #B5CEA8.
		new AttributesDescriptor("Bad value", ProcSyntaxHighlighter.BAD_CHARACTER) // #DCDCDC, #FF0000.
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
		try (Reader reader = new InputStreamReader(getClass().getResourceAsStream("DemoText.proc"), StandardCharsets.UTF_8)) {
			String result = StreamUtil.readText(reader);
			return StringUtil.convertLineSeparators(result);
		}
		catch (IOException ignored) {}

		return "*error loading text*";
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
