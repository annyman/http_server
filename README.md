# 🌐 Tiny HTTP Server

A minimal HTTP server written from scratch in C, using nothing but raw TCP sockets. No frameworks, no dependencies — just syscalls. Perfect for understanding how HTTP really works under the hood. 🛠️

---

## ✨ Features

- 🔌 **Raw sockets** — built directly on `socket()`, `bind()`, `listen()`, `accept()`
- 📡 **Listens on port `8080`** on all interfaces (`INADDR_ANY`)
- 🧠 **Parses requests** — extracts method, path, and protocol
- 📦 **Reads request bodies** after the `\r\n\r\n` header terminator
- 🛑 **Graceful shutdown** — send a body of `close` and the server exits
- 💬 **Responds** to every request with `HTTP/1.1 200 OK` → `Got message!`

---

## 📁 Project Structure

```
http_server/
├── src/
│   └── main.c       # The whole server
├── include/         # (headers, currently empty)
├── bin/             # Compiled binary lands here
├── justfile         # Build recipes
└── README.md
```

---

## ⚙️ Requirements

- 🧰 A C compiler (`clang`, set in the `justfile`)
- 🚀 [`just`](https://github.com/casey/just) — a modern `make` alternative

Install `just`:

```sh
# Cargo
cargo install just

# Arch
sudo pacman -S just

# macOS
brew install just
```

---

## 🏗️ Build & Run

```sh
just build    # 🔨 compile → bin/http_server
just run      # ▶️  build and start the server
just clean    # 🧹 remove build artifacts
just rebuild  # ♻️  clean + build
```

Or compile manually:

```sh
clang -Wall -Wextra -O2 -Iinclude src/*.c -o bin/http_server
./bin/http_server
```

---

## 🧪 Try It Out

In another terminal, send a request:

```sh
curl -i -X POST http://localhost:8080/hello -d "hi there"
```

Response:

```http
HTTP/1.1 200 OK
Content-Length: 2

Got message!
```

Stop the server by sending `close` as the body:

```sh
curl -X POST http://localhost:8080/ -d "close"
```

The server logs `[*] Close requested` and shuts down cleanly. 👋

---

## 🔍 How It Works

1. **`socket(AF_INET, SOCK_STREAM, 0)`** — ask the kernel for a TCP socket.
2. **`bind()`** — attach it to port `8080` on all interfaces.
3. **`listen()`** — mark it as accepting connections (backlog of 128).
4. **`accept()`** — block until a client connects.
5. **`read()`** — pull up to 500 bytes of the request into a buffer.
6. **`sscanf()`** — parse `METHOD PATH PROTOCOL` from the request line.
7. **`strstr()`** — find `\r\n\r\n` to locate the body.
8. **`write()`** — send the canned response, then `close()` the client.

Repeat until the loop sees `close` in the body. 🔁

---

## ⚠️ Limitations (by design)

This is a **learning project**, not production software:

- 🧵 Single-threaded — one client at a time
- 📏 500-byte request buffer — no large bodies
- 🗂️ No routing, static files, or real headers
- 🔒 No TLS, timeouts, or error handling beyond basics
- 🧪 No tests (yet)

Great starting point for exploring concurrency, HTTP parsing, and static file serving. 🌱

---

## 📜 License

MIT — do whatever you like. Attribution appreciated. ❤️

---

## 👤 Author

**annyman** ✍️
📧 [annyman.81194@protonmail.com](mailto:annyman.81194@protonmail.com)
