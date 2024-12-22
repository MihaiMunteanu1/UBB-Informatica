from teste.teste import Teste
teste=Teste()
teste.run_all_tests()
from repository.repo_agentie import RepositoryAgentieFisiere
cale_fisier="C:\\Users\\PycharmProjects\\agentie_imobiliara\\agentie.txt"
repo_fisier=RepositoryAgentieFisiere(cale_fisier)
from validare.validator_agentie import ValidatorAgentie
valid_agentie=ValidatorAgentie()
from service.service_agentie import ServiceAgentie
serv_agentie=ServiceAgentie(repo_fisier,valid_agentie)
from console.ui import UI
ui=UI(serv_agentie)
ui.run()
