# Get Next Line

![C](https://img.shields.io/badge/language-C-blue.svg)

### Overview
C function that returns a line read from a file descriptor. Part of the 42 curriculum and designed to integrate with a custom [**libft**](https://github.com/biertisch/libft).

---
### Features

* Reads a line from a **file** or **standard input**.
* Returns `NULL` on EOF or error.
* Lines include the terminating `'\n'` character if present.
* **Adjustable buffer size** via `-D BUFFER_SIZE=n`.
* Supports **multiple file descriptors simultaneously** (bonus).
* **Tester** (extra): sample data and a simple shell script that tests:
	* Mandatory and bonus functions
	* Multiple files and standard input
	* Various buffer sizes (valid and invalid)

---
### Installation

```
git clone https://github.com/biertisch/get_next_line.git
```

---
### Usage

Function prototype:
```
char	*get_next_line(int fd);
```
Example:
```
int fd = open("myfile", O_RDNLY);
char *line = get_next_line(fd);
```

Integrated in [**libft**](https://github.com/biertisch/libft).


To run the tester:
```
./test/test.sh			# mandatory
./test/test.sh bonus	# bonus
```

---
### About 42

42 is a computer science school founded in Paris in 2013. It follows a project-based, peer-to-peer pedagogy focused on low-level programming and algorithmic thinking.

---
### License & Contact

This repository is open for learning and reuse. Contributions, suggestions, and discussions are welcome — feel free to open an issue or reach out.