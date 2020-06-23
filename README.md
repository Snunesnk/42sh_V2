# 42sh [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d9485b7923204fa3b69323aee56e4506)](https://www.codacy.com/manual/antoinepaulbarthelemy/42sh?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ant0wan/42sh&amp;utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.org/Ant0wan/42sh.svg?branch=master)](https://travis-ci.org/Ant0wan/42sh)

An implementation of a small **shell** [a 42 project].

This project follows [21sh](https://github.com/Ant0wan/21sh) and aims at getting a better grasp of the parsing theories, job control and general programming in Unix environment.




---

## Demo

[![asciicast](https://asciinema.org/a/pwgqLz2bphIzeWLxUZmDp6TyJ.svg)](https://asciinema.org/a/pwgqLz2bphIzeWLxUZmDp6TyJ)



---

#### Debugging

Detect leaks and runtime errors:
```shell
valgrind --leak-check=full --track-origins=yes ./21sh
```

Monitor subshells and child processes:
```shell
ps -o stat,pid,pgid,ppid,sid,tpgid,comm
```

Trace process signals and status updates:
```shell
strace -e 'trace=!all' bash --posix
```

Locate source of bug:
```C
ft_printf("%s line: %d : e_invalid_input\n", __FILE__, __LINE__); //DEBUGG
```
