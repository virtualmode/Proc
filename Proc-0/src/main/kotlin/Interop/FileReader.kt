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
class FileReader(fileName: String): Reader {

	private var _handle: File
	private var _inputStream: FileInputStream

	init {
		_handle = File(fileName)
		_inputStream = _handle.inputStream()
	}

	companion object {

		/**
		 * Compiler is not support state logic.
		 * TODO Эту фигню надо будет заменить таблицей.
		 */
		fun BaseToBytes(baseObj: Int): Int {
			return log2(baseObj.toDouble()).toInt() / 8
		}
	}

	fun Close() {
		_inputStream.close()
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
}
