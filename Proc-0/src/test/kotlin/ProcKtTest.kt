import org.junit.jupiter.api.Assertions.*

internal class ProcKtTest {

	@org.junit.jupiter.api.BeforeEach
	fun setUp() {
	}

	@org.junit.jupiter.api.AfterEach
	fun tearDown() {
	}

	@org.junit.jupiter.api.Test
	fun sum() {
		val expected = 42
		assertEquals(expected, proc.sum(0, 42))
	}
}
