package proc.Source.Symbol

/**
 * Информация о зарезервированном слове.
 */
class Keyword {

	public var Symbol: Type

	public var Identifier: proc.Text.String?

	init {
		Symbol = Type.Unknown
		Identifier = null
	}
}
