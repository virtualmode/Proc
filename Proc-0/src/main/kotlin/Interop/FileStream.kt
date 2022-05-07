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

import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import kotlin.math.log2

// Если использовать interface segregation, то может и не будет смысла в объединённом интерфейсе.
// Также есть идея объединений для безымянных композиций интерфейсов и др. типов.
//class Stream: public Reader, public Writer, public Seeker {
//};

/**
 * Файловый поток.
 */
class FileStream(fileName: String): Reader, Writer {

	private var _handle: File
	private var _inputStream: FileInputStream
	private var _outputStream: FileOutputStream

	init {
		_handle = File(fileName)
		_inputStream = _handle.inputStream()
		_outputStream = _handle.outputStream()
	}

	companion object {

		/**
		 * Compiler is not support state logic.
		 * TODO Эту фигню надо будет заменить таблицей.
		 */
		fun BaseToBytes(baseObj: Int): Int {
			return log2(baseObj as Double) as Int / 8
		}
	}

	fun Close() {
		_inputStream.close()
		_outputStream.close()
	}

	override fun Read(destination: Writer): Any {
		TODO("Not yet implemented")
	}

	/**
	 * Пока что тип данных будет выглядеть как base[exponent][exponent][..].
	 * @param baseObj Тип данных, основание, как раз и представляющий количество состояний.
	 * @param destination Содержит указатель на место, в которое будет записано states состояний.
	 */
	override fun Read(destination: Any, baseObj: Any): Any {
		return _inputStream.read(destination as ByteArray, 0, BaseToBytes(baseObj as Int))
	}

	override fun Write(source: Reader): Any {
		TODO("Not yet implemented")
	}

	override fun Write(source: Any, baseObj: Any): Any {
		var byteCount: Int = BaseToBytes(baseObj as Int)
		_outputStream.write(source as ByteArray, 0, byteCount)
		return byteCount
	}
}
