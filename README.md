# Minishell [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)
[![Build Status](https://travis-ci.com/Ant0wan/Minishell.svg?branch=master)](https://travis-ci.com/Ant0wan/Minishell)

An implementation of some a simple start of a **shellscript** [a 42 project].

This project aims to get familiar with some of the core of the Unix system and explore an important part of the system’s API: process creation and synchronisation.

It implies to code in the cleanest and simplest manner


## Description

```
./include:
builtins.h error.h    input.h    job.h      lexer.h    path.h     prompt.h

./src:
error.c input   job     lexer   main.c

./src/input:
input.c  path.c   prompt.c

./src/job:
README.md             builtins.c            builtins_dispatcher.c job.c

./src/lexer:
lexer.c
```

## Architecture

Organized in modules.

The following is the main steps in the minishell workflow:

- Input Stream

- Lexical Analysis

- Parsing

- Dispatcher

- Dispatcher

## General Architecture

```
hello
```


## Lexical Analysis

After the input stream has been capture. A raw string is passed to `function` for a lexical analysis. A process of tokenization takes place.

> Each token is stored in a node of a linked-list.
> Each token will be executed in a fork or as a builtin after been dispatched.

input sample : ls -l -- file repo ; echo $? ; env -i ls ; coco ";s;s'"

Linked-list containing the tokens :
```
		 ---------------------------------
		|		Command 1
		| bin:
		|
		|
		|
		 ---------------------------------




```

And this will produce a flow chart:

## Usage

```shell=
git clone --recurse-submodules https://github.com/Ant0wan/Minishell.git
```

