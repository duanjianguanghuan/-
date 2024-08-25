import sqlite3

class StudentManagementSystem:
    def __init__(self, db_name='student_management.db'):
        self.conn = sqlite3.connect(db_name)
        self.create_tables()

    def create_tables(self):
        cursor = self.conn.cursor()
        
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS students (
                student_id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                gender TEXT NOT NULL,
                dob DATE,
                contact TEXT
            )
        ''')
        
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS scores (
                score_id INTEGER PRIMARY KEY AUTOINCREMENT,
                student_id INTEGER,
                subject TEXT NOT NULL,
                score INTEGER,
                FOREIGN KEY (student_id) REFERENCES students (student_id)
            )
        ''')
        
        self.conn.commit()

    def add_student(self, name, gender, dob, contact):
        try:
            cursor = self.conn.cursor()
            cursor.execute('''
                INSERT INTO students (name, gender, dob, contact)
                VALUES (?, ?, ?, ?)
            ''', (name, gender, dob, contact))
            self.conn.commit()
            print("学生信息已成功添加！")
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")
        except Exception as e:
            print(f"其他错误: {e}")

    def view_students(self):
        try:
            cursor = self.conn.cursor()
            cursor.execute('SELECT * FROM students')
            students = cursor.fetchall()
            if not students:
                print("没有学生记录。")
            for student in students:
                print(student)
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")

    def update_student(self, student_id, name, gender, dob, contact):
        try:
            cursor = self.conn.cursor()
            cursor.execute('''
                UPDATE students
                SET name = ?, gender = ?, dob = ?, contact = ?
                WHERE student_id = ?
            ''', (name, gender, dob, contact, student_id))
            self.conn.commit()
            if cursor.rowcount == 0:
                print("未找到指定ID的学生。")
            else:
                print("学生信息已更新！")
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")

    def delete_student(self, student_id):
        try:
            cursor = self.conn.cursor()
            cursor.execute('DELETE FROM students WHERE student_id = ?', (student_id,))
            self.conn.commit()
            if cursor.rowcount == 0:
                print("未找到指定ID的学生。")
            else:
                print("学生信息已删除！")
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")

    def add_score(self, student_id, subject, score):
        try:
            cursor = self.conn.cursor()
            cursor.execute('''
                INSERT INTO scores (student_id, subject, score)
                VALUES (?, ?, ?)
            ''', (student_id, subject, score))
            self.conn.commit()
            print("成绩已成功添加！")
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")
        except Exception as e:
            print(f"其他错误: {e}")

    def view_scores(self):
        try:
            cursor = self.conn.cursor()
            cursor.execute('SELECT * FROM scores')
            scores = cursor.fetchall()
            if not scores:
                print("没有成绩记录。")
            for score in scores:
                print(score)
        except sqlite3.Error as e:
            print(f"数据库错误: {e}")

    def close(self):
        self.conn.close()

def main():
    system = StudentManagementSystem()

    while True:
        print("\n学生信息管理系统")
        print("1. 添加学生")
        print("2. 查看所有学生")
        print("3. 更新学生信息")
        print("4. 删除学生")
        print("5. 添加成绩")
        print("6. 查看所有成绩")
        print("7. 退出")
        
        choice = input("请输入操作编号: ")

        if choice == '1':
            name = input("请输入学生姓名: ")
            gender = input("请输入学生性别: ")
            dob = input("请输入出生日期 (YYYY-MM-DD): ")
            contact = input("请输入联系方式: ")
            system.add_student(name, gender, dob, contact)
        
        elif choice == '2':
            system.view_students()
        
        elif choice == '3':
            try:
                student_id = int(input("请输入学生ID: "))
                name = input("请输入学生姓名: ")
                gender = input("请输入学生性别: ")
                dob = input("请输入出生日期 (YYYY-MM-DD): ")
                contact = input("请输入联系方式: ")
                system.update_student(student_id, name, gender, dob, contact)
            except ValueError:
                print("请输入有效的学生ID。")
        
        elif choice == '4':
            try:
                student_id = int(input("请输入学生ID: "))
                system.delete_student(student_id)
            except ValueError:
                print("请输入有效的学生ID。")
        
        elif choice == '5':
            try:
                student_id = int(input("请输入学生ID: "))
                subject = input("请输入科目: ")
                score = int(input("请输入成绩: "))
                system.add_score(student_id, subject, score)
            except ValueError:
                print("请输入有效的学生ID和成绩。")
        
        elif choice == '6':
            system.view_scores()
        
        elif choice == '7':
            system.close()
            print("退出系统。")
            break
        
        else:
            print("无效的操作编号，请重新输入。")

if __name__ == "__main__":
    main()
