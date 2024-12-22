from domeniu.laborator import Laborator
class LaboratorService:
    def __init__(self,repo_labs,validator_laborator):
        self.__repo_labs=repo_labs
        self.__validator_laborator=validator_laborator
    def add_laborator(self,numar_problema,descriere,deadline):
        laborator=Laborator(numar_problema,descriere,deadline)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_labs.add_laborator(laborator)

    def sterge_laborator(self,numar_problema):
        self.__repo_labs.sterge_laborator(numar_problema)
    def modifica_laborator(self,numar_problema,descriere,deadline):
        laborator=Laborator(numar_problema,descriere,deadline)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_labs.modifica_laborator(laborator)

    def cauta_laborator_dupa_numar_problema(self,numar_problema):
        return self.__repo_labs.cauta_laborator_dupa_numar_problema(numar_problema)

    def get_all(self):
        return self.__repo_labs.get_all()