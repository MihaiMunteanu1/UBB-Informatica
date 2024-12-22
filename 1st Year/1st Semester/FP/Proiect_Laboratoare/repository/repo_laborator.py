class LaboratorRepository:
    def __init__(self):
        self.__labs = {}

    def add_laborator(self, laborator):
        numar_problema = laborator.get_numar_problema()
        if numar_problema in self.__labs:
            raise Exception("numar problema existent")
        self.__labs[numar_problema] = laborator

    def sterge_laborator(self,numar_problema):
        if numar_problema in self.__labs:
            del self.__labs[numar_problema]
        else:
            raise Exception("laborator inexistent")

    def modifica_laborator(self,laborator):
        numar_problema=laborator.get_numar_problema()
        if numar_problema in self.__labs:
            self.__labs[numar_problema]=laborator
        else:
            raise Exception("numar problema invalid")

    def cauta_laborator_dupa_numar_problema(self,numar_problema):
        if numar_problema<0:
            raise Exception("numar problema invalid")
        if numar_problema in self.__labs:
            return self.__labs[numar_problema]
        raise Exception("Nu exista laborator cu acest numar de problema")

    def get_all(self):
        return [self.__labs[x] for x in self.__labs.keys()]

