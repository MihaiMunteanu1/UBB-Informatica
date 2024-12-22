from domeniu.student import Student
import random,string
class StudentService:
    def __init__(self,repo_students,validator_student):
        self.__repo_students=repo_students
        self.__validator_student=validator_student

    def add_student(self,id_student,nume,grup):
        student=Student(id_student, nume, grup)
        self.__validator_student.valideaza_student(student)
        self.__repo_students.add_student(student)

    def sterge_student(self,id_student):
        self.__repo_students.sterge_student(id_student)

    def modifica_student(self,id_student,nume,grup):
        student=Student(id_student, nume, grup)
        self.__validator_student.valideaza_student(student)
        self.__repo_students.modifica_student(student)

    def cauta_student_dupa_id(self,id_student):
        return self.__repo_students.cauta_student_dupa_id(id_student)

    def genereaza_id_student_random(self):
        return random.randint(1, 10000)

    def genereaza_nume_student_random(self):
        nume_student = (''.join(random.choices(string.ascii_uppercase, k=1)))
        nume_student += (''.join(random.choices(string.ascii_lowercase, k=5)))
        return nume_student

    def genereaza_grup_student_random(self):
        return random.randint(1, 100)

    def adauga_studenti_random(self, numar):
        random.seed(random.randint(0, 100))
        for x in range(0, numar):
            id = self.genereaza_id_student_random()
            nume = self.genereaza_nume_student_random()
            grup = self.genereaza_grup_student_random()
            student = Student(id, nume, grup)
            self.__validator_student.valideaza_student(student)
            self.__repo_students.add_student(student)

    def get_all(self):
        return self.__repo_students.get_all()


