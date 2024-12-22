from domeniu.student import Student
from domeniu.laborator import Laborator
from domeniu.notaDTO import NotaDTO
from validare.validator_student import ValidatorStudent
from validare.validator_laborator import ValidatorLaborator
from validare.validator_nota import ValidatorNota
from repository.repo_student import StudentRepository
from repository.repo_laborator import LaboratorRepository
from repository.repo_nota import NotaRepository
from service.service_student import StudentService
import random
class TesteStudent:
    def __creeaza_student(self):
        id_student = 1
        nume = "Mihai"
        grup = 1
        student = Student(id_student, nume, grup)
        epsilon=00000.1
        assert student.get_id_student()==id_student
        assert student.get_nume()==nume
        assert abs((student.get_grup()-grup))<epsilon
        id_gresit=2
        nume_gresit="Andrei"
        grup_gresit=3
        student_gresit=Student(id_gresit, nume_gresit, grup_gresit)
        assert student!=student_gresit
    def __valideaza_student(self):
        id_student = 1
        nume = "Mihai"
        grup = 1
        student = Student(id_student, nume, grup)
        validator = ValidatorStudent()
        validator.valideaza_student(student)
        id_gresit = -2
        nume_gresit = ""
        grup_gresit = -3
        student_gresit = Student(id_gresit, nume_gresit, grup_gresit)
        try:
            validator.valideaza_student(student_gresit)
            assert False
        except Exception as ex:
            assert (str(ex)=="id invalid\nnume invalid\ngrup invalid\n")

    def __teste_repo_add_student(self):
        student1=Student(1, "Mihai", 1)
        student2=Student(2, "Andrei", 3)
        repo_student=StudentRepository()
        repo_student.add_student(student1)
        repo_student.add_student(student2)
        assert len(repo_student.get_all())==2

    def __test_sterge_student(self):
        student1 = Student(1, "Mihai", 1)
        student2 = Student(2, "Andrei", 3)
        repo_student = StudentRepository()
        repo_student.add_student(student1)
        repo_student.add_student(student2)
        repo_student.sterge_student(student2.get_id_student())
        assert len(repo_student.get_all())==1
        assert student2 not in repo_student.get_all()
    def __test_modifica_student(self):
        id_student= 1
        nume="Andrei"
        grup=1
        student=Student(id_student, nume, grup)
        bad_id=2
        bad_student=Student(bad_id, nume, grup)
        new_nume="Mihai"
        new_grup=2
        new_student=Student(id_student, new_nume, new_grup)
        student_repo=StudentRepository()
        student_repo.add_student(student)
        assert len(student_repo.get_all())==1
        try:
            student_repo.modifica_student(bad_student)
            assert False
        except Exception as ex:
            assert (str(ex)=="id invalid")
        student_repo.modifica_student(new_student)
        student_list=student_repo.get_all()
        assert student_list[0]==new_student

    def __test_modifica_student2(self):
        student1=Student(1, "Mihai", 1)
        repo=StudentRepository()
        repo.add_student(student1)
        student2=Student(1, "Andrei", 2)
        repo.modifica_student(student2)
        assert student1==student2

    def __teste_cautare_student_dupa_id(self):
        student_repo=StudentRepository()
        id_student = 1
        nume = "Mihai"
        grup = 1
        student = Student(id_student, nume, grup)
        student_repo.add_student(student)
        student_cautat=student_repo.cauta_student_dupa_id(student.get_id_student())
        assert student.get_id_student()==student_cautat.get_id_student()

        id_student_gresit = 2
        nume_gresit = "Mihai"
        grup_gresit = 1
        student_gresit = Student(id_student_gresit, nume_gresit, grup_gresit)
        student_repo.add_student(student_gresit)
        assert student_gresit.get_id_student() != student_cautat.get_id_student()

    def __teste_genereaza_student(self):
        repo=StudentRepository()
        valid=ValidatorStudent()
        student_srv=StudentService(repo,valid)
        random.seed(3)
        student_1=Student(student_srv.genereaza_id_student_random(),student_srv.genereaza_nume_student_random(),
                          student_srv.genereaza_grup_student_random())
        random.seed(3)
        student_2 = Student(student_srv.genereaza_id_student_random(),student_srv.genereaza_nume_student_random(),
                          student_srv.genereaza_grup_student_random())
        assert student_1.get_id_student()==student_2.get_id_student()
        assert student_1.get_nume()==student_2.get_nume()
        assert student_1.get_grup()==student_2.get_grup()

        random.seed(2)
        student_3=Student(student_srv.genereaza_id_student_random(),student_srv.genereaza_nume_student_random(),
                          student_srv.genereaza_grup_student_random())
        assert student_1.get_id_student()!= student_3.get_id_student()
        assert student_1.get_nume() != student_3.get_nume()
        assert student_1.get_grup() != student_3.get_grup()
    def run_all_tests(self):
        self.__creeaza_student()
        self.__valideaza_student()
        self.__teste_repo_add_student()
        self.__test_sterge_student()
        self.__test_modifica_student2()
        self.__teste_cautare_student_dupa_id()
        self.__teste_genereaza_student()
class TesteLaborator:
    def __creeaza_laborator(self):
        numar_problema = 1
        descriere = "Teste"
        deadline = "10.10.2023"
        laborator = Laborator(numar_problema, descriere, deadline)
        numar_problema_gresit = 2
        descriere_gresita = "Afisari"
        deadline_gresit = "12.12.2023"
        laborator_gresit = Laborator(numar_problema_gresit, descriere_gresita, deadline_gresit)
        assert laborator.get_numar_problema()==numar_problema
        assert laborator.get_descriere()==descriere
        assert laborator.get_deadline()==deadline
        assert laborator!=laborator_gresit
    def __valideaza_laborator(self):
        numar_problema = 1
        descriere = "Teste"
        deadline = "10.10.2023"
        laborator = Laborator(numar_problema, descriere, deadline)
        validator = ValidatorLaborator()
        validator.valideaza_laborator(laborator)
        numar_problema_gresit = -1
        descriere_gresita = ""
        deadline_gresit = ""
        laborator_gresit = Laborator(numar_problema_gresit, descriere_gresita, deadline_gresit)
        try:
            validator.valideaza_laborator(laborator_gresit)
            assert False
        except Exception as ex:
            assert (str(ex)=="numar problema invalida\ndescriere invalida\ndata deadline invalida\n")

    def __teste_repo_add_laborator(self):
        lab1=Laborator(1,"Teste","10.10.2023")
        lab2=Laborator(2,"Andrei","12.12.2024")
        repo_lab=LaboratorRepository()
        repo_lab.add_laborator(lab1)
        repo_lab.add_laborator(lab2)
        assert len(repo_lab.get_all())==2

    def __test_sterge_laborator(self):
        lab1 = Laborator(1, "Teste", "10.10.2023")
        lab2 = Laborator(2, "Andrei", "12.12.2024")
        repo_lab = LaboratorRepository()
        repo_lab.add_laborator(lab1)
        repo_lab.add_laborator(lab2)
        repo_lab.sterge_laborator(lab1.get_numar_problema())
        assert len(repo_lab.get_all())==1
        assert lab1 not in repo_lab.get_all()

    def __test_modifica_laborator(self):
        lab1=Laborator(1, "Teste", "a")
        repo=LaboratorRepository()
        repo.add_laborator(lab1)
        lab2=Laborator(1, "Validari", "b")
        repo.modifica_laborator(lab2)
        assert lab1==lab2

    def __teste_cautare_laborator_dupa_numar_problema(self):
        lab_repo=LaboratorRepository()
        numar_prob = 1
        descriere = "Teste"
        deadline = "12.12.2023"
        laborator = Laborator(numar_prob, descriere, deadline)
        lab_repo.add_laborator(laborator)
        lab_cautat=lab_repo.cauta_laborator_dupa_numar_problema(laborator.get_numar_problema())
        assert laborator.get_numar_problema()==lab_cautat.get_numar_problema()
    def run_all_tests(self):
        self.__creeaza_laborator()
        self.__valideaza_laborator()
        self.__teste_repo_add_laborator()
        self.__test_sterge_laborator()
        self.__test_modifica_laborator()
        self.__teste_cautare_laborator_dupa_numar_problema()


class TesteNota:
    def __test_asignare_nota(self):
        student=Student(1,"Mihai",1)
        lab=Laborator(1,"Teste","10.10.2023")
        repo_student=StudentRepository()
        repo_student.add_student(student)
        lab_repo=LaboratorRepository()
        lab_repo.add_laborator(lab)
        repo_nota=NotaRepository()
        nota=NotaDTO(1,student.get_id_student(),lab.get_numar_problema(),10)
        repo_nota.add_nota(nota)
        assert len(repo_nota.get_all())==1
    def __test_validare_nota(self):
        student = Student(1, "Mihai", 1)
        lab = Laborator(1, "Teste", "10.10.2023")
        repo_student = StudentRepository()
        repo_student.add_student(student)
        lab_repo = LaboratorRepository()
        lab_repo.add_laborator(lab)
        nota=NotaDTO(1,student.get_id_student(),lab.get_numar_problema(),10)
        validator_nota=ValidatorNota()
        validator_nota.validare_nota(nota)
        nota_gresit=NotaDTO(1,student.get_id_student(),lab.get_numar_problema(),100)
        try:
            validator_nota.validare_nota(nota_gresit)
            assert False
        except Exception as ex:
            assert(str(ex)=="nota invalida\n")

    def __test_adauga_nota_repo(self):
        student = Student(1, "Mihai", 1)
        lab = Laborator(1, "Teste", "10.10.2023")
        repo_student = StudentRepository()
        repo_student.add_student(student)
        lab_repo = LaboratorRepository()
        lab_repo.add_laborator(lab)
        nota = NotaDTO(1, student.get_id_student(), lab.get_numar_problema(), 10)
        validator_nota = ValidatorNota()
        validator_nota.validare_nota(nota)
        nota_repo=NotaRepository()
        nota_repo.add_nota(nota)
        assert len(nota_repo.get_all())==1

    def run_all_tests(self):
        self.__test_asignare_nota()
        self.__test_validare_nota()
        self.__test_adauga_nota_repo()
class Teste:
    def run_all_tests(self):
        teste_student=TesteStudent()
        teste_laborator=TesteLaborator()
        teste_nota=TesteNota()
        teste_laborator.run_all_tests()
        teste_student.run_all_tests()
        teste_nota.run_all_tests()