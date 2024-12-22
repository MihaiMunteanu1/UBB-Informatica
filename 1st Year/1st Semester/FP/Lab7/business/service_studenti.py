import random,string

from domeniu.student import Student
class StudentService:
    def __init__(self,repo_studentz,validator_student):
        self.__repo_studentz=repo_studentz
        self.__validator_student=validator_student

    def add_student(self,studentID,nume,grup):
        student = Student(studentID,nume,grup)
        self.__validator_student.valideaza_student(student)
        self.__repo_studentz.add_student(student)

    def sterge_student(self,studentID):
        self.__repo_studentz.sterge_student(studentID)

    def modifica_student(self,studentID,new_nume,new_grup):
        student = Student(studentID, new_nume,new_grup)
        self.__validator_student.valideaza_student(student)
        self.__repo_studentz.modifica_student(student)

    """def cauta_student_dupa_id(self,studentID):
        if studentID<0:
            raise Exception("id invalid")
        index=0
        return self.__repo_studentz.cauta_student_dupa_id(studentID,index)"""
    #recursiv
    def cauta_student_dupa_id(self,studentID,i):
        studenti=self.__repo_studentz.get_all()
        if i > len(studenti):
            raise Exception("ID student inexistent")
        if studenti[i].get_studentid() == studentID:
            return studenti[i]
        i=i+1
        return self.cauta_student_dupa_id(studentID,i)

    def get_all_students(self):
        return self.__repo_studentz.get_all()
    def genereaza_id_student_random(self):
        return random.randint(1,10000)

    def genereaza_nume_student_random(self):
        nume_student = (''.join(random.choices(string.ascii_uppercase, k=1)))
        nume_student += (''.join(random.choices(string.ascii_lowercase, k=5)))
        return nume_student

    def genereaza_grup_student_random(self):
        return random.randint(1, 100)

    """def generate_student(self,numar):
        random.seed(random.randint(0,100))
        for x in range(0,numar):
            id=self.genereaza_id_student_random()
            nume=self.genereaza_nume_student_random()
            grup=self.genereaza_grup_student_random()
            student=Student(id,nume,grup)
            self.__validator_student.valideaza_student(student)
            self.__repo_studentz.add_student(student)"""

    #recursiv
    def generate_student(self, numar, index=0):
        if index == numar:
            return

        id_student = self.genereaza_id_student_random()
        nume_student = self.genereaza_nume_student_random()
        grup_student = self.genereaza_grup_student_random()

        student = Student(id_student, nume_student, grup_student)
        self.__validator_student.valideaza_student(student)
        self.__repo_studentz.add_student(student)

        self.generate_student(numar, index + 1)

