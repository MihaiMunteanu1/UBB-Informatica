from domeniu.student import Student
from infrastructura.repo_studenti import StudentRepository
from infrastructura.repo_studenti import FileRepoStudent

class TesteFisier:
    def __init__(self,test_student,test_lab,test_note):
        self.__test_student=test_student
        self.__test_lab=test_lab
        self.__test_note=test_note
    def __goleste_fisier(self, students_file_path):
        with open(students_file_path, 'w') as f:
            f.write('')

    def __ruleaza_teste_adaugare_student_repo(self):
        self.__goleste_fisier(self.__test_student)
        with open(self.__test_student, 'w') as f:
            f.write("1,Mihai,1")
        student_repo = StudentRepository()
        with open(self.__test_student,"r") as f:
            lines = f.readlines()
            for line in lines:
                if line != "":
                    parts = line.split(",")
                    student_id = int(parts[0])
                    nume = parts[1]
                    grup = int(parts[2])
                    student_file = Student(student_id, nume, grup)
                    student_repo.add_student(student_file)
        assert len(student_repo.get_all()) == 1

    def __test_sterge_student(self):
        file_repo_student=FileRepoStudent(self.__test_student)
        student1=Student(1,"Mihai",1)
        student2=Student(2,"Andrei",2)
        self.__goleste_fisier(self.__test_student)
        file_repo_student.add_student(student1)
        file_repo_student.add_student(student2)
        assert len(file_repo_student.get_all())==2
        file_repo_student.sterge_student(1)
        assert len(file_repo_student.get_all())==1
        assert student1 not in file_repo_student.get_all()
    def __test_modifica_student(self):
        self.__goleste_fisier(self.__test_student)
        file_repo_student = FileRepoStudent(self.__test_student)
        student1 = Student(1, "Mihai", 1)
        student2 = Student(2, "Andrei", 2)
        file_repo_student.add_student(student1)
        file_repo_student.add_student(student2)
        student_modificat=Student(1,"Vlad",4)
        file_repo_student.modifica_student(student_modificat)
        assert student1==student_modificat

    def __test_cauta_student(self):
        self.__goleste_fisier(self.__test_student)
        file_repo_student = FileRepoStudent(self.__test_student)
        student1 = Student(1, "Mihai", 1)
        student2 = Student(2, "Andrei", 2)
        file_repo_student.add_student(student1)
        file_repo_student.add_student(student2)
        student_cautat=file_repo_student.cauta_student_dupa_id(1)
        assert student_cautat==student1

    def ruleaza_teste(self):
        self.__ruleaza_teste_adaugare_student_repo()
        self.__ruleaza_teste_adaugare_student_repo()
        self.__test_modifica_student()
        self.__test_cauta_student()

