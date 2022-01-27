package com.virtualmode.proc;

import com.intellij.lang.Language;

public class ProcLanguage extends Language {
    public static final ProcLanguage INSTANCE = new ProcLanguage();

    private ProcLanguage() {
        super("Proc");
    }
}
