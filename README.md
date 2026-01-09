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
- A queue-like structure is used to manage remaining undealt cards.

### ✔ **3. Dynamic Arrays (`std::vector`)**  
- Used in columns and deck because card counts change dynamically.

### ✔ **4. Custom Linked Structure (Optional / Future)**  
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


### 🔸 **Team Parallelization**
Every module was designed so each team member could work **independently** without blocking others.

### 🔸 **Interface-first Development**
We first froze:
- Class names  
- Method signatures  
- Data structures  

This allowed us to code simultaneously — exactly how real-world teams operate.

### 🔸 **DSA-heavy Backend + Clean GUI Layer**
- Logic is completely separated from GUI.
- Raylib only redraws states; no game logic inside rendering.

---

# 🧩 **Class Architecture (High-Level Overview)**


---

# 📂 **Folder Structure**

---

# 🚀 **How to Run the Project**
1. Install **Raylib**  
2. Compile using g++ or CMake  
3. Run executable  
4. Enjoy the game 🎮

---

# 📸 **Screenshots**
(Will be added as soon as GUI is completed)

---

# 🏆 **Conclusion**
This project allowed us to demonstrate:

- Strong understanding of **DSA fundamentals**  
- Real application of **OOP**  
- Building an actual **GUI game in C++**  
- **Team collaboration**, version control, and modular architecture  

Spider Solitaire is a perfect blend of:
> **Algorithmic thinking + Data Structures + Game Development**

We proudly present this as our **3rd Semester DSA Project**.

---

# 💙 **Thank You!**
If you like this project or want to contribute, feel free to reach out.

