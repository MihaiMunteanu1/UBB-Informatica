import random
from domeniu.student import Student
from domeniu.laborator import Laborator
from domeniu.notaDTO import NotaDTO
from validare.validator_student import ValidatorStudent
from validare.validator_laborator import ValidatorLaborator
from infrastructura.repo_laboratoare import LaboratorRepository
from infrastructura.repo_studenti import StudentRepository
from infrastructura.repo_nota import NotaRepository
from business.service_studenti import StudentService
class Teste:

    def __teste_cautare_student_dupa_id(self):
        student_repo=StudentRepository()
        studentID = 1
        nume = "Mihai"
        grup = 1
        student = Student(studentID, nume, grup)
        student_repo.add_student(student)
        student_cautat=student_repo.cauta_student_dupa_id(student.get_studentid())
        assert student.get_studentid()==student_cautat.get_studentid()

        studentID_gresit = 2
        nume_gresit = "Mihai"
        grup_gresit = 1
        student_gresit = Student(studentID_gresit, nume_gresit, grup_gresit)
        student_repo.add_student(student_gresit)
        assert student_gresit.get_studentid() != student_cautat.get_studentid()
    def __teste_genereaza_studenta(self):
        repo=StudentRepository()
        valid=ValidatorStudent()
        student_srv=StudentService(repo,valid)
        random.seed(3)
        student_1=Student(student_srv.genereaza_id_student_random(),student_srv.genereaza_nume_student_random(),
                          student_srv.genereaza_grup_student_random())
        random.seed(3)
        student_2 = Student(student_srv.genereaza_id_student_random(),student_srv.genereaza_nume_student_random(),
                          student_srv.genereaza_grup_student_random())
        assert student_1.get_studentid()==student_2.get_studentid()
        assert student_1.get_nume()==student_2.get_nume()
        assert student_1.get_grup()==student_2.get_grup()

        random.seed(2)
        student_3=Student(student_srv.genereaza_id_student_random(),student_srv.genereaza_nume_student_random(),
                          student_srv.genereaza_grup_student_random())
        assert student_1.get_studentid() != student_3.get_studentid()
        assert student_1.get_nume() != student_3.get_nume()
        assert student_1.get_grup() != student_3.get_grup()

    def __test_create_student(self):
        studentID = 1
        nume = "Mihai"
        grup = 1
        student = Student(studentID, nume, grup)
        other_studentID = -10
        other_nume = ""
        other_grup = -90
        epsilon = 0.0001
        other_student = Student(other_studentID, other_nume, other_grup)
        assert student.get_studentid() == studentID
        assert student.get_nume() == nume
        assert abs(student.get_grup()-grup)<epsilon
        #assert student == other_student

    def __test_validate_student(self):
        studentID = 1
        nume = "Mihai"
        grup = 1
        student = Student(studentID, nume, grup)
        bad_studentID = -10
        bad_nume = ""
        bad_grup = -90
        epsilon = 0.0001
        bad_student = Student(bad_studentID, bad_nume, bad_grup)
        validator = ValidatorStudent()
        validator.valideaza_student(student)
        try:
            validator.valideaza_student(bad_student)
            assert False
        except Exception as ex:
            assert (str(ex)=="id invalid!\nnume invalid!\ngrup invalid!\n")

    def __test_student(self):
        student_repo=StudentRepository()
        student1 = Student(1, "Mihai", 1)
        student2 = Student(2, "Andrei", 2)
        student_repo.add_student(student1)
        student_repo.add_student(student2)
        assert len(student_repo.get_all()) == 2

    def __test_sterge_student(self):
        student_repo = StudentRepository()
        student1 = Student(3, "Mihai", 1)
        student2 = Student(4, "Andrei", 2)
        student_repo.add_student(student1)
        student_repo.add_student(student2)
        student_repo.sterge_student(student1.get_studentid())
        assert len(student_repo.get_all()) == 1
        assert student1 not in student_repo.get_all()
    def __test_modifica_student(self):
        student_repo = StudentRepository()
        student1 = Student(3, "Mihai", 1)
        student2 = Student(4, "Andrei", 2)
        student_repo.add_student(student1)
        student_repo.add_student(student2)
        student_modificat=Student(3,"Vlad",5)
        student_repo.modifica_student(student_modificat)
        assert student1==student_modificat


    def run_all_tests(self):
        self.__test_create_student()
        self.__test_validate_student()
        self.__test_student()
        self.__test_sterge_student()
        self.__teste_genereaza_studenta()
        self.__teste_cautare_student_dupa_id()
        self.__test_modifica_student()
class TesteL:
    def __teste_cautare_laborator_dupa_numar_problema(self):
        lab_repo=LaboratorRepository()
        numar_prob = 1
        descriere = "Teste"
        deadline = "12.12.2023"
        laborator = Laborator(numar_prob, descriere, deadline)
        lab_repo.add_laborator(laborator)
        lab_cautat=lab_repo.cauta_laborator_dupa_numar_problema(laborator.get_numar_problema())
        assert laborator.get_numar_problema()==lab_cautat.get_numar_problema()


    def __test_create_laborator(self):
        numar_problema = 1
        descriere = "Adaugare teste"
        deadline = "10.12.2023"
        laborator = Laborator(numar_problema, descriere, deadline)
        other_numar_problema = -10
        other_descriere = ""
        other_deadline = "24.24.2010"
        other_laborator = Laborator(other_numar_problema, other_descriere, other_deadline)
        assert laborator.get_numar_problema() == numar_problema
        assert laborator.get_descriere() == descriere
        assert laborator.get_deadline() == deadline
        #assert laborator == other_laborator

    def __test_validate_laborator(self):
        numar_problema = 1
        descriere = "Adaugare teste"
        deadline = "10.12.2023"
        laborator = Laborator(numar_problema, descriere, deadline)
        bad_numar_problema = -10
        bad_descriere = ""
        bad_deadline = "24.24.2010"
        bad_laborator = Laborator(bad_numar_problema, bad_descriere, bad_deadline)
        validator = ValidatorLaborator()
        validator.validate_laborator(laborator)
        try:
            validator.validate_laborator(bad_laborator)
            assert False
        except Exception as ex:
            assert (str(ex) == "numar problema invalid!\ndescriere invalida!\n")

    def __test_laborator(self):
        laborator_repo = LaboratorRepository()
        laborator1 = Laborator(1, "Descriere1", "12.12.2023")
        laborator2 = Laborator(2, "Descriere2", "10.10.2023")
        laborator_repo.add_laborator(laborator1)
        laborator_repo.add_laborator(laborator2)
        assert len(laborator_repo.get_all()) == 2

    def __test_sterge_laborator(self):
        laborator_repo = LaboratorRepository()
        laborator1 = Laborator(3, "Descriere3", "14.2.2024")
        laborator2 = Laborator(4, "Descriere4", "14.4.2024")
        laborator_repo.add_laborator(laborator1)
        laborator_repo.add_laborator(laborator2)
        laborator_repo.sterge_laborator(laborator1.get_numar_problema())
        assert len(laborator_repo.get_all()) == 1
        assert laborator1 not in laborator_repo.get_all()


    def run_all_tests(self):
        self.__test_create_laborator()
        self.__test_validate_laborator()
        self.__test_laborator()
        self.__test_sterge_laborator()
        self.__teste_cautare_laborator_dupa_numar_problema()

class TesteN:
    def __test_asignare_nota(self):
        student_repo = StudentRepository()
        lab_repo = LaboratorRepository()
        nota_repo = NotaRepository()
        student = Student(1, "Mihai",1)
        lab = Laborator(1, "Teste","12.12.2023")
        student_repo.add_student(student)
        lab_repo.add_laborator(lab)
        nota = NotaDTO(1,student.get_studentid(), lab.get_numar_problema(),10)
        nota_repo.add_nota(nota)
        nota_list = nota_repo.get_all_nota()
        assert len(nota_list) == 1

    def run_all_tests(self):
        self.__test_asignare_nota()