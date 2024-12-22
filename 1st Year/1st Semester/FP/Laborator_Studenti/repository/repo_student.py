from domeniu.student import Student
class RepositoryStudent:
    def __init__(self):
        self._students={}
    def add_student(self,student):
        id_student=student.get_id_student()
        if id_student in self._students:
            raise Exception("id existent")
        self._students[id_student]=student
    def sterge_student(self,id_student):
        if id_student in self._students:
            del self._students[id_student]
        else:
            raise Exception("id inexistent")
    def modifica_student(self,student):
        id_student=student.get_id_student()
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

class RepositoryStudentFisiere(RepositoryStudent):
    def __init__(self, cale_fisier):
        RepositoryStudent.__init__(self)
        self.__cale_fisier = cale_fisier

    def __read_all_students_from_file(self):
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
                f.write(str(self._students[id_student])+"\n")
    def add_student(self,student):
        self.__read_all_students_from_file()
        RepositoryStudent.add_student(self,student)
        self.__write_all_students_to_file()

    def sterge_student(self, id_student):
        self.__read_all_students_from_file()
        RepositoryStudent.sterge_student(self, id_student)
        self.__write_all_students_to_file()

    def modifica_student_in_fisier(self, student):
        modified_lines = []
        with open(self.__cale_fisier, 'r') as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != '':
                    parti = line.split(',')
                    id_student = int(parti[0])
                    if id_student == student.get_id_student():
                        modified_line = f"{id_student},{student.get_nume()},{student.get_grup()}\n"
                        modified_lines.append(modified_line)
                    else:
                        modified_lines.append(line)

        with open(self.__cale_fisier, 'w') as f:
            f.writelines(modified_lines)

    def modifica_student(self, student):
        self.__read_all_students_from_file()
        RepositoryStudent.modifica_student(self, student)
        self.modifica_student_in_fisier(student)

    def cauta_student_dupa_id(self, id_student):
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
        raise Exception("ID de student inexistent în fisier")
    def get_all(self):
        self.__read_all_students_from_file()
        return RepositoryStudent.get_all(self)