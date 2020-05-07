# 42sh [![42](https://i.imgur.com/9NXfcit.jpg)](i.imgur.com/9NXfcit.jpg)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/d9485b7923204fa3b69323aee56e4506)](https://www.codacy.com/manual/antoinepaulbarthelemy/42sh?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ant0wan/42sh&amp;utm_campaign=Badge_Grade) [![Build Status](https://travis-ci.org/Ant0wan/42sh.svg?branch=master)](https://travis-ci.org/Ant0wan/42sh)

An implementation of a small **shell** [a 42 project].

This project follows [Minishell](https://github.com/Ant0wan/Minishell) and aims at getting a better grasp of the LL(1) parsing theory, job control and general programming in Unix environment.

---

#### Testing

```shell=
valgrind --leak-check=full --track-origins=yes ./21sh

ps -o stat,pid,pgid,ppid,sid,tpgid,comm

```





## Known bugs

Liste de bugs et description du comportement (du coup c'est pas forcement un bug ca peut etre une precision pour s'assurer que ca fonctionne).

```
Revoir l'ensemble du fonctionnement du shell avec env -i et env modifie:
- input (termcapabilities check)
- builtins: cd, env, export, historique, etc (ex: env -i HOME=okok puis un cd)

DONE => quotes: dans les heredoc, pas de quotes.
DONE => quotes: dans le subprompt venant du parser les quotes doivent etre fonctionnelles

DONE => autocompletion: dans le subprompt venant du parser la suggestion doit etre fonctionnelle, mais pas dans les heredoc. etc (comme un input de base).

DONE => autocompletions: suggestions dans cd dysfonctionnelles

cd: encore casse, cd -P /lib puis cd - faisait leaks. A tester avec un environnement modifier.

export: parsing de nom de variables (check POSIX, un nom de var ne doit pas commencer par un chiffre etc). Format de nom de variables : alpha ou underscore pour première lettre, puis alnum pour le reste
DONE => export: verifier tous les messages d'erreurs

env: peut produire des leaks dans certains cas, le comportement n'a pu etre reproduit mais la commande incriminee est: env cmd env

singaux: revoir toutes les valeurs de retour des signaux
signaux: filtrer messages suivant s'ils sont envoyes depuis la ligne de commande ou par le child
DONE => signaux: implementer CTRL Z et CTRL \ etc

DONE => job control: revoir le comportement des sousshells comme ls && cat &  ou   vim && ls -l &.

DONE => exit: revoir la gestion des arguments faite par exit ex: 9999999999999999999999999 etc.
DONE => exit: mettre en place une procedure pour ne pas quitter le shell lorsque des jobs sont en background.

fc: modification imprevu de fichier (je me souviens plus comment le bug etait produit).

historique:valid string in hist => enlever non-print char (a verifier si bash fait bien ca)

display: display prompt=> si il n'est pas print sur l'output il ne faut pas avancer le curseur (pourquoi pas ouvrir un fd 255 comme bash ?)

readline: Mauvais term mode (en fait c'est pas le term mode mais les termcapabilities a checker). Le terminal fonctionne meme si on change TERM normalement, a reverifier c'est dans tty.c terminal.c
```

Mauvais display d'erreur avec cd
Bug avec fc -s
Leak avec le fc quand mauvaise commande sur fc S
DONE => Écho ////// print toujours 2 /
Use after free in history
DONE => Ne pas inib dans les heredocs
Voir pour implementer les raccourcis clavier dans le mode insert de vi
