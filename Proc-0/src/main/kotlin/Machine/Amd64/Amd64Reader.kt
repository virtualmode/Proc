package proc.Machine.Amd64

import proc.Interop.FileStream
import proc.Text.CharReader
import proc.Text.Utf8

/**
 * Лексический анализатор двоичного кода архитектуры AMD64.
 */
class Amd64Reader {

	private var _reader: CharReader

	private var _writer: FileStream
	private var _utf8: Utf8

	init {
	}

	constructor(reader: CharReader) {
		_reader = reader
		_writer = FileStream("debug.txt")
		_utf8 = Utf8(_writer, _writer)
	}

	// TODO Avoid this.
	//protected fun finalize() {
	//	delete _utf8
	//	_writer->Close()
	//	delete _writer
	//}

	fun Get(): Boolean {
		var symbol: Int = _reader.ReadChar()
		if (symbol > 0) {

			// Вывод UTF-8.
			if (symbol < 256)
				print("$symbol")
			else
				print("[$symbol]")

			// Запись UTF-8.
			_utf8.WriteChar(symbol)

			return true
		}

		return false
	}
}
