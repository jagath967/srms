Student Management System in C

Overview:
This is a simple Student Management System implemented in C that allows Admin, Staff, and Students to manage and view student details, marks, CGPA, and receive subject advice. The system uses text files to store data.

Features:

Admin:
- Add new students with roll number, name, and marks.
- Display all students.
- Display CGPA list of all students.
- View class merit (average CGPA).
- Get subject-wise advice for weak subjects.
- Logout.

Staff:
- Display all students.
- Display CGPA list of all students.
- Logout.

Student:
- Display CGPA list.
- Get subject advice.
- Logout.

File Structure:
The program uses the following text files:

1. students.txt - Stores student roll numbers and names.  
   Format: roll name

2. marks.txt - Stores student marks in subjects.  
   Format: roll maths dsa os

3. cgpa.txt - Stores student CGPA.  
   Format: roll cgpa

4. credentials.txt - Stores login credentials and roles.  
   Format: username password role  
   Example:
   admin admin123 admin
   staff staff123 staff
   student1 pass123 student

CGPA Calculation:
- Marks are converted into grade points using the following scale:
  90-100 -> 10
  80-89  -> 9
  70-79  -> 8
  60-69  -> 7
  50-59  -> 6
  40-49  -> 5
  <40    -> 0

- CGPA = Weighted average of grade points:
  Maths (Credits = 4)
  DSA (Credits = 3)
  OS (Credits = 3)
  Formula: (GP1*4 + GP2*3 + GP3*3)/10

How to Run:
1. Compile the code using a C compiler:
   gcc main.c -o student_system
2. Make sure the text files (students.txt, marks.txt, cgpa.txt, credentials.txt) exist in the same directory.
3. Run the program:
   ./student_system
4. Login using credentials from credentials.txt:
   - Admin example: admin / admin123
   - Staff example: staff / staff123
   - Student example: student1 / pass123
5. Navigate through the menus based on your role.

Notes:
- Admin can perform all operations including adding students.
- Staff can only view student and CGPA information.
- Students can only view CGPA and get advice on weak subjects.
- All data is stored in simple text files.
- Subject advice is given for marks below 50.

Author:
Jagath Kamalesh
