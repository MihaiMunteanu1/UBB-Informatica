from repository.repo_materiale import RepositoryMaterialeFisiere
from repository.repo_vanzare import RepositoryVanzarea

class Teste:
    def __init__(self,cale,cale1,cale2):
        self.__cale=cale
        self.__cale1=cale1
        self.__cale2=cale2

    def __test_adauga_materiale_repo(self):
        """
        Functie de test care testeaza adaugarea materialelor in repository
        :return:
        """
        repo_materiale = RepositoryMaterialeFisiere(self.__cale,self.__cale1,self.__cale2)
        repo_materiale.add_material()
        assert len(repo_materiale.get_all())==5

    def __test_functionalitate_1(self):
        """
        Functie de test care testeaza functionalitatea 1
        :return:
        """
        repo_material = RepositoryMaterialeFisiere(self.__cale,self.__cale1,self.__cale2)
        repo_material.add_material()
        valoare=int(10)
        epsilon=0.00001
        repo_material.valoare_mai_mare(valoare)
        with open(self.__cale1,"r") as f:
            count=len(f.readlines())
        assert abs(count-5)<epsilon

    def __test_efectueaza_vanzare(self):
        """
        Functie care testeaza creeare unei vanzari
        :return:
        """
        id_vanzare=1
        repo_vanzare=RepositoryVanzarea()
        repo_vanzare.valideaza_id_vanzare(id_vanzare)
        repo_materiale = RepositoryMaterialeFisiere(self.__cale,self.__cale1,self.__cale2)
        repo_materiale.add_material()
        repo_materiale.efectueaza_vanzarea(1,10)
        epsilon = 0.00001
        with open(self.__cale2,"r") as f:
            count=len(f.readlines())
        assert abs(count-1)<epsilon

    def run_all_tests(self):
        self.__test_adauga_materiale_repo()
        self.__test_functionalitate_1()
        self.__test_efectueaza_vanzare()