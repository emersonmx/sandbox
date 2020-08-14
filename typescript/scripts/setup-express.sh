#!/bin/bash
set -euo pipefail
IFS=$'\n\t'

if [[ "$(ls -A)" ]]
then
    echo "Directory is not empty!"
    exit 1
fi

yarn init -p -y
yarn add -D typescript ts-node-dev @types/express
yarn add express
yarn tsc --init

mkdir -p src
cat > src/app.ts << EOF
import express from 'express';

const app = express();

app.get('/', (req, res) => {
    res.send('Hello World!');
});

const port = 3000;
app.listen(port);
console.log(\`Running on http://localhost:\${port} (Press CTRL+C to quit)\`);
EOF

sed -r -i \
    -e '/"main":/ d' \
    -e '/"private":/ a\
        "scripts": {\
            "dev:server": "ts-node-dev --respawn --transpile-only src/app.ts"\
        },' \
    package.json

sed -r -i \
    -e '\#//\s*"outDir":.*# s##"outDir": "./dist",#' \
    -e '\#^\s*//# d' \
    -e 's#/\*.*\*/##g' \
    -e '/^\s*$/ d' \
    tsconfig.json

npx prettier --write package.json tsconfig.json src/app.ts
