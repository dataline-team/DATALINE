# CONTRUBUTE.md

## Description

This file describes style of all the project

## Code

### Functions

```c++
void functionName();
int sum(int a, int b);
```

### Variables

```c++
int a;
int var_for_smth = 0;
string ip_addres;
```

### Class names

```c++
class MyClass
{

};

class Class
{

};
```

## Commits

It is better to use short commits that describes only one change

### Commit structure

```git
[Part of programm][Update|Add|Remove|Fix...etc] <commit_message>
```

### Examples

```git
[Parser][Add] Parser for 'select' is added

[Database][Fix] Issue #123

[Console][Add] Command 'create'
```

## Pull requests

You can make pull request for issue, trello task or the feature you wont to add

### Branch name

Branch name should contain your full name and header of task or number of issue.

```git
<first_name>.<last_name>_<header-or-number-or-your-own>
```

### Example

```git
mykhailo.didur_iss123
volodymyr.makotkin_code-style
```

### Description of pull request

just describe what you did in such style.

```git
Changes:
- did this
- added smth
...
```
