# Problem Set 1

## Amelia Macdonald

**In plain English:** 

`#include <stdio.h>`
>Bring over the file `stdio.h `, there's some stuff in it I might want to reference later

`int main() {}`
>Everything in the curly braces is the code I want to run

`printf("Hello, World!\n");`
>Print the text in the double quotes and put a line break at the end

--

**Questions:**

1. What is the code doing?

 	The code is initialized with `#include <stdio.h>`. This includes various standard input and output functions/macros, including `printf()` that is used in this code. 
 	
 	`int main()` is a function that is standard for all C code. It is where the code will begin to execute, contained in the following curly braces. `int` declares that the `main()` function will return an integer; this integer will be 0 upon successful execution of the code. 
 	
 	`printf()` will make the contents of the parentheses print to the terminal. In `"Hello, World!\n"`, the double quotes are ignored as they suggest their contents are a string (plain text). All punctuation that is otherwise syntax in C is ignored and taken literally, with the exception of `\` and its modifier. In this case, `\n` is a line break, forcing a paragraph break at the end of the code.
 	
 	Everything preceded by `//` (until a line break) or contained within `/*` to `*/` is a comment and is not run.

2. What programming elements are used in the code (e.g., comments)?

	Element | Use | Syntax
	:--|:--|:--
	Comment | Notekeeping, code that is not run | `//` to line break<br> `/*` to `*/`
	Header File | Includes files whose contents can<br> be used thoughout the main code | Preprocessor directive: `#include`<br> Points to file: `<>`
	Function | Executes code withing a <br> predetermined framework | Functions can include a data type<br> they return upon successful completion<br> with a precursor: `int`<br> Function: `functionName()`
	String | Text to be taken literally (ignore<br> syntax)<br> **Some exceptions: see below* | `"Text goes here!"`
	Line break | Forces a paragraph break<br> Syntax still works within a string | `\n`

3. What is the result of compiling and running the program?

	The program prints `Hello, World!` to the terminal.

4. What happens if you change the text inside double quotes (") within the printf function to something else?

	The text you replace it with will print to the console instead
	
	**As long as you save, recompile, and run the code again*