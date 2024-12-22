from teste.teste import Teste
cale_fisier_teste="teste.txt"
teste=Teste(cale_fisier_teste)
teste.run_all_tests()

from repo.repo_piese import FileRepoPiese
cale_fisier="piese.txt"
file_repo=FileRepoPiese(cale_fisier)

from valid.validator_piesa import ValidatorPiesa
valid_piesa=ValidatorPiesa()

from service.service_piese import ServicePiese
srv_piesa=ServicePiese(file_repo,valid_piesa)
file_repo.get_all()
from console.ui import UI
ui=UI(srv_piesa)
ui.run()
