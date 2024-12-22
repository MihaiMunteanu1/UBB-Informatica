from domain.vanzare import Vanzare
class ServiceVanzare:
    def __init__(self,repo_vanzare):
        self.__repo_vanzare=repo_vanzare

    def add_vanzare(self,id_vanzare,cod,cantitate_ceruta):
        """
        Functie care creeaza o vanzare noua
        """
        vanzare=Vanzare(id_vanzare,cod,cantitate_ceruta)
        self.__repo_vanzare.valideaza_id_vanzare(id_vanzare)
        self.__repo_vanzare.add_vanzare(vanzare)

    def valideaza_id_vanzare(self,id_vanzare):
        self.__repo_vanzare.valideaza_id_vanzare(id_vanzare)