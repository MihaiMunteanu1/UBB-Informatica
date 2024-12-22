from domeniu.laborator import Laborator
class LaboratorService:
    def __init__(self, repo_laboratoare, validator_laborator):
        self.__repo_laboratoare = repo_laboratoare
        self.__validator_laborator = validator_laborator

    def add_laborator(self, numar_problema, descriere, deadline):
        laborator = Laborator(numar_problema, descriere, deadline)
        self.__validator_laborator.validate_laborator(laborator)
        self.__repo_laboratoare.add_laborator(laborator)

    def sterge_laborator(self,numar_problema):
        self.__repo_laboratoare.sterge_laborator(numar_problema)

    def modifica_laborator(self,numar_problema,new_descriere,new_deadline):
        laborator = Laborator(numar_problema, new_descriere, new_deadline)
        self.__validator_laborator.validate_laborator(laborator)
        self.__repo_laboratoare.modifica_laborator(laborator)

    def cauta_laborator_dupa_numar_problema(self,numar_problema):
        if numar_problema<0:
            raise Exception("id invalid")
        return self.__repo_laboratoare.cauta_laborator_dupa_numar_problema(numar_problema)

    def get_all_laboratoare(self):
        return self.__repo_laboratoare.get_all()