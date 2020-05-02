# 42sh [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d9485b7923204fa3b69323aee56e4506)](https://www.codacy.com/manual/antoinepaulbarthelemy/42sh?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ant0wan/42sh&amp;utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.org/Ant0wan/42sh.svg?branch=master)](https://travis-ci.org/Ant0wan/42sh)

An implementation of a small **shell** [a 42 project].

This project follows [Minishell](https://github.com/Ant0wan/Minishell) and aims at getting a better grasp of the LL(1) parsing theory, job control and general programming in Unix environment.

---

#### Testing

```shell=
valgrind --leak-check=full --track-origins=yes ./21sh
```
