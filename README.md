![ClarityComesFirst.jpg](https://bitbucket.org/repo/na6B6g/images/1990121355-ClarityComesFirst.jpg)

# 1 - Clarity comes first

# 2 - General naming rules

## 2.1 Classes/Structures naming:
Sorted by prioritization  

|Prefix | Meaning | Example |
| ----- | ------- | ------- |
| **I~** | Interface class aka virtual pure of declarations only (no body at all) | IWindowHandle describes the public interface that a Window handle system must implement |
| **A~** | Abstract class aka pure virtual with some body definitions | Not yet |
| **The~** | Unique instance class only | TheMemoryManager is a unique instance supposed to handle the others allocators |
| **C~** | Standard class (can be instantiated, destroyed, inherited...) | CCamera is classic OO class |

Remark: When the class is an Interface, the file that holds it must be named ~Interface and the implementation file must be named as the interface file but without the 'Interface' (so ~ )


## 2.2 Variables naming:
Think about IntelliSense...  

|Prefix | Meaning |
| ----- | ------- |
| **a_~** | Argument. In functions, name the arguments with this prefix (**In source .cpp files only!!!** use the same name in the header declarations without the prefix) |
| **m_~** | Member class variable (as french "attributs"). Each this-(>/.)m_var must beginning with m_! |
| **g_~** | Global variable (static when also a member). |

:no_entry: Please, don't use names like `dyInt a;` even in formulas, prefer explicit and long names!  
(Math language is very poorly documented/typed with too much of obscure syntax!!!)

```
