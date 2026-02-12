# Clac - Project Overview

Clac is a **programmable RPN (Reverse Polish Notation) calculator** inspired by the HP48 series, written in **C++20**. It features a three-tier architecture with embeddable core libraries.

---

## Core Components

### 1. ClacEntity (Static Library)
The data type library containing 12 entity types derived from an abstract `Entity` base class:

| Type | Description |
|------|-------------|
| `BinaryEntity` | Binary/bitfield values |
| `ComplexEntity` | Complex numbers |
| `DirectoryEntity` | Named variable storage |
| `FloatEntity` | Floating-point numbers |
| `IntegerEntity` | Arbitrary-precision integers |
| `RationalEntity` | Rational numbers (fractions) |
| `StringEntity` | Text strings |
| `VectorEntity`, `MatrixEntity` | Linear algebra types |
| `ListEntity` | Collections |
| `ProgramEntity` | Stored programs |
| `LabeledEntity` | Tagged values |

The `Entity` base class (`Entity.hpp`) defines a polymorphic interface with:
- **Unary operations**: `abs()`, `sin()`, `cos()`, `sqrt()`, `neg()`, etc.
- **Binary operations**: `plus()`, `minus()`, `multiply()`, `divide()`, `power()`, etc.
- **Relational operations**: `is_equal()`, `is_less()`, etc.
- **Type conversions**: `to_float()`, `to_integer()`, `to_complex()`, etc.
- **File serialization**: `read()`, `write()`, `file_size()`

**Dependency**: Links against **SpicaCpp** (a git submodule providing `VeryLong` arbitrary-precision integers and other utilities).

### 2. ClacEngine (Static Library)
The execution engine coordinating computations:

- **`ClacStack`**: A `std::deque<Entity*>`-based stack with RPN operations (`push`, `pop`, `swap`, `dup`, `roll_up`, `roll_down`, etc.)
- **`WordStream` hierarchy**: Input abstraction with `StringStream`, `FileStream`, and `MasterStream` (a stack of streams for nested execution)
- **`actions.cpp/hpp`**: Built-in command implementations (stack manipulation, display modes, I/O)
- **`words.cpp/hpp`**: Word lookup and user-defined word management
- **`Global`**: Singleton-like access to the global stack and word source via `clac::global::the_stack()` and `clac::global::word_source()`

**Dependency**: Links against ClacEntity.

### 3. ClacConsoleUI (Executable: `clac`)
A scrolling text console interface:

- **Main loop** in `clac.cpp`: Displays top 8 stack levels → reads input → pushes to `MasterStream` → calls `process_words()`
- **Command dispatch**: Lookup tables (`binary_words[]`, `unary_words[]`, `action_words[]`) map word strings to `Entity` method pointers or action functions
- **Type coercion**: Uses `convert_table` for implicit type conversion between operands
- **Error handling**: Implements `error_message()` and `info_message()` callbacks required by ClacEntity

---

## Component Interactions

```
┌─────────────────────────────────────────────────────────────────┐
│                      ClacConsoleUI                              │
│  ┌─────────────┐    ┌─────────────────────────────────────────┐ │
│  │   main()    │───>│ process_words() loop                    │ │
│  └─────────────┘    │  - Reads from MasterStream              │ │
│                     │  - Dispatches to builtin/unary/binary   │ │
│                     │  - Pushes entities via get_entity()     │ │
│                     └───────────────┬─────────────────────────┘ │
└─────────────────────────────────────│───────────────────────────┘
                                      │
                 ┌────────────────────▼────────────────────┐
                 │              ClacEngine                 │
                 │  ┌────────────┐  ┌────────────────────┐ │
                 │  │ ClacStack  │  │ MasterStream       │ │
                 │  │ (deque)    │  │ (stack of streams) │ │
                 │  └──────┬─────┘  └────────────────────┘ │
                 │         │                               │
                 │  actions.cpp (do_dup, do_swap, etc.)    │
                 └─────────│───────────────────────────────┘
                           │
        ┌──────────────────▼───────────────────┐
        │           ClacEntity                 │
        │  Entity* polymorphic hierarchy       │
        │  - Arithmetic via virtual methods    │
        │  - Type conversion via convert_table │
        └──────────────────┬───────────────────┘
                           │
        ┌──────────────────▼───────────────────┐
        │           SpicaCpp                   │
        │  (VeryLong, etc.)                    │
        └──────────────────────────────────────┘
```

Data flow: User input → `StringStream` → `MasterStream` → `process_words()` → `Entity` operations → `ClacStack` → display.

---

## Deployment Architecture

**Build System**: CMake with presets for cross-platform builds:
- `windows-x64-debug`, `windows-arm64-debug` (MSVC/Ninja)
- `linux-clang-debug`, `macos-clang-debug` (Clang/Ninja)

**Build Steps**:
```bash
git clone --recurse-submodules https://github.com/pchapin/clac.git
cmake --preset <preset-name>
cmake --build --preset <preset-name>
```

**Output**: Single executable `clac` in `build/<preset>/`.

**External Dependencies**: None beyond a C++20-compliant compiler. SpicaCpp is vendored as a submodule.

**Documentation**: Doxygen for API docs; LaTeX for Tutorial, Reference, and Design documents.

---

## Runtime Behavior

1. **Initialization**: `SetUp` RAII class handles startup (debugging flag, future state reload).

2. **Main Loop** (`clac::Main`):
   - Display stack levels 1–8 with type abbreviations (e.g., `INT`, `FLT`)
   - Prompt `=> ` and read line via `getline()`
   - Wrap input in `StringStream`, push to `MasterStream`
   - Call `process_words()`

3. **Word Processing** (`process_words()`):
   - Pull next word from `MasterStream`
   - Check builtin tables (binary → unary → action)
   - If not builtin, attempt to parse as a literal via `get_entity()`
   - Push result to stack; handle exceptions gracefully

4. **Error Handling**: All Entity operations can throw `Entity::Error`. Exceptions are caught in the main loop and displayed via `error_message()`.

5. **Exit**: Word `quit` returns `false` from `process_words()`, terminating the loop.

---

## Historical Context & Technical Debt

1. **Origins and Evolution**:
   - Clac was originally written in the mid-1990s in a pre-C++98 style.
   - Some sections have been refactored to modern C++, but the codebase is still a mix of styles.
   - The original plan included a Forth-like programming language, which was never implemented.
  
2. **Specific Technical Debt**:
   - Much of the code still assumes `new` returns a null pointer on failure.
   - There is minimal or ineffective use of modern C++ features and libraries.
   - Naming conventions reflect pre-namespace C++ practices, despite the recent addition of namespaces.
   - The `docs` folder contains outdated and incomplete documentation.
   - The program is missing significant functionality, and the design may need to be revisited.
  
3. **Guidance for AI Assistants**:
   - Focus on refactoring code to modern C++ standards (specifically, C++ 2020) while preserving existing functionality.
   - Avoid introducing new features or significant design changes without explicit instructions.
   - Cross-platform compatibility is crucial; ensure that any code changes do not break builds on supported platforms.
   - When improving documentation, ensure it accurately reflects the current state of the codebase and is clear for future developers.
   - Provide suggestions for code modernization where appropriate.