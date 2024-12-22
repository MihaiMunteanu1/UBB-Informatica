class ServiceMateriale:
    def __init__(self,repo_materiale):
        self.__repo_materiale=repo_materiale

    def add_material(self):
        """
        Functie care apeleaza adaugarea materialelor din repository
        """
        return self.__repo_materiale.add_material()
    def valoare_mai_mare(self,valoare):
        """
        Functie care apeleaza efectuarea functionalitatii 1 din ripository

        """
        self.__repo_materiale.valoare_mai_mare(valoare)
    def efectueaza_vanzarea(self,cod,cantitate_ceruta):
        """
                Functie care apeleaza efectuarea functionalitatii 2 din ripository

                """
        self.__repo_materiale.efectueaza_vanzarea(cod,cantitate_ceruta)
    def get_all(self):
        return self.__repo_materiale.get_all()