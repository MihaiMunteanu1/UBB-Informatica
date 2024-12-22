from repository.repo_student import RepositoryStudent
from domeniu.student import Student
from repository.repo_student import RepositoryStudentFisiere
class TesteFisiere:
    def __goleste_fisier(self, students_file_path):
        with open(students_file_path, 'w') as f:
            f.write('')
    def __test_adaugare_student_repo(self):
        student_repo=RepositoryStudent()
        cale_fisier="C:\\Users\\munte\\PycharmProjects\\doar_o_clasa\\teste_fisiere\\test_student.txt"
        self.__goleste_fisier(cale_fisier)
        with open(cale_fisier, "w") as f:
            f.write("1,Mihai,1\n")
        with open(cale_fisier, "r") as f:
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

    def __test_stergere_student_din_fisier(self):
        # Creează un student în fișier
        cale_fisier = "C:\\Users\\munte\\PycharmProjects\\doar_o_clasa\\teste_fisiere\\test_student.txt"
        self.__goleste_fisier(cale_fisier)
        with open(cale_fisier, "w") as f:
            f.write("1,Mihai,1\n")

        # Verifică că studentul există în fișier înainte de ștergere
        with open(cale_fisier, "r") as f:
            lines_before = f.readlines()
        assert len(lines_before) == 1

        # Citește studentul din fișier și verifică că a fost citit corect
        student_repo = RepositoryStudentFisiere(cale_fisier)
        student_din_fisier = student_repo.cauta_student_dupa_id(1)
        assert student_din_fisier.get_nume() == "Mihai"
        assert student_din_fisier.get_grup() == 1

        # Șterge studentul și verifică că s-a șters din fișier
        student_repo.sterge_student(1)

        # Verifică că fișierul este acum gol (nu conține niciun rând)
        with open(cale_fisier, "r") as f:
            lines_after = f.readlines()
        assert len(lines_after) == 0

    def __test_modificare_student_in_fisier(self):
        # Creează un student în fișier
        cale_fisier = "C:\\Users\\munte\\PycharmProjects\\doar_o_clasa\\teste_fisiere\\test_student.txt"
        self.__goleste_fisier(cale_fisier)
        with open(cale_fisier, "w") as f:
            f.write("1,Mihai,1\n")

        # Citește studentul din fișier și verifică că a fost citit corect
        student_repo = RepositoryStudentFisiere(cale_fisier)
        student_din_fisier = student_repo.cauta_student_dupa_id(1)
        assert student_din_fisier.get_nume() == "Mihai"
        assert student_din_fisier.get_grup() == 1

        # Modifică studentul în memorie
        student_din_fisier.set_nume("Andrei")
        student_din_fisier.set_grup(4)

        # Modifică studentul în fișier și verifică că modificările au fost făcute corect
        student_repo.modifica_student_in_fisier(student_din_fisier)

        # Citește din nou studentul din fișier și verifică că a fost modificat corect
        student_din_fisier_modificat = student_repo.cauta_student_dupa_id(1)
        assert student_din_fisier_modificat.get_nume() == "Andrei"
        assert student_din_fisier_modificat.get_grup() == 4
        assert student_din_fisier==student_din_fisier_modificat
    def run_all_tests(self):
        self.__test_adaugare_student_repo()
        self.__test_stergere_student_din_fisier()
        self.__test_modificare_student_in_fisier()