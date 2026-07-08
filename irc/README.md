# ft_irc - Serveur IRC en C++98

Un serveur IRC (Internet Relay Chat) écrit en C++98, conforme au protocole IRC (RFC 2812).

## Compilation

```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et l'exécutable
make re     # Recompile entièrement
```

## Utilisation

```bash
./ircserv <port> <password>
```

- **port** : numéro de port TCP (1-65535) sur lequel le serveur écoute
- **password** : mot de passe requis pour se connecter au serveur

### Exemple

```bash
./ircserv 6667 mypassword
```

## Connexion avec un client IRC

### Avec irssi
```
/connect 127.0.0.1 6667 mypassword
```

### Avec WeeChat
```
/server add local 127.0.0.1/6667 -password=mypassword
/connect local
```

### Avec nc (netcat)
```bash
nc 127.0.0.1 6667
PASS mypassword
NICK monpseudo
USER monuser 0 * :Mon Nom
JOIN #general
PRIVMSG #general :Hello tout le monde!
```

## Commandes supportées

| Commande | Description |
|----------|-------------|
| `PASS`   | Authentification par mot de passe |
| `NICK`   | Définir/changer son nickname |
| `USER`   | Définir son username et realname |
| `JOIN`   | Rejoindre un ou plusieurs channels |
| `PART`   | Quitter un ou plusieurs channels |
| `PRIVMSG`| Envoyer un message (channel ou privé) |
| `KICK`   | Expulser un utilisateur d'un channel (op) |
| `INVITE` | Inviter un utilisateur dans un channel (op) |
| `TOPIC`  | Voir/modifier le topic d'un channel |
| `MODE`   | Modifier les modes d'un channel (op) |
| `QUIT`   | Se déconnecter du serveur |
| `PING`   | Vérifier la connexion (keepalive) |

## Modes de channel

| Mode | Description |
|------|-------------|
| `+i` | Invite-only : seuls les utilisateurs invités peuvent rejoindre |
| `+t` | Topic restreint : seuls les opérateurs peuvent changer le topic |
| `+k` | Clé : un mot de passe est requis pour rejoindre le channel |
| `+o` | Opérateur : donne/retire le statut opérateur à un membre |
| `+l` | Limite : définit un nombre maximum de membres |

### Exemples de MODE
```
MODE #chan +i           # Active le mode invite-only
MODE #chan +k secret    # Définit le mot de passe "secret"
MODE #chan +o nick      # Donne le statut opérateur à nick
MODE #chan +l 10        # Limite le channel à 10 membres
MODE #chan -it          # Retire invite-only et topic restreint
```

## Architecture technique

```
src/
├── main.cpp       # Point d'entrée, validation des arguments
├── Server.cpp     # Boucle principale (poll), gestion des connexions
├── Commands.cpp   # Implémentation des commandes IRC
├── Client.cpp     # Gestion d'un client (buffers, état)
└── Channel.cpp    # Gestion d'un channel (membres, modes)

includes/
├── Server.hpp     # Déclaration de la classe Server
├── Client.hpp     # Déclaration de la classe Client
└── Channel.hpp    # Déclaration de la classe Channel
```

## Points techniques clés

- **Un seul poll()** : toute la multiplexation I/O passe par un unique appel à `poll()`
- **Non-bloquant** : tous les fd sont en mode `O_NONBLOCK` via `fcntl()`
- **Buffer d'envoi** : les messages sont stockés dans un buffer par client et envoyés uniquement quand `POLLOUT` est signalé par `poll()` — le serveur ne bloque jamais
- **Buffer de réception** : les commandes partielles sont accumulées jusqu'à réception d'un `\r\n`
- **Pas de fork** : tout est géré dans un seul processus
- **Gestion des signaux** : arrêt propre avec `SIGINT` (Ctrl+C) et `SIGTERM`

## Auteur

Maxime Martin - 42
