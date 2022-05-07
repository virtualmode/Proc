/*
	2. Универсальная машина не может работать без входных и выходных данных. Мне еще не известно, как эти данные должны
	выглядеть и передаваться. Поэтому необходимо ввести некоторую абстракцию для работы с потоками, известными как
	ленты. Каждая клетка ленты может содержать несколько различных значений, как в машине Тьюринга. На отдельных
	архитектурах такие клетки могут быть основаны на разных физических принципах и могут кодировать количество
	состояний - оснований, а объём данных можно выразить через логарифм общего количества состояний по основанию
	архитектуры. Такое представление объёма, к сожалению, возрастает экспоненциально, но полностью отвязывает код от
	оборудования.
*/

package proc.Interop

// Если использовать interface segregation, то может и не будет смысла в объединённом интерфейсе.
// Также есть идея объединений для безымянных композиций интерфейсов и др. типов.
//class Stream: public Reader, public Writer, public Seeker {
//};

/**
 * Файловый поток.
 */
class FileStream: Reader, Writer {

	override fun Read(destination: Writer): Object {
		TODO("Not yet implemented")
	}

	override fun Read(destination: Object, baseObj: Object): Object {
		TODO("Not yet implemented")
	}

	override fun Write(source: Reader): Object {
		TODO("Not yet implemented")
	}

	override fun Write(source: Object, baseObj: Object) {
		TODO("Not yet implemented")
	}

	/*
	private System.IO.FileStream _handle;

	public FileStream(string fileName, FileMode fileMode, FileAccess fileAccess)
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

	/// <summary>
	/// baseobj - это тип данных, основание, как раз и представляющий количество состояний.
	/// Пока что тип данных будет выглядеть как base[exponent][exponent][..].
	/// destination должен содержать указатель на место, в которое будет записано states состояний.
	/// </summary>
	/// <param name="destination"></param>
	/// <param name="baseobj"></param>
	/// <returns></returns>
	/// <exception cref="NotImplementedException"></exception>
	public object Read(object destination, object baseobj)
	{
		return (object)_handle.Read((byte[])destination, 0, BaseToBytes((int)baseobj));
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

	public object Read(Writer destination)
	{
		throw new NotImplementedException();
	}
	 */
}
