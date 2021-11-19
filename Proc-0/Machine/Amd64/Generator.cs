using Source.Symbol;

using String = Text.String;

/// <summary>
/// Генератор кода.
/// </summary>
class Generator
{
	private TypeDescription _boolType;
	private TypeDescription _integerType;

	private Writer _writer;
	private ProcSyntax _syntax;

	public Generator(Writer writer, ProcSyntax syntax)
	{
		_writer = writer;
		_syntax = syntax;

		_boolType = new TypeDescription()
		{
			Form = TypeDescription.TypeForm.Boolean,
			Size = 1
		};

		_integerType = new TypeDescription()
		{
			Form = TypeDescription.TypeForm.Integer,
			Size = 4
		};

		_syntax.Enter(ClassMode.Type, 1, "bool", _boolType);
		_syntax.Enter(ClassMode.Type, 2, "int", _integerType);
		_syntax.Enter(ClassMode.Constant, 1, "true", _boolType);
		_syntax.Enter(ClassMode.Constant, 0, "false", _boolType);

		// TODO Добавить регистрацию инструкций процессора.
		//SetMnemo(MOV, "MOV ");
		//SetMnemo(MVN, "MVN ");
		//SetMnemo(ADD, "ADD ");
		//SetMnemo(SUB, "SUB ");
		//SetMnemo(MUL, "MUL ");
		//SetMnemo(DIV, "DIV ");
		//SetMnemo(MOD, "MOD ");
		//SetMnemo(CMP, "CMP ");
		//SetMnemo(MOVI, "MOVI");
		//SetMnemo(MVNI, "MVNI");
		//SetMnemo(ADDI, "ADDI");
		//SetMnemo(SUBI, "SUBI");
		//SetMnemo(MULI, "MULI");
		//SetMnemo(DIVI, "DIVI");
		//SetMnemo(MODI, "MODI");
		//SetMnemo(CMPI, "CMPI");
		//SetMnemo(CHKI, "CHKI");
		//SetMnemo(LDW, "LDW ");
		//SetMnemo(LDB, "LDB ");
		//SetMnemo(POP, "POP ");
		//SetMnemo(STW, "STW ");
		//SetMnemo(STB, "STB ");
		//SetMnemo(PSH, "PSH ");
		//SetMnemo(BEQ, "BEQ ");
		//SetMnemo(BNE, "BNE ");
		//SetMnemo(BLT, "BLT ");
		//SetMnemo(BGE, "BGE ");
		//SetMnemo(BLE, "BLE ");
		//SetMnemo(BGT, "BGT ");
		//SetMnemo(BR, "BR  ");
		//SetMnemo(BSR, "BSR ");
		//SetMnemo(RET, "RET ");
		//SetMnemo(RD, "RD  ");
		//SetMnemo(WRD, "WRD ");
		//SetMnemo(WRH, "WRH ");
		//SetMnemo(WRL, "WRL ");

		Open();
	}

	private void SetMnemo(char op, String name)
	{
		//memcpy(mnemo[op], name, strlen(name));
	}

	/// <summary>
	/// Инициализация регистров.
	/// </summary>
	void Open()
	{
		//curlev = 0;
		//pc = 0;
		//cno = 0;
		//memset(regs, 0, sizeof(char) * 64);
	}

	private void Decode()
	{
		//long i, w, op, a;
		//fprintf(writerOsg, "entry %u\n", entry * 4);
		//i = 0;
		//while (i < pc)
		//{
		//	w = code[i];
		//	op = w / 67108864 % 64;
		//	fprintf(writerOsg, "%u 9X [%s] ", 4 * i, mnemo[op]);
		//	if (op < BEQ)
		//	{
		//		a = w % 262144;
		//		if (a >= 131072)
		//		{
		//			a -= 262144; // Расширение знака.
		//		}
		//		fprintf(writerOsg, "9X %u, %u, ", w / 4194304 % 16, w / 262144 % 16);
		//	}
		//	else
		//	{
		//		a = w % 67108864;
		//		if (a >= 33554432)
		//		{
		//			a -= 67108864; // Расширение знака.
		//		}
		//	}
		//	fprintf(writerOsg, "%u\n", a);
		//	i++;
		//}
		//fprintf(writerOsg, "\n");
	}

	public void CompileAndEmit()
	{
		_syntax.Global(); // Основная цель синтаксического разбора.
		Decode(); // Запись инструкций в файл.
	}
}
