# ⚡ Monke-Shell

![C](https://img.shields.io/badge/C-17-blue?logo=c)
![Unix](https://img.shields.io/badge/Unix-Shell-brightgreen?logo=linux)
![License](https://img.shields.io/badge/License-MIT-purple)

A **lightweight Unix-style command-line shell** implemented in C to explore operating system fundamentals. Built with direct system calls for process management, file operations, and terminal interaction.

---

## 🚀 Features

### 🔧 Built-in Commands
- **Navigation**: `cd`, `pwd`
- **File operations**: `ls`, `mkdir`, `rmdir`, `rm`, `touch`, `cat`, `cp`, `mv`
- **System utilities**: `exit`, `clear`, `echo`, `help`
- **Color-coded `ls` output** (directories in blue, executables in red, files in green)

### 🎨 User Experience
- **Dynamic colored prompt** showing current working directory
- **Welcome banner** with system information (uses `figlet` if available)
- **Helpful command reference** via `help` command
- **Clean error messages** for invalid operations

### ⚙️ Core Functionality
- **Executes external commands** using `fork()` and `execvp()`
- **Basic argument parsing** for built-in commands
- **Proper error handling** for file operations and system calls
- **Direct implementation** of common Unix utilities in C

---

## ⚠️ Limitations

This is a learning project and does **NOT** support yet:
- Input/output redirection (`>`, `<`, `>>`)
- Piping (`|`)
- Command chaining (`&&`, `||`, `;`)
- Environment variable expansion
- Advanced argument parsing (e.g., `ls -l`)

---

## 🎯 Quick Start

### Prerequisites
```bash
# Standard Unix-like system (Linux/macOS)
# GCC compiler (usually pre-installed or available via package manager)
```

----

## Build & Run

### Clone & Build
```
git clone https://github.com/yourusername/monke-shell.git
cd monke-shell
gcc -o monke-shell *.c

# Start the shell
./monke-shell
```

---

## Usage Examples

### Built-in Commands
```bash
monke-shell > ls
monke-shell > cd /tmp
monke-shell > echo Hello World
monke-shell > help
```

### External Commands
```bash
monke-shell > date
monke-shell > whoami
monke-shell > ps
```

---

# 🏗 Architecture

```
Input Loop → Parser → Command Dispatcher
                     ↓
        Built-ins Handler   External Executor
                     ↓              ↓
            Direct C Functions   fork()/execvp()
```

## Core Components

- **commands.c** - Implementation of all built-in commands  
- **shell.c** - Main shell loop, banner, and prompt  
- **utils.c** - Input parsing and external command execution  
- **main.c** - Entry point  
- **shell.h** - Header with constants and function declarations  

# 🔬 Technical Details

## Process Management

- Uses `fork()` to create child processes  
- `execvp()` for external command execution  
- `wait()` to prevent zombie processes  

## File System Operations

- Direct system calls: `open()`, `close()`, `unlink()`, `mkdir()`, `rmdir()`  
- Directory traversal: `opendir()`, `readdir()`, `closedir()`  
- File metadata: `stat()` for type and permission checking  
- Navigation: `chdir()`, `getcwd()` for directory changes  

## Terminal Interaction

- ANSI escape codes for colored output  
- `fgets()` for safe input reading  
- Dynamic prompt with current working directory  

# 📚 Learning Outcomes

This project demonstrates:

- **Operating system concepts** - Process lifecycle, file systems, terminal I/O  
- **Systems programming** - Direct system call usage in C  
- **Shell fundamentals** - Command parsing, built-in vs external execution  
- **Memory and resource management** - Proper cleanup and error handling  

# 🤝 Contributing

This is a personal educational project. Potential extensions include:

- Adding redirection and piping support  
- Implementing environment variables  
- Adding command history functionality  
- Job control with background processes  

## Fork the repository

1. Create a feature branch  
   ```bash
   git checkout -b feature/your-feature
   ```

2. Commit your changes  
   ```bash
   git commit -m 'Add your feature'
   ```

3. Push to the branch  
   ```bash
   git push origin feature/your-feature
   ```

4. Open a Pull Request  

# 📄 License

Distributed under the MIT License. See `LICENSE` for more information.

---

**wiseMonke** - EEE Student & Software Developer  

![GitHub](https://img.shields.io/badge/GitHub-wiseMonke-black?logo=github)

---

