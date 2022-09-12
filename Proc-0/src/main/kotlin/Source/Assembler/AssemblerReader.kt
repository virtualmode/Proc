/*
	5. Здесь будет что-то типа читабельного представления машинного языка, а может сразу нескольких. Как вариант
	стоит подумать в принципе о наследовании анализаторов от LexicalScanner.
*/

package proc.Source.Assembler

import proc.Interop.FileWriter
import proc.Text.CharReader
import proc.Text.Utf8

/**
 * AssemblerScanner.
 * TODO Варианты для переименования: Amd64AssemblerScanner,
 * TODO т.к. хрен его знает можно ли другие ассемблеры представить одинаково.
 */
class AssemblerReader {

	private var _reader: CharReader

	private var _writer: FileWriter
	//private var _utf8: Utf8

	init {
	}

	constructor(reader: CharReader) {
		_reader = reader
		_writer = FileWriter("debug.txt")
		//_utf8 = Utf8(null, _writer)
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
			//_utf8.WriteChar(symbol)

			return true
		}

		return false
	}
}
