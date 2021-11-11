# Challenge server
This repository contains a server filled with challenges ranging from simple inspection of text to using shell programs and calculus.
It also contains a client to communicate with it.

## Installation
Run the *make install* command to create the output folder as follows:

```python
user@linux:$ make install
```

Then run the *make* command to build both the server and the client on the bin folder:

```python
user@linux:$ make
```

## Usage

To fully interact with the server, you must have two terminals opened. One to run the server and another one to run the client.
Note that both terminals must be on the bin folder before running the server or client.
Once located on the bin folder, run:

```python
user@linux:$ ./server
```

or

```python
user@linux:$ ./client
```

to run either the client or server.