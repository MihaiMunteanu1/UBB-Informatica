from domeniu.student import Student
class StudentRepository:
    def __init__(self):
        self._students={}
    def add_student(self,student):
        id_student=student.get_studentid()
        if id_student in self._students:
            raise Exception("id existent")
        self._students[id_student]=student
    def sterge_student(self,id_student):
        if id_student in self._students:
            del self._students[id_student]
        else:
            raise Exception("id inexistent")
    def modifica_student(self,student):
        id_student=student.get_studentid()
        if id_student in self._students:
            self._students[id_student]=student
        else:
            raise Exception("id inexistent")
    def cauta_student_dupa_id(self,id_student):
        if id_student<0:
            raise Exception("id invalid")
        if id_student in self._students:
            return self._students[id_student]
        else:
            raise Exception("id inexistent")
    def get_all(self):
        return [self._students[x] for x in self._students.keys()]

class FileRepoStudent(StudentRepository):
    def __init__(self, cale_fisier):
        StudentRepository.__init__(self)
        self.__cale_fisier = cale_fisier

    """def __read_all_students_from_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._students.clear()
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parti = line.split(",")
                    id_student = int(parti[0])
                    nume = parti[1]
                    grup = int(parti[2])
                    student = Student(id_student, nume, grup)
                    self._students[id_student] = student
    def __write_all_students_to_file(self):
        with open(self.__cale_fisier, "w") as f:
            for id_student in self._students:
                f.write(str(self._students[id_student])+"\n")"""
    def __read_all_students_from_file(self):
        with open(self.__cale_fisier,"r") as f:
            self._students.clear()
            lines = f.readlines()
            i=0
            while i<len(lines):
                id_student = int(lines[i].strip())
                nume = lines[i + 1].strip()
                grup = int(lines[i + 2].strip())
                student = Student(id_student, nume, grup)
                self._students[id_student] = student
                i += 3
    def __write_all_students_to_file(self):
        with open(self.__cale_fisier, "w") as f:
            for id_student in self._students:
                student=self._students[id_student]
                f.write(str(student.get_studentid())+"\n"+str(student.get_nume())+"\n"+str(student.get_grup())+"\n")
    def add_student(self,student):
        self.__read_all_students_from_file()
        StudentRepository.add_student(self,student)
        self.__write_all_students_to_file()

    def sterge_student(self, id_student):
        self.__read_all_students_from_file()
        StudentRepository.sterge_student(self, id_student)
        self.__write_all_students_to_file()


    #modificare cu 1,mihai,1
    """def modifica_student_in_fisier(self, student):
        modified_lines = []
        with open(self.__cale_fisier, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    parti = line.split(',')
                    id_student = int(parti[0])
                    if id_student == student.get_studentid():
                        modified_line = f"{id_student},{student.get_nume()},{student.get_grup()}\n"
                        modified_lines.append(modified_line)
                    else:
                        modified_lines.append(line)

        with open(self.__cale_fisier, 'w') as f:
            f.writelines(modified_lines)"""

    def modifica_student_in_fisier(self, student):
        modified_lines = []
        with open(self.__cale_fisier, 'r') as f:
            lines = f.readlines()
            i = 0
            while i < len(lines):
                current_id_student = int(lines[i].strip())
                if current_id_student == student.get_studentid():
                    modified_lines.append(str(current_id_student) + "\n")
                    modified_lines.append(str(student.get_nume()) + "\n")
                    modified_lines.append(str(student.get_grup()) + "\n")
                else:
                    modified_lines.append(lines[i])
                    modified_lines.append(lines[i+1])
                    modified_lines.append(lines[i+2])
                i += 3

        with open(self.__cale_fisier, 'w') as f:
            f.writelines(modified_lines)

    def modifica_student(self, student):
        self.__read_all_students_from_file()
        StudentRepository.modifica_student(self, student)
        self.modifica_student_in_fisier(student)


    #cautare cu 1,mihai,1
    """def cauta_student_dupa_id(self, id_student):
        with open(self.__cale_fisier, "r") as f:
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parti = line.split(",")
                    current_id_student = int(parti[0])
                    if current_id_student == id_student:
                        nume = parti[1]
                        grup = int(parti[2])
                        return Student(current_id_student, nume, grup)
        raise Exception("ID de student inexistent în fisier")"""

    def cauta_student_dupa_id(self, id_student):
        with open(self.__cale_fisier, "r") as f:
            lines = f.readlines()
            i = 0
            while i < len(lines):
                current_id_student = int(lines[i].strip())
                if current_id_student == id_student:
                    nume = lines[i + 1].strip()
                    grup = int(lines[i + 2].strip())
                    return Student(current_id_student, nume, grup)
                i += 3
        raise Exception("ID de student inexistent în fisier")
    def get_all(self):
        self.__read_all_students_from_file()
        return StudentRepository.get_all(self)