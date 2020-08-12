import express from 'express';

const app = express();

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

interface User {
    id: number;
    name: string;
    email: string;
}

let users = Array<User>();

app.get('/users', (_, res) => {
    res.json(users);
});

app.post('/users', (req, res) => {
    let id = users.length + 1;
    let user: User = { id, ...req.body };
    users.push(user);
    res.status(201).json(user);
});

app.get('/users/:id', (req, res) => {
    let user = users.find((e) => e.id == parseInt(req.params.id));
    if (!user) {
        res.sendStatus(404);
        return;
    }

    res.json(user);
});

app.put('/users/:id', (req, res) => {
    let index = users.findIndex((e) => e.id == parseInt(req.params.id));
    if (index == -1) {
        res.sendStatus(404);
        return;
    }

    let user = users[index];
    user = { ...user, ...req.body, id: user.id };
    users[index] = user;
    res.json(user);
});

app.delete('/users/:id', (req, res) => {
    let index = users.findIndex((e) => e.id == parseInt(req.params.id));
    if (index == -1) {
        res.sendStatus(404);
        return;
    }

    users.splice(index, 1);
    res.status(204).send();
});

const port = 3000;
app.listen(port);
console.log('Running on http://localhost:%d ...', port);
