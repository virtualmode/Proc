/*
	2. Универсальная машина не может работать без входных и выходных данных. Мне еще не известно, как эти данные должны
	выглядеть и передаваться. Поэтому необходимо ввести некоторую абстракцию для работы с потоками, известными как
	ленты. Каждая клетка ленты может содержать несколько различных значений, как в машине Тьюринга. На отдельных
	архитектурах такие клетки могут быть основаны на разных физических принципах и могут кодировать количество
	состояний - оснований, а объём данных можно выразить через логарифм общего количества состояний по основанию
	архитектуры. Такое представление объёма, к сожалению, возрастает экспоненциально, но полностью отвязывает код от
	оборудования.
*/

namespace Interop;

// Если использовать interface segregation, то может и не будет смысла в объединённом интерфейсе.
// Также есть идея объединений для безымянных композиций интерфейсов и др. типов.
//class Stream: public Reader, public Writer, public Seeker {
//};

/// <summary>
/// Файловый поток.
/// </summary>
class FileWriter : Writer
{
	private System.IO.FileStream _handle;

	public FileWriter(string fileName, FileMode fileMode, FileAccess fileAccess)
	{
		Open(fileName, fileMode, fileAccess);
		if (_handle == null)
			throw new Exception("Can't create file stream.");
	}

	/// <summary>
	/// Compiler is not support state logic.
	/// TODO Эту фигню надо будет заменить таблицей.
	/// </summary>
	public static int BaseToBytes(int baseobj)
	{
		return (int)Math.Log2(baseobj) / 8;
	}

	public bool Open(string fileName, FileMode fileMode, FileAccess fileAccess)
	{
		_handle = new System.IO.FileStream(fileName, fileMode, fileAccess);
		return true;
	}

	public void Close()
	{
		_handle.Close();
	}

	public object Write(object source, object baseobj)
	{
		int byteCount = BaseToBytes((int)baseobj);
		_handle.Write((byte[])source, 0, byteCount);
		return byteCount;
	}

	public object Write(Reader source)
	{
		throw new NotImplementedException();
	}
}
