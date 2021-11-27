# Kaleido 
Kaleido is supposed to be a toy language that I'm implementing in accordance to the [LLVM tutorial](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl01.html).
My aim is to learn the LLVM infrastructure and APIs effectively.

The original tutorial notes that it doesn't the "best engineering practices" to teach the more important concepts - such as how to implement a lexer. In contrast to this, I intend to maintain as much readability as possible.

I'm also not implementing things the tutorial way to get a feel for things myself.
## Update [Nov 27, 2021]
Somehow, I can't even get the code to compile! 
C++ compilers are so bloody stuck in the past that they do not allow for simple cyclic dependencies in type definitions. 
This lead to me using all sorts of `class DeclarationOnly;` 
hoping it would compile. But oh goodness! Clang really tried, but even that brave soul couldn't. 
What's worse is that all this time, Clion _was_ able to work with these cyclic type definitions perfectly fine!
Literally _every_ compiler allows this! 😭😭😭😭
I'll do this whole thing again but in the _much better_ alternative : Rust. 
I wish I had known Rust earlier when I started the project.
Aight, I'm out, peace!