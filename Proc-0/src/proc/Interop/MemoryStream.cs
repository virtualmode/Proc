/// <summary>
/// Поток памяти.
/// </summary>
class MemoryStream: Reader, Writer
{
	public MemoryStream(object pointer)
	{
	}

	public object Read(Writer destination)
	{
		throw new NotImplementedException();
	}

	public object Read(object destination, object baseobj)
	{
		throw new NotImplementedException();
	}

	public object Write(Reader source)
	{
		throw new NotImplementedException();
	}

	public object Write(object source, object baseobj)
	{
		throw new NotImplementedException();
	}
}
