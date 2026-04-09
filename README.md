# Typing: A Terminal-Based Speed Test

**Typing** is a lightweight, minimalist typing speed trainer inspired by [Monkeytype](https://monkeytype.com/), built specifically for the command line. Test your WPM (Words Per Minute) and accuracy in your terminal environment.

---

## 🚀 Getting Started

### Prerequisites
* **CMake** (3.10 or higher)
* **C++ Compiler** (GCC, Clang, or MSVC)
* **Git**

### Installation & Building
To clone and build the application on macOS or Linux, run the following commands:

```bash
# Clone the repository
git clone https://github.com/Cibucya/typing.git
cd typing

# Configure and build
cmake -S . -B build
cmake --build build
```
---
### 🛠 Usage
Once the build is complete, the `SpeedTest` executable will be located in the `build/` directory.
### Run a Test

You can start a session by specifying the number of words you wish to type:

Bash

```
# General Usage
./build/SpeedTest [number_of_words]

# Examples
./build/SpeedTest      # Program will promt you at start
./build/SpeedTest 20   # 20-word session
```
