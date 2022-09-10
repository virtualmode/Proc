package proc.Interop

import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import kotlin.math.log2

/**
 * Файловый поток для записи.
 */
class FileWriter(fileName: String): Writer {

	private var _handle: File
	private var _outputStream: FileOutputStream

	init {
		_handle = File(fileName)
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
		_outputStream.close()
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
