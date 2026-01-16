# Class vs. Students 🎮📚

A turn-based tactical battle game where students fight based on their academic schedules and subject specialties.

## ✨ Features
*   **Schedule-Driven Combat**: Battles unfold across a simulated 5-day school week with 8 classes per day. Subject of the current class influences combat.
*   **Diverse Character System**: 28 unique students, each with distinct academic attributes (e.g., Chinese Rep, Math Rep) and special traits.
*   **Tri-Resource Management**: Strategize using Health (Red), Sanity (Blue), and Stamina (White).
*   **Team-Based Gameplay**: Command Team A and Team B in tactical 3v3 skirmishes each period.

## 🚀 Quick Start
### Prerequisites
*   Windows OS
*   MinGW GCC Compiler (included in project scripts)
*   Or any C++11 compatible environment

### Build & Run
1.  **Clone the repository**:
    ```bash
    git clone https://github.com/cso666/Class-vs-Students.git
    cd Class-vs-Students
    ```

2.  **Compile the project**:
    *   Run the `compile.bat` script in the project root.
    *   Or compile manually:
      ```bash
      g++ -std=c++11 main.cpp app.res -o main.exe
      ```

3.  **Launch the game**:
    ```bash
    main.exe
    ```

## 🛠️ Development
### Project Structure
Class-vs-Students/

├── main.cpp # Main game loop & control logic

├── student.h # Header aggregating all character classes

├── teacher.h # Weekly class schedule data

├── students/ # Individual character headers (A0.h, A1.h, ...)

├── compile.bat # Windows one-click build script

├── headers.h # Standard library includes

├── app.rc & icon.ico # Application resources & icon

└── README.md # This file
### Core Developers
This project was collaboratively created by:
*   [JSGF](https://www.luogu.com.cn/user/1513597)
*   [delHYfish](https://www.luogu.com.cn/user/1382890)
*   [cso666](https://www.luogu.com.cn/user/1300229) (Repository Maintainer)

## 📄 License
No licence.Just for fun!