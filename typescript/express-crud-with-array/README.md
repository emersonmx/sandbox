# Express CRUD with array

Esse projeto é apenas uma simples API usando Express. Nada de conexão com
banco, padrões de projeto, nem qualquer coisa complicada. Só vendo como
funciona o Express. Então vamos seguindo.

## Setup

Só rodar os comandos abaixo para instalar e iniciar o servidor na URL
http://localhost:3000.

```sh
yarn
yarn dev:server
```

## Implementação

A implementação foi o mais besta possível. O "banco" é apenas um `array` e não
há validação dos dados da requisão, mas isso não importa 😁.

Segue as rotas implementadas:

```
GET /users
POST /users
GET /users/:id
PUT /users/:id
DELETE /users/:id
```

## Testando

Você pode realizar as requisições usando o que quiser, mas aqui vou usar o
[HTTPie](https://httpie.org/).

Segue exemplos:

```sh
# Criar dois usuários
http post http://localhost:3000/users name='John Doe' email=johndoe@example.com

# Mostra todos os usuários
http get http://localhost:3000/users

# Mostra o usuário com id 1
http get http://localhost:3000/users/1

# Atualiza o nome do usuário com o id 1
http put http://localhost:3000/users/1 name="John"

# Apaga o usuário 1
http delete http://localhost:3000/users/1
```

## Conclusão

A lição desse projeto era apenas ver como funciona o Express. Então nada muito
complicado.
