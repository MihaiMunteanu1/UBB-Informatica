class ServiceAgentie:
    def __init__(self,repo,valid):
        self.__repo=repo
        self.__valid=valid

    def add_agentie(self):
        self.__repo.add_agentie()
    def filtrare_locuinte(self,oras,buget):
        rezultat=[]
        for agentie in self.__repo.get_all():
            if agentie.get_oras()==oras:
                if agentie.get_pret()<=buget:
                    rezultat.append(agentie)
        return rezultat

    def inchiriere_locuinta(self,id):
        return self.__repo.inchiriere_locuinta(id)


    def get_all(self):
        return self.__repo.get_all()