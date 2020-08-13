# TypeScript

O único ponto que me faz preferir TypeScript a Javascript é a produtividade que
ela dá. Ao colocar o tipo nas coisas, você ajuda a IDE a te ajudar. Eu não
tenho mais paciência pra ficar lendo documentação fulêra das bibliotecas ou
ficar caçando implementação das classes na mão. O `Ctrl+click`/`Ctrl+space` da IDE
serve pra isso. E se a IDE não está ajudando, então é melhor programar no
notepad que pelo menos abre mais rápido.

E o interessante é que eu falo de produtividade, mas eu acho a configuração
inicial de um projeto com Node muito trabalhosa. Uma ruma de builders, uma ruma
de gerador de código, uma ruma de biblioteca pra coisa besta, etc. Eu quero
rodar poucos comandos e já ter um projeto base pra eu começar a fuçar. Por isso
eu acabo criando vários scripts pra essas coisas. Dá trabalho demais ficar
repetindo comandos.

E dito isso, segue alguns "guias" de como iniciar um projeto com TypeScript e
seus birimbelos.

## Setup

Eu vou colocar alguns scripts em [scripts](scripts) para fazer o setup dessas
besteiras.

### Yarn

Para iniciar um projeto com Yarn, basta um `yarn init -y`, mas eu normalmente
uso `yarm init -p -y` e modifico depois o que precisar.

### TypeScript

Rodou o Yarn? Agora é a vez do TypeScript. Resumindo:

```sh
yarn add -D typescript
yarn tsc --init
```

E depois eu normalmente mexo no `outDir` e apago o que não preciso.

### Express

Configurou o TypeScript? Agora começa as besteiras...
Normalmente só precisa instalar o Express e o editor vai pedir pra ir
configurando o resto, mas segue o que normalmente eu instalo.

```sh
yarn add express
yarn add -D ts-node-dev @types/express
```

o `ts-node-dev` é só pra reiniciar o servidor do Express caso algum arquivo
seja modificado (Um `Cima+Enter` a menos \o/).

Depois disso eu crio um novo script no `package.json` parecido com isso
`"ts-node-dev --respawn --transpile-only <arquivo.ts>"` e defino o `outDir`
para `./dist`.

Depois eu escrevo um `app.ts` e rodo o script do definido no `package.json` pra
iniciar o servidor.
