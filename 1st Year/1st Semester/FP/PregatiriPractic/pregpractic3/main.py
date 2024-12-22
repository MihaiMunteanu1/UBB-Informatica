from teste.teste import Teste
teste=Teste('teste.txt')
teste.run_all_tests()

from repository.repo_produse import FileRepoProduse
cale_fisier='produse.txt'
file_repo=FileRepoProduse(cale_fisier)

from validator.validator_produs import ValidatorProdus
valid_produs=ValidatorProdus()

from service.service_produs import ServiceProdus
srv_produs=ServiceProdus(file_repo,valid_produs)
file_repo.get_all()
from console.ui import UI
ui=UI(srv_produs)
ui.run()
