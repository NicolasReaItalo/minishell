# Minishell  
A [42 Paris](https://42.fr) Project  


Welcome to **Minishell**, a minimalistic yet powerful shell written entirely in **C**. 

This project is part of the curriculum at [42 Paris](https://42.fr), where the goal was to implement a fully interactive and functional Linux shell from scratch.  

---

### Features  

- **Command Parsing and Execution**:  
  Supports standard Linux commands with arguments and modifiers.  
- **Advanced Shell Operations**:  
  - **Pipes (`|`)**  
  - **Redirections (`>`, `<`)**  
  - **Here-docs (`<<`)**  
  - **Parentheses (`()`)**  
  - **Conditional Operators (`&&`, `||`)**  
  - **Simple Expansions (`*`)**  
- **Abstract Syntax Tree (AST)** for efficient parsing and execution logic.  

---

### Collaboration  

This project was developed in collaboration with [Thomas Joyeux](https://github.com/tomjoy75).  

- **My Contributions**:  
  - Designed and implemented the **parsing system** using an **Abstract Syntax Tree (AST)**.  
  - Developed the logic for **command execution** and **redirections**.  
- This journey taught me a great deal about **multi-processing**, **signals**, and the **Linux programming interface**.

---

### Getting Started  

1. **Clone the Repository**:  
   ```bash
   git clone https://github.com/username/minishell.git
   cd minishell
   ```
2. **Simply run make to compile the shell**:
```bash
make
```
3. **To launch the shell run**:
```bash
./minishell
```



   
