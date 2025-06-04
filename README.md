# 🛰️ minitalk

**minitalk** is a small LINUX-based messaging project developed as part of the 42 Network curriculum.

This project demonstrates how two separate processes can communicate using POSIX signals — specifically SIGUSR1 and SIGUSR2 — to transmit characters one bit at a time. The purpose is not to build a production-ready application, but to practice and understand key system-level programming concepts such as:

-	**Signal handling** with `signal`
-   **Asynchronous communication**
-   **Process synchronization**
-   **Bit-level data transmission**

Through this project, I learned how to use signals to transmit data between processes, how to implement a basic communication protocol from scratch, and how to deal with the limitations of signal-based messaging.
It helped me get more comfortable with low-level programming in C and understand the basics of inter-process communication.

---

### 🛠️ System Functions Used

```c
kill() /* sends a signal to another process */
signal() /* Defines a handler for a spesific signal */ 
write()  /* Writes data to given filedescriptors (like stdout) */
usleep() /* Pauses the program for a given nummbe of microseconds */ 
exit()  /* Terminates the program with a status code */
getpid()  /* Returns the process id (PID) of the current process */
pause() /* suspends the program until a signal is received */
```
---

### ⚙️ Compilation

To compile the project, simply run:

```bash
make
```
This will create two executables

	•	server
	•	client

### 🧪 Usage

First, run the server:

```bash
./server
```

It will print its PID to the standard output. For example:

```
SERVER PID: 12345
```
Then, in another terminal, run the client with the server’s PID and your message as arguments:

```bash
./client 12345 "hello from client"
```
