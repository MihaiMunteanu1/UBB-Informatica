from domeniu.student import Student
from validare.validator_student import ValidatorStudent
from repository.repo_student import RepositoryStudent
class Teste:
    def __test_add_student(self):
        id_student=1
        nume="Mihai"
        grup=1
        epsilon=0.00001
        student=Student(id_student,nume,grup)
        assert student.get_id_student()==id_student
        assert student.get_nume()==student.get_nume()
        assert abs(student.get_grup()-grup)<epsilon
        id_gresit=2
        nume_gresit="Andrei"
        grup_gresit=3
        student_gresit=Student(id_gresit,nume_gresit,grup_gresit)
        assert student!=student_gresit
    def __test_valideaza_student(self):
        id_student = 1
        nume = "Mihai"
        grup = 1
        student = Student(id_student, nume, grup)
        valid_student=ValidatorStudent()
        valid_student.valideaza_student(student)
        student_incorect=Student(-1,"",-100)
        try:
            valid_student.valideaza_student(student_incorect)
            assert False
        except Exception as ex:
            assert (str(ex)=="id invalid\nnume invalid\ngrup invalid\n")

    def __test_add_student_repo(self):
        student = Student(1,"Mihai",1)
        repo_student=RepositoryStudent()
        repo_student.add_student(student)
        assert len(repo_student.get_all())==1
    def __test_sterge_student(self):
        student = Student(1, "Mihai", 1)
        repo_student = RepositoryStudent()
        repo_student.add_student(student)
        repo_student.sterge_student(student.get_id_student())
        assert len(repo_student.get_all())==0
        assert student not in repo_student.get_all()
    def __test_modifica_student(self):
        student = Student(1, "Mihai", 1)
        repo_student = RepositoryStudent()
        repo_student.add_student(student)
        student_modificat=Student(1,"Andrei",2)
        repo_student.modifica_student(student_modificat)
        assert student==student_modificat
    def __test_cauta_student_dupa_id(self):
        student = Student(1, "Mihai", 1)
        repo_student = RepositoryStudent()
        repo_student.add_student(student)
        student_cautat=repo_student.cauta_student_dupa_id(student.get_id_student())
        assert student==student_cautat

    def run_all_teste(self):
        self.__test_add_student()
        self.__test_valideaza_student()
        self.__test_add_student_repo()
        self.__test_sterge_student()
        self.__test_modifica_student()
        self.__test_cauta_student_dupa_id()