from domain.produs import Produs
class ServiceProdus:
    def __init__(self,repo_produs,valid_produs):
        self.__repo_produs=repo_produs
        self.__valid_produs=valid_produs

    def add_produs(self,id,denumire,pret):
        produs=Produs(id,denumire,pret)
        self.__valid_produs.valideaza_produs(produs)
        self.__repo_produs.add_produs(produs)

    def filtrare(self,text,numar):
        return self.__repo_produs.filtrare(text,numar)
    def filtrare2(self,numar):
        return self.__repo_produs.filtrare2(numar)

    def undo(self):
        self.__repo_produs.undo()

    def sterge_produse(self,cifra):
        if cifra<0:
            print("valoare negativa")
            return
        self.__repo_produs.sterge_produse(cifra)

    def get_all(self):
        return self.__repo_produs.get_all()