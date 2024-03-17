/// <summary>
/// Интерпретатор кода AMD64.
/// TODO Не уверен, что есть необходимость писать отдельный интерпретатор для конкретной платформы.
/// TODO Скорее придется написать общий интерпретатор, на входе которого будет синтаксическое дерево.
/// TODO Но наверное это не особо возможно из-за особенностей отдельных архитектур.
/// TODO Где-то в этой цепочке должна быть виртуальная машина.
/// </summary>
[Obsolete]
class Interpreter
{
	public Interpreter()
	{
	}

	//void LoadOsg(Identf s) {
	//	RISC.Load(code, pc);
	//	RISC.Execute(entry * 4, s, Oberon.Log);
	//}

	//void ExecOsg(Identf s) {
	//	i = 0;
	//	while (i < cno && s != comname[i]) {
	//		i++;
	//	}
	//	if (i < cno) {
	//		RISC.Execute(comadr[i], s, Oberon.Log);
	//	}
	//}
}
