# my_mini_shell

A small Unix-like shell written in C, supporting built-in commands, external
program execution, and a 10-entry command history with `!n` recall.

## Features

- Custom prompt: `user@miniShell$[YYYY-mm-dd HH:MM:SS]`
- Interactive loop with whitespace tokenization (tabs, multiple spaces)
- External commands via `fork()` + `execvp()` + `waitpid()`
  (absolute and relative paths supported)
- Built-in commands implemented in-process (no `exec`):
  - `cd [dir]` — change directory (`chdir`)
  - `pwd` — print working directory (`getcwd`)
  - `history` — list the last 10 commands
  - `!n` — re-run the n-th command from `history`
  - `exit` — leave the shell
- Error handling: command not found, wrong arguments, permission denied,
  `fork()` failure
- Clean exit on EOF (Ctrl+D); zombie processes are reaped

## Build & Run

    make
    ./minishell

Requires `gcc` (C11) and a POSIX system. No third-party dependencies.

## Example

    ->pwd
    /home/user
    ->echo hello world
    hello world
    ->history
    1   pwd
    2   echo hello world
    3   history
    ->!2
    hello world

## Limitations

- No pipes, redirection, or background jobs
- No quoting, globbing, or variable expansion
- `pwd` is limited to paths shorter than 100 characters

## Files

| File | Purpose |
|---|---|
| `main.c` | REPL loop and buffers |
| `basicFunction.c/.h` | prompt, tokenizing, command dispatch |
| `commands.c/.h` | built-in command table |
| `queue.c/.h` | 10-entry history ring buffer |
