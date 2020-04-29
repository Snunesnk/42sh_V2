# 21sh [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e1478850d3fe4d5e98656784d25de438)](https://www.codacy.com/manual/antoinepaulbarthelemy/21sh?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ant0wan/21sh&amp;utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.org/Ant0wan/21sh.svg?branch=master)](https://travis-ci.org/Ant0wan/21sh)


An implementation of a small **shell** [a 42 project].

This project follows [Minishell](https://github.com/Ant0wan/Minishell) and aims at getting a better grasp of the LL(1) parsing theory, job control and general programming in Unix environment.

---

#### Testing

```shell=
valgrind --leak-check=full --track-origins=yes ./21sh
```
