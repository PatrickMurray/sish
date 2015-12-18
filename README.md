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


