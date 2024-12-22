from teste.teste import Teste
teste=Teste()
teste.run_all_tests()

from repository.repo_laborator import LaboratorRepository
from repository.repo_student import StudentRepository
from repository.repo_nota import NotaRepository
from service.service_laborator import LaboratorService
from service.service_student import StudentService
from service.service_nota import NotaService
from validare.validator_laborator import ValidatorLaborator
from validare.validator_student import ValidatorStudent
from validare.validator_nota import ValidatorNota

repo_student=StudentRepository()
repo_laborator=LaboratorRepository()
repo_nota=NotaRepository()
valid_student=ValidatorStudent()
valid_lab=ValidatorLaborator()
valid_nota=ValidatorNota()
service_student=StudentService(repo_student,valid_student)
service_laborator=LaboratorService(repo_laborator,valid_lab)
service_nota=NotaService(repo_nota,repo_student,repo_laborator,valid_nota)

from console.ui import UI
ui=UI(service_student,service_laborator,service_nota)
ui.run()