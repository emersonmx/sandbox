# Express CRUD with array

This project is a simple API using Express. No database, design patterns or
anything. Just Express and nothing more.

## Setup

Run the following commands to install and start the Express server at
[http://localhost:3000](http://localhost:3000).

```sh
yarn
yarn dev:server
```

## Code

The code is the most simple possible. The "database" is just an `array` and it
doesn't have data validation at requests.

Here are the available routes:

```
GET /users
POST /users
GET /users/:id
PUT /users/:id
DELETE /users/:id
```

## Testing

Use any HTTP client that you like, but here I will use
[HTTPie](https://httpie.org/).

Examples:

```sh
# Create a user
http post http://localhost:3000/users name='John Doe' email=johndoe@example.com

# List all users
http get http://localhost:3000/users

# Show user with ID 1
http get http://localhost:3000/users/1

# Update the name of user with ID 1
http put http://localhost:3000/users/1 name="John"

# Delete user with ID 1
http delete http://localhost:3000/users/1
```

## Conclusion

This project is just a test to see how Express works. So nothing complex to see.
