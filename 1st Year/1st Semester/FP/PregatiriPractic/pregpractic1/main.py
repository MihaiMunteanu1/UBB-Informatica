from teste.teste import Teste
cale_fisier_teste="C:\\Users\\munte\\PycharmProjects\\preg_practic1\\teste\\testeE.txt"
teste=Teste(cale_fisier_teste)
teste.run_al_tests()

from repository.repo_emisiuni import RepositoryEmisiuniFiles
cale_fisier="C:\\Users\\munte\\PycharmProjects\\preg_practic1\\emisiuni.txt"
repo_fisier=RepositoryEmisiuniFiles(cale_fisier)
repo_fisier.get_all()
from validators.validator_emisiune import ValidatorEmisiune
valid_emisiune=ValidatorEmisiune()

from service.service_emisiuni import ServiceEmisiuni
srv_emisiune=ServiceEmisiuni(repo_fisier,valid_emisiune)

from console.ui import UI
ui=UI(srv_emisiune)
ui.run()
