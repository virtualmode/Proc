// To import multiple packages use `import org.jetbrains.grammarkit.tasks.*` instead.
import org.jetbrains.grammarkit.tasks.GenerateLexer
import org.jetbrains.grammarkit.tasks.GenerateParser

plugins {
    id("java")
    id("idea")
    id("org.jetbrains.grammarkit") version "2021.1.2"
    id("org.jetbrains.intellij") version "1.8.0"
    id("org.jetbrains.kotlin.jvm") version "1.7.20" // Alias is `kotlin("jvm") version "1.7.20"`.
}

group = "proc"
version = "1.0.0"

repositories {
    mavenCentral()
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-reflect:1.7.20")
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.9.0")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.9.0")
}

// Configure Gradle IntelliJ Plugin
// Read more: https://plugins.jetbrains.com/docs/intellij/tools-gradle-intellij-plugin.html
intellij {
    version.set("2021.1")
    plugins.set(listOf("java", "gradle", "gradle-java"))
    downloadSources.set(true)
    updateSinceUntilBuild.set(false)
}

sourceSets {
    getByName("main").java.srcDirs("src/gen")
}

tasks {
    // IDE version limit.
    /*patchPluginXml {
        sinceBuild.set("213")
        untilBuild.set("223.*")
    }*/

    val generateProcLexer by registering(GenerateLexer::class) {
        source = "src/main/java/proc/Proc.flex"
        targetDir = "src/gen/proc/"
        targetClass = "ProcLexer"
        purgeOldFiles = true
    }

    val generateProcParser by registering(GenerateParser::class) {
        dependsOn(generateProcLexer)

        source = "src/main/java/proc/Proc.bnf"
        targetRoot = "src/gen"
        pathToParser = "/proc/parser/ProcParser.java"
        pathToPsiRoot = "/proc/psi"
        purgeOldFiles = true
    }

    compileKotlin {
        dependsOn(generateProcParser)
    }

    compileJava {
        dependsOn(generateProcParser)
    }

    test {
        useJUnitPlatform()
    }
}
