# Telephone Directory - Static C Version

A small command-line telephone directory written in C.

The project keeps the original fixed-size array approach and text-file persistence while repairing the main correctness and safety problems in the old implementation.

## Features

- Add one or several contacts
- Search contacts by identifier
- Modify contacts
- Delete contacts
- Sort contacts by name and first name
- Maintain favorites and blocked-contact lists
- Save and reload data from text files

## Requirements

- A C11-compatible compiler such as GCC
- `make` is optional; the project can also be compiled directly with GCC or opened with the existing Code::Blocks project file

## Build

Using Make:

```sh
make
```

Or directly with GCC:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic main.c contact.c -o contact
```

## Run

Linux/macOS:

```sh
./contact
```

Windows with GCC/MinGW:

```sh
contact.exe
```

## Tests

The tests use only the C standard library and `assert()`.

```sh
make test
```

Or compile them directly:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic test_contact.c contact.c -o test_contact
./test_contact
```

## Data files

The application stores local data in:

- `repertoire.txt`
- `favoris.txt`
- `blacklist.txt`

These files are generated at runtime and are ignored by Git.

The original whitespace-separated file format is preserved, so text fields such as names, streets and cities are currently single-word values.

## Project constraints

This project intentionally stays simple:

- C only
- C standard library only
- Fixed arrays with a maximum of 100 entries per list
- Plain text persistence
- No external libraries
- No database
- No GUI
