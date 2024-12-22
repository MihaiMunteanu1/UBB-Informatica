from domeniu.student import Student
class ServiceStudent:
    def __init__(self,repo_student,validator_student):
        self.__repo_student=repo_student
        self.__valid_student=validator_student

    def add_student(self,id_student,nume,grup):
        student=Student(id_student,nume,grup)
        self.__valid_student.valideaza_student(student)
        self.__repo_student.add_student(student)

    def sterge_student(self,id_student):
        self.__repo_student.sterge_student(id_student)

    def modifica_student(self,id_student,nume,grup):
        student=Student(id_student,nume,grup)
        self.__valid_student.valideaza_student(student)
        self.__repo_student.modifica_student(student)

    def cauta_student_dupa_id(self,id_student):
        return self.__repo_student.cauta_student_dupa_id(id_student)
    def sortare_dupa_grup(self):
        sortare=[]
        for student in self.__repo_student.get_all():
            sortare.append(student)
        sortare.sort(key=lambda x:x.get_grup())
        return sortare

    def get_all(self):
        return self.__repo_student.get_all()
