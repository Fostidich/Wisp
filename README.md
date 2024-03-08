# Wisp

## Overview
This password hash generator is a simple application that allows users to generate a secure 
hash based on a combination of a provider, username, a token, and personal secret key.
This hash can be used as a password without the need to store or encrypt, 
eliminating synchronization problems across devices. By generating the same hash each time,
users can authenticate themselves without the need to remember complex passwords.

## Features
- Hash Generation: generate a secure hash based on provider, username, a token, and personal secret key.
- Easy Authentication: use the generated hash as a password for authentication.
- No Storage Required: eliminate the need to store or encrypt passwords, enhancing security.

## Usage

### General Actions

- `wisp -h` or `wisp --help`: show help for the command.
- `wisp -l` or `wisp --list`: access stored data.

### Generating Hash

To generate a hash:

```bash
wisp get -p <provider> -u <username>
```

Optional flags:
- `-h, --hash <hash mask>`: use a custom hash mask for generation.
- `-n, --update <update number>`: use a custom update number for generation.
- `-c, --clipboard`: save the hash to clipboard without printing it.

### Setting Custom Provider-Username Info

To set custom provider-username info:

```bash
wisp set -p <provider> -u <username> -h <hash mask> -n <update number> -a "<note>"
```

Optional flag:
- `-r, --remove`: removes an entry from the list.

### Global Actions for Non-Custom Generations

To set global parameters for non-custom generations:

```bash
wisp glob -h <hash mask>
```
```bash
wisp glob -t -g
```

Optional token actions:
- `-t, --token`: private token actions.
    - `-c, --change <token>`: set a new private token.
    - `-g, --generate`: a new private token is generated.
    - `-s, --show`: the current private token is shown.


## Help
Click [here](assets/help-text/help.txt) for command list

## Example
Click [here](assets/help-text/helpExample.txt) for command examples

- - -
###### Code made by Francesco Ostidich
