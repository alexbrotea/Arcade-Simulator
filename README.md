# Arcade Simulator – SDA Assignment

---

### **Task 1: Matrix Row Rotation**

To begin the assignment, I dynamically allocated a matrix of dimensions n x m.  
I saved the values from a specified column **c** into a temporary matrix **tmp**, in order to facilitate the rotation and reinsertion of values.

The values were then rotated back into the original matrix.  
This was done using a modular arithmetic operation **(i + r) % n**, where **r** represents the number of rotations.  
This ensures a correct circular rotation even when the number of rotations exceeds the matrix height.  
Finally, I displayed the rotated matrix and freed all allocated memory.

---

### **Task 2: Sequence Scoring**

For this task, I first allocated and populated the matrix similarly to Task 1.  
Then, I declared several variables:

- **nr_comb**: Number of winning combinations  
- **score**: Current score  
- **nr_sym**: Number of distinct symbols (used for score calculation)

Each distinct symbol (between 0 and 9) was stored in a dynamically allocated array.  
My goal was to detect the longest sequence (in length and symbol consistency) across the matrix, both row-wise and diagonally.

I scanned the matrix and recorded sequences of equal symbols.  
If a sequence exceeded 3 identical symbols in a row, column, or diagonal, I recorded it as a valid sequence.  
The scoring mechanism increased based on the number of combinations and symbol frequency.

The second part of the task analyzed both diagonals for such patterns.  
I also increased the score depending on the frequency of symbol appearances.

Memory cleanup was handled at the end.

---

### **Task 4: Maximum Score Search**

This task followed a similar structure.  
After reading and allocating the matrix, I used the variable **max_sym** and a temporary variable **max_possible_sym** to keep track of the best possible score that could be obtained.

Each matrix symbol was checked and, if needed, replaced with another symbol to maximize the score.  
I created a copy of the original matrix to preserve data integrity during this process.

After each substitution, I recalculated the score and updated the best score found.  
Memory was freed as in the previous tasks.
