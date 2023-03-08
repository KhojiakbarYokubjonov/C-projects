#### It implements the Beaufort cipher for encrypting messages.
It requires a key for encryption. `beaufort.c` expects that the first line it gets on
standard input will be the value of the key (a char sequence with only upper-case alphabetical letters). All
remaining lines it can expect will be input strings to encrypt. The program ends when it encounters its first
empty input line. The program also expects that all of the text coming from standard input will be
upper-case. If it sees a space in a message to encrypt, it will be left-as-is.

