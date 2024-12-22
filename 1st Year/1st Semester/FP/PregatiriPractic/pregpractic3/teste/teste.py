from domain.produs import Produs
from repository.repo_produse import FileRepoProduse
from service.service_produs import ServiceProdus
from validator.validator_produs import ValidatorProdus
class Teste:
    def __init__(self,cale_fisier):
        self.__cale_fisier=cale_fisier

    def __goleste_fisier(self):
        with open(self.__cale_fisier,'w') as f:
            f.write('')

    def __test_adauga_din_fisier_in_repo(self):
        self.__goleste_fisier()
        with open(self.__cale_fisier,'w') as f:
            f.write('1,cola,5')
        repo=FileRepoProduse(self.__cale_fisier)
        assert len(repo.get_all())==1

    def run_all_tests(self):
        self.__test_adauga_din_fisier_in_repo()