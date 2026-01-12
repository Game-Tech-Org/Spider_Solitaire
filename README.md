# 🕷️ SpiderSolitaire — C++ | DSA | OOP | Raylib  
### *3rd Semester Data Structures Project — Namal University Mianwali*  
---

## 👥 **Project Members**
| Name | Roll No |
|------|---------|
| **Sundeep Kumar** | NUM-BSCS-2024-75 |
| **Breera Ijaz** | NUM-BSCS-2024-20 |
| **Shahbaz Ali** | NUM-BSCS-2024-73 |
| **Tayyab Shahzad** | NUM-BSCS-2024-77 |
| **Muhammad Imran** | NUM-BSCS-2024-50 |

**Instructor:** Sir Abdul Rafay  
**Course:** Data Structures & Algorithms (DSA)  
**Project:** Spider Solitaire (Full Game Implementation)

---

# 🎯 **Introduction**
Spider Solitaire is one of the most popular card-based puzzle games.  
This project is a **complete Spider Solitaire game developed in C++**, applying:

- **Object-Oriented Programming**
- **Data Structures and Algorithms**
- **Raylib Game Engine** (for GUI)
- **Team-based software engineering workflow**
- **Clean architecture & modular design**

This project demonstrates our ability to build a **fully functional, interactive game** using **core DSA concepts**, while applying real-world engineering practices.

---

# 🧠 **DSA Concepts Used**
Spider Solitaire heavily relies on multiple data structures.  
Our implementation includes:

### ✔ **1. Stack (Used for card piles & undo system)**  
- Cards in each column behave like a stack.  
- Undo/redo actions use multiple stacks.

### ✔ **2. Queue (For dealing new rows — optional)**  
- A queue-like structure manages remaining undealt cards.

### ✔ **3. Dynamic Arrays (`std::vector`)**  
- Used in columns and deck because card counts change dynamically.

### ✔ **4. Custom Linked Structure (implement stack and queue using this custom linked structure)**  
- Columns may support linked-subsequence moves.

### ✔ **5. Game State Machine**  
- State transitions follow a controlled update loop:
  - Input → Validation → Action → Rendering.

---

# 🕹️ **Game Features**
### ✅ Fully playable Spider Solitaire  
### ✅ Drag & drop card movement  
### ✅ Auto-detect complete sequences (King → Ace)  
### ✅ Deal new rows  
### ✅ Column-based card handling  
### ✅ Move validation (same suit + descending order)  
### ✅ Undo / Redo support  
### ✅ Polished Raylib GUI  
### ✅ Modular C++ architecture for team development  

---

# 🏗️ **Software Engineering Approach**
We structured the game using **industry-standard engineering practices**:

### 🔸 **Modular Architecture**
- Each module is independent and reusable.

### 🔸 **Team Parallelization**
- Each member works on separate modules without blocking others.

### 🔸 **Interface-first Development**
- Class names, method signatures, and data structures were frozen early.
- Allowed simultaneous coding with minimal conflicts.

### 🔸 **DSA-heavy Backend + Clean GUI Layer**
- Game logic is completely separated from rendering.
- Raylib only redraws game states.

---

# 🧩 **Class Architecture using .h files (High-Level Overview)**
- **LinkedList.h** — Provide Linked list data structure.  
- **Card.h** — Represents a single card (rank, suit, face-up/face-down).    
- **Column.h** — Stack-based structure for cards on the table using linked list.  
- **StockPiles.h** — Queue based for deal logic in Game.  
- **SpiderSolitaire.h** — Deals with the main logic and validation of the Game.  
- **Main.cpp** — Handles integration of the classes and provide executable game.

---

# 📂 **Folder Structure**
## Using Linked list
Game.LinkedList/  
├─ Deck Images/ # Card images  
│  
├─ src/  
│ ├─ core/   
│ │ ├─ Card.h  
│ │ ├─ Column.h  
│ │ ├─ LinkedList.h  
│ │ ├─ StockPile.h  
│ │ ├─ SpiderSolitaire.h  
│ └─ main.cpp   
|  
└─ README.md  
## Using Queue
Game.Queue/  
│  
└─ main.cpp
## Using Stack
Game.Stack/  
│  
└─ main.cpp

---

# 🚀 **How to Run the Project**
1. Install **Raylib** for your platform.
   - For Linux: `sudo apt install libraylib-dev`  
   - For Windows: download Raylib installer or use vcpkg.  

2. **Clone the Repository**
   ```bash
   git clone https://github.com/SundeepKumar07/NAMAL_COMPLAINT_PORTAL