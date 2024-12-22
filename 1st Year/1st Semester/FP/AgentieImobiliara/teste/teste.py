from domeniu.agentie import Agentie
from repository.repo_agentie import RepositoryAgentie
from repository.repo_agentie import RepositoryAgentieFisiere
from service.service_agentie import ServiceAgentie
from validare.validator_agentie import ValidatorAgentie
class Teste:
    def __test_adauga_in_repo(self):
        cale_fisier="C:\\Users\\munte\\PycharmProjects\\agentie_imobiliara\\teste\\teste_agentie.txt"
        repo_agentie = RepositoryAgentie()
        with open(cale_fisier,"r") as f:
            lines=f.readlines()
            for line in lines:
                if line!="":
                    line.strip()
                    parti=line.split(',')
                    id=int(parti[0])
                    adresa=parti[1]
                    oras=parti[2]
                    pret=float(parti[3])
                    garantie=float(parti[4])
                    agentie=Agentie(id,adresa,oras,pret,garantie)
                    repo_agentie.add_agentie(agentie)
        assert len(repo_agentie.get_all())==10

    def __test_filtrare_locuinte(self):
        cale_fisier = "C:\\Users\\munte\\PycharmProjects\\agentie_imobiliara\\teste\\teste_agentie.txt"
        repo_agentie = RepositoryAgentie()
        with open(cale_fisier, "r") as f:
            lines = f.readlines()
            for line in lines:
                if line != "":
                    line.strip()
                    parti = line.split(',')
                    id = int(parti[0])
                    adresa = parti[1]
                    oras = parti[2]
                    pret = float(parti[3])
                    garantie = float(parti[4])
                    agentie = Agentie(id, adresa, oras, pret, garantie)
                    repo_agentie.add_agentie(agentie)
        valid_agentie=ValidatorAgentie()
        srv_agentie=ServiceAgentie(repo_agentie,valid_agentie)
        locuinte_filtrate=srv_agentie.filtrare_locuinte("Cluj",600)
        assert len(locuinte_filtrate)==2

    def __test_inchiriere_locuinta(self):
        cale_fisier = "C:\\Users\\munte\\PycharmProjects\\agentie_imobiliara\\teste\\teste_agentie.txt"
        repo = RepositoryAgentieFisiere(cale_fisier)
        repo.add_agentie()

        locuinta_inchiriata = repo.inchiriere_locuinta(8)

        assert len(repo.get_all()) == 9

        assert locuinta_inchiriata["id"] == 8
        assert locuinta_inchiriata["adresa"] == "str plm 1"
        assert locuinta_inchiriata["oras"] == "Bucuresti"
        assert locuinta_inchiriata["pret"] == 900
        assert locuinta_inchiriata["garantie"] == 400
        assert locuinta_inchiriata["suma initiala necesara"] == 1750
    def run_all_tests(self):
        self.__test_adauga_in_repo()
        self.__test_filtrare_locuinte()
        self.__test_inchiriere_locuinta()