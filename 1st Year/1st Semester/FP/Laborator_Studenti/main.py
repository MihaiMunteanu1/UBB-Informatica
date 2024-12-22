from teste.teste import Teste
teste=Teste()
teste.run_all_teste()
from teste_fisiere.teste_fisiere import TesteFisiere
teste_fisiere=TesteFisiere()
teste_fisiere.run_all_tests()

from repository.repo_student import RepositoryStudent
from validare.validator_student import ValidatorStudent

repo_student=RepositoryStudent()
valid_student=ValidatorStudent()

from repository.repo_student import RepositoryStudentFisiere
cale_fisier="C:\\Users\\munte\\PycharmProjects\\doar_o_clasa\\student.txt"
repo_student_fisiere=RepositoryStudentFisiere(cale_fisier)

from service.service_student import ServiceStudent
srv_student=ServiceStudent(repo_student,valid_student)

srv_student_fisiere=ServiceStudent(repo_student_fisiere,valid_student)

from console.ui import UI
ui=UI(srv_student)
ui_fisier=UI(srv_student_fisiere)

#ui.run()
ui_fisier.run()