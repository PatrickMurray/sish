# sish - a simple hell

### synopsis
```bash
sish [-x] [-c command]
```

### collaboration

#### Neal Trischitta
- Implementation Research
- Token Evaluation
- Input / Output Redirection
- Pipelines
- Command Execution
- Testing & Debugging

#### Patrick Murray
- Argument Parsing
- SHELL Environment Variable
- Command Parsing and Tokenization
- Built-in Functions
- Variable Support (i.e. $$, $?)
- Background Commands
- Testing & Debugging
- NetBSD Portability

### testing


#### basic

```bash
$ ./sish 
sish$ echo $$
15101
sish$ ls
cd.c  command.c  echo.c  eval.c  Makefile  parser.c  README.md	sish  sish.c  sish.h
sish$ ls | wc -l
10
sish$ something
something: No such file or directory
sish$ echo $?
256
sish$ rm /etc/passwd
rm: remove write-protected regular file `/etc/passwd'? yes
rm: cannot remove `/etc/passwd': Permission denied
sish$ echo $?
256
sish$ exit
```

```bash
$ ./sish -c date
Thu Dec 17 22:30:21 EST 2015
```

```bash
$ ./sish -x
sish$ ls
+ ls
cd.c  command.c  echo.c  eval.c  Makefile  parser.c  README.md	sish  sish.c  sish.h
sish$ ls | wc -l
+ ls
+ wc -l
10
sish$ cd /tmp
+ cd /tmp
sish$ pwd
+ pwd
/tmp
sish$ cd
+ cd
sish$ pwd
+ pwd
/home/pmurray1
sish$ exit
+ exit
```



#### miscellaneous

```bash
$ ./sish 
sish$ ls -la >
-sish: '>' missing output source
sish$ ls -la <
-sish: '<' missing input source
sish$ ls -la >>
-sish: '>>' missing output source
sish$ ls -la >> dne
sish$ cat dne 
total 60
drwxr-xr-x+  3 pmurray1 student    14 Dec 17 22:41 .
drwxr-xr-x+ 10 pmurray1 student    24 Dec 17 22:35 ..
-rw-r--r--+  1 pmurray1 student  1171 Dec 17 12:57 cd.c
-rw-r--r--+  1 pmurray1 student  2639 Dec 17 22:22 command.c
-rw-r--r--+  1 pmurray1 student     0 Dec 17 22:41 dne
-rw-r--r--+  1 pmurray1 student   586 Dec 17 13:10 echo.c
-rw-r--r--+  1 pmurray1 student  5498 Dec 17 20:58 eval.c
drwxr-xr-x+  8 pmurray1 student    16 Dec 17 22:34 .git
-rw-r--r--+  1 pmurray1 student   598 Dec 17 21:33 Makefile
-rw-r--r--+  1 pmurray1 student   663 Dec 17 20:37 parser.c
-rw-r--r--+  1 pmurray1 student  1224 Dec 17 22:34 README.md
-rwxr-xr-x+  1 pmurray1 student 31384 Dec 17 22:27 sish
-rw-r--r--+  1 pmurray1 student  3075 Dec 17 20:35 sish.c
-rw-r--r--+  1 pmurray1 student   907 Dec 17 20:45 sish.h
sish$ wc -l < dne 
15
sish$ ls -1 >> dne 
sish$ cat dne 
total 60
drwxr-xr-x+  3 pmurray1 student    14 Dec 17 22:41 .
drwxr-xr-x+ 10 pmurray1 student    24 Dec 17 22:35 ..
-rw-r--r--+  1 pmurray1 student  1171 Dec 17 12:57 cd.c
-rw-r--r--+  1 pmurray1 student  2639 Dec 17 22:22 command.c
-rw-r--r--+  1 pmurray1 student     0 Dec 17 22:41 dne
-rw-r--r--+  1 pmurray1 student   586 Dec 17 13:10 echo.c
-rw-r--r--+  1 pmurray1 student  5498 Dec 17 20:58 eval.c
drwxr-xr-x+  8 pmurray1 student    16 Dec 17 22:34 .git
-rw-r--r--+  1 pmurray1 student   598 Dec 17 21:33 Makefile
-rw-r--r--+  1 pmurray1 student   663 Dec 17 20:37 parser.c
-rw-r--r--+  1 pmurray1 student  1224 Dec 17 22:34 README.md
-rwxr-xr-x+  1 pmurray1 student 31384 Dec 17 22:27 sish
-rw-r--r--+  1 pmurray1 student  3075 Dec 17 20:35 sish.c
-rw-r--r--+  1 pmurray1 student   907 Dec 17 20:45 sish.h
cd.c
command.c
dne
echo.c
eval.c
Makefile
parser.c
README.md
sish
sish.c
sish.h
sish$ wc -l < dne 
26
```


```bash
$ ./sish -x
sish$ ls
+ ls
cd.c  command.c  echo.c  eval.c  Makefile  parser.c  README.md	sish  sish.c  sish.h
sish$ ls -la | wc -l > dne
+ ls -la
+ wc -l > dne
sish$ cat dne 
+ cat dne
0
tal 62
drwxr-xr-x+  3 pmurray1 student    14 Dec 17 22:43 .
drwxr-xr-x+ 10 pmurray1 student    24 Dec 17 22:42 ..
-rw-r--r--+  1 pmurray1 student  1171 Dec 17 12:57 cd.c
-rw-r--r--+  1 pmurray1 student  2639 Dec 17 22:22 command.c
-rw-r--r--+  1 pmurray1 student     0 Dec 17 22:43 dne
-rw-r--r--+  1 pmurray1 student   586 Dec 17 13:10 echo.c
-rw-r--r--+  1 pmurray1 student  5498 Dec 17 20:58 eval.c
drwxr-xr-x+  8 pmurray1 student    16 Dec 17 22:34 .git
-rw-r--r--+  1 pmurray1 student   598 Dec 17 21:33 Makefile
-rw-r--r--+  1 pmurray1 student   663 Dec 17 20:37 parser.c
-rw-r--r--+  1 pmurray1 student  3227 Dec 17 22:42 README.md
-rwxr-xr-x+  1 pmurray1 student 31384 Dec 17 22:27 sish
-rw-r--r--+  1 pmurray1 student  3075 Dec 17 20:35 sish.c
-rw-r--r--+  1 pmurray1 student   907 Dec 17 20:45 sish.h

```
