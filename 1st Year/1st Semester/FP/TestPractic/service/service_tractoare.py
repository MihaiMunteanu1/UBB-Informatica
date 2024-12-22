from domain.tractor import Tractor
class ServiceTractoare:
    def __init__(self,repo_tractoare,validator_tractoare):
        self.__repo_tractoare=repo_tractoare
        self.__validator_tractoare=validator_tractoare

    def filtrare_tractoare(self,text,numar):
        """
        Functia care returneaza tractoarele filtrate in repository
        :param text:
        :param numar:
        :return:
        """
        return self.__repo_tractoare.filtreaza_tractoare(text,numar)

    def undo(self):
        """
        Functie care apeleaza functia de undo din repository
        :return:
        """
        self.__repo_tractoare.undo()

    def sterge_tractor(self,cifra):
        """
        Functie care verifica daca cifra este negativa si apelaza functia de stergere din repository
        care sterge tractoarele al caror id continea acea cifra
        :param cifra:
        :return:
        """
        if cifra<0:
            raise Exception("cifra negativa")
            return
        self.__repo_tractoare.sterge_tractor(cifra)

    def add_tractor(self,id,denumire,pret,model,data):
        """
        Functie ca creeaza tractorul, il valideaza si il trimite sa fie adaugat in repository

        """
        tractor=Tractor(id,denumire,pret,model,data)
        self.__validator_tractoare.valideaza_tractor(tractor)
        self.__repo_tractoare.add_tractor(tractor)

    def get_all(self):
        """
        Functie care returneaza toate tractoarele din repository
        :return:
        """
        return self.__repo_tractoare.get_all()